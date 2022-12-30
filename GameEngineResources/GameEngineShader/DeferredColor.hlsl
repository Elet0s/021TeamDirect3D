#include "TransformHeader.hlsli"
#include "LightHeader.hlsli"
#include "DeferredRenderingHeader.hlsli"

struct Input
{
    float4 localPosition_ : POSITION;
    float4 localNormal_ : NORMAL;
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 viewPosition_ : POSITION;
    float4 viewNormal_ : NORMAL;
};

//함수 이름과 파일명이 달라도 상관없지만 일단 통일시킨다.
Output DeferredColor_VS(Input _input)
{
    Output result = (Output) 0;

    result.wvpPosition_ = mul(_input.localPosition_, worldViewProjectionMatrix_);

    result.viewPosition_ = mul(_input.localPosition_, worldViewMatrix_);

    _input.localNormal_.w = 0.f;
    result.viewNormal_ = normalize(mul(_input.localNormal_, worldViewMatrix_));
    result.viewNormal_.w = 0.f;

    return result;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

DeferredRenderingOutput DeferredColor_PS(Output _input)
{
    DeferredRenderingOutput deferredResult = (DeferredRenderingOutput) 0;

    deferredResult.color_ = Color;
    deferredResult.viewPosition_ = _input.viewPosition_;
    deferredResult.viewNormal_ = _input.viewNormal_;
    deferredResult.viewNormal_.w = 1.f;
    
    deferredResult.objectDepth_ = float4(1.f, 0.f, 0.f, 1.f);

    return deferredResult;
}