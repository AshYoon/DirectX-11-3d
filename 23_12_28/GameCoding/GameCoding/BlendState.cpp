#include "pch.h"
#include "BlendState.h"
// 얘를 어떻게 분석해서 전해줘야할지를 정해줘야한다 


BlendState::BlendState(ComPtr<ID3D11Device> device)
	:_device(device)
{

}

BlendState::~BlendState()
{

}

void BlendState::Create(D3D11_RENDER_TARGET_BLEND_DESC blendDesc ,float factor)
{
	_blendFactor = factor;


	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	//렌더타겟부분은 넘겨받은걸로 교체 
	desc.RenderTarget[0] = blendDesc;

	//desc.RenderTarget[0].BlendEnable = true;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;



	HRESULT hr = _device->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);

}


