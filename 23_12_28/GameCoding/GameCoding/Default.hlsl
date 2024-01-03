

struct VS_INPUT
{
					  // input layout �ۼ��Ҷ� �̸��̶� �����ִ� �̸�
	float4 position : POSITION; 
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION; //system value , ��� �ʼ������� �־���Ѵ� ����� (SV)
	float4 color : COLOR;
};

// ó���� VS INPUT���� ���´� 
// IA - VS - RS - PS - OM 
//VS�ܰ�� �� ������ �°Բ� ���� ������ �ϴ� �Ѿ�´� 
// �츮�� game.cpp���� �Ѱ���  ������ ���⿡ ���´ٴ� �ǹ� , �ٸ� ��� ���������� ���� 

VS_OUTPUT VS(VS_INPUT input) // �Լ� ���ϰ� �Լ��̸� �Լ� �Ķ���� ���� 
{
	// ��ġ�� ���õ� �κ��� �־��شٰ���ǰ� , ���� ���úκ� 
	VS_OUTPUT output;
	// �ϴ� ��ǲ �״�� �Ѱ��ֱ� 


	output.position = input.position;
	output.color = input.color;
	

	return output;
}

// VS���� ���ϰ����� ���°� ���⼭�� input���� ���´� 
float4 PS(VS_OUTPUT input) : SV_Target // �� ������� SV_Target�� ������ϴ� �� Ű���带 �ٿ�����Ѵ�
{
	//float4 color =
	//��� �ȼ�������� �����ϴ� �Լ� , ��������̶�� �����ϰ� �����غ���ȴ� 


	//�츮�� �־��� �� -> input.color 
	return input.color;

}



// �����Ͽ� vertex shader �� pixel shader�� ���� �ִ°� �ո��� 