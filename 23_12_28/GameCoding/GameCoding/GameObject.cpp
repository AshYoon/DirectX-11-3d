#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device)
{
	// 객체마다 들고있어야하는 부분들 // 


	//_geometry = make_shared<Geometry<VertexTextureData>>();
	//GeometryHelper::CreateRectangle(_geometry);// 사각형으로 geometry만들기 , 기하학적인 도형 표현 
	//Mesh와 같은 역할 
	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry, Color{ 1.f,0.f,0.f,1.f });



	//IA - 	도현을 표현하면 그걸 이용해서 buffer를 만들어주는게 vertex buffer
	_vertexBuffer = make_shared<VertexBuffer>(_device); // cycle 생각하면서 사용해야된다 ,
	_vertexBuffer->Create(_geometry->GetVertices());

	//
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	// VS   shader를 먼저 만들어서 blob생성 
	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");	//-> 각각의 쉐이더를 로드 

	// Input Layout gpu랑 shader랑 연결하는 단계 
	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());// 이 vs단계에서 건내줘야하는 구조체의 생김새 정의를 

	// PS 
	_pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Color.hlsl", "PS", "ps_5_0");

	// RS 
	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	// 마지막에 어떻게 섞일지를 결정 
	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();


	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_constantBuffer->Create();


	// Material 같은역할 
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Pig.png");// ShaderResourceView 호출 


	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

	// 물체랑 연관성 있는 부분 

	// Scale Rotation Translation

	_localPosition.x += 0.001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3); // srt 중 s 먼저 ,scale vecotr에 따라 변화하는 행렬 생성
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z 도 똑같이 x에 곱해줘서 변화하게 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT , 이미 * 연산자 오버로딩 되어있음 

	_transformData.matWorld = matWorld; //이제 이걸 쉐이더에 넘겨줘야한다 


	_constantBuffer->CopyData(_transformData);



}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{

	// 파이프라인을 이용


	//렌더링을 할때는 pipeline 
	// 파이프라인을 이런 정보로 채워주세요 부분 
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;
	pipeline->UpdatePipeline(info);

	//IA
	//dc에 가서 vertexbuffer를 연결시켜줘야한다 
	pipeline->SetVertexBuffer(_vertexBuffer);

	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);

	pipeline->SetSamplerState(0, SS_VertexShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);




}
