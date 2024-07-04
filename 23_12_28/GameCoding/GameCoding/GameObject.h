#pragma once


// unity 방식  actor의개념 , 
// 중앙에띄우는걸 목표 , gameobject라는 별도의클래스로 묶음 
// 지금 단계에서는 이렇게 정리하는작업 
class GameObject
{


public:

	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	//
	void Update();

	//Render할때는 pipeline 받아줘야함
	void Render(shared_ptr<Pipeline> pipeline);



private:

	ComPtr<ID3D11Device> _device;





	// 전체에서 한번만 만들어도되는건지 graphics , device , deviceContext ,swapChain
	// 클래스 종속 - vertexbuffer , indexbuffer , geometry  
	// 객체 종속인지 constantbuffer , shaderResourceView 
	//

	//이 게임 Object가  어떻게 생겨먹었는지를 설명 
	//shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<Geometry<VertexColorData>> _geometry;


	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;
	//[CPU <-> RAM]  [GPU <-> VRAM ]
	// VS shader -> 어떤 shader를 써서  표현할껀지 
	shared_ptr<VertexShader> _vertexShader;
	// PS
	shared_ptr<PixelShader> _pixelShader;
	// RS texture , constatnt vuffer -> 쉐이더 단계에서 쓸수있는 인자 
	shared_ptr<RasterizerState> _rasterizerState;
	//ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
	//SRV 
	shared_ptr<Texture> _texture1;
	//samplerState , RS Sampler State , BlendState 옵션으로 설정할수있는부분
	shared_ptr<SamplerState> _samplerState;
	//ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	shared_ptr<BlendState> _blendState;
	//ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	//SRT , 진짜 물체마다 다른것 
	TransformData _transformData;

	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localScale = { 1.f , 1.f, 1.f };

};

