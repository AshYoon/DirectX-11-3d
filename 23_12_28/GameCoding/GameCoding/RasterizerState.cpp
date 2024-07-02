#include "pch.h"
#include "RasterizerState.h"

// �긦 ��� �м��ؼ� ������������� ��������Ѵ� 


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
	// 3�� �� �߿��ϴ� 
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;


	HRESULT hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);


}
