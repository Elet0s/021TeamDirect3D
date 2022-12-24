#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "DeferredRenderingHeader.hlsli"
#include "LightHeader.hlsli"


struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    //uint instancingIndex_ : ROWINDEX; //인스턴싱 인덱스. unsigned int 한개만 사용. 더 이상 필요 없음.
    uint instanceIndex_ : SV_InstanceID; //인스턴싱 인덱스. unsigned int 한개만 사용.
    uint textureIndex_ : TEXTUREINDEX; //텍스처 인덱스. 인스턴스별로 사용할 텍스처 번호.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 viewPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.
    //uint instancingIndex_ : ROWINDEX; 필요 없음.
    uint textureIndex_ : TEXTUREINDEX; //텍스처 인덱스. 인스턴스별로 사용할 텍스처 번호.
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
    
    result.wvpPosition_ = mul(_input.localPosition_, Inst_TransformData[_input.instanceIndex_].worldViewProjectionMatrix_);
    //정점의 wvp변환 위치 계산.
    
    result.viewPosition_ = mul(_input.localPosition_, Inst_TransformData[_input.instanceIndex_].worldViewMatrix_);
    //정점의 뷰공간에서의 위치 계산 후 전달.
    
    result.texcoord_.x = (_input.texcoord_.x * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.x)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * Inst_AtlasData[_input.instanceIndex_].textureFrameSize_.y)
        + Inst_AtlasData[_input.instanceIndex_].textureFramePos_.y;
    result.texcoord_.z = 0.f;
    
    //result.instancingIndex_ = _input.instancingIndex_;
    
    result.textureIndex_ = _input.textureIndex_;
    
    return result;
}

DeferredRenderingOutput ExtractionDeferredRenderingData_PSINST(Output _input)
{
    DeferredRenderingOutput result = (DeferredRenderingOutput) 0.f;
    
    result.color_ = Inst_Textures.Sample(
        POINTCLAMP,
        float3(_input.texcoord_.xy, _input.textureIndex_)
    );
    
    result.normal_ = normalize(
            -CalTrueNormalVector(Inst_Textures.Sample(
                POINTCLAMP,
                float3(_input.texcoord_.xy, 1 /*<-나중에 인풋레이아웃이나 렌더옵션의 변수 인덱스로 변경*/)
            )
        )
    );
    //노말텍스처에서 노말벡터 추출.
    
    //2D인 로그제네시아 특성상 뷰변환에 필요한 요소들 중에 카메라 방향과 위치Z값은 고정이고 
    //직교투영으로 보고 있으므로 추출한 노말벡터에 뷰변환은 하지 않아도 될 것 같다.
    
    result.normal_.w = 1.f;
    //노말벡터는 방향벡터이므로 w를 0으로 만든다.
    
    result.position_ = _input.viewPosition_;
    
    
    return result;
}