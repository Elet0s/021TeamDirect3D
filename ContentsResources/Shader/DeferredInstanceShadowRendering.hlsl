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

Output DeferredInstanceShadowRendering_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

SamplerState POINTCLAMP : register(s0);

float4 DeferredInstanceShadowRendering_PS(Output _input) : SV_Target0
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

Output DeferredInstanceShadowRendering_VSINST(Input _input)
{
    Output result = (Output) 0;
    
    float4 vertexPos = _input.localPosition_;
    vertexPos += Inst_AtlasData[_input.instanceIndex_].pivotPos_;
    vertexPos.x = ((-sin(radians(Inst_RenderOption[_input.instanceIndex_].lightingRotationY_)) * (vertexPos.y + 0.5f) + vertexPos.x)) * Inst_RenderOption[_input.instanceIndex_].vertexInversion_;
    //정점좌표를 shadowAngle_만큼 기울여 준다.
    
    vertexPos.y = tan(radians(Inst_RenderOption[_input.instanceIndex_].lightingRotationX_)) * (vertexPos.y + 0.5f) - 0.5f;
    
    result.wvpPosition_ 
        = mul(vertexPos, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
     //정점의 wvp변환 위치 계산.
    
    result.shadowPosition_ = result.wvpPosition_;
    //그림자의 투영공간 내 위치 전달.
    
    if (-1 == Inst_RenderOption[_input.instanceIndex_].vertexInversion_)
    {
        _input.texcoord_.x = 1.f - _input.texcoord_.x;
        //오브젝트가 좌우반전되면 texcoord도 좌우반전해서 그려지게 한다.
    }
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    //인스턴스별 텍스처 uv좌표 계산.

    result.colorTextureIndex_ = _input.colorTextureIndex_;
    //텍스처 배열 내 컬러 텍스처 번호를 픽셀셰이더로 전달.
    
    return result;
}

float4 DeferredInstanceShadowRendering_PSINST(Output _input) : SV_Target0
{
    float4 sampledColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.colorTextureIndex_)
    );
    
    float4 shadowDepth = float4(1.f, 0.f, 0.f, 1.f);
    //그림자의 기본 깊이값을 1로 설정하여 가장 뒤로 가게 한다.
  
    if (0.0f < sampledColor.a)
    {
        shadowDepth = float4(_input.shadowPosition_.z / _input.shadowPosition_.w, 0.f, 0.f, 1.f);
        //그림자의 투영공간 내 z값을 깊이값으로 덮어 씌운다.
        //사실 직교투영이면 w가 1 고정이므로 필요없는 연산이지만 원근투영도 사용하므로 w로 나누어준다.
    }
    else
    {
        clip(-1);
    }
    
    return shadowDepth;
}