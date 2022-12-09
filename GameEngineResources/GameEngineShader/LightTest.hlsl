#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    //��������� ������ ���� �߿����� �ʴ�. ��ǲ ���̾ƿ��� ���� �� ��������� �����°��� ��Ȯ�� �˷��ָ� �ȴ�.
    //���� ���Ǹ� ���ؼ� �ǵ��� ������ ��ų ���̴�.
    float4 pos_ : POSITION;
    float4 normal_ : NORMAL;
};

struct Output
{
    float4 wvpPos_ : SV_Position;
    float4 viewSpacePos_ : POSITION;
    float4 viewSpaceNormal_ : NORMAL;
};

Output LightTest_VS(Input _input)
{
    Output newOutput = (Output) 0; //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.

    newOutput.wvpPos_ = mul(_input.pos_, worldViewProjectionMatrix_); //������ǥ�� WVP��� ����.
    
    newOutput.viewSpacePos_ = mul(_input.pos_, worldViewMatrix_); //������ǥ�� ������İ� ����ĸ� ����.
    
    _input.normal_.w = 0.f; //�Ʒ� ��꿡 �������� ���� ������ �ִ°��� ���� ���� w�� 0���� �����.
    
    newOutput.viewSpaceNormal_ = mul(_input.normal_, worldViewMatrix_); //�������Ϳ� ������İ� ����ĸ� ����.
    
    newOutput.viewSpaceNormal_.w = 0.f; //�������ʹ� �̵��� ����Ǹ� �ȵǴ� ���⺤���̹Ƿ� w�� 0���� �����.
    
    return newOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 color_;
}

float4 LightTest_PS(Output _input) : SV_Target0
{
    float4 specularLight = 0.f;
   
    float4 diffuseLight = CalAllDiffuseLight(_input.viewSpaceNormal_);
    
    if (diffuseLight.r > 0.f || diffuseLight.g > 0.f || diffuseLight.b > 0.f)
    {
        specularLight = CalAllSpecularLight(_input.viewSpacePos_, _input.viewSpaceNormal_);
        //���ݻ籤�� rgb���� �ϳ��� 0�� �������� ���ݻ籤�� ����Ѵ�.
        //�ȱ׷��� ������ �޸����� ���ư��� ī�޶� ���� ��ġ�� �ʴµ��� ���ݻ籤�� ��ģ��.
    }
   
    float4 ambientLight = CalAllAmbientLight();
    
    float4 resultLight = color_ * (diffuseLight + specularLight) + ambientLight;
    //float4 resultLight = color_ * diffuseLight + specularLight + ambientLight;
    
    resultLight.a = 1.f;
    
    return resultLight;
}