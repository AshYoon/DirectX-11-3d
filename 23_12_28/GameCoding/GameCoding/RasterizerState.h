#pragma once
class RasterizerState
{
public:
	RasterizerState(ComPtr<ID3D11Device> device);

	~RasterizerState();

	ComPtr<ID3D11RasterizerState> GetComptr() { return _rasterizerState; }


	void Create();// 파라미터로 fill mode cull mode 넣어줄수있음 



private:

	ComPtr<ID3D11RasterizerState> _rasterizerState;

	ComPtr<ID3D11Device> _device;

};

