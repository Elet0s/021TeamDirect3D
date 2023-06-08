//���� 3���� ����.
// ���ݻ籤(Specular Light): ���� �ݻ�Ȱ� ������ �󸶳� ��������.
// ���ݻ籤(Diffuse Light): ���� ���⿡ ���� ǥ�������� ��� �����ɰų�?
// ȯ�汤, �ֺ���(Ambient Light): 
// ���� ������ ���� ǥ���Ϸ��� ȯ�汤�� ����� ����ؾ� �ϴµ�, ��귮�� �ʹ� ���Ƽ� �� ����ϴ°�  �Ұ��ɿ� ������ ������ 
// ��迡 ����� �������� ó���ϰų�, �׳� ������� �־������.
//�� �ܿ��� Ȯ�걤(Emissive Lighting, �������� Ư�� �������� ������� ���������� ��) ���� �͵� �ִ�.

struct LightingData
{
    float4 mainLightColor_; //�� ����� ����. ���ݻ籤, ���ݻ籤�� ����.
    float4 ambientLightColor_; //�ֺ��� ����.

    float specularLightRatio_; //���ݻ籤 ���� ����. 0~1.
    float diffuseLightRatio_; //���ݻ籤 ���� ����. 0~1.
    float ambientLightRatio_; //�ֺ��� ���� ����. 0~1.

    float specularLightExponent_; //���ݻ籤 ����. �� ��ġ�� Ŀ���� ���ݻ籤�� �ݻ�Ǵ� ������ �����ݺ�ʷ� �پ���.
	//�ݴ�� ������ �Ǹ� �� ������ ���ߴ� ��� ������ ���ݻ籤�� �����.
    
    //float4x4 lightingViewMatrix_; //������ �����.
    //float4x4 inverseLightingViewMatrix_; //������ ������� �����.
    
    //float4x4 lightingProjectionMatrix_; //������ �������.
    //float4x4 inverseLightingProjectionMatrix_; //������ ��������� �����.

	//float4x4 lightingViewProjectionMatrix_;	//������ ��, ���� �������.

    float4x4 cameraViewMatrix_; //ī�޶��� �����.
    float4x4 inverseCameraViewMatrix_; //ī�޶��� ������� �����.

    //float shadowRenderTargetWidth_; //�׸��� ����Ÿ�� ���α���.
    //float shadowRenderTargetHeight_; //�׸��� ����Ÿ�� ���α���.
    //float lightingViewFrustumNearZ_; //������ ���������� ����� z��.
    //float lightingViewFrustumFarZ_; //������ ���������� ����� z��.

    float4 lightingPosition_; //������� ���� ��ġ.
    float4 lightingDirection_; //������� ���� ����.
    float4 inverseLightingDirection_; //������� ���� ������.
	//���̴��� �� ���� ���� �� ���� ���� �� ������ �׷��� ������.

    float4 viewLightingPosition_; //����������� ���� ��ġ.
    float4 viewLightingDirection_; //����������� ���� ����.
    float4 inverseViewLightingDirection_; //����������� ���� ������.
    
    //float4 viewSpaceCameraPosition_; //ī�޶� ��ġ. 
    //����� ī�޶���ġ�� (0, 0, 0) ���� �ƴѰ�?
};

cbuffer AllLightingDatas : register(b13)
{
    int lightingCount_; //���� ����.
    LightingData lightings_[16]; //LightingData ����.
    //�����δ� 3�� ���Ϸ� �� �Ŷ� �����.
};

struct LightOutput
{
    float4 diffuseLight_ : SV_Target0;
    float4 specularLight_ : SV_Target1;
    float4 ambientLight_ : SV_Target2;
};


float4 CalSpecularLight(
    float4 _viewSpaceFocusPosition, //���� �����ִ� ������Ʈ ǥ���� ����� ���� ��ġ ����.
    float4 _viewSpaceNormalVector, //����������� ������Ʈ ǥ�� Ư�� ������ ��������. �� ����� ��������� �����ؾ� �Ѵ�.
    LightingData _lightingData //���������.
)
{
    float3 normalVector = normalize(_viewSpaceNormalVector.xyz);
    //������Ʈ ǥ�� �������͸� �ٽ��ѹ� ����ȭ.
    
    float3 lightingRevDirection = normalize(_lightingData.inverseViewLightingDirection_.xyz);
    //���� �����⺤�͸� �ٽ��ѹ� ����ȭ.
    
    float3 orthogonalProjectionVector = normalVector * dot(lightingRevDirection, normalVector);
    //�������Ϳ� ���� �����⺤���� �ڻ��ΰ�(��� ������)�� ���ؼ� ���翵���͸� �����.
    
    float3 reflectionAngle = normalize(2.f * orthogonalProjectionVector - lightingRevDirection);
    //���̸� �ι�� �ø� ���翵���Ϳ� ���� ���⺤�͸� ���ϸ�(== ���� �����⺤�͸� ����) ���� �ݻ簢���͸� ���� �� �ִ�.
    
    //float3 negEyeDirection = normalize(_lightingData.viewSpaceCameraPosition_.xyz - _viewSpaceFocusPosition.xyz);
    //ī�޶���ġ���Ϳ��� ���� �����ִ� ������ ��ġ���͸� ���� �ü� ������ ���͸� ���Ѵ�
    
    float3 negEyeDirection = normalize(-_viewSpaceFocusPosition.xyz);
    //����������� ī�޶� ��ġ�� (0, 0, 0)�̹Ƿ� ���� �����ִ� ��ġ������ ������ == �ü� ������ ����.
    
    float brightness = saturate(dot(reflectionAngle, negEyeDirection));
    //�ü� �����⺤�Ϳ� ���� �ݻ簢���͸� �����ϸ� ī�޶� ������ ���ݻ籤�� ��⸦ ���� �� �ִ�.
    //saturate(): �־��� ���� 0���� ������ 0����, 1���� ũ�� 1�� �ٲٴ� �Լ�.
    
    float4 specularLight = _lightingData.mainLightColor_ * pow(brightness, _lightingData.specularLightExponent_);
    //���ݻ籤�� ��⸦ ���� ������ specularLightExponent_��ŭ ������ ���� �� ����� ���󰪿� ���Ѵ�.
    //0~1 ���� ���� ������ ���� �� ���� 0�� ����� ���� ������ʷ� 0�� �� ����� ���� ���ڰ� �Ǽ� 
    // ��������� ���ݻ籤 ���� ������ �پ��°� ���� ȿ���� �����ش�.
    
    specularLight.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ��������.
    
    return specularLight * _lightingData.specularLightRatio_;
}

float4 CalAllSpecularLight(
    float4 _viewSpaceFocusPosition, //���� �����ִ� ������Ʈ ǥ���� ����� ���� ��ġ ����.
    float4 _viewSpaceNormalVector //����������� ������Ʈ ǥ�� Ư�� ������ ��������. �� ����� ��������� �����ؾ� �Ѵ�.
)
{
    float4 specularLight = (float4) 0.f;
    
    for (int i = 0; i < lightingCount_; ++i)
    {
        specularLight += CalSpecularLight(_viewSpaceFocusPosition, _viewSpaceNormalVector, lightings_[i]);
    }
    
    specularLight.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ��������.
    
    return specularLight;
}

//���ݻ籤 ���.
float4 CalDiffuseLight(
    float4 _viewSpaceNormalVector, //����������� ������Ʈ ǥ�� Ư�� ������ ��������. �� ����� ��������� �����ؾ� �Ѵ�.
    LightingData _lightingData //���������.
)
{
    //������Ʈ/����Ʈ(Lambert) ���ݻ籤 ��� ��. 
    //������Ʈ ���� ī�޶� ��� ��ġ�� �ֵ� �������, ī�޶� ������ ��� ���ݻ籤�� ���� ���ٰ� �����Ѵ�.
    //����ȭ�� ������Ʈ Ư�� ������ ���� �Ի簢�� �����Ϳ�, ���� ����ȭ�� �� ������ �������͸� ������ ���� ���ݻ籤�� �����̴�.
   
    float4 normalVector = normalize(_viewSpaceNormalVector);
    //������Ʈ ǥ�� �������͸� �ٽ��ѹ� ����ȭ.
    
    float4 lightingRevDirection = normalize(_lightingData.inverseViewLightingDirection_);
    //���� �����⺤�͸� �ٽ��ѹ� ����ȭ.
    
    float4 diffuseLight = max(0.f, dot(normalVector.xyz, lightingRevDirection.xyz));
    //�������� -1~1 ������ �����µ� �������� ������ �Ǹ� ���� �׳� 0���� �ٲ������.
    //max(): �־��� �� �� �� ū ���� ��ȯ�ϴ� �Լ�.
    
    diffuseLight *= _lightingData.mainLightColor_;
    //�� ����� ���� ����.
    
    diffuseLight.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ����.
    
    return diffuseLight * _lightingData.diffuseLightRatio_;
}

float4 CalAllDiffuseLight(float4 _viewSpaceNormal)
{
    float4 diffuseLighting = (float4) 0.f;
    
    for (int i = 0; i < lightingCount_; ++i)
    {
        diffuseLighting += CalDiffuseLight(_viewSpaceNormal, lightings_[i]);
    }
    diffuseLighting.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ����.
    
    return diffuseLighting;
}

//�ֺ��� ���.
float4 CalAmbientLight(LightingData _lightingData)
{
    return _lightingData.ambientLightColor_ * _lightingData.ambientLightRatio_;
}

float4 CalAllAmbientLight()
{
    float4 ambientLight = (float4) 0.f;
    
    for (int i = 0; i < lightingCount_; ++i)
    {
        ambientLight += CalAmbientLight(lightings_[i]);
    }
    
    ambientLight.a = 1.f;
    //� ������ ������ ���İ��� 0�̸� ������ �����Ƿ� ���İ��� 1�� ����.
    
    return ambientLight;
}

float3 CalTrueNormalVector(float3 _sampledNormal)
{
    float3 trueNormalVector = _sampledNormal * 2.f - 1.f;
        
    return normalize(trueNormalVector);
}