#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    
    uint index_ : ROWINDEX; //인스턴싱 데이터. unsigned int 한개만 사용.
};

struct Output
{
    float4 pos_ : SV_Position; 
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    int index_ : ROWINDEX;
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
    
    //result.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    
    //result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    //result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    result.index_ = _input.index_;
    
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


struct InstAtlasData     //인스턴싱용 아틀라스데이터.
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
};

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
//Texture2DArray Inst_Textures : register(t14); Texture2DArray는 반드시 같은 크기, 같은 포맷의 텍스처 여러장이어야 한다. 
//Texture2D Inst_Textures[36] : register(t14);

StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);

Output Test_VSINST(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.index_].worldViewProjectionMatrix_);
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.index_].textureFrameSize_.x)
        + Inst_AtlasData[_input.index_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.index_].textureFrameSize_.y)
        + Inst_AtlasData[_input.index_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.index_ = _input.index_;
    
    return result;
}

float4 Test_PSINST(Output _input) : SV_Target0
{
    //Texture2D instTexture = Inst_Textures[testIndex]; Texture2DArray는 uvw3차원 좌표 체계를 사용한다.
    
    //const uint instancingTextureIndex = Inst_RenderOption[_input.index_].bytePad1_;
    
    //Texture2D temp = Inst_Textures[instancingTextureIndex.x]; 상수 외엔 사용불가.
   
    //resultColor = (instTexture.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
    float4 resultColor = Tex.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    resultColor.a = Inst_RenderOption[_input.index_].shadowAngle_; //렌더옵션 전달 테스트용 임시코드. 나중에 반드시 지울 것.
  
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