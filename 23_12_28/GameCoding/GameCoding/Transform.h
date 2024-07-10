#pragma once
#include "Component.h"

// 가장 핵심적인 부품 , 어디 위치에 있느냐를 결정 + 계층구조 관리
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


	// 만약 부모가 생기면 복잡해진다.
	//실시간으로 구해도되고 , Cache를 해도된다 
	//World 
	Vec3 GetScale() { return _scale; }

	void Scale(const Vec3& worldScale);

	Vec3 GetRotation() { return _rotation; }

	void SetRotation(const Vec3& worldRotation);

	Vec3 GetPosition() { return _position; }

	void SetPosition(const Vec3& worldPosition);

	// 월드 변환행렬
	Matrix GetWorldMatrix() { return _matWorld; }





	// 계층관게

	bool HasParent() { return _parent != nullptr; }

	shared_ptr<Transform> GetParent() { return _parent; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	void AddChild(shared_ptr<Transform> child) { _children = _children; }





private:

	//local을 붙여서 local 좌표임을 명시 ( world랑 구별되게) 
	Vec3 _localScale = { 1.f , 1.f, 1.f };
	Vec3 _localRotation = { 0.f, 0.f ,0.f };
	Vec3 _localPosition = { 0.f , 0.f , 0.f };
	
	// 부모를 기준으로하는 좌표를 구할수있는 변환행렬을 알아야한다.
	// 부모를 상대로하는 나의 local position 
	// -> 부모가 없으면 srt를 곱하면 바로 좌표가나오는데 , 
	// matLocal이 부모를 기준으로하는 좌표계 그걸 다시 행렬로 만들어주면 world 좌표 

	
	//항등행렬 
	// local 행렬 
	Matrix _matLocal = Matrix::Identity;
	// world 행렬 
	Matrix _matWorld = Matrix::Identity;


	// Cache
	Vec3 _scale;
	// x, y, z 뿐만아니라 w 까지 쿼터니언으로 관리한다 gimbal lock 방지 
	Vec3 _rotation;
	Vec3 _position;

	Vec3 _right;
	Vec3 _up;
	Vec3 _look; // forward vector


private:

	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

