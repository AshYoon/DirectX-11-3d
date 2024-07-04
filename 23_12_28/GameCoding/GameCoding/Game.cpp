#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	// hwnd를 넘겨주면 graphics에서 알아서 만들어줌 


	_graphics = make_shared<Graphics>(hwnd); // 메모리 공간뿐만아니라 ref카운트관리까지하니깐 makeshared로 
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());

	// game object 




}

void Game::Update()
{
	// Scale Rotation Translation

	_gameObject->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();// 도화지 초기화 
	

	//IA - VS - RS - PS - OM
	//input aseembler , vertext shader , tesellator , resterizer , pixel shader , output merger

	//HDC 
	{
		_gameObject->Render(_pipeline);
	}


	_graphics->RenderEnd(); // 그림 제출 
}












