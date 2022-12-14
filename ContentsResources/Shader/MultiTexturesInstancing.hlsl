#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    uint instancingIndex_ : ROWINDEX;   //인스턴싱 인덱스. unsigned int 한개만 사용.
    uint textureIndex_ : TEXTUREINDEX;  //텍스처 인덱스.
};

struct Output
{
    float4 pos_ : SV_Position;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    int instancingIndex_ : ROWINDEX;
    uint textureIndex_ : TEXTUREINDEX;
};

Output MultiTexturesInstancing_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

SamplerState POINTCLAMP : register(s0);

float4 MultiTexturesInstancing_PS(Output _input) : SV_Target0
{
    float4 resultColor = (float4) 0;
    
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

//struct InstPixelData 
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
Texture2DArray Inst_Textures : register(t14);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);
//StructuredBuffer<InstPixelData> Inst_PixelData : register(t16);

Output MultiTexturesInstancing_VSINST(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.instancingIndex_].worldViewProjectionMatrix_);
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.instancingIndex_ = _input.instancingIndex_;
    
    result.textureIndex_ = _input.textureIndex_;
    
    return result;
}

float4 MultiTexturesInstancing_PSINST(Output _input) : SV_Target0
{
    //if (_input.texcoord_.x < Inst_PixelData[_input.instancingIndex_].slice_.x)
    //{
    //    clip(-1);
    //}
    //
    //if (_input.texcoord_.y < Inst_PixelData[_input.instancingIndex_].slice_.y)
    //{
    //    clip(-1);
    //}
    
    //float4 resultColor = (Tex.Sample(
    //    POINTCLAMP,
    //    _input.texcoord_.xy)
    //* Inst_PixelData[_input.instancingIndex_].mulColor_)
    //+ Inst_PixelData[_input.instancingIndex_].plusColor_;
    
    float4 resultColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.textureIndex_)
    );
  
    if (0.01f >= resultColor.a)
    {
        clip(-1);
    }
    else if (1.f < resultColor.a)
    {
        resultColor.a = 1.f;
    }
    
    return resultColor;
}