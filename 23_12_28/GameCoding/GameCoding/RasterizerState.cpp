#include "pch.h"
#include "RasterizerState.h"

// 얘를 어떻게 분석해서 전해줘야할지를 정해줘야한다 


RasterizerState::RasterizerState(ComPtr<ID3D11Device> device)
	:_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// 3개 다 중요하다 
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;


	HRESULT hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);


}
