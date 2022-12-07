//빛의 3가지 종류.
// 정반사광(Specular Lighting): 빛이 반사된게 내눈에 얼마나 들어오느냐.
// 난반사광(Diffuse Lighting): 빛의 방향에 따라서 표면적으로 어떻게 분포될거냐?
// 환경광, 주변광(Ambient Light): 
// 가장 리얼한 빛을 표현하려면 환경광을 제대로 계산해야 하는데, 계산량이 너무 많아서 다 계산하는게  불가능에 가깝기 때문에 
// 통계에 가까운 공식으로 처리하거나, 그냥 상수값을 넣어버린다.
//그 외에도 확산광(Emissive Lighting, 전구같은 특정 광원에서 사방으로 퍼져나오는 빛) 같은 것도 있다.

struct LightingData
{
    float4 lightColor_; //빛 색.
    
    float4 lightingPos_; //조명 위치.
    float4 lightingDirection_; //조명 방향.
    float4 lightingInversedDirection_; //조명 역방향.
    
    
    float4 viewLightingPos_; //뷰행렬이 적용된 조명 위치.
    float4 viewLightingDirection_; //뷰행렬이 적용된 조명 방향.
    float4 viewLightingInversedDirection_; //뷰행렬이 적용된 조명 역방향.
};

cbuffer LightingDatas : register(b13)
{
    int lightingCount_; //조명 개수.
    LightingData lightings_[128]; //LightingData 모음. 최대 128개 제한.
};

float4 CalDiffuseLight(
    float4 _viewSpaceNormal, //뷰행렬이 적용된 오브젝트 표면 특정 지점의 법선벡터. 조명 계산은 뷰공간에서 진행해야 한다.
    LightingData _lightingData //
)
{
    //람베르트(Lambert) 모델. 
    // 람베르트 모델은 카메라가 어느 위치에 있든 상관없이, 카메라에 들어오는 모든 난반사광의 양은 같다고 가정한다.
    // 그래서 알아야 하는 변수는 조명의 위치와 조사각, 오브젝트 표면에서 수직으로 뻗어나온 법선벡터 이 세가지만 필요하다.
    
   
    
    
    float4 viewSpaceNormalVector = normalize(_viewSpaceNormal);
    //표면 법선벡터를 다시한번 정규화.
    
    float4 lightInvDirection = normalize(_lightingData.lightingInversedDirection_);
    //빛의 역방향 정규화.
    
    float4 diffuseLighting = max(0.f, dot(viewSpaceNormalVector.xyz, lightInvDirection.xyz));
    //내적값은 -1~1 범위로 나오는데 내적값이 음수가 되면 값을 그냥 0으로 바꿔버린다.
    
    diffuseLighting *= _lightingData.lightColor_;
    //빛 색 적용.
    
    diffuseLighting.a = 1.f;
    //어떤 색상값이 나오든 알파값이 0이면 보이지 않으므로 알파값을 1로 강제고정.
    
    
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