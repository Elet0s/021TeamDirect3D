#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint instancingIndex_ : ROWINDEX; //�ν��Ͻ� �ε���. unsigned int �Ѱ��� ���.
    uint textureIndex_ : TEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    uint instancingIndex_ : ROWINDEX;
    uint textureIndex_ : TEXTUREINDEX; //�ؽ�ó �ε���. �ν��Ͻ����� ����� �ؽ�ó ��ȣ.
};

Output MultiTexturesInstShadow_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

SamplerState POINTCLAMP : register(s0);

float4 MultiTexturesInstShadow_PS(Output _input) : SV_Target0
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

Output MultiTexturesInstShadow_VSINST(Input _input)
{
    Output result = (Output) 0;
    
    float4 vertexPos = _input.localPosition_;
    vertexPos += Inst_AtlasData[_input.instancingIndex_].pivotPos_;
    
    
    vertexPos.x = (-sin(radians(Inst_RenderOption[_input.instancingIndex_].shadowAngle_)) * (vertexPos.y + 0.5f) + vertexPos.x) * Inst_RenderOption[_input.instancingIndex_].vertexInversion_;
    //������Ʈ�� �¿�����Ǹ� -1�� ���ؼ� �׸��ڴ� �ٽ��ѹ� �¿������Ų��.

    vertexPos.y = cos(radians(Inst_RenderOption[_input.instancingIndex_].shadowAngle_)) * (vertexPos.y + 0.5f) - 0.5f;
    
    result.wvpPosition_ = mul(vertexPos, Inst_TransformData[_input.instancingIndex_].worldViewProjectionMatrix_);
    
    if (-1 == Inst_RenderOption[_input.instancingIndex_].vertexInversion_)
    {
        _input.texcoord_.x = 1.f - _input.texcoord_.x;
        //������Ʈ�� �¿�����Ǹ� texcoord�� �¿�����ؼ� �׷����� �Ѵ�.
    }
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instancingIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instancingIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.instancingIndex_ = _input.instancingIndex_;
    
    result.textureIndex_ = _input.textureIndex_;
    
    return result;
}

float4 MultiTexturesInstShadow_PSINST(Output _input) : SV_Target0
{
    float4 sampledColor = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.textureIndex_)
    );
    float4 shadowColor = float4(0.f, 0.f, 0.f, 1.f);
  
    if (0.01f >= sampledColor.a)
    {
        clip(-1);
    }
    
    return shadowColor;
}