

struct VS_INPUT
{
					  // input layout �ۼ��Ҷ� �̸��̶� �����ִ� �̸�
	float4 position : POSITION; 
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION; //system value , ��� �ʼ������� �־���Ѵ� ����� (SV)
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

// ó���� VS INPUT���� ���´� 
// IA - VS - RS - PS - OM 
//VS�ܰ�� �� ������ �°Բ� ���� ������ �ϴ� �Ѿ�´� 
// �츮�� game.cpp���� �Ѱ���  ������ ���⿡ ���´ٴ� �ǹ� , �ٸ� ��� ���������� ���� 


cbuffer TransformData : register(b0)
{
	float4 offset;
}




VS_OUTPUT VS(VS_INPUT input) // �Լ� ���ϰ� �Լ��̸� �Լ� �Ķ���� ���� 
{
	// ��ġ�� ���õ� �κ��� �־��شٰ����ǰ� , ���� ���úκ� 
	VS_OUTPUT output;
	// �ϴ� ��ǲ �״�� �Ѱ��ֱ� 


	output.position = input.position + offset;
	output.uv = input.uv;
	//output.color = input.color;
	

	return output;
}


Texture2D texture0 : register(t0); 
							//t->Texture�� ���� 
SamplerState sampler0 : register(s0);
//������ �Ծ࿡���� �������� ��ȣ 

Texture2D texture1 : register(t1);




// VS���� ���ϰ����� ���°� ���⼭�� input���� ���´� 
float4 PS(VS_OUTPUT input) : SV_Target // �� ������� SV_Target�� ������ϴ� �� Ű���带 �ٿ�����Ѵ�
{
	//float4 color =
	//��� �ȼ�������� �����ϴ� �Լ� , ��������̶�� �����ϰ� �����غ���ȴ� 


	//�츮�� �־��� �� -> input.color 
	//return input.color;


	float4 color = texture1.Sample(sampler0, input.uv);
	//Sample�̶�� �Լ����̿��ؼ� sampler0���̶� input��uv�� �����ǳ��ش� 
	// texture0���� uv ��ǥ�� �����ͼ� �ű��ش��ϴ� ������ ���´ٶ�� ���� 



	return color;



}



// �����Ͽ� vertex shader �� pixel shader�� ���� �ִ°� �ո��� 