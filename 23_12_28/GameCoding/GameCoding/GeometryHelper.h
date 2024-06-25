#pragma once



//기본적인 도형들 ( 사각형 , 삼각형 등등 ) 
//기본적은 도형을 그려주는 클래스 
class GeometryHelper
{
public:
	// 어떤형태로 만들어 줄지를 정해줘야한다
	static void CreateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry);


private:



};

