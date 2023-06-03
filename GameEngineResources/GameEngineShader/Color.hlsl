//HLSL(High-Level Shader Language): 
//그래픽카드 메모리에 저장된 특정 데이터에 대한 처리 방식을 GPU에 지시할 수 있는 셰이더 제작용 언어.

//셰이더 규칙0: 버텍스 셰이더는 "_VS + (",픽셀 셰이더는 "_PS + ("가 문자열내부에 포함되어있어야 한다.
//셰이더 규칙1: 셰이더파일명.hlsl 파일은 반드시 셰이더파일명_VS, 셰이더파일명_PS라는 이름의 
// 버텍스 셰이더, 픽셀 셰이더 한개씩만을 가질수 있다. 그리고 "셰이더파일명.hlsl" 이라는 이름으로 저장된다. 

#include "TransformHeader.hlsli"

struct Input
{
    //멤버변수간 순서는 전혀 중요하지 않다. 인풋 레이아웃을 통해 각 멤버변수의 오프셋값만 정확히 알려주면 된다.
    //단지 편의를 위해서 되도록 순서를 지킬 뿐이다.
    float4 pos_ : POSITION;
};

struct Output
{
    //시맨틱(semantic). GPU에게 알려주는, 해당 값의 종류. GPU가 자동으로 처리할 수 있는 종류의 값이면 자동으로 처리해준다.
    float4 pos_ : SV_Position;
    //SV_Position: 이 시맨틱을 통해서만이 버텍스 셰이더에서 변경된 정점 위치를 래스터라이저로 전달해 뷰포트변환이 이루어진다.
    //SV는 System-Value semantic의 약자로, DirectX10에서부터 도입된, 용도가 정해져 있어서 GPU가 자동으로 처리하는 시맨틱 키워드이다.   
    
};

Output Color_VS(Input _input)
{
    Output newOutput = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.
    
    //HLSL의 경우에는 대부분의 상황에서 형변환이 가능하다.

    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    

    return newOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 color_;
}


//버텍스 셰이더의 반환값은 웬만하면 자동으로 픽셀셰이더의 매개변수로 들어간다.
//건져낸 픽셀 숫자만큼 호출된다.
float4 Color_PS(Output _input) : SV_Target0
//SV_Target[n]: 이 셰이더를 거친 결과값이 n번 렌더타겟에 저장된다는 의미의 시맨틱.
{
    return color_;
    
  
    //원 그리기.
    //if (0.5f < length(_input.posLocal_.xy))
    //{
    //    clip(-1);
    //}
    
    //타원 그리기1.
    //if (0.5f < length(_input.pos2_.xy - f))
    //{
    //    clip(-1);
    //}
    //if (0.5f < length(_input.pos2_.xy + (float2)0.2f))
    //{
    //    clip(-1);
    //}
    
    
    //타원 그리기2.
    //if (0.5f < length(_input.pos2_.xy - float2(0.2f, 0.f)))
    //{
    //    clip(-1);
    //}
    //if (0.5f < length(_input.pos2_.xy + float2(0.2f, 0.f)))
    //{
    //    clip(-1);
    //}
    
    
  
    //if (_input.pos_.x < 675.f)  
    //{
    //    clip(-1);
    //}
    

}