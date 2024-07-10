#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device)
{
	// ��ü���� ����־���ϴ� �κе� // 


	//_geometry = make_shared<Geometry<VertexTextureData>>();
	//GeometryHelper::CreateRectangle(_geometry);// �簢������ geometry����� , ���������� ���� ǥ�� 
	//Mesh�� ���� ���� 
	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry, Color{ 1.f,0.f,0.f,1.f });



	//IA - 	������ ǥ���ϸ� �װ� �̿��ؼ� buffer�� ������ִ°� vertex buffer
	_vertexBuffer = make_shared<VertexBuffer>(_device); // cycle �����ϸ鼭 ����ؾߵȴ� ,
	_vertexBuffer->Create(_geometry->GetVertices());

	//
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	// VS   shader�� ���� ���� blob���� 
	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");	//-> ������ ���̴��� �ε� 

	// Input Layout gpu�� shader�� �����ϴ� �ܰ� 
	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());// �� vs�ܰ迡�� �ǳ�����ϴ� ����ü�� ����� ���Ǹ� 

	// PS 
	_pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Color.hlsl", "PS", "ps_5_0");

	// RS 
	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	// �������� ��� �������� ���� 
	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();


	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_constantBuffer->Create();


	// Material �������� 
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Pig.png");// ShaderResourceView ȣ�� 


	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

	// ��ü�� ������ �ִ� �κ� 

	// Scale Rotation Translation

	_localPosition.x += 0.001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3); // srt �� s ���� ,scale vecotr�� ���� ��ȭ�ϴ� ��� ����
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z �� �Ȱ��� x�� �����༭ ��ȭ�ϰ� 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT , �̹� * ������ �����ε� �Ǿ����� 

	_transformData.matWorld = matWorld; //���� �̰� ���̴��� �Ѱ�����Ѵ� 


	_constantBuffer->CopyData(_transformData);



}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{

	// ������������ �̿�


	//�������� �Ҷ��� pipeline 
	// ������������ �̷� ������ ä���ּ��� �κ� 
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;
	pipeline->UpdatePipeline(info);

	//IA
	//dc�� ���� vertexbuffer�� �����������Ѵ� 
	pipeline->SetVertexBuffer(_vertexBuffer);

	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);

	pipeline->SetSamplerState(0, SS_VertexShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);




}
