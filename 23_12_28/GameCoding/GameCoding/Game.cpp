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
	_graphics = new Graphics(hwnd);

	//_graphics = make_shared<Graphics>();



	CreateGeometry();// -> 삼각형의 도형 만들기 
	CreateVS(); //-> 각각의 쉐이더를 로드 
	CreateInputLayout(); // 이 vs단계에서 건내줘야하는 구조체의 생김새 정의를 만들어줬다.
	CreatePS();

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateSRV(); // ShaderResourceView 호출 
	CreateConstantBuffer();
}

void Game::Update()
{
	// Scale Rotation Translation
	 
	//_localPosition.x += 0.0001f;

	Matrix matScale =  Matrix::CreateScale(_localScale/3); // srt 중 s 먼저 ,scale vecotr에 따라 변화하는 행렬 생성
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z 도 똑같이 x에 곱해줘서 변화하게 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT , 이미 * 연산자 오버로딩 되어있음 

	_transformData.matWorld = matWorld; //이제 이걸 쉐이더에 넘겨줘야한다 



	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));



	_graphics->GetDeviceContext()->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_graphics->GetDeviceContext()->Unmap(_constantBuffer.Get(), 0);
}

void Game::Render()
{
	_graphics->RenderBegin();// 도화지 초기화 
	

	//IA - VS - RS - PS - OM
	//input aseembler , vertext shader , tesellator , resterizer , pixel shader , output merger





	{

		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;

		auto _deviceContext = _graphics->GetDeviceContext();


		

		//IA
		//dc에 가서 vertexbuffer를 연결시켜줘야한다 
		_deviceContext->IASetVertexBuffers(0, 1, _vertextBuffer.GetAddressOf(), &stride, &offset);
		//							버퍼슬롯1개 , 버퍼갯수 , 버퍼건내기 , vertex크기 , 
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		//                               내 인덱스 버퍼 ,     4바이트로했으니깐 32비트짜리다라는뜻 

		//input layout 으로 우리가 건네준거 묘사 
		_deviceContext->IASetInputLayout(_inputLayout.Get());

		//정점을 어떻게 이어붙일지 알려줘야함 
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		/// IA 단계에서는 이렇게 세팅만 



		//VS

		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0); // 우리가만든거 써라 
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());


		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());



		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		//OM

		//_graphics->GetDeviceContext()->Draw(_vertices.size(), 0); // 그려달라고 요청 
		_deviceContext->DrawIndexed(_indices.size(), 0, 0); // index 기반 draw 
								   // index 갯수 



	}

	//TODO



	_graphics->RenderEnd(); // 그림 제출 
}






void Game::CreateGeometry()
{
	//vertex data
	{
		_vertices.resize(4);

		// 좌표는 - 1 ~ 1 사이 반시계로 
		//어떻게 삼각형을 표현할지 데이터로 만들어주기 아직까진 CPU <->RAM
		//GPU에 똑같이 만들어줘야한다
		// 시계방향으로 만들었으면 시계방향으로 유지 


		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
		_vertices[0].uv = Vec2(0.f, 1.f);
		//_vertices[0].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
		_vertices[1].uv = Vec2(0.f, 0.f);
		//_vertices[1].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
		_vertices[2].uv = Vec2(1.f, 1.f);
		//_vertices[2].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
		_vertices[3].uv = Vec2(1.f, 0.f);
		//_vertices[3].color = Color(1.f, 0.f, 0.f,1.f);
	}

	//vertex buffer
	{
		//새로운 리소스 만들어야하니 device에서 create buffer
		//Input Assembler단계에서 vertex buffer를넣어주고있는거
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // 세팅해준거 고칠일없어서 immutable
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // vertex buffer bind 용도로 사용할꺼다
		desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size()); // Vertex 메모리 size x vertices vector size()
		// 버퍼 묘사 끝 

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_vertices[0]; // vertex 배열의 첫번째의 시작주소 

		// 설정한 값을 기반으로 gpu쪽에 버퍼가 만들어지면서 초기값이 복사가된다 
		//그다음은 gpu만 read only로 작동이된다 , 이게 정점 버퍼 
		HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, &data, _vertextBuffer.GetAddressOf());
		CHECK(hr);

	}

	//index

	{
		_indices = { 0 ,1 ,2 , 2 ,1 ,3 }; //정점에 들어가는 순서 

	}

	//index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // IMMUTABLE까지는 같다 
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(uint32) * _indices.size());


		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_indices[0]; // _indicies.data() 도 가능 


		HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}


}


// 얘를 어떻게 분석해서 전해줘야할지를 정해줘야한다 
void Game::CreateInputLayout()
{
	//배열 형태로 제작 
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT,0 ,0,D3D11_INPUT_PER_VERTEX_DATA,0},//FLOAT가 각각 32BIT (VEC3)
		{"TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT,0 ,12,D3D11_INPUT_PER_VERTEX_DATA,0}, //Vec4 COLOR RGBA + 구조묘사
	};

	// 배열의 크기에 배열하나의 아이템크기를 나누면 배열에 해당 아이템 갯수가 나온다 . size로 계산하니깐 
	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC); // element갯수 구하기 

	_graphics->GetDevice()->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	//input layout 이기때문에 , VS단계에서 넘겨받은 데이터에 대한 묘사를 하는것이기에 
	//PS의 Blob이랑은 상관없고 VS_Blob의 정보만 주면된다 
	//input layout도 com객체로 만들어지게된다 
	// 우리가 넘겨주는 vertex의 구조열을 묘사하는게 -> inputLayout 
}

void Game::CreateVS()
{
	// 파일로 존재하던 shader를 다시 로드해서 메모리에 들고있어가지고
	// 이런식으로 작동해달라고 GPU에게 건내줘야한다 , 또이걸 로드하는작업을 CreateVS, PS 에서 실행 

	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);

	// 쉐이더를 로드해서 blob을만들어서 Blob의 bufferPointer , buffersize를 이용해서 vertexShader를 만들어줄수있다.
	HRESULT hr = _graphics->GetDevice()->CreateVertexShader(_vsBlob->GetBufferPointer(),
		_vsBlob->GetBufferSize(),
		nullptr,
		_vertexShader.GetAddressOf()
	);
	CHECK(hr);
}

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

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);

	HRESULT hr = _graphics->GetDevice()->CreatePixelShader(_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(),
		nullptr,
		_pixelShader.GetAddressOf()
	);


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

void Game::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC; // cpu_write + gpu_read
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	CHECK(hr);





}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // 디버그용도 , 최적화는 건너뛰겠다는뜻

	//pch 에서 d3dcompiler.h 에서 지원해준다 
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(), // 우리가만든 blob객체에 채워준다 
		nullptr
	);
	//LPCWSTR , 즉 W string을 (W캐릭터포인터) 받고있고 그다음부터는 W가없이그냥 STR

//이제 이걸 범용적으로 사용하면된다 
	CHECK(hr);



}