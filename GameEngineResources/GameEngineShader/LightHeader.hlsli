//���� 3���� ����.
// ���ݻ籤(Specular Lighting): ���� �ݻ�Ȱ� ������ �󸶳� ��������.
// ���ݻ籤(Diffuse Lighting): ���� ���⿡ ���� ǥ�������� ��� �����ɰų�?
// ȯ�汤, �ֺ���(Ambient Light): 
// ���� ������ ���� ǥ���Ϸ��� ȯ�汤�� ����� ����ؾ� �ϴµ�, ��귮�� �ʹ� ���Ƽ� �� ����ϴ°�  �Ұ��ɿ� ������ ������ 
// ��迡 ����� �������� ó���ϰų�, �׳� ������� �־������.
//�� �ܿ��� Ȯ�걤(Emissive Lighting, �������� Ư�� �������� ������� ���������� ��) ���� �͵� �ִ�.

struct LightingData
{
    float4 lightColor_; //�� ��.
    
    float4 lightingPos_; //���� ��ġ.
    float4 lightingDirection_; //���� ����.
    float4 lightingInversedDirection_; //���� ������.
    
    
    float4 viewLightingPos_; //������� ����� ���� ��ġ.
    float4 viewLightingDirection_; //������� ����� ���� ����.
    float4 viewLightingInversedDirection_; //������� ����� ���� ������.
};

cbuffer LightingDatas : register(b13)
{
    int lightingCount_; //���� ����.
    LightingData lightings_[128]; //LightingData ����. �ִ� 128�� ����.
};

float4 CalDiffuseLight(
    float4 _viewSpaceNormal, //������� ����� ������Ʈ ǥ�� Ư�� ������ ��������. ���� ����� ��������� �����ؾ� �Ѵ�.
    LightingData _lightingData //
)
{
    //������Ʈ(Lambert) ��. 
    // ������Ʈ ���� ī�޶� ��� ��ġ�� �ֵ� �������, ī�޶� ������ ��� ���ݻ籤�� ���� ���ٰ� �����Ѵ�.
    // �׷��� �˾ƾ� �ϴ� ������ ������ ��ġ�� ���簢, ������Ʈ ǥ�鿡�� �������� ����� �������� �� �������� �ʿ��ϴ�.
    
   
    
    
    float4 viewSpaceNormalVector = normalize(_viewSpaceNormal);
    //ǥ�� �������͸� �ٽ��ѹ� ����ȭ.
    
    float4 lightInvDirection = normalize(_lightingData.lightingInversedDirection_);
    //���� ������ ����ȭ.
    
    float4 diffuseLighting = max(0.f, dot(viewSpaceNormalVector.xyz, lightInvDirection.xyz));
    //�������� -1~1 ������ �����µ� �������� ������ �Ǹ� ���� �׳� 0���� �ٲ������.
    
    diffuseLighting *= _lightingData.lightColor_;
    //�� �� ����.
    
    diffuseLighting.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ��������.
    
    
    return diffuseLighting;
}

float4 CalAllDiffuseLight(float4 _viewSpaceNormal)
{
    float4 diffuseLighting = (float4) 0;
    
    for (int i = 0; i < lightingCount_; ++i)
    {
        diffuseLighting += CalDiffuseLight(_viewSpaceNormal, lightings_[i]);
    }
    
    return diffuseLighting;
}