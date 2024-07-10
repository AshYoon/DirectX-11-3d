#pragma once
#include "Component.h"

// ���� �ٽ����� ��ǰ , ��� ��ġ�� �ִ��ĸ� ���� + �������� ����
class Transform : public Component
{
public:
	Transform();
	~Transform();


	virtual void Init() override;

	virtual void Update() override;

	//
	void UpdateTransform();

	//local

	Vec3 GetLocalScale() { return _localScale; }

	void SetLocalScale(const Vec3& localScale) { _localScale = localScale; UpdateTransform(); }

	Vec3 GetLocalRotation() { return _localRotation; }

	void SetLocalRotation(const Vec3& localRotation) { _localRotation = localRotation; UpdateTransform();
	}

	Vec3 GetLocalPosition() { return _localPosition; }

	void SetLocalPosition(const Vec3& localPosition) { _localPosition = localPosition; UpdateTransform();
	}


	// ���� �θ� ����� ����������.
	//�ǽð����� ���ص��ǰ� , Cache�� �ص��ȴ� 
	//World 
	Vec3 GetScale() { return _scale; }

	void Scale(const Vec3& worldScale);

	Vec3 GetRotation() { return _rotation; }

	void SetRotation(const Vec3& worldRotation);

	Vec3 GetPosition() { return _position; }

	void SetPosition(const Vec3& worldPosition);

	// ���� ��ȯ���
	Matrix GetWorldMatrix() { return _matWorld; }





	// ��������

	bool HasParent() { return _parent != nullptr; }

	shared_ptr<Transform> GetParent() { return _parent; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	void AddChild(shared_ptr<Transform> child) { _children = _children; }





private:

	//local�� �ٿ��� local ��ǥ���� ��� ( world�� �����ǰ�) 
	Vec3 _localScale = { 1.f , 1.f, 1.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	
	// �θ� ���������ϴ� ��ǥ�� ���Ҽ��ִ� ��ȯ����� �˾ƾ��Ѵ�.
	// �θ� �����ϴ� ���� local position 
	// -> �θ� ������ srt�� ���ϸ� �ٷ� ��ǥ�������µ� , 
	// matLocal�� �θ� ���������ϴ� ��ǥ�� �װ� �ٽ� ��ķ� ������ָ� world ��ǥ 

	
	//�׵���� 
	// local ��� 
	Matrix _matLocal = Matrix::Identity;
	// world ��� 
	Matrix _matWorld = Matrix::Identity;


	// Cache
	Vec3 _scale;
	// x, y, z �Ӹ��ƴ϶� w ���� ���ʹϾ����� �����Ѵ� gimbal lock ���� 
	Vec3 _rotation;
	Vec3 _position;

	Vec3 _right;
	Vec3 _up;
	Vec3 _look; // forward vector


private:

	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

