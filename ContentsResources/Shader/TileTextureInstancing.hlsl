#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint instancingIndex_ : ROWINDEX; //�ν��Ͻ� �ε���. unsigned int �Ѱ��� ���.
};

struct Output
{
    float4 pos_ : SV_Position;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    int instancingIndex_ : ROWINDEX;
};

//cbuffer PixelData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

Output TileTextureInstancing_VS(Input _input)
{
    Output result = (Output) 0;

    //_input.pos_ += pivotPos_;
    
    //result.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP��� ����.
    
    
    //result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    //result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    //result.instancingIndex_ = _input.instancingIndex_;
    
    return result;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 TileTextureInstancing_PS(Output _input) : SV_Target0
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

struct InstAtlasData     //�ν��Ͻ̿� ��Ʋ�󽺵�����.
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
//Texture2DArray Inst_Textures : register(t14);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);
//StructuredBuffer<InstPixelData> Inst_PixelData : register(t16);

Output TileTextureInstancing_VSINST(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.instancingIndex_].worldViewProjectionMatrix_);
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.instancingIndex_ = _input.instancingIndex_;
    
    return result;
}

float4 TileTextureInstancing_PSINST(Output _input) : SV_Target0
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
    
    float4 resultColor = Tex.Sample(
        POINTCLAMP,
        _input.texcoord_.xy
    );
  
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