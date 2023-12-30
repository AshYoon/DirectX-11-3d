#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;
	
	
	
	// TODO
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void Game::Update()
{
}

void Game::Render()
{
	RenderBegin(); // 도화지 초기화 

	//TODO



	RenderEnd(); // 그림 제출 
}

void Game::RenderBegin()
{
	// 준비작업을 하고 
	//렌더링 파이프라인에서 우리가만든 리소스를 묶어줘야한다 
	//_deviceContext를 사용해줘야한다
	// OM이 마지막단계 ,결과물을 이 도화지를 건내줘
	_deviceContext->OMSetRenderTargets(1,_renderTartgetView.GetAddressOf(),nullptr); // 후면버퍼에 요청
	_deviceContext->ClearRenderTargetView(_renderTartgetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewport);



}

void Game::RenderEnd()
{
	//마지막에 호출 
	// [전면으로 복사  ] <- [후면버퍼에서 다그리면 ]
	HRESULT hr = _swapChain->Present(1, 0); // 내부적으로 제출 
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	//윈도우에서 제공하는함수쓰기 
	// 디바이스 만들고 swap chain 만들면 단계가 늘어나서 설정해야할게많아짐 
	//driver_type_hardware 우리가가지고있는 그래픽카드 사용
	////feature level->dx버전에 해당하는 기능을 다 지원
	//d3d11버전 매크로
	//swap chain description 요구함 , 
	DXGI_SWAP_CHAIN_DESC desc;
	//::memset(&desc, 0, sizeof(desc)); // 여기있는값을 다 0으로초기화
	// memset이랑같은기능 
	ZeroMemory(&desc, sizeof(desc)); 
	{
		// 버퍼 크기 화면크기랑 맞춰줘야함
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1; // 멀티샘플링과관련된 문제
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 최종결과물을 그려주는 역할로 정함
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}
	
	
	//ID3D11Device*
	//_device.Get();


	//ID3D11Device**
	//_device.GetAddressOf();

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,                     // pAdapter
		D3D_DRIVER_TYPE_HARDWARE,    // DriverType
		nullptr,                     // Software
		0,                           // Flags
		nullptr,                     // pFeatureLevels
		0,                           // FeatureLevels
		D3D11_SDK_VERSION,           // SDKVersion
		&desc,                       // pSwapChainDesc
		_swapChain.GetAddressOf(),   // ppSwapChain
		_device.GetAddressOf(),      // ppDevice
		nullptr,                     // pFeatureLevel
		_deviceContext.GetAddressOf() // ppImmediateContext
	);

	// 애가 ture면 성공 실패하면 crash 나게 유도 
	CHECK(hr);
}

//스왑체인에 후면버퍼를 만들어달라고해서 더블버퍼링은 ok
//이 후면버퍼라는것을 알려줘야한다 , 여기에 그림을 그려달라 그게 이 함수
void Game::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	//swapchain에 후면 버퍼를 가지고와달라는 호출을 해줘야함 
	//swapChain은 이제부터 일반 포인터랑 똑같이 사용가능 , 아무리 스마트포인터라도 다 오버로딩되어있음 
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	//getbuffer해서 backbuffer를 호출하면  id3d11texture2d 얘를 backbuffer에 넣어준다 
	CHECK(hr);
	//swap chain에서 후면 버퍼에 해당하는 리소스를 id3d11 texture2d 라는 이걸로 리턴해주고 
	
	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTartgetView.GetAddressOf());
	CHECK(hr);
	//우리가 다시 이걸 device의 createRenderTargetView라는 걸 통해 가지고 이 아이를 묘사하는
	//RenderTargetView를 만들어 줬고
	//이제 우리가 gpu랑 통신해서 이 _renderTargetView를 가져다주면 gpu에서 그려준다
	//gpu에 요청할때 사용하는 스페셜한 포인터 느낌 

}

void Game::SetViewport()
{
	//간단 
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;


}
