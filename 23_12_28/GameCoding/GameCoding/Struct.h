#pragma once
#include "Types.h"
// 공용으로 사용할 Struct  

//struct Vertex
//{
//	Vec3 position; // vector3 
//	//Color color; // RGB 
//	Vec2 uv; // uv 좌표 float 2개 
//	// 내가 해당하는 texture의 퍼센티지같은느낌 
//
//
//};

struct TransformData
{

	// 모두 항등 행렬로 초기화 
	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;



	//
	// 이게 constant buffer를 만들때는 16바이트 정렬을 해야되서 더미로 쓰레기값넣기 
};