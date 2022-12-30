#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "DeferredRenderingHeader.hlsli"
#include "LightHeader.hlsli"


struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    //uint instancingIndex_ : ROWINDEX; //인스턴싱 인덱스. unsigned int 한개만 사용. 더 이상 필요 없음.
    uint instanceIndex_ : SV_InstanceID; //인스턴스 식별번호.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //인스턴스별로 사용할 컬러텍스처 번호.
    uint normalMapTextureIndex_ : NORMALTEXTUREINDEX; //인스턴스별로 사용할 노말맵텍스처 번호.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 projSpacePosition_ : POSITION1;   //투영변환 이후의 오브젝트 위치. 
    float4 viewPosition_ : POSITION2;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    //uint instancingIndex_ : ROWINDEX; 필요 없음.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //인스턴스별로 사용할 컬러텍스처 번호.
    uint normalMapTextureIndex_ : NORMALTEXTUREINDEX; //인스턴스별로 사용할 노말맵텍스처 번호.
};

Output ExtractionDeferredRenderingData_VS(Input _input)
{
    Output result = (Output) 0;
    
    return result;
}

SamplerState POINTCLAMP : register(s0);

float4 ExtractionDeferredRenderingData_PS(Output _input) : SV_Target0
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

struct InstAtlasData     //인스턴싱용 아틀라스데이터.
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
};

//struct InstPixelData 
//{
//    float4 mulColor_;
//    float4 plusColor_;
//    float4 slice_;
//};

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstRenderOption> Inst_RenderOption : register(t13);
Texture2DArray Inst_Textures : register(t14);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t15);
//StructuredBuffer<InstPixelData> Inst_PixelData : register(t16);

Output ExtractionDeferredRenderingData_VSINST(Input _input)
{
    Output result = (Output) 0;
    
    result.wvpPosition_ 
        = mul(_input.localPosition_, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
    //정점의 wvp변환 위치 계산.
    
    result.projSpacePosition_ = result.wvpPosition_;
    
    result.viewPosition_ = mul(_input.localPosition_, Inst_TransformData[_input.instanceIndex_].worldViewMatrix_);
    //정점의 뷰공간에서의 위치 계산 후 전달.
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    result.colorTextureIndex_ = _input.colorTextureIndex_;
    result.normalMapTextureIndex_ = _input.normalMapTextureIndex_;
    
    return result;
}

DeferredRenderingOutput ExtractionDeferredRenderingData_PSINST(Output _input)
{
    DeferredRenderingOutput result = (DeferredRenderingOutput) 0.f;
    
    result.color_ = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.colorTextureIndex_)
    );
    
    if (0.0f >= result.color_.a)
    {
        result.color_ = float4(0.f, 0.f, 0.f, 0.f);
    }
    
    result.viewNormal_ = normalize(
        CalTrueNormalVector(Inst_Textures.Sample(
                POINTCLAMP,
                float3(_input.texcoord_.xy, _input.normalMapTextureIndex_)
            )
        )
    );
    
    result.viewNormal_ = float4(-result.viewNormal_.x, -result.viewNormal_.y, result.viewNormal_.z, 1.f);
    
    //노말텍스처에서 노말벡터 추출.
    
    //2D인 로그제네시아 특성상 뷰변환에 필요한 요소들 중에 카메라 방향과 위치Z값은 고정이고 
    //카메라와 조명 모두 각도만 다른 직교투영으로 보고 있으므로 추출한 법선벡터에 뷰변환은 하지 않아도 될 것 같다.
    //뷰변환을 하지 않는 대신 법선벡터 x, y의 부호를 바꿔주어야 제대로 된 난반사광 계산이 되는 값들이 노말텍스처에 저장되어 있으므로 뒤집어준다.
    
    result.viewPosition_ = _input.viewPosition_;
    
    
    result.objectDepth_ = float4(1.f, 0.f, 0.f, 1.f);
    if (0.01f < result.color_.a)
    {
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    
    return result;
}