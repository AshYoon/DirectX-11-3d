#pragma once

class GameObject;

// 각 오브젝트의 기능을 조립형으로 붙여주는 형식 
// 각 객체에 붙일 Component의 최상위 객체 
class Component
{

public:


	Component();

	virtual ~Component();

	virtual void Init() abstract;

	virtual void Update() abstract;


	// shared로 만들면 순환이 생길수있어서 weak로 만드는게 맞을수도있다. 
	shared_ptr<GameObject> GetOwner() { return _owner.lock(); }


protected:

	


	weak_ptr<GameObject> _owner;

};

