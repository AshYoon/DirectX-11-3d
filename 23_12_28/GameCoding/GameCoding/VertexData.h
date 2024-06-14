#pragma once




struct VertexTextureData
{
	Vec3 position;

	Vec2 uv;
	// uv ��ǥ float 2�� 
	// ���� �ش��ϴ� texture�� �ۼ�Ƽ���������� 

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
	//�̰� id /key ������ �޾Ƽ� ������ id �� ���� texture ���� inputlayout���� �־�Ǵµ�
	// static vector�� ������༭ �� ���̿� �ش��ϴ� ���縦 static���� ������شٴ� �������� �ص��ȴ�.
	//static�̴ٺ��� �����θ� CPP�� ���������Ѵ� 
};



struct VertexColorData
{
	Vec3 position = { 0,0,0 };

	Color color = { 0,0,0,0 };// RGB 

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

