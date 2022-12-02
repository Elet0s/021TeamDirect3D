#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    
    uint vertexIndex_ : ROWINDEX; //인스턴싱 데이터. unsigned int 한개만 사용.
    
    int instancingTextureIndex_ : INSTTEXTUREINDEX;
};

struct Output
{
    float4 pos_ : SV_Position; 
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    
    
    int instancingTextureIndex_ : INSTTEXTUREINDEX;
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

cbuffer PixelData : register(b0)
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

Output Test_VS(Input _input)
{
    Output result = (Output) 0;

    _input.pos_ += pivotPos_;
    
    result.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    
    result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return result;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 Test_PS(Output _input) : SV_Target0
{
    if (_input.texcoord_.x < slice_.x)
    {
        clip(-1);
    }
    
    if (_input.texcoord_.y < slice_.y)
    {
        clip(-1);
    }
    
    float4 resultColor = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
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
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t13);
Texture2DArray Inst_Textures : register(t14);

Output Test_VSINST(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.vertexIndex_].worldViewProjectionMatrix_);
    
    result.instancingTextureIndex_ = _input.instancingTextureIndex_;
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.vertexIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.vertexIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.vertexIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.vertexIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    return result;
}

float4 Test_PSINST(Output _input) : SV_Target0
{
    float4 resultColor = (float4) 0;
    
    //Texture2D instTexture = Inst_Textures[_input.instancingTextureIndex_];
    //
    //resultColor = (instTexture.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
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