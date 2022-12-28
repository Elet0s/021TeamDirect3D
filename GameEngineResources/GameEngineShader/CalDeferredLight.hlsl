#include "LightHeader.hlsli"
#include "DeferredRenderingHeader.hlsli"

struct Input
{
    float4 position_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    float4 position_ : SV_Position;
    float4 texcoord_ : TEXCOORD;
};

Output CalDeferredLight_VS(Input _input)
{
    Output result = (Output) 0;
    result.position_ = _input.position_;
    result.texcoord_ = _input.texcoord_;
    return result;
}

Texture2D PositionTexture : register(t0);
Texture2D NormalTexture : register(t1);
SamplerState POINTCLAMP : register(s0);

LightOutput CalDeferredLight_PS(Output _input)
{
    float4 position = PositionTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 normal = NormalTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    if (position.a <= 0.0f)
    {
        clip(-1);
    }
    
    normal.w = 0.0f;
    
    LightOutput result = (LightOutput) 0.0f;
    
    result.diffuseLight_ = CalAllDiffuseLight(normal);
    
    if (result.diffuseLight_.r > 0.f || result.diffuseLight_.g > 0.f || result.diffuseLight_.b > 0.f)
    {
        result.specularLight_ = CalAllSpecularLight(position, normal);
        //난반사광의 rgb값중 하나라도 0을 넘을때만 정반사광을 계산한다.
        //안그러면 조명이 뒷면으로 돌아가서 카메라에 빛이 비치지 않는데도 정반사광이 비친다.
    }
    else
    {
        result.specularLight_ = 0.f;
    }
    
    result.ambientLight_ = CalAllAmbientLight();

    
    return result;
}