#pragma once
class RasterizerState
{
public:
	RasterizerState(ComPtr<ID3D11Device> device);

	~RasterizerState();

	ComPtr<ID3D11RasterizerState> GetComptr() { return _rasterizerState; }


	void Create();// �Ķ���ͷ� fill mode cull mode �־��ټ����� 



private:

	ComPtr<ID3D11RasterizerState> _rasterizerState;

	ComPtr<ID3D11Device> _device;

};

