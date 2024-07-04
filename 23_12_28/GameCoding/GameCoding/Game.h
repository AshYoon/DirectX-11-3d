#pragma once


#include "Graphics.h"
#include "GameObject.h"


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
	HWND _hwnd;


	// 별도로 클래스로 묶어서 사용하고있으니 스마트포인터로 가져오기
	//전방선언해도된다 .
	shared_ptr<Graphics> _graphics; 

	shared_ptr<Pipeline> _pipeline;

	// 이 객체가 씬에 배치된 여러가지 오브젝트의 기반 
	shared_ptr<GameObject> _gameObject;


};