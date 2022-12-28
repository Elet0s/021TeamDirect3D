#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    //멤버변수간 순서는 전혀 중요하지 않다. 인풋 레이아웃을 통해 각 멤버변수의 오프셋값만 정확히 알려주면 된다?
    //단지 편의를 위해서 되도록 순서를 지킬 뿐이다?
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD;
    
    uint index_ : SV_InstanceID; //인스턴스 식별번호.
};

struct Output
{
    //시맨틱(semantic). GPU에게 알려주는, 해당 값의 종류. GPU가 자동으로 처리할 수 있는 종류의 값이면 자동으로 처리해준다.
    float4 pos_ : SV_Position; //SV_Position: 이 시맨틱을 통해서만 버텍스 셰이더에서 변경된 정점 위치를 래스터라이저로 전달할 수 있다.
    //SV는 System-Value semantic의 약자로, DirectX10에서부터 도입된, 용도가 정해져 있어서 GPU가 자동으로 처리하는 시맨틱 키워드이다.

    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output TextureAtlas_VS(Input _input)
{
    Output newOutput = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.
    //HLSL의 경우에는 대부분의 상황에서 형변환이 가능하다.

    _input.pos_ += pivotPos_;
    //정점들의 로컬좌표를 피봇 보정치만큼 변경한다.
    
    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    
    newOutput.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    newOutput.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return newOutput;
}

cbuffer PixelData: register(b0)
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 TextureAtlas_PS(Output _input) : SV_Target0 //SV_Target[n]: n번 렌더타겟에 결과값을 저장한다.
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

Output TextureAtlas_VSINST(Input _input)
{
    // _Input.Index => 인스턴싱 버퍼를 통해서 전달.
    // 인스턴싱 버퍼를 통해서 행렬을 전달하지 않은 이유는 인스턴싱 버퍼를 매번 새롭게 정의해야 하기 때문이다.
    
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.index_].worldViewProjectionMatrix_);
    
    
    result.texcoord_ = (_input.texcoord_.x * Inst_AtlasData[_input.index_].textureFrameSize_.x)
        + Inst_AtlasData[_input.index_].textureFramePos_.x;
    result.texcoord_ = (_input.texcoord_.y * Inst_AtlasData[_input.index_].textureFrameSize_.y)
        + Inst_AtlasData[_input.index_].textureFramePos_.y;
    
    return result;
}
