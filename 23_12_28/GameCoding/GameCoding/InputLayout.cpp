#include "pch.h"
#include "InputLayout.h"

InputLayout::InputLayout(ComPtr<ID3D11Device> device)
	:_device(device)
{


}

InputLayout::~InputLayout()
{


}

void InputLayout::Create(const vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob)
{	
	//desc -> ������ ����ɼ��������ϱ� vector�� �޾ƾ��Ѵ�
	// �迭�� ũ�⿡ �迭�ϳ��� ������ũ�⸦ ������ �迭�� �ش� ������ ������ ���´� . size�� ����ϴϱ� 
	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC); // element���� ���ϱ� 

	const int32 count = static_cast<int32>(descs.size());

	_device->CreateInputLayout(descs.data(), count, blob->GetBufferPointer(), blob->GetBufferSize(), _inputLayout.GetAddressOf());
	//input layout �̱⶧���� , VS�ܰ迡�� �Ѱܹ��� �����Ϳ� ���� ���縦 �ϴ°��̱⿡ 
	//PS�� Blob�̶��� ������� VS_Blob�� ������ �ָ�ȴ� 
	//input layout�� com��ü�� ��������Եȴ� 
	// �츮�� �Ѱ��ִ� vertex�� �������� �����ϴ°� -> inputLayout 
}
