#include "TransformHeader.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    float4 pos_ : SV_Position;
    float4 texcoord_ : TEXCOORD;
};

//cbuffer AtlasData : register(b1)
//{
//    float2 textureFramePos_;
//    float2 textureFrameSize_;
//    float4 pivotPos_;
//}

Output TextureShadow_VS(Input _input)
{
    Output newOutput = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.
    //HLSL의 경우에는 대부분의 상황에서 형변환이 가능하다.

    float4 vertexPos = _input.pos_;
    
    vertexPos.x = -sin(radians(45.f)) * (vertexPos.y + 0.5f) + vertexPos.x;

    vertexPos.y = cos(radians(45.f)) * (vertexPos.y + 0.5f) - 0.5f;
    
    //_input.pos_ += pivotPos_;
    
    
    newOutput.pos_ = mul(vertexPos, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    //newOutput.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    //newOutput.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    
    
    
    
    return newOutput;
}

//Texture2D Tex : register(t0);
//SamplerState LINEARCLAMP : register(s0);

cbuffer ShadowColor : register(b8)
{
    float4 color_;
}

float4 TextureShadow_PS(Output _input) : SV_Target0
{  
    //if (Tex.Sample(LINEARCLAMP, _input.texcoord_.xy).a <= 0.f)
    //{
    //    clip(-1);
    //}
    //else
    //{
        return color_;
    //}
}