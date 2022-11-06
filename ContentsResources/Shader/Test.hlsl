#include "TransformHeader.hlsli"

struct Input
{
    float4 pos_ : POSITION;
};

struct Output
{
    float4 pos_ : SV_Position;
};

Output Test_VS(Input _input)
{
    Output newOutput = (Output) 0;
   
    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); 

    return newOutput;
}

cbuffer TestColor : register(b8)
{
    float4 color_;
}

float4 Test_PS(Output _input) : SV_Target0
{
    return color_;
}