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
		// 물체랑 연관성 있는 부분 

	// Scale Rotation Translation

	_localPosition.x += 0.001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3); // srt 중 s 먼저 ,scale vecotr에 따라 변화하는 행렬 생성
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y); // y , z 도 똑같이 x에 곱해줘서 변화하게 
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation; // 

	// 하지만 계층관점에서 부모를 들고있을떄 ,  
	if (HasParent())
	{
		//부모가있을때

		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal; // 직속 부모가 없을떄는 이게 world 행렬 
	}


	// 내가 들고있을 Scale Rotation Translation 
	// 
	// world 변환행렬이 
	// [ 1, 2, 3, 4]
	// [ 5, 6, 7, 8]
	// [ 9, 10, 11, 12]
	// [ 13, 14, 15, 16]
	//이렇게 있다고 가정할때 , 내 right vector를 어떻게 구할까 ? 
	//_right vector , world 기준  
	//matworld 에 구하는것도 방법이지만 
	// decompose를 통해 역으로 쪼갤수있다 근데 반환을 쿼터니언이라는 걸로 해준다 
	// 벡터로 관리하면 짐벌락현상이 일어나기때문에 쿼터니언으로 관리해야함 (gimbal lock) 
	Quaternion quat;


	_matWorld.Decompose(_scale , quat , _position );

	//quaternion으로 받았으니 다시 우리가쓰는 오일러방식으로 변환해줘야함 

	_rotation = ToEulerAngles(quat);

	// v [ x y z ? ] m , _matworld를 곱하는 2가지 방식 
	// TransformCoord 방식 -> normal 안붙은거 , 어떤 vector를 곱할때 xyz가있으면 마지막에 뭘 곱해주냐 차이 
	//TransformNormal 방식 두가지가 있다 , 위치 상관없고 방향만 구하는거면 Normal 방식 사용 
	_right = Vec3::TransformNormal(Vec3::Right, _matWorld);
	
	_up = Vec3::TransformNormal(Vec3::Up, _matWorld);

	_look = Vec3::TransformNormal(Vec3::Backward, _matWorld);//원래 forward 인데 오른손 좌표계라 반대로되어있음
	// 우리가 바라보는 방향이 0 , 0 , 1 이 backward로 되어있어서 라이브러리 수정하거나해야함 





	//children
	for (const shared_ptr<Transform>& child : _children)
		child->UpdateTransform();// 자식들도 update해줘야함 

	







}

void Transform::Scale(const Vec3& worldScale)
{

	if (HasParent())
	{
		//부모가 있다면 
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;

		scale.x /= worldScale.x;
		scale.y /= worldScale.y;
		scale.z /= worldScale.z;

		SetLocalScale(scale);
	}
	else
	{
		// 부모가 없다면
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
		//부모가 있을때 월드좌표 세팅
		//SRT를 곱하면 cube를 기준으로하는 좌표 , 만약 그냥 world 좌표를 구하는거면 쉬운데
		//set position을 이용해서 10,0을 했을때 , 계층구조를 넣었을떄 , 상대적인 좌표를 구해야함 

		_parent->GetWorldMatrix().Invert();// 부모의 로컬에서 월드를 안다면 월드에서 부모 좌표계로 가는건 어케할까 
		

	}
	else
	{
		SetLocalPosition(worldPosition);
	}

}
