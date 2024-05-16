#pragma once



class Game
{
public:
	Game();
	~Game();



public:

	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	


private:


private:
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();
	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();

	void CreateConstantBuffer();


	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
	// 쉐이더 경로 ,       이 파일의 이름,          쉐이더 버전 , blob 이런 애를 뱉는데 그걸 줘  
private:
	HWND _hwnd;


	// 별도로 클래스로 묶어서 사용하고있으니 스마트포인터로 가져오기
	//전방선언해도된다 .
	// shared_ptr<Graphics> _graphics; 
	Graphics* _graphics;

private:
	//Geometry
	vector<Vertex> _vertices;
	//ComPtr<ID3D11Buffer> _vertextBuffer = nullptr;
	vector<uint32> _indices; // 인덱스목록 
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	//[CPU <-> RAM]  [GPU <-> VRAM ]

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;
	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;
	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;



	//SRV 
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;

	//samplerState
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;


	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localScale = { 1.f , 1.f, 1.f };
};