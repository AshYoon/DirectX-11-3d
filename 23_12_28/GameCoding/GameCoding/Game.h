#pragma once



class Game
{
public:
	Game();
	~Game();
	


public:

	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void RenderBegin();
	void RenderEnd();


private:
	// �Լ������� ����� ������ �����ϱ����� 
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;


private:






	//DX 
	///////////////////////////// Device & SwapChain ////////////////////////////////
	// i �� interface�� ���� 
	// �߿��Ѱ��� ���̵��� com��ü��� �Ҹ��� �͵� 
	// ���ο� ��ü�� new _device �̷��µ� �곻���� �׷��� �����
	//����̾ƴ϶� Ư���Լ��� ȣ���ؼ� ������� �޾Ƽ� ���°� 
	// �����Ҷ��� delete �� �ƴ϶� release  or ad ref
	//ref count - ����Ʈ ������ �������� ref (���� ����) 
	//device �����͸� �ٸ� Ŭ������ �Ѱ��ָ� �����ֱⰡ �ָ����� 
	// �ٸ����� ���縦 �ϸ� ref count�� 1 �������ְ� �پ��� release �������
	//ref count �� 0 �̵Ǹ� ��ü�� �Ҹ��ϰԵȴ� . �Ҹ�ɲ� �Ű澵���ƴϴ� �˾Ƽ�����
	// �⺻���� new delete ����� �ƴϴ� ,add ref , release ¦�̾ȸ´ٸ� ?
	// release�� add ref���� �����ϰų� �̷��� ? �޸� ���� ���� 
	// �������� �����ϴ°� �ٶ����������� , ������ �������� �����ʰ� 
	// ����Ʈ ������ ������� �۾��ؾ� ref count�� �ڵ����� ����  // 
	// ���������� _device�� rapping �ϴ� ����Ʈ �����͸� ��� 
	// ComPtr�� ��� �˾Ƽ� C# ó�� �˾Ƽ� release �� com��ü�� �����ϴ� ptr
	//wlr�̶�� ���̿� �پ��ִ� . namespace���� �߰��ؼ� ����Ҽ��ִ°� 
	// comptr -> component model�� ���� �߿��Ѱ� �� ���̰� ���ϴ°��ΰ�
	// 1�� gpu�� ��ȭ���ϸ鼭 �뿹�� �θ��°� , 
	// gpu ���� 3070 3050 ��� �̰� if else �� ������ �������ټ�����
	// �� com�������̽��� ms ���� ���� dx lib�� �̷�Ư�� Ŭ������ �������
	//�츮�� ����۾����ϸ� �װŶ� ���������� ��� gpu��ǰ�̶� �˾Ƽ� ����
	//�İ�ü�� �ٽ� - �츮�� �̰Ÿ������ϸ� �ϵ�������κκ��� ms�� �����簡 �������
	//ref count ������ ���ְ� 
	// ������ ���� ���ҽ��� �������ϴµ� �� device�� ���ظ������� 
	// ��Ÿ�� �����ϸ� Ŀ�ǵ弾�� - ������ ? �ѻ�ɰ����� ���� 
	//�̹� ������� ���ҽ��� ������ͼ� ������ ���������ο� �����ϰ�ʹ� -> deviceContext
	// �������鲨�� device 
	//�������� ����� �����ų� ������ �϶�� ��ų���� device 
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; 
	//Create device & swap chain���� ����ų� Create device ��ñ�� ����ų� 
	//�츰 Create device & swap chain
	// device�Ӹ��ƴ϶� swapchain���������� 
	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	//swap chain�� ���ϴ��� -> ���� ���۸� �ϸ� �������°� ? 
	// ȭ�鿡 ���̴°Ŷ� �׸��°Ŷ� ���ÿ� �����̵Ǹ� �������ɼ��ִ�.
	// �� ���ۿ� �׸������� �ٷ� ȭ�鿡 ���̰ԵǸ� ȭ�鿡 ���̴¼����� �ΰ��ӷ����� 
	//����Ǽ� �����ִ� ������ ��ġ�������� �Ϻκ��� ȭ�鿡 �׸����ִµ� �Ϻκ��� 
	//�����̵ǰԵǸ� ���������ӿ� �������� �ڼ��ϼ��ִ� 
	//////////////////////////////////////////////////////////////////////



	////// RTV 
	// �ĸ� ���۸� �����ϴ� ����
	ComPtr<ID3D11RenderTargetView> _renderTartgetView;

	//Misc
	//����Ʈ
	D3D11_VIEWPORT _viewport = { 0 }; // ȭ���� �����ϴ� ����ü 

	float _clearColor[4] = { 0.f , 0.f , 0.f , 0.5f }; //RGBA
};

