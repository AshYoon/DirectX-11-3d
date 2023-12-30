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
	// 함수단위로 기능을 만들어야 공부하기편함 
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
	// i 가 interface에 약자 
	// 중요한건이 아이들은 com객체라고 불리는 것들 
	// 새로운 객체는 new _device 이러는데 얘내들은 그렇게 만드는
	//방식이아니라 특정함수를 호출해서 결과값을 받아서 쓰는것 
	// 삭제할때도 delete 가 아니라 release  or ad ref
	//ref count - 스마트 포인터 쓰기전에 ref (참조 관리) 
	//device 포인터를 다른 클래스에 넘겨주면 생명주기가 애매해짐 
	// 다른곳에 복사를 하면 ref count를 1 증가해주고 다쓰면 release 해줘야함
	//ref count 가 0 이되면 객체가 소멸하게된다 . 소멸될껀 신경쓸껀아니다 알아서해줌
	// 기본적인 new delete 방식이 아니다 ,add ref , release 짝이안맞다면 ?
	// release를 add ref보다 많이하거나 이러면 ? 메모리 누수 가능 
	// 수동으로 관리하는건 바람직하지않음 , 일일히 수동으로 하지않고 
	// 스마트 포인터 방식으로 작업해야 ref count를 자동으로 관리  // 
	// 실질적으로 _device를 rapping 하는 스마트 포인터를 사용 
	// ComPtr을 써야 알아서 C# 처럼 알아서 release 함 com객체를 관리하는 ptr
	//wlr이라는 아이에 붙어있다 . namespace까지 추가해서 사용할수있는것 
	// comptr -> component model의 약자 중요한건 이 아이가 뭘하는것인가
	// 1번 gpu랑 대화를하면서 노예를 부리는것 , 
	// gpu 버전 3070 3050 등등 이걸 if else 로 일일히 관리해줄수없음
	// 이 com인터페이스는 ms 에서 만든 dx lib의 이런특정 클래스를 대상으로
	//우리가 몇가지작업만하면 그거랑 실질적으로 모든 gpu제품이랑 알아서 연계
	//컴객체의 핵심 - 우리가 이거만집중하면 하드웨어적인부분은 ms와 제조사가 맞춰야함
	//ref count 관리도 해주고 
	// 굉장히 많은 리소스를 만들어야하는데 이 device를 통해만들어야함 
	// 스타를 비유하면 커맨드센터 - 만능형 ? 총사령관같은 개념 
	//이미 만들어진 리소스를 가지고와서 렌더링 파이프라인에 연결하고싶다 -> deviceContext
	// 내가만들꺼다 device 
	//유닛한테 명령을 내리거나 뭔가를 하라고 시킬때는 device 
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; 
	//Create device & swap chain으로 만들거나 Create device 모시기로 만들거나 
	//우린 Create device & swap chain
	// device뿐만아니라 swapchain도만들어야함 
	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	//swap chain이 뭘하는지 -> 더블 버퍼링 하면 떠오르는것 ? 
	// 화면에 보이는거랑 그리는거랑 동시에 진행이되면 문제가될수있다.
	// 이 버퍼에 그린내용을 바로 화면에 보이게되면 화면에 보이는순간에 인게임로직이 
	//실행되서 여기있는 내용을 고치고있으면 일부분은 화면에 그리고있는데 일부분은 
	//갱신이되게되면 여러프레임에 그정보가 뒤섞일수있다 
	//////////////////////////////////////////////////////////////////////



	////// RTV 
	// 후면 버퍼를 묘사하는 존재
	ComPtr<ID3D11RenderTargetView> _renderTartgetView;

	//Misc
	//뷰포트
	D3D11_VIEWPORT _viewport = { 0 }; // 화면을 묘사하는 구조체 

	float _clearColor[4] = { 0.f , 0.f , 0.f , 0.5f }; //RGBA
};

