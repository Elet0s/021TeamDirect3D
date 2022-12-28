#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 clipPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

Output TextureShadow_VS(Input _input)
{
    Output result = (Output) 0.f;
    
    result.wvpPosition_ = mul(_input.localPosition_, worldViewProjectionMatrix_);
    result.clipPosition_ = mul(_input.localPosition_, worldViewProjectionMatrix_);
    
    return result;
}

float4 TextureShadow_PS(Output _input):SV_Target0
{
    return float4(_input.clipPosition_.z / _input.clipPosition_.w, 0.f, 0.f, 1.f);
}
