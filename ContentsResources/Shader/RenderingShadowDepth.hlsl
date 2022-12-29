#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    uint instanceIndex_ : SV_InstanceID; //인스턴스 식별번호.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //텍스처 인덱스. 인스턴스별로 사용할 텍스처 번호.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 shadowPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //텍스처 인덱스. 인스턴스별로 사용할 텍스처 번호.
};

//cbuffer PixelData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

Output RenderingShadowDepth_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

SamplerState POINTCLAMP : register(s0);

float4 RenderingShadowDepth_PS(Output _input) : SV_Target0
{
    float4 resultColor = (1.f, 0.f, 0.f, 1.f);
    
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

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
Texture2DArray Inst_Textures : register(t14);  
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);

Output RenderingShadowDepth_VSINST(Input _input)
{
    Output result = (Output) 0;
    
    
    float4 vertexPos = _input.localPosition_;
    vertexPos += Inst_AtlasData[_input.instanceIndex_].pivotPos_;
    vertexPos.x = (-sin(radians(Inst_RenderOption[_input.instanceIndex_].shadowAngle_)) * (vertexPos.y + 0.5f) + vertexPos.x);
    vertexPos.y = cos(radians(Inst_RenderOption[_input.instanceIndex_].shadowAngle_)) * (vertexPos.y + 0.5f) - 0.5f;

    
    result.wvpPosition_ 
        = mul(vertexPos, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
    
    result.shadowPosition_ = result.wvpPosition_;
    
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;

    result.colorTextureIndex_ = _input.colorTextureIndex_;
    
    return result;
}

float4 RenderingShadowDepth_PSINST(Output _input) : SV_Target0
{
    float4 sampledColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.colorTextureIndex_)
    );
    
    float4 shadowDepth = float4(1.f, 0.f, 0.f, 1.f);
  
    if (0.0f < sampledColor.a)
    {
        shadowDepth = float4(_input.shadowPosition_.z / _input.shadowPosition_.w, 0.f, 0.f, 1.f);
        //사실 직교투영 특성상 w가 1 고정이므로 별 의미없는 연산이지만 그래도 한다.
    }
    
    return shadowDepth;
}