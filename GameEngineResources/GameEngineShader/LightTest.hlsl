#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    //멤버변수간 순서는 전혀 중요하지 않다. 인풋 레이아웃을 통해 각 멤버변수의 오프셋값만 정확히 알려주면 된다.
    //단지 편의를 위해서 되도록 순서를 지킬 뿐이다.
    float4 pos_ : POSITION;
    float4 normal_ : NORMAL;
};

struct Output
{
    float4 wvpPos_ : SV_Position;
    float4 viewSpacePos_ : POSITION;
    float4 viewSpaceNormal_ : NORMAL;
};

Output LightTest_VS(Input _input)
{
    Output newOutput = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.

    newOutput.wvpPos_ = mul(_input.pos_, worldViewProjectionMatrix_); //정점좌표에 WVP행렬 적용.
    
    newOutput.viewSpacePos_ = mul(_input.pos_, worldViewMatrix_); //정점좌표에 월드행렬과 뷰행렬만 적용.
    
    _input.normal_.w = 0.f; //아래 계산에 예상하지 못한 영향을 주는것을 막기 위해 w를 0으로 만든다.
    
    newOutput.viewSpaceNormal_ = mul(_input.normal_, worldViewMatrix_); //법선벡터에 월드행렬과 뷰행렬만 적용.
    
    newOutput.viewSpaceNormal_.w = 0.f; //법선벡터는 이동이 적용되면 안되는 방향벡터이므로 w를 0으로 만든다.
    
    return newOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 color_;
}

float4 LightTest_PS(Output _input) : SV_Target0
{
    float4 specularLight = 0.f;
   
    float4 diffuseLight = CalAllDiffuseLight(_input.viewSpaceNormal_);
    
    if (diffuseLight.r > 0.f || diffuseLight.g > 0.f || diffuseLight.b > 0.f)
    {
        specularLight = CalAllSpecularLight(_input.viewSpacePos_, _input.viewSpaceNormal_);
        //난반사광의 rgb값중 하나라도 0을 넘을때만 정반사광을 계산한다.
        //안그러면 조명이 뒷면으로 돌아가서 카메라에 빛이 비치지 않는데도 정반사광이 비친다.
    }
   
    float4 ambientLight = CalAllAmbientLight();
    
    float4 resultLight = color_ * (diffuseLight + specularLight) + ambientLight;
    //float4 resultLight = color_ * diffuseLight + specularLight + ambientLight;
    
    resultLight.a = 1.f;
    
    return resultLight;
}