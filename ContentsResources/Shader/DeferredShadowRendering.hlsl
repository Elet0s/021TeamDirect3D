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
    float4 shadowPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output DeferredShadowRendering_VS(Input _input)
{
    Output result = (Output) 0;

    float4 vertexPos = _input.localPosition_;
    vertexPos += pivotPos_;
    vertexPos.x = (-sin(radians(shadowAngle_)) * (vertexPos.y + 0.5f) + vertexPos.x) * vertexInversion_;
    //������Ʈ�� �¿�����Ǹ� -1�� ���ؼ� �׸��ڴ� �ٽ��ѹ� �¿������Ų��.

    vertexPos.y = cos(radians(shadowAngle_)) * (vertexPos.y + 0.5f) - 0.5f;
    
    result.wvpPosition_ = mul(vertexPos, worldViewProjectionMatrix_); //WVP��� ����.
    
    result.shadowPosition_ = result.wvpPosition_;
    
    if (-1 == vertexInversion_)
    {
        _input.texcoord_.x = 1.f - _input.texcoord_.x;
        //������Ʈ�� �¿�����Ǹ� texcoord�� �¿�����ؼ� �׷����� �Ѵ�.
    }
    
    result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return result;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 DeferredShadowRendering_PS(Output _input) : SV_Target0
{
    float4 sampledColor = Tex.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 shadowDepth = float4(1.f, 0.f, 0.f, 1.f);
    
    if (0.0f < sampledColor.a)
    {
        shadowDepth = float4(_input.shadowPosition_.z / _input.shadowPosition_.w, 0.f, 0.f, 1.f);
        //��� �������� Ư���� w�� 1 �����̹Ƿ� �� �ǹ̾��� ���������� �׷��� �Ѵ�.
    }
    else
    {
        clip(-1);
    }
    
    return shadowDepth;
}