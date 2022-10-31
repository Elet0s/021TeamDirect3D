#include "TransformHeader.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 tex_ : TEXCOORD;
};

struct Output
{
    float4 pos_ : SV_Position;
    float4 posLocal_ : POSITION;
    float4 tex_ : TEXCOORD;
};

Output Texture_VS(Input _input)
{
    Output newOutput = (Output) 0;
    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_);
    newOutput.posLocal_ = _input.pos_;
    newOutput.tex_ = _input.tex_;
    return newOutput;
}

cbuffer DebugInfo : register(b8)
{
    int4 type_;
    float4 color_;
}

Texture2D Tex : register(t0);
SamplerState POINTWRAP : register(s0);

float4 Texture_PS(Output _input) : SV_Target0
{
    float4 texColor = Tex.Sample(POINTWRAP, _input.tex_.xy);
    
    if (color_.a <= 0.f)
    {
        clip(-1);
    }
    
    return color_ * texColor;
}