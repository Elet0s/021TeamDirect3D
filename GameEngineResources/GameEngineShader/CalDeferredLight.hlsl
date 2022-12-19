#include "LightHeader.hlsli"
#include "DeferredHeader.hlsli"

struct Input
{
    float4 position_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    float4 position_ : SV_Position;
    float4 texcoord_ : TEXCOORD;
};


// �׷���ī�忡�� �̷����°�.
Output CalDeferredLight_VS(Input _input)
{
    Output result = (Output) 0;
    result.position_ = _input.position_;
    result.texcoord_ = _input.texcoord_;
    return result;
}

Texture2D PositionTexture : register(t0);
Texture2D NormalTexture : register(t1);
SamplerState POINTCLAMP : register(s0);

struct LightOutput
{
    float4 diffuseLight_ : SV_Target0;
    float4 specularLight_ : SV_Target1;
    float4 ambientLight_ : SV_Target2;
};

LightOutput CalDeferredLight_PS(Output _input)
{
    float4 position = PositionTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 normal = NormalTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    if (position.a <= 0.0f)
    {
        clip(-1);
    }
    
    normal.w = 0.0f;
    
    LightOutput result = (LightOutput) 0.0f;
    
    result.diffuseLight_ = CalAllDiffuseLight(normal);
    
    if (result.diffuseLight_.r > 0.f || result.diffuseLight_.g > 0.f || result.diffuseLight_.b > 0.f)
    {
        result.specularLight_ = CalAllSpecularLight(position, normal);
        //���ݻ籤�� rgb���� �ϳ��� 0�� �������� ���ݻ籤�� ����Ѵ�.
        //�ȱ׷��� ������ �޸����� ���ư��� ī�޶� ���� ��ġ�� �ʴµ��� ���ݻ籤�� ��ģ��.
    }
    else
    {
        result.specularLight_ = 0.f;
    }
    
    result.ambientLight_ = CalAllAmbientLight();

    
    return result;
}