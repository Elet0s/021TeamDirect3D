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
    Output newOutput = (Output) 0; //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.
    //HLSL�� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.

    float4 vertexPos = _input.pos_;
    
    vertexPos.x = -sin(radians(30.f)) * (vertexPos.y + 0.5f) + vertexPos.x;

    vertexPos.y = cos(radians(30.f)) * (vertexPos.y + 0.5f) - 0.5f;
    
    //_input.pos_ += pivotPos_;
    
    
    newOutput.pos_ = mul(vertexPos, worldViewProjectionMatrix_); //WVP��� ����.
    newOutput.texcoord_ = _input.texcoord_;
    //newOutput.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    //newOutput.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return newOutput;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 TextureShadow_PS(Output _input) : SV_Target0
{  
    float4 sampledColor = Tex.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 shadowColor = (float4) 0;
    
    if (sampledColor.a <= 0.f)
    {
        clip(-1);
    }
    else if (sampledColor.a >= 0.75f)
    {
        shadowColor.a = 0.75f;
    }
    else
    {
        shadowColor.a = sampledColor.a;
    }
    

    return shadowColor;
}