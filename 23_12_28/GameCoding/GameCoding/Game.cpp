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


	CreateGeometry();// -> �ﰢ���� ���� ����� 
	CreateVS(); //-> ������ ���̴��� �ε� 
	CreateInputLayout(); // �� vs�ܰ迡�� �ǳ�����ϴ� ����ü�� ����� ���Ǹ� ��������.
	CreatePS();

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateSRV(); // ShaderResourceView ȣ�� 
	CreateConstantBuffer();
}

void Game::Update()
{
	// Scale Rotation Translation
	//_transformData.offset.x += 0.0003f;
	//_transformData.offset.y = 0.3f;

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));

	_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_deviceContext->Unmap(_constantBuffer.Get(), 0);
}

void Game::Render()
{
	RenderBegin(); // ��ȭ�� �ʱ�ȭ 

	//IA - VS - RS - PS - OM
	//input aseembler , vertext shader , tesellator , resterizer , pixel shader , output merger


	{

		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		//IA
		//dc�� ���� vertexbuffer�� �����������Ѵ� 
		_deviceContext->IASetVertexBuffers(0, 1, _vertextBuffer.GetAddressOf(), &stride, &offset);
		//							���۽���1�� , ���۰��� , ���۰ǳ��� , vertexũ�� , 
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		//                               �� �ε��� ���� ,     4����Ʈ�������ϱ� 32��Ʈ¥���ٶ�¶� 

		//input layout ���� �츮�� �ǳ��ذ� ���� 
		_deviceContext->IASetInputLayout(_inputLayout.Get());

		//������ ��� �̾������ �˷������ 
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 
		/// IA �ܰ迡���� �̷��� ���ø� 



		//VS

		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0); // �츮������� ��� 
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());


		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());



		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		//OM

		//_deviceContext->Draw(_vertices.size(), 0); // �׷��޶�� ��û 
		_deviceContext->DrawIndexed(_indices.size(),0, 0); // index ��� draw 
								   // index ���� 



	}

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
	
	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTartgetView.GetAddressOf());


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

void Game::CreateGeometry()
{
	//vertex data
	{
		_vertices.resize(4);

		// ��ǥ�� - 1 ~ 1 ���� �ݽð�� 
		//��� �ﰢ���� ǥ������ �����ͷ� ������ֱ� �������� CPU <->RAM
		//GPU�� �Ȱ��� ���������Ѵ�
		// �ð�������� ��������� �ð�������� ���� 


		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
		_vertices[0].uv = Vec2(0.f, 5.f);
		//_vertices[0].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
		_vertices[1].uv = Vec2(0.f, 0.f);
		//_vertices[1].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
		_vertices[2].uv = Vec2(5.f, 5.f);
		//_vertices[2].color = Color(1.f, 0.f, 0.f,1.f);

		_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
		_vertices[3].uv = Vec2(5.f, 0.f);
		//_vertices[3].color = Color(1.f, 0.f, 0.f,1.f);
	}

	//vertex buffer
	{
		//���ο� ���ҽ� �������ϴ� device���� create buffer
		//Input Assembler�ܰ迡�� vertex buffer���־��ְ��ִ°�
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // �������ذ� ��ĥ�Ͼ�� immutable
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // vertex buffer bind �뵵�� ����Ҳ���
		desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size()); // Vertex �޸� size x vertices vector size()
		// ���� ���� �� 
		
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_vertices[0]; // vertex �迭�� ù��°�� �����ּ� 

		// ������ ���� ������� gpu�ʿ� ���۰� ��������鼭 �ʱⰪ�� ���簡�ȴ� 
		//�״����� gpu�� read only�� �۵��̵ȴ� , �̰� ���� ���� 
		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertextBuffer.GetAddressOf()); 
		CHECK(hr);

	}

	//index

	{
		_indices = { 0 ,1 ,2 , 2 ,1 ,3 }; //������ ���� ���� 

	}

	 //index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // IMMUTABLE������ ���� 
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(uint32) * _indices.size());


		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_indices[0]; // _indicies.data() �� ���� 


		HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}


}


// �긦 ��� �м��ؼ� ������������� ��������Ѵ� 
void Game::CreateInputLayout()
{
	//�迭 ���·� ���� 
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT,0 ,0,D3D11_INPUT_PER_VERTEX_DATA,0},//FLOAT�� ���� 32BIT (VEC3)
		{"TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT,0 ,12,D3D11_INPUT_PER_VERTEX_DATA,0}, //Vec4 COLOR RGBA + ��������
	};

	// �迭�� ũ�⿡ �迭�ϳ��� ������ũ�⸦ ������ �迭�� �ش� ������ ������ ���´� . size�� ����ϴϱ� 
	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC); // element���� ���ϱ� 
	
	_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	//input layout �̱⶧���� , VS�ܰ迡�� �Ѱܹ��� �����Ϳ� ���� ���縦 �ϴ°��̱⿡ 
	//PS�� Blob�̶��� ������� VS_Blob�� ������ �ָ�ȴ� 
	//input layout�� com��ü�� ��������Եȴ� 
	// �츮�� �Ѱ��ִ� vertex�� �������� �����ϴ°� -> inputLayout 
}

void Game::CreateVS()
{
	// ���Ϸ� �����ϴ� shader�� �ٽ� �ε��ؼ� �޸𸮿� ����־����
	// �̷������� �۵��ش޶�� GPU���� �ǳ�����Ѵ� , ���̰� �ε��ϴ��۾��� CreateVS, PS ���� ���� 

	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
	
	// ���̴��� �ε��ؼ� blob������ Blob�� bufferPointer , buffersize�� �̿��ؼ� vertexShader�� ������ټ��ִ�.
	HRESULT hr = _device->CreateVertexShader(_vsBlob->GetBufferPointer(),
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
	// 3�� �� �߿��ϴ� 
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;


	HRESULT hr =	_device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
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
	//border color�� RGBA �����ȴ� 
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//��� ���ϸ���� 
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.0f;


	HRESULT hr = _device->CreateSamplerState(&desc,_samplerState.GetAddressOf());
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



	HRESULT hr = _device->CreateBlendState(&desc,_blendState.GetAddressOf());
	CHECK(hr);



}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);

	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(),
		nullptr,
		_pixelShader.GetAddressOf()
	);


	CHECK(hr);


}

void Game::CreateSRV()
{
	//�̹����� �������� �Լ��� ���������ִ� 
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	
	HRESULT hr = ::LoadFromWICFile(L"Pig.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	//��������ϸ� �̹����� �ε��Ѱ� 

	//shader resource view ��°� �������Ѵ� 
	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());

	CHECK(hr);

	hr = ::LoadFromWICFile(L"Sample.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	//��������ϸ� �̹����� �ε��Ѱ� 

	//shader resource view ��°� �������Ѵ� 
	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView2.GetAddressOf());

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

	HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	CHECK(hr);


	 


}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // ����׿뵵 , ����ȭ�� �ǳʶٰڴٴ¶�

	//pch ���� d3dcompiler.h ���� �������ش� 
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(), // �츮������ blob��ü�� ä���ش� 
		nullptr
	);
		//LPCWSTR , �� W string�� (Wĳ����������) �ް��ְ� �״������ʹ� W�����̱׳� STR
	
	//���� �̰� ���������� ����ϸ�ȴ� 
	CHECK(hr);

}
