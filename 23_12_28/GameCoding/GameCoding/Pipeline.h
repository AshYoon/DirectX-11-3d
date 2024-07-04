#pragma once



//�⺻������ ���ֵ��� ���������� ����ϴ� ����
// ��ġ ���� ���Ƴ���°�ó�� 
struct PipelineInfo
{
	//��ü���� �����ϰ� �������ְų� , �ϳ��� �����ϴ°ſ����� �ٸ��� 
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
	// ������������������ ���� 
	// �����ٽ��� DeviceContext�� �ڿ����� 
	//


public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);

	~Pipeline();


	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);

	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);


	//�Լ��� �����ϴ� ���ø� �길 ����� �������ָ�� 
	template<typename T>
	void SetConstantBuffer(uint32 slot ,uint32 scope, shared_ptr<ConstantBuffer<T>> buffer)
	{
		// constant buffer ������ ���� 
		// buffer ��ü�� constantbuffer�� transformData�� ��� �����̴� 
		// transformdata�� �������� �޶������ֱ⶧���� �������� �ϵ��ڵ��Ҽ���� 
		// ����ü�� �ᱹ template���� ����������� 


		// constant buffer�� VS�ܰ谡 �����־ VS�ܰ迡���� ��밡���ѰŰ����� PS�ܰ迡���� ��밡��
		//���� Scope������ ��� ������� ���������� 

		if(scope & SS_VertexShader) // ��Ʈ���� , Scope �� ShaderScopeEnum�̶� ��Ʈ�����ؼ� 0�� �ƴϸ� ���� 
			_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

		if (scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

	}

	void SetTexture(uint32 slot, uint32 scope , shared_ptr<Texture> texture);

	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);



	// draw , drawindex 
	// -> indexed �� index���� ���� , ������ ����Ҳ��� draw �� 


	void Draw(uint32 vertexCount, uint32 startVertexLocation);

	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);



private:


	ComPtr<ID3D11DeviceContext> _deviceContext;


};

