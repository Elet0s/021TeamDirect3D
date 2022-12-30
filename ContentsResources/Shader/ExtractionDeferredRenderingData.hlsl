#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "DeferredRenderingHeader.hlsli"
#include "LightHeader.hlsli"


struct Input
{
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    //uint instancingIndex_ : ROWINDEX; //�ν��Ͻ� �ε���. unsigned int �Ѱ��� ���. �� �̻� �ʿ� ����.
    uint instanceIndex_ : SV_InstanceID; //�ν��Ͻ� �ĺ���ȣ.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //�ν��Ͻ����� ����� �÷��ؽ�ó ��ȣ.
    uint normalMapTextureIndex_ : NORMALTEXTUREINDEX; //�ν��Ͻ����� ����� �븻���ؽ�ó ��ȣ.
};

struct Output
{
    float4 wvpPosition_ : SV_Position;
    float4 projSpacePosition_ : POSITION1;   //������ȯ ������ ������Ʈ ��ġ. 
    float4 viewPosition_ : POSITION2;
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
    //uint instancingIndex_ : ROWINDEX; �ʿ� ����.
    uint colorTextureIndex_ : COLORTEXTUREINDEX; //�ν��Ͻ����� ����� �÷��ؽ�ó ��ȣ.
    uint normalMapTextureIndex_ : NORMALTEXTUREINDEX; //�ν��Ͻ����� ����� �븻���ؽ�ó ��ȣ.
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

struct InstAtlasData     //�ν��Ͻ̿� ��Ʋ�󽺵�����.
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
    //������ wvp��ȯ ��ġ ���.
    
    result.projSpacePosition_ = result.wvpPosition_;
    
    result.viewPosition_ = mul(_input.localPosition_, Inst_TransformData[_input.instanceIndex_].worldViewMatrix_);
    //������ ����������� ��ġ ��� �� ����.
    
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
    
    //�븻�ؽ�ó���� �븻���� ����.
    
    //2D�� �α����׽þ� Ư���� �亯ȯ�� �ʿ��� ��ҵ� �߿� ī�޶� ����� ��ġZ���� �����̰� 
    //ī�޶�� ���� ��� ������ �ٸ� ������������ ���� �����Ƿ� ������ �������Ϳ� �亯ȯ�� ���� �ʾƵ� �� �� ����.
    //�亯ȯ�� ���� �ʴ� ��� �������� x, y�� ��ȣ�� �ٲ��־�� ����� �� ���ݻ籤 ����� �Ǵ� ������ �븻�ؽ�ó�� ����Ǿ� �����Ƿ� �������ش�.
    
    result.viewPosition_ = _input.viewPosition_;
    
    
    result.objectDepth_ = float4(1.f, 0.f, 0.f, 1.f);
    if (0.01f < result.color_.a)
    {
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    
    return result;
}