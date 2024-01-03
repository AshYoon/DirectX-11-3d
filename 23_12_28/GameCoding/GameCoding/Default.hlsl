

struct VS_INPUT
{
					  // input layout 작성할때 이름이랑 맞춰주는 이름
	float4 position : POSITION; 
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION; //system value , 얘는 필수적으로 있어야한다 라고명시 (SV)
	float4 color : COLOR;
};

// 처음에 VS INPUT으로 들어온다 
// IA - VS - RS - PS - OM 
//VS단계는 이 포멧이 맞게끔 가야 도형이 일단 넘어온다 
// 우리가 game.cpp에서 넘겨준  값들이 여기에 들어온다는 의미 , 다만 얘는 정점단위로 실행 

VS_OUTPUT VS(VS_INPUT input) // 함수 리턴값 함수이름 함수 파라미터 형식 
{
	// 위치와 관련된 부분을 넣어준다고보면되고 , 정점 관련부분 
	VS_OUTPUT output;
	// 일단 인풋 그대로 넘겨주기 


	output.position = input.position;
	output.color = input.color;
	

	return output;
}

// VS에서 리턴값으로 들어온게 여기서은 input으로 들어온다 
float4 PS(VS_OUTPUT input) : SV_Target // 이 결과물을 SV_Target에 쏴줘야하니 이 키워드를 붙여줘야한다
{
	//float4 color =
	//모든 픽셀대상으로 실행하는 함수 , 색상관련이라고 간단하게 생각해보면된다 


	//우리가 넣어준 색 -> input.color 
	return input.color;

}



// 한파일에 vertex shader 랑 pixel shader랑 같이 넣는게 합리적 