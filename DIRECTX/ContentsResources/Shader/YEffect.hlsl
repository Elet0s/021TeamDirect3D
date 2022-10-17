// #include "myshader.hlsli"
#include "..\..\GameEngineResources\GameEngineShader\RenderOption.fx"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.



struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};


struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};


// �׷���ī�忡�� �̷����°�.
Output YEffect_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001
Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 YEffect_PS(Output _Input) : SV_Target0
{
    // ���� �� ������?
    
    float4 Color = Tex.Sample(Smp, _Input.Tex.xy);
    
    float TempDeltaTime = SumDeltaTime;
    
    TempDeltaTime = clamp(TempDeltaTime, 0.0f, 1.0f);
    
    if (_Input.Tex.y > sin(TempDeltaTime))
    {
        clip(-1);
    }
    
    return Color;
}
