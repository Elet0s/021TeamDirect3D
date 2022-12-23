#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint instancingIndex_ : ROWINDEX; //�ν��Ͻ� �ε���. unsigned int �Ѱ��� ���.
    uint textureIndex_ : TEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
};

struct Output
{
    float4 pos_ : SV_Position; 
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    int instancingIndex_ : ROWINDEX;
    uint textureIndex_ : TEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
};

//cbuffer PixelData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

Output Test_VS(Input _input)
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


float4 Test_PS(Output _input) : SV_Target0
{
    float4 resultColor = (1.f, 0.f, 0.f, 1.f);
    
    //if (_input.texcoord_.x < slice_.x)
    //{
    //    clip(-1);
    //}
    
    //if (_input.texcoord_.y < slice_.y)
    //{
    //    clip(-1);
    //}
    
    //float4 resultColor = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    //float4 resultColor = Tex.Sample(POINTCLAMP, _input.texcoord_.xy);
    
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

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
Texture2DArray Inst_Textures : register(t14);  
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);

Output Test_VSINST(Input _input)
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

float4 Test_PSINST(Output _input) : SV_Target0
{
    //Texture2D instTexture = Inst_Textures[testIndex]; Texture2D�� �ε����� ����� ����� �� �ִ�.
    
    float4 resultColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.textureIndex_)
    );
    
    //Texture2D temp = Inst_Textures[_input.textureIndex_];
    
    float4 temp2 = Inst_Textures.Load(int4(_input.texcoord_.xy, 1, 0));
    temp2.a = 1.f;
    
    //if (0.01f >= resultColor.a)
    //{
    //    clip(-1);
    //}
    //else if (1.f < resultColor.a)
    //{
    //    resultColor.a = 1.f;
    //}
    
    return temp2;
}