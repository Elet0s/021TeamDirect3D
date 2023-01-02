#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "DeferredRenderingHeader.hlsli"
#include "LightHeader.hlsli"

struct Input
{
    //��������� ������ ���� �߿����� �ʴ�. ��ǲ ���̾ƿ��� ���� �� ��������� �����°��� ��Ȯ�� �˷��ָ� �ȴ�?
    //���� ���Ǹ� ���ؼ� �ǵ��� ������ ��ų ���̴�?
    float4 localPosition_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    //�ø�ƽ(semantic). GPU���� �˷��ִ�, �ش� ���� ����. GPU�� �ڵ����� ó���� �� �ִ� ������ ���̸� �ڵ����� ó�����ش�.
    float4 wvpPosition_ : SV_Position; //SV_Position: �� �ø�ƽ�� ���ؼ��� ���ؽ� ���̴����� ����� ���� ��ġ�� �����Ͷ������� ������ �� �ִ�.
    //SV�� System-Value semantic�� ���ڷ�, DirectX10�������� ���Ե�, �뵵�� ������ �־ GPU�� �ڵ����� ó���ϴ� �ø�ƽ Ű�����̴�.
    float4 viewPosition_ : POSITION1;
    float4 projSpacePosition_ : POSITION2; //������ȯ ������ ������Ʈ ��ġ. 
    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output DeferredRendering_VS(Input _input)
{
    Output result = (Output) 0; //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.
    //HLSL�� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.

    _input.localPosition_ += pivotPos_;
    //�������� ������ǥ�� �Ǻ� ����ġ��ŭ �����Ѵ�.
    
    result.viewPosition_ = mul(_input.localPosition_, worldViewMatrix_);
    
    result.wvpPosition_ = mul(_input.localPosition_, worldViewProjectionMatrix_); //WVP��� ����.
    
    result.projSpacePosition_ = result.wvpPosition_;
    
    result.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    result.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return result;
}

cbuffer PixelData : register(b0)
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

DeferredRenderingOutput DeferredRendering_PS(Output _input)
{
    //if (_input.texcoord_.x < slice_.x)
    //{
    //    clip(-1);
    //}
    
    //if (_input.texcoord_.y < slice_.y)
    //{
    //    clip(-1);
    //}
    
    DeferredRenderingOutput result = (DeferredRenderingOutput) 0.f;
    
    result.color_ = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    result.objectDepth_ = float4(1.f, 0.f, 0.f, 1.f);
    
    if (0.f >= result.color_.a)
    {
        clip(-1);
    }
    else if (1.f < result.color_.a)
    {
        result.color_.a = 1.f;
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    else
    {
        result.objectDepth_ = float4(_input.projSpacePosition_.z / _input.projSpacePosition_.w, 0.f, 0.f, 1.f);
    }
    
    result.viewNormal_ = float4(-0.5773f, 0.5773f, -0.5773f, 1.f);
    //if (-1 != _input.normalMapTextureIndex_)
    //{
    //    result.viewNormal_ = normalize(
    //        CalTrueNormalVector(Inst_Textures.Sample(
    //                POINTCLAMP,
    //                float3(_input.texcoord_.xy, _input.normalMapTextureIndex_)
    //            )
    //        )
    //    );
    
    //    result.viewNormal_ = float4(-result.viewNormal_.x, -result.viewNormal_.y, result.viewNormal_.z, 1.f);
    //}
    
    result.viewPosition_ = _input.viewPosition_;
     
    return result;
}