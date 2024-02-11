

struct VS_INPUT
{
					    // input layout 작성할때 이름이랑 맞춰주는 이름
	float4 position : POSITION; 
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION; //system value , 얘는 필수적으로 있어야한다 라고명시 (SV)
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};


// 처음에 VS INPUT으로 들어온다 
// IA - VS - RS - PS - OM 
//VS단계는 이 포멧이 맞게끔 가야 도형이 일단 넘어온다 
// 우리가 game.cpp에서 넘겨준  값들이 여기에 들어온다는 의미 , 다만 얘는 정점단위로 실행 



cbuffer TransformData : register(b0)
{
	//float4 offset;
	// float 을 받아주는게아니라 TransformData의 WVP 를 받아와준다 그걸 상수Buffer에 넣어준다 
	
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProjection;
	

}



//행렬을 이용해서 cpu부담을 크게 줄인다 -> matrix를 쓰는 이유 
VS_OUTPUT VS(VS_INPUT input) //함수 리턴값 함수이름 함수 파라미터 형식 
{
	// 위치와 관련된 부분을 넣어준다고보면되고 , 정점 관련부분 
    VS_OUTPUT output;

	
	//WVP , 이것도 cpu에서 한번에 계산해서 넘겨줄수도있다.
    float4 position = mul(input.position, matWorld); //W 
    position = mul(position, matView); // V 
    position = mul(position, matProjection); // P 
	
	
	// 일단 인풋 그대로 넘겨주기
    output.position = position;
    output.uv = input.uv;
	//output.color = input.color;
	

	return output;
}

Texture2D texture0 : register(t0);
							//t->Texture의 약자 
SamplerState sampler0 : register(s0);
//정해진 규약에따른 레지스터 번호 

Texture2D texture1 : register(t1);




// VS에서 리턴값으로 들어온게 여기서은 input으로 들어온다 
float4 PS(VS_OUTPUT input) : SV_Target // 이 결과물을 SV_Target에 쏴줘야하니 이 키워드를 붙여줘야한다
{
	//float4 color =
	//��� �ȼ�������� �����ϴ� �Լ� , ��������̶�� �����ϰ� �����غ���ȴ� 


	//�츮�� �־��� �� -> input.color 
	//return input.color;


	float4 color = texture1.Sample(sampler0, input.uv);
	//Sample이라는 함수를이용해서 sampler0번이랑 input의uv를 각각건네준다 
	// texture0번의 uv 좌표를 가져와서 거기해당하는 색상을 넣는 느낌 



	return color;



}



