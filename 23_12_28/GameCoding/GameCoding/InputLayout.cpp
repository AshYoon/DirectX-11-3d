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
	//desc -> 갯수가 변경될수도있으니깐 vector로 받아야한다
	// 배열의 크기에 배열하나의 아이템크기를 나누면 배열에 해당 아이템 갯수가 나온다 . size로 계산하니깐 
	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC); // element갯수 구하기 

	const int32 count = static_cast<int32>(descs.size());

	_device->CreateInputLayout(descs.data(), count, blob->GetBufferPointer(), blob->GetBufferSize(), _inputLayout.GetAddressOf());
	//input layout 이기때문에 , VS단계에서 넘겨받은 데이터에 대한 묘사를 하는것이기에 
	//PS의 Blob이랑은 상관없고 VS_Blob의 정보만 주면된다 
	//input layout도 com객체로 만들어지게된다 
	// 우리가 넘겨주는 vertex의 구조열을 묘사하는게 -> inputLayout 
}
