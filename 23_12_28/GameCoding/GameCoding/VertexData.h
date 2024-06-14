#pragma once




struct VertexTextureData
{
	Vec3 position;

	Vec2 uv;
	// uv 좌표 float 2개 
	// 내가 해당하는 texture의 퍼센티지같은느낌 

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
	//이걸 id /key 값으로 받아서 동일한 id 에 대한 texture 값을 inputlayout으로 넣어도되는데
	// static vector로 만들어줘서 이 아이에 해당하는 묘사를 static으로 만들어준다는 컨셉으로 해도된다.
	//static이다보니 구현부를 CPP에 만들어줘야한다 
};



struct VertexColorData
{
	Vec3 position = { 0,0,0 };

	Color color = { 0,0,0,0 };// RGB 

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

