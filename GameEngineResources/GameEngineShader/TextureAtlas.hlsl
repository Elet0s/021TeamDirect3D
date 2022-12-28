#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"

struct Input
{
    //��������� ������ ���� �߿����� �ʴ�. ��ǲ ���̾ƿ��� ���� �� ��������� �����°��� ��Ȯ�� �˷��ָ� �ȴ�?
    //���� ���Ǹ� ���ؼ� �ǵ��� ������ ��ų ���̴�?
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD;
    
    uint index_ : SV_InstanceID; //�ν��Ͻ� �ĺ���ȣ.
};

struct Output
{
    //�ø�ƽ(semantic). GPU���� �˷��ִ�, �ش� ���� ����. GPU�� �ڵ����� ó���� �� �ִ� ������ ���̸� �ڵ����� ó�����ش�.
    float4 pos_ : SV_Position; //SV_Position: �� �ø�ƽ�� ���ؼ��� ���ؽ� ���̴����� ����� ���� ��ġ�� �����Ͷ������� ������ �� �ִ�.
    //SV�� System-Value semantic�� ���ڷ�, DirectX10�������� ���Ե�, �뵵�� ������ �־ GPU�� �ڵ����� ó���ϴ� �ø�ƽ Ű�����̴�.

    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.
};

cbuffer AtlasData : register(b1)
{
    float2 textureFramePos_;
    float2 textureFrameSize_;
    float4 pivotPos_;
}

Output TextureAtlas_VS(Input _input)
{
    Output newOutput = (Output) 0; //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.
    //HLSL�� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.

    _input.pos_ += pivotPos_;
    //�������� ������ǥ�� �Ǻ� ����ġ��ŭ �����Ѵ�.
    
    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP��� ����.
    
    
    newOutput.texcoord_.x = (_input.texcoord_.x * textureFrameSize_.x) + textureFramePos_.x;
    newOutput.texcoord_.y = (_input.texcoord_.y * textureFrameSize_.y) + textureFramePos_.y;
    
    return newOutput;
}

cbuffer PixelData: register(b0)
{
    float4 mulColor_;
    float4 plusColor_;
    float4 slice_;
};

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);

float4 TextureAtlas_PS(Output _input) : SV_Target0 //SV_Target[n]: n�� ����Ÿ�ٿ� ������� �����Ѵ�.
{

    if (_input.texcoord_.x < slice_.x)
    {
        clip(-1);
    }
    
    if (_input.texcoord_.y < slice_.y)
    {
        clip(-1);
    }
    
    float4 resultColor = (Tex.Sample(POINTCLAMP, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
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

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t13);

Output TextureAtlas_VSINST(Input _input)
{
    // _Input.Index => �ν��Ͻ� ���۸� ���ؼ� ����.
    // �ν��Ͻ� ���۸� ���ؼ� ����� �������� ���� ������ �ν��Ͻ� ���۸� �Ź� ���Ӱ� �����ؾ� �ϱ� �����̴�.
    
    Output result = (Output) 0;
    result.pos_ = mul(_input.pos_, Inst_TransformData[_input.index_].worldViewProjectionMatrix_);
    
    
    result.texcoord_ = (_input.texcoord_.x * Inst_AtlasData[_input.index_].textureFrameSize_.x)
        + Inst_AtlasData[_input.index_].textureFramePos_.x;
    result.texcoord_ = (_input.texcoord_.y * Inst_AtlasData[_input.index_].textureFrameSize_.y)
        + Inst_AtlasData[_input.index_].textureFramePos_.y;
    
    return result;
}
