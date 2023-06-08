#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint instanceIndex_ : SV_InstanceID; //�ν��Ͻ� �ĺ���ȣ.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 shadowPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
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

Output DeferredInstanceShadowRendering_VSINST(Input _input)
{
    Output result = (Output) 0;
    
    float4 vertexPos = _input.localPosition_;
    vertexPos += Inst_AtlasData[_input.instanceIndex_].pivotPos_;
    vertexPos.x = ((-sin(radians(Inst_RenderOption[_input.instanceIndex_].lightingRotationY_)) * (vertexPos.y + 0.5f) + vertexPos.x)) * Inst_RenderOption[_input.instanceIndex_].vertexInversion_;
    //������ǥ�� shadowAngle_��ŭ ��￩ �ش�.
    
    vertexPos.y = tan(radians(Inst_RenderOption[_input.instanceIndex_].lightingRotationX_)) * (vertexPos.y + 0.5f) - 0.5f;
    
    result.wvpPosition_ 
        = mul(vertexPos, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
     //������ wvp��ȯ ��ġ ���.
    
    result.shadowPosition_ = result.wvpPosition_;
    //�׸����� �������� �� ��ġ ����.
    
    if (-1 == Inst_RenderOption[_input.instanceIndex_].vertexInversion_)
    {
        _input.texcoord_.x = 1.f - _input.texcoord_.x;
        //������Ʈ�� �¿�����Ǹ� texcoord�� �¿�����ؼ� �׷����� �Ѵ�.
    }
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    //�ν��Ͻ��� �ؽ�ó uv��ǥ ���.

    result.colorTextureIndex_ = _input.colorTextureIndex_;
    //�ؽ�ó �迭 �� �÷� �ؽ�ó ��ȣ�� �ȼ����̴��� ����.
    
    return result;
}

float4 DeferredInstanceShadowRendering_PSINST(Output _input) : SV_Target0
{
    float4 sampledColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.colorTextureIndex_)
    );
    
    float4 shadowDepth = float4(1.f, 0.f, 0.f, 1.f);
    //�׸����� �⺻ ���̰��� 1�� �����Ͽ� ���� �ڷ� ���� �Ѵ�.
  
    if (0.0f < sampledColor.a)
    {
        shadowDepth = float4(_input.shadowPosition_.z / _input.shadowPosition_.w, 0.f, 0.f, 1.f);
        //�׸����� �������� �� z���� ���̰����� ���� �����.
        //��� ���������̸� w�� 1 �����̹Ƿ� �ʿ���� ���������� ���������� ����ϹǷ� w�� �������ش�.
    }
    else
    {
        clip(-1);
    }
    
    return shadowDepth;
}