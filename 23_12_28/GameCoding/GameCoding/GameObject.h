#pragma once


// unity ���  actor�ǰ��� , 
// �߾ӿ����°� ��ǥ , gameobject��� ������Ŭ������ ���� 
// ���� �ܰ迡���� �̷��� �����ϴ��۾� 
class GameObject
{


public:

	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	//
	void Update();

	//Render�Ҷ��� pipeline �޾������
	void Render(shared_ptr<Pipeline> pipeline);



private:

	ComPtr<ID3D11Device> _device;





	// ��ü���� �ѹ��� �����Ǵ°��� graphics , device , deviceContext ,swapChain
	// Ŭ���� ���� - vertexbuffer , indexbuffer , geometry  
	// ��ü �������� constantbuffer , shaderResourceView 
	//

	//�� ���� Object��  ��� ���ܸԾ������� ���� 
	//shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<Geometry<VertexColorData>> _geometry;


	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;
	//[CPU <-> RAM]  [GPU <-> VRAM ]
	// VS shader -> � shader�� �Ἥ  ǥ���Ҳ��� 
	shared_ptr<VertexShader> _vertexShader;
	// PS
	shared_ptr<PixelShader> _pixelShader;
	// RS texture , constatnt vuffer -> ���̴� �ܰ迡�� �����ִ� ���� 
	shared_ptr<RasterizerState> _rasterizerState;
	//ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
	//SRV 
	shared_ptr<Texture> _texture1;
	//samplerState , RS Sampler State , BlendState �ɼ����� �����Ҽ��ִºκ�
	shared_ptr<SamplerState> _samplerState;
	//ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	shared_ptr<BlendState> _blendState;
	//ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	//SRT , ��¥ ��ü���� �ٸ��� 
	TransformData _transformData;

	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localScale = { 1.f , 1.f, 1.f };

};

