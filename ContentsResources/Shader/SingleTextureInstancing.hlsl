#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    uint instanceIndex_ : SV_InstanceID; //인스턴스 식별번호.
};

struct Output
{
    float4 pos_ : SV_Position;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    uint instanceIndex_ : SV_InstanceID; //인스턴스 식별번호.
};

//cbuffer PixelData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

Output SingleTextureInstancing_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 SingleTextureInstancing_PS(Output _input) : SV_Target0
{
    float4 resultColor = (float4)0;
    
    //if (_input.texcoord_.x < slice_.x)
    //{
    //    clip(-1);
    //}
    
    //if (_input.texcoord_.y < slice_.y)
    //{
    //    clip(-1);
    //}
    
    //float4 resultColor = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
    if (0.f >= resultColor.a)
    {
        clip(-1);
    }
    else if (1.f < resultColor.a)
    {
        resultColor.a = 1.f;
    }
    
    return resultColor;
}

struct InstAtlasData     //인스턴싱용 아틀라스데이터.
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
};

struct InstPixelData 
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
//Texture2DArray Inst_Textures : register(t14);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);
StructuredBuffer<InstPixelData> Inst_PixelData : register(t16);

Output SingleTextureInstancing_VSINST(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.instanceIndex_ = _input.instanceIndex_;
    
    return result;
}

float4 SingleTextureInstancing_PSINST(Output _input) : SV_Target0
{
    if (_input.texcoord_.x < Inst_PixelData[_input.instanceIndex_].slice_.x)
    {
        clip(-1);
    }
    
    if (_input.texcoord_.y < Inst_PixelData[_input.instanceIndex_].slice_.y)
    {
        clip(-1);
    }
    
    float4 resultColor = Tex.Sample(POINTCLAMP, _input.texcoord_.xy);
    resultColor *= Inst_PixelData[_input.instanceIndex_].mulColor_;
    resultColor += Inst_PixelData[_input.instanceIndex_].plusColor_;
    
    if (0.f >= resultColor.a)
    {
        clip(-1);
    }
    else if (1.f < resultColor.a)
    {
        resultColor.a = 1.f;
    }
    
    return resultColor;
}