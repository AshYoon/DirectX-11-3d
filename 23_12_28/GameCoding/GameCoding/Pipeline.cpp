#include "pch.h"
#include "Pipeline.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext)
	:_deviceContext(deviceContext)
{


}

Pipeline::~Pipeline()
{


}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	// info를받아서 정보를 갈아끼우기 



	//input layout 으로 우리가 건네준거 묘사 
	_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());

	//정점을 어떻게 이어붙일지 알려줘야함 
	_deviceContext->IASetPrimitiveTopology(info.topology);
	/// IA 단계에서는 이렇게 세팅만 



	//VS
	if(info.vertexShader)
		_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0); // 우리가만든거 써라 
	
	//constantbuffer는 우리가 사용할지안할지모르니깐 따로 객체마다 세팅하는걸로 빼야함 
	//_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer->GetComPtr().GetAddressOf());


	//RS
	_deviceContext->RSSetState(info.rasterizerState->GetComptr().Get());



	//PS
	_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);

	//_deviceContext->PSSetShaderResources(0, 1, _texture1->GetCompPtr().GetAddressOf());


	//OM
	if(info.blendState)
		_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(), info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());
	
	
	////_graphics->GetDeviceContext()->Draw(_vertices.size(), 0); // 그려달라고 요청 
	//_deviceContext->DrawIndexed(_geometry->GetIndexCount(), 0, 0); // index 기반 draw 
	//// index 갯수 





}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> buffer)
{

	uint32 stride = buffer->GetStride();

	uint32 offset = buffer->GetOffset();


	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetComptr().GetAddressOf(), &stride, &offset);

}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

}

void Pipeline::SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture)
{
	if (scope & SS_VertexShader)
		_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

}

void Pipeline::SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState)
{

	if (scope & SS_VertexShader)
		_deviceContext->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	_deviceContext->Draw(vertexCount, 0); // 그려달라고 요청 
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation)
{
	_deviceContext->DrawIndexed(indexCount , 0, 0); // index 기반 draw 
}


