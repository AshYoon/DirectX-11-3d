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
	RenderBegin(); // ��ȭ�� �ʱ�ȭ 

	//TODO



	RenderEnd(); // �׸� ���� 
}

void Game::RenderBegin()
{
	// �غ��۾��� �ϰ� 
	//������ ���������ο��� �츮������ ���ҽ��� ��������Ѵ� 
	//_deviceContext�� ���������Ѵ�
	// OM�� �������ܰ� ,������� �� ��ȭ���� �ǳ���
	_deviceContext->OMSetRenderTargets(1,_renderTartgetView.GetAddressOf(),nullptr); // �ĸ���ۿ� ��û
	_deviceContext->ClearRenderTargetView(_renderTartgetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewport);



}

void Game::RenderEnd()
{
	//�������� ȣ�� 
	// [�������� ����  ] <- [�ĸ���ۿ��� �ٱ׸��� ]
	HRESULT hr = _swapChain->Present(1, 0); // ���������� ���� 
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	//�����쿡�� �����ϴ��Լ����� 
	// ����̽� ����� swap chain ����� �ܰ谡 �þ�� �����ؾ��ҰԸ����� 
	//driver_type_hardware �츮���������ִ� �׷���ī�� ���
	////feature level->dx������ �ش��ϴ� ����� �� ����
	//d3d11���� ��ũ��
	//swap chain description �䱸�� , 
	DXGI_SWAP_CHAIN_DESC desc;
	//::memset(&desc, 0, sizeof(desc)); // �����ִ°��� �� 0�����ʱ�ȭ
	// memset�̶�������� 
	ZeroMemory(&desc, sizeof(desc)); 
	{
		// ���� ũ�� ȭ��ũ��� ���������
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1; // ��Ƽ���ø������õ� ����
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ����������� �׷��ִ� ���ҷ� ����
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

	// �ְ� ture�� ���� �����ϸ� crash ���� ���� 
	CHECK(hr);
}

//����ü�ο� �ĸ���۸� �����޶���ؼ� ������۸��� ok
//�� �ĸ���۶�°��� �˷�����Ѵ� , ���⿡ �׸��� �׷��޶� �װ� �� �Լ�
void Game::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	//swapchain�� �ĸ� ���۸� ������ʹ޶�� ȣ���� ������� 
	//swapChain�� �������� �Ϲ� �����Ͷ� �Ȱ��� ��밡�� , �ƹ��� ����Ʈ�����Ͷ� �� �����ε��Ǿ����� 
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	//getbuffer�ؼ� backbuffer�� ȣ���ϸ�  id3d11texture2d �긦 backbuffer�� �־��ش� 
	CHECK(hr);
	//swap chain���� �ĸ� ���ۿ� �ش��ϴ� ���ҽ��� id3d11 texture2d ��� �̰ɷ� �������ְ� 
	
	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTartgetView.GetAddressOf());
	CHECK(hr);
	//�츮�� �ٽ� �̰� device�� createRenderTargetView��� �� ���� ������ �� ���̸� �����ϴ�
	//RenderTargetView�� ����� ���
	//���� �츮�� gpu�� ����ؼ� �� _renderTargetView�� �������ָ� gpu���� �׷��ش�
	//gpu�� ��û�Ҷ� ����ϴ� ������� ������ ���� 

}

void Game::SetViewport()
{
	//���� 
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;


}
