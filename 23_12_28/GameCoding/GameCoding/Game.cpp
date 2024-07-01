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

	// hwnd를 넘겨주면 graphics에서 알아서 만들어줌 


	_graphics = make_shared<Graphics>(hwnd); // 메모리 공간뿐만아니라 ref카운트관리까지하니깐 makeshared로 
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice()); // cycle 생각하면서 사용해야된다 
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexShader = make_shared<VertexShader>(_graphics->GetDevice());
	_pixelShader = make_shared<PixelShader>(_graphics->GetDevice());
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());



	CreateGeometry();// -> 삼각형의 도형 만들기 

	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");	//-> 각각의 쉐이더를 로드 


	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());// 이 vs단계에서 건내줘야하는 구조체의 생김새 정의를 만들어줬다.


	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateSRV(); // ShaderResourceView 호출 
	_constantBuffer->Create();
}

void Game::Update()
{
	// Scale Rotation Translation

	//_localPosition.x += 0.0001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3); // srt 중 s 먼저 ,scale vecotr에 따라 변화하는 행렬 생성
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z 도 똑같이 x에 곱해줘서 변화하게 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT , 이미 * 연산자 오버로딩 되어있음 

	_transformData.matWorld = matWorld; //이제 이걸 쉐이더에 넘겨줘야한다 


	_constantBuffer->CopyData(_transformData);

}

void Game::Render()
{
	_graphics->RenderBegin();// 도화지 초기화 
	

	//IA - VS - RS - PS - OM
	//input aseembler , vertext shader , tesellator , resterizer , pixel shader , output merger





	{

		uint32 stride = sizeof(VertexTextureData);
		uint32 offset = 0;

		auto _deviceContext = _graphics->GetDeviceContext();


		

		//IA
		//dc에 가서 vertexbuffer를 연결시켜줘야한다 
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComptr().GetAddressOf(), &stride, &offset);
		//							버퍼슬롯1개 , 버퍼갯수 , 버퍼건내기 , vertex크기 , 
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		//                               내 인덱스 버퍼 ,     4바이트로했으니깐 32비트짜리다라는뜻 

		//input layout 으로 우리가 건네준거 묘사 
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());

		//정점을 어떻게 이어붙일지 알려줘야함 
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		/// IA 단계에서는 이렇게 세팅만 



		//VS

		_deviceContext->VSSetShader(_vertexShader->GetComPtr().Get(), nullptr, 0); // 우리가만든거 써라 
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer->GetComPtr().GetAddressOf());


		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());



		//PS
		_deviceContext->PSSetShader(_pixelShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		//OM

		//_graphics->GetDeviceContext()->Draw(_vertices.size(), 0); // 그려달라고 요청 
		_deviceContext->DrawIndexed(_geometry->GetIndexCount(), 0, 0); // index 기반 draw 
								   // index 갯수 



	}

	//TODO



	_graphics->RenderEnd(); // 그림 제출 
}






void Game::CreateGeometry()
{
	//이것도 다른곳에 옮겨서 작업할것 . 



	//vertex data
	{

		GeometryHelper::CreateRectangle(_geometry);
	}

	//vertex buffer
	{
		_vertexBuffer->Create(_geometry->GetVertices()); 

	}

	//인덱스 버퍼가 왜 필요할까? 
	// 중복되서 사용되는 정점의 갯수를 줄이기위해서     



	//index Buffer
	{
		_indexBuffer->Create(_geometry->GetIndices());
	}


}


// 얘를 어떻게 분석해서 전해줘야할지를 정해줘야한다 




void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// 3개 다 중요하다 
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;


	HRESULT hr = _graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);

}

void Game::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	//border color는 RGBA 라고보면된다 
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//어떻게 비교하면될지 
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.0f;


	HRESULT hr = _graphics->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	CHECK(hr);

}

void Game::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;



	HRESULT hr = _graphics->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);



}



void Game::CreateSRV()
{
	//이미지를 가져오는 함수는 여러개가있다 
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;

	HRESULT hr = ::LoadFromWICFile(L"Pig.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	//여기까지하면 이미지를 로드한것 

	//shader resource view 라는걸 만들어야한다 
	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());

	CHECK(hr);

	hr = ::LoadFromWICFile(L"Sample.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	//여기까지하면 이미지를 로드한것 

	//shader resource view 라는걸 만들어야한다 
	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView2.GetAddressOf());

	CHECK(hr);



}

