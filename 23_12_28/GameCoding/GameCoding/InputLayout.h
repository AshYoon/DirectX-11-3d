#pragma once
class InputLayout
{
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();

	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; };

	void Create(const vector<D3D11_INPUT_ELEMENT_DESC>& descs , ComPtr<ID3DBlob> blob);

private:

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;


	//어떤 부분을 어떻게 만들어야 오브젝트를 만들때어떤부분이 적용되는지
	//그런부분에 대해서 생각하면서 해야 의미가있다

};

