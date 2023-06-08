#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

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

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output TextureShadow_VS(Input _input)
{
    Output newOutput = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.

    float4 vertexPos = _input.pos_;
    vertexPos += pivotPos_;
    vertexPos.x = (-sin(radians(lightingRotationY_)) * (vertexPos.y + 0.5f) + vertexPos.x) * vertexInversion_;
    //오브젝트가 좌우반전되면 -1을 곱해서 그림자는 다시한번 좌우반전시킨다.

    vertexPos.y = tan(radians(lightingRotationX_)) * (vertexPos.y + 0.5f) - 0.5f;
    
    newOutput.pos_ = mul(vertexPos, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    if (-1 == vertexInversion_)
    {
        _input.texcoord_.x = 1.f - _input.texcoord_.x;
        //오브젝트가 좌우반전되면 texcoord도 좌우반전해서 그려지게 한다.
    }
    
    newOutput.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    newOutput.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    //if (-1 == vertexInversion_)
    //{
    //    newOutput.texcoord_.x = 1.f - newOutput.texcoord_.x;
    //}
    //그림자가 한박자 늦게 움직이므로 사용 금지.
    
    return newOutput;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 TextureShadow_PS(Output _input) : SV_Target0
{
    float4 sampledColor = Tex.Sample(LINEARWRAP, _input.texcoord_.xy);
    float4 shadowColor = float4(0.f, 0.f, 0.f, 1.f);
    
    //if (sampledColor.a <= 0.f)
    //{
    //    clip(-1);
    //}
    //else if (sampledColor.a >= 0.75f)
    //{
    //    shadowColor.a = 0.75f;
    //}
    //else
    //{
    //    shadowColor.a = sampledColor.a;
    //}
    
    if (0.01f >= sampledColor.a)
    {
        clip(-1);
    }
    

    return shadowColor;
}