#pragma once

class GameObject;

// �� ������Ʈ�� ����� ���������� �ٿ��ִ� ���� 
// �� ��ü�� ���� Component�� �ֻ��� ��ü 
class Component
{

public:


	Component();

	virtual ~Component();

	virtual void Init() abstract;

	virtual void Update() abstract;


	// shared�� ����� ��ȯ�� ������־ weak�� ����°� ���������ִ�. 
	shared_ptr<GameObject> GetOwner() { return _owner.lock(); }


protected:

	


	weak_ptr<GameObject> _owner;

};

