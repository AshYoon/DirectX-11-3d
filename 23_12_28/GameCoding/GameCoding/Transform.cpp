#include "pch.h"
#include "Transform.h"

Transform::Transform()
{



}

Transform::~Transform()
{


}

void Transform::Init()
{


}

void Transform::Update()
{


}

Vec3 ToEulerAngles(Quaternion q)
{
	// quat to euler angle 

	Vec3 angles;

	//roll ( x - axis rotation) 
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);

	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	//pitch ( y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	//yaw ( z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;



}




void Transform::UpdateTransform()
{
	//
		// ��ü�� ������ �ִ� �κ� 

	// Scale Rotation Translation

	_localPosition.x += 0.001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3); // srt �� s ���� ,scale vecotr�� ���� ��ȭ�ϴ� ��� ����
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z �� �Ȱ��� x�� �����༭ ��ȭ�ϰ� 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation; // 

	// ������ ������������ �θ� ��������� ,  
	if (HasParent())
	{
		//�θ�������

		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal; // ���� �θ� �������� �̰� world ��� 
	}


	// ���� ������� Scale Rotation Translation 
	// 
	// world ��ȯ����� 
	// [ 1, 2, 3, 4]
	// [ 5, 6, 7, 8]
	// [ 9, 10, 11, 12]
	// [ 13, 14, 15, 16]
	//�̷��� �ִٰ� �����Ҷ� , �� right vector�� ��� ���ұ� ? 
	//_right vector , world ����  
	//matworld �� ���ϴ°͵� ��������� 
	// decompose�� ���� ������ �ɰ����ִ� �ٵ� ��ȯ�� ���ʹϾ��̶�� �ɷ� ���ش� 
	// ���ͷ� �����ϸ� ������������ �Ͼ�⶧���� ���ʹϾ����� �����ؾ��� (gimbal lock) 
	Quaternion quat;


	_matWorld.Decompose(_scale , quat , _position );

	//quaternion���� �޾����� �ٽ� �츮������ ���Ϸ�������� ��ȯ������� 

	_rotation = ToEulerAngles(quat);

	// v [ x y z ? ] m , _matworld�� ���ϴ� 2���� ��� 
	// TransformCoord ��� -> normal �Ⱥ����� , � vector�� ���Ҷ� xyz�������� �������� �� �����ֳ� ���� 
	//TransformNormal ��� �ΰ����� �ִ� , ��ġ ������� ���⸸ ���ϴ°Ÿ� Normal ��� ��� 
	_right = Vec3::TransformNormal(Vec3::Right, _matWorld);
	
	_up = Vec3::TransformNormal(Vec3::Up, _matWorld);

	_look = Vec3::TransformNormal(Vec3::Backward, _matWorld);//���� forward �ε� ������ ��ǥ��� �ݴ�εǾ�����
	// �츮�� �ٶ󺸴� ������ 0 , 0 , 1 �� backward�� �Ǿ��־ ���̺귯�� �����ϰų��ؾ��� 





	//children
	for (const shared_ptr<Transform>& child : _children)
		child->UpdateTransform();// �ڽĵ鵵 update������� 

	







}

void Transform::Scale(const Vec3& worldScale)
{

	if (HasParent())
	{
		//�θ� �ִٸ� 
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;

		scale.x /= worldScale.x;
		scale.y /= worldScale.y;
		scale.z /= worldScale.z;

		SetLocalScale(scale);
	}
	else
	{
		// �θ� ���ٸ�
		SetLocalScale(worldScale);
	}

}

void Transform::SetRotation(const Vec3& worldRotation)
{


}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent)
	{
		//�θ� ������ ������ǥ ����
		//SRT�� ���ϸ� cube�� ���������ϴ� ��ǥ , ���� �׳� world ��ǥ�� ���ϴ°Ÿ� ���
		//set position�� �̿��ؼ� 10,0�� ������ , ���������� �־����� , ������� ��ǥ�� ���ؾ��� 

		_parent->GetWorldMatrix().Invert();// �θ��� ���ÿ��� ���带 �ȴٸ� ���忡�� �θ� ��ǥ��� ���°� �����ұ� 
		

	}
	else
	{
		SetLocalPosition(worldPosition);
	}

}
