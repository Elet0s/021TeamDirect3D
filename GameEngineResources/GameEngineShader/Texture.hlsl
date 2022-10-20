#include "TransformHeader.hlsli"

struct Input
{
    //��������� ������ ���� �߿����� �ʴ�. ��ǲ ���̾ƿ��� ���� �� ��������� �����°��� ��Ȯ�� �˷��ָ� �ȴ�??
    //���� ���Ǹ� ���ؼ� �ǵ��� ������ ��ų ���̴�??
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    //�ø�ƽ(semantic). GPU���� �˷��ִ�, �ش� ���� ����. GPU�� �ڵ����� ó���� �� �ִ� ������ ���̸� �ڵ����� ó�����ش�.
    float4 pos_ : SV_Position; //SV_Position: �� �ø�ƽ�� ���ؼ����� ���ؽ� ���̴����� ����� ���� ��ġ�� �����Ͷ������� ������ �� �ִ�.
    //SV�� System-Value semantic�� ���ڷ�, DirectX10�������� ���Ե�, �뵵�� ������ �־ GPU�� �ڵ����� ó���ϴ� �ø�ƽ Ű�����̴�.
    
    float4 posLocal_ : POSITION;    //���� ������ǥ(-0.5~0.5 ���� ��ǥ). 

    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: �ؽ����� UV���� �ǹ��ϴ� �ø�ƽ����. �ؽ�����ǥ�� ���ϴ� Texture Coordinate�� ���Ӹ�.

};

Output Texture_VS(Input _input)
{
    Output result = (Output) 0; //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.
    //HLSL�� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.

    result.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP��� ����.
    
    result.posLocal_ = _input.pos_; //WVP��� ������. ���� ������ǥ(-0.5~0.5 ���� ��ǥ) ����.
    
    result.texcoord_ = _input.texcoord_;
    
    return result;
}

//cbuffer ColorData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 Texture_PS(Output _input) : SV_Target0 //SV_Target[n]: n�� ����Ÿ�ٿ� ������� �����Ѵ�.
{   
    float4 resultColor = Tex.Sample(Smp, _input.texcoord_.xy);
    //float4 color = (Tex.Sample(Smp, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
    if (resultColor.a <= 0.f)
    {
        clip(-1);
    }

    return resultColor;
}