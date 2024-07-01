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



	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();


	
private:
	HWND _hwnd;


	// 별도로 클래스로 묶어서 사용하고있으니 스마트포인터로 가져오기
	//전방선언해도된다 .
	shared_ptr<Graphics> _graphics; 

private:
	// 전체에서 한번만 만들어도되는건지 graphics , device , deviceContext ,swapChain
	// 클래스 종속 - vertexbuffer , indexbuffer , geometry  
	// 객체 종속인지 constantbuffer , shaderResourceView 
	//

	//Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	//InputLayout
	shared_ptr<InputLayout> _inputLayout;
	//[CPU <-> RAM]  [GPU <-> VRAM ]
	// VS
	shared_ptr<VertexShader> _vertexShader;
	// PS
	shared_ptr<PixelShader> _pixelShader;
	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
	//SRV 
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr; // 텍스쳐 같은 개념 

	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;
	//samplerState
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	//SRT
	TransformData _transformData;
	
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localScale = { 1.f , 1.f, 1.f };
};