#pragma once
#include "Types.h"
// �������� ����� Struct  

struct Vertex
{
	Vec3 position; // vector3 
	//Color color; // RGB 
	Vec2 uv; // uv ��ǥ float 2�� 
	// ���� �ش��ϴ� texture�� �ۼ�Ƽ���������� 


};

struct TransformData
{
	Vec3 offset;
	float dummy;
	// �̰� constant buffer�� ���鶧�� 16����Ʈ ������ �ؾߵǼ� ���̷� �����Ⱚ�ֱ� 
};