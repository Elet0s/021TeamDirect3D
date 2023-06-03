#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "DeferredRenderingHeader.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    //멤버변수간 순서는 전혀 중요하지 않다. 인풋 레이아웃을 통해 각 멤버변수의 오프셋값만 정확히 알려주면 된다?
    //단지 편의를 위해서 되도록 순서를 지킬 뿐이다?
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    //시맨틱(semantic). GPU에게 알려주는, 해당 값의 종류. GPU가 자동으로 처리할 수 있는 종류의 값이면 자동으로 처리해준다.
    float4 wvpPosition_ : SV_Position; //SV_Position: 이 시맨틱을 통해서만 버텍스 셰이더에서 변경된 정점 위치를 래스터라이저로 전달할 수 있다.
    //SV는 System-Value semantic의 약자로, DirectX10에서부터 도입된, 용도가 정해져 있어서 GPU가 자동으로 처리하는 시맨틱 키워드이다.
    float4 viewPosition_ : POSITION1;
    float4 projSpacePosition_ : POSITION2; //투영변환 이후의 오브젝트 위치. 
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output DeferredRendering_VS(Input _input)
{
    Output result = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.
    //HLSL의 경우에는 대부분의 상황에서 형변환이 가능하다.

    _input.localPosition_ += pivotPos_;
    //정점들의 로컬좌표를 피봇 보정치만큼 변경한다.
    
    result.viewPosition_ = mul(_input.localPosition_, worldViewMatrix_);
    
    result.wvpPosition_ = mul(_input.localPosition_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    result.projSpacePosition_ = result.wvpPosition_;
    
    result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return result;
}

cbuffer PixelData : register(b0)
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

DeferredRenderingOutput DeferredRendering_PS(Output _input)
{
    //if (_input.texcoord_.x < slice_.x)
    //{
    //    clip(-1);
    //}
    
    //if (_input.texcoord_.y < slice_.y)
    //{
    //    clip(-1);
    //}
    
    DeferredRenderingOutput result = (DeferredRenderingOutput) 0.f;
    
    result.color_ = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    result.objectDepth_ = float4(1.f, 0.f, 0.f, 1.f);
    
    if (0.f >= result.color_.a)
    {
        clip(-1);
    }
    else if (1.f < result.color_.a)
    {
        result.color_.a = 1.f;
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    else
    {
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    
    result.viewNormal_ = float4(-0.5773f, 0.5773f, -0.5773f, 1.f);
    
    result.viewPosition_ = _input.viewPosition_;
     
    return result;
}