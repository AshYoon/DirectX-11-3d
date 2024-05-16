#pragma once
class Graphics
{

public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();

	void RenderEnd();

	// �ܺο��� �����ü������ϱ� 
	ComPtr<ID3D11Device> GetDevice() { return _device; };

	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; };



private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND _hwnd = {};
	uint32 _width = GWinSizeX;
	uint32 _height = GWinSizeY;


private:

	//Device & SwapChain 
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;

	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	////// RTV 
	// �ĸ� ���۸� �����ϴ� ����
	ComPtr<ID3D11RenderTargetView> _renderTartgetView;

	//Misc
	//����Ʈ
	D3D11_VIEWPORT _viewport = { 0 }; // ȭ���� �����ϴ� ����ü 

	float _clearColor[4] = { 0.f , 0.f , 0.f , 0.5f }; //RGBA BackGroundColor





};

