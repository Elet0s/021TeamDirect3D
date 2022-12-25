//빛의 3가지 종류.
// 정반사광(Specular Light): 빛이 반사된게 내눈에 얼마나 들어오느냐.
// 난반사광(Diffuse Light): 빛의 방향에 따라서 표면적으로 어떻게 분포될거냐?
// 환경광, 주변광(Ambient Light): 
// 가장 리얼한 빛을 표현하려면 환경광을 제대로 계산해야 하는데, 계산량이 너무 많아서 다 계산하는게  불가능에 가깝기 때문에 
// 통계에 가까운 공식으로 처리하거나, 그냥 상수값을 넣어버린다.
//그 외에도 확산광(Emissive Lighting, 전구같은 특정 광원에서 사방으로 퍼져나오는 빛) 같은 것도 있다.

struct LightingData
{
    float4 mainLightColor_; //주 조명광 색상값. 정반사광, 난반사광에 적용.
    float4 ambientLightColor_; //주변광 색상값.

    float specularLightRatio_; //정반사광 적용 비율. 0~1.
    float diffuseLightRatio_; //난반사광 적용 비율. 0~1.
    float ambientLightRatio_; //주변광 적용 비율. 0~1.

    float specularLightExponent_; //정반사광 지수. 이 수치가 커지면 정반사광이 반사되는 면적이 제곱반비례로 줄어든다.
	//반대로 음수가 되면 이 조명이 비추는 모든 영역에 정반사광이 비춘다.
    
    float4x4 lightingViewMatrix_; //조명의 뷰행렬.
    float4x4 inverseLightingViewMatrix_; //조명의 뷰행렬의 역행렬.

    float4x4 lightingProjectionMatrix_; //조명의 투영행렬.
    float4x4 inverseLightingProjectionMatrix_; //조명의 투영행렬의 역행렬.

	//float4x4 lightingViewProjectionMatrix_;	//조명의 뷰, 투영 통합행렬.

    float4x4 cameraViewMatrix_; //카메라의 뷰행렬.
    float4x4 inverseCameraViewMatrix_; //카메라의 뷰행렬의 역행렬.

    float shadowRenderTargetWidth_; //그림자 렌더타겟 가로길이.
    float shadowRenderTargetHeight_; //그림자 렌더타겟 세로길이.
    float lightingViewFrustumNearZ_; //조명의 뷰프러스텀 근평면 z값.
    float lightingViewFrustumFarZ_; //조명의 뷰프러스텀 원평면 z값.

    float4 lightingPosition_; //월드공간 조명 위치.
    float4 lightingDirection_; //월드공간 조명 방향.
    float4 inverseLightingDirection_; //월드공간 조명 역방향.
	//셰이더가 이 값을 직접 쓸 일은 없을 것 같지만 그래도 보낸다.

    float4 viewLightingPosition_; //뷰공간에서의 조명 위치.
    float4 viewLightingDirection_; //뷰공간에서의 조명 방향.
    float4 inverseViewLightingDirection_; //뷰공간에서의 조명 역방향.
    
    //float4 viewSpaceCameraPosition_; //카메라 위치. 
    //뷰공간 카메라위치는 (0, 0, 0) 고정 아닌가?
};

cbuffer LightingDatas : register(b13)
{
    int lightingCount_; //조명 개수.
    LightingData lightings_[16]; //LightingData 모음.
    //실제로는 3개 이하로 쓸 거라 예상됨.
};


float4 CalSpecularLight(
    float4 _viewSpaceFocusPosition, //내가 보고있는 오브젝트 표면의 뷰공간 기준 위치 벡터.
    float4 _viewSpaceNormalVector, //뷰공간에서의 오브젝트 표면 특정 지점의 법선벡터. 빛 계산은 뷰공간에서 진행해야 한다.
    LightingData _lightingData //조명데이터.
)
{
    float3 normalVector = normalize(_viewSpaceNormalVector.xyz);
    //오브젝트 표면 법선벡터를 다시한번 정규화.
    
    float3 lightingRevDirection = normalize(_lightingData.inverseViewLightingDirection_.xyz);
    //조명 역방향벡터를 다시한번 정규화.
    
    float3 orthogonalProjectionVector = normalVector * dot(lightingRevDirection, normalVector);
    //법선벡터에 조명 역방향벡터의 코사인값(대신 내적값)을 곱해서 정사영벡터를 만든다.
    
    float3 reflectionAngle = normalize(2.f * orthogonalProjectionVector - lightingRevDirection);
    //길이를 두배로 늘린 정사영벡터에 조명 방향벡터를 더하면(== 조명 역방향벡터를 빼면) 빛의 반사각벡터를 구할 수 있다.
    
    //float3 negEyeDirection = normalize(_lightingData.viewSpaceCameraPosition_.xyz - _viewSpaceFocusPosition.xyz);
    //카메라위치벡터에서 내가 보고있는 지점의 위치벡터를 빼서 시선 역방향 벡터를 구한다
    
    float3 negEyeDirection = normalize(-_viewSpaceFocusPosition.xyz);
    //뷰공간에서의 카메라 위치는 (0, 0, 0)이므로 내가 보고있는 위치벡터의 역벡터 == 시선 역방향 벡터.
    
    float brightness = saturate(dot(reflectionAngle, negEyeDirection));
    //시선 역방향벡터와 빛의 반사각벡터를 내적하면 카메라에 들어오는 정반사광의 밝기를 구할 수 있다.
    //saturate(): 주어진 값이 0보다 작으면 0으로, 1보다 크면 1로 바꾸는 함수.
    
    float4 specularLight = _lightingData.mainLightColor_ * pow(brightness, _lightingData.specularLightExponent_);
    //정반사광의 밝기를 조명 정보의 specularLightExponent_만큼 제곱한 값을 주 조명광 색상값에 곱한다.
    //0~1 범위 값에 제곱을 많이 할 수록 0에 가까운 값은 제곱비례로 0에 더 가까운 작은 숫자가 되서 
    // 결과적으로 정반사광 적용 면적이 줄어드는것 같은 효과를 보여준다.
    
    specularLight.a = 1.f;
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 강제고정.
    
    return specularLight * _lightingData.specularLightRatio_;
}

float4 CalAllSpecularLight(
    float4 _viewSpaceFocusPosition, //내가 보고있는 오브젝트 표면의 뷰공간 기준 위치 벡터.
    float4 _viewSpaceNormalVector //뷰공간에서의 오브젝트 표면 특정 지점의 법선벡터. 빛 계산은 뷰공간에서 진행해야 한다.
)
{
    float4 specularLight = (float4) 0.f;
    
    for (int i = 0; i < lightingCount_; ++i)
    {
        specularLight += CalSpecularLight(_viewSpaceFocusPosition, _viewSpaceNormalVector, lightings_[i]);
    }
    
    specularLight.a = 1.f;
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 강제고정.
    
    return specularLight;
}

//난반사광 계산.
float4 CalDiffuseLight(
    float4 _viewSpaceNormalVector, //뷰공간에서의 오브젝트 표면 특정 지점의 법선벡터. 빛 계산은 뷰공간에서 진행해야 한다.
    LightingData _lightingData //조명데이터.
)
{
    //람베르트(Lambert) 난반사광 계산 모델. 
    // 람베르트 모델은 카메라가 어느 위치에 있든 상관없이, 카메라에 들어오는 모든 난반사광의 양은 같다고 가정한다.
    // 그래서 알아야 하는 변수는 조명의 위치와 조사각(빛의 입사각), 오브젝트 표면에서 수직으로 뻗어나온 법선벡터 이 세가지만 필요하다.
    
   
    
    
    float4 normalVector = normalize(_viewSpaceNormalVector);
    //오브젝트 표면 법선벡터를 다시한번 정규화.
    
    float4 lightingRevDirection = normalize(_lightingData.inverseViewLightingDirection_);
    //조명 역방향벡터를 다시한번 정규화.
    
    float4 diffuseLight = max(0.f, dot(normalVector.xyz, lightingRevDirection.xyz));
    //내적값은 -1~1 범위로 나오는데 내적값이 음수가 되면 값을 그냥 0으로 바꿔버린다.
    //max(): 주어진 두 값 중 큰 값만 반환하는 함수.
    
    diffuseLight *= _lightingData.mainLightColor_;
    //주 조명광 색상값 적용.
    
    diffuseLight.a = 1.f;
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 고정.
    
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
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 고정.
    
    return diffuseLighting;
}

//주변광 계산.
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
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 고정.
    
    return ambientLight;
}

float3 CalTrueNormalVector(float3 _sampledNormal)
{
    float3 trueNormalVector = _sampledNormal * 2.f - 1.f;
        
    return normalize(trueNormalVector);
}