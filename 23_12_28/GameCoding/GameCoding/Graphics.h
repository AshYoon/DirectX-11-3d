#pragma once
class Graphics
{

public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();

	void RenderEnd();

	// 외부에서 가져올수있으니깐 
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
	// 후면 버퍼를 묘사하는 존재
	ComPtr<ID3D11RenderTargetView> _renderTartgetView;

	//Misc
	//뷰포트
	D3D11_VIEWPORT _viewport = { 0 }; // 화면을 묘사하는 구조체 

	float _clearColor[4] = { 0.f , 0.f , 0.f , 0.5f }; //RGBA BackGroundColor





};

