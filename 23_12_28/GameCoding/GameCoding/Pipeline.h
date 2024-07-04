#pragma once



//기본적으로 모든애들이 공통적으로 사용하는 정보
// 마치 포를 갈아끼우는것처럼 
struct PipelineInfo
{
	//물체마다 고유하게 가지고있거나 , 하나를 공유하는거에따라 다르게 
	// 
	//InputLayout
	shared_ptr<InputLayout> inputLayout;
	//[CPU <-> RAM]  [GPU <-> VRAM ]
	// VS
	shared_ptr<VertexShader> vertexShader;
	// PS
	shared_ptr<PixelShader> pixelShader;

	//RS
	shared_ptr<RasterizerState> rasterizerState;



	shared_ptr<BlendState> blendState;

	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};



class Pipeline
{
	// 렌더링파이프라인을 묘사 
	// 가장핵심은 DeviceContext의 자원매핑 
	//


public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);

	~Pipeline();


	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);

	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);


	//함수에 적용하는 템플릿 얘만 헤더에 구현해주면됨 
	template<typename T>
	void SetConstantBuffer(uint32 slot ,uint32 scope, shared_ptr<ConstantBuffer<T>> buffer)
	{
		// constant buffer 세팅을 보면 
		// buffer 자체가 constantbuffer에 transformData를 담는 형식이다 
		// transformdata는 언제든지 달라질수있기때문에 언제까지 하드코딩할수없어서 
		// 얘자체도 결국 template으로 선언해줘야함 


		// constant buffer는 VS단계가 적혀있어서 VS단계에서만 사용가능한거같지만 PS단계에서도 사용가능
		//따라서 Scope변수로 어디서 사용할지 명시해줘야함 

		if(scope & SS_VertexShader) // 비트연산 , Scope 랑 ShaderScopeEnum이랑 비트연산해서 0이 아니면 실행 
			_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

		if (scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

	}

	void SetTexture(uint32 slot, uint32 scope , shared_ptr<Texture> texture);

	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);



	// draw , drawindex 
	// -> indexed 는 index까지 적용 , 정점만 사용할꺼면 draw 만 


	void Draw(uint32 vertexCount, uint32 startVertexLocation);

	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);



private:


	ComPtr<ID3D11DeviceContext> _deviceContext;


};

