//윈도우창 전체를 커버하는 이 셰이더 특성상 "TransformHeader.hlsli"가 필요 없다.

struct Input
{
    float4 pos_ : POSITION;
    float4 tex_ : TEXCOORD;
};

struct Output
{
    float4 pos_ : SV_POSITION;
    float4 tex_ : TEXCOORD;
};

Output TargetMerge_VS(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = _input.pos_;
    result.tex_ = _input.tex_;
    return result;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 TargetMerge_PS(Output _input): SV_Target0
{
    float4 resultColor = Tex.Sample(Smp, _input.tex_.xy);

    if(resultColor.a <= 0.f)
    {
        clip(-1);
    }
    
    if (resultColor.a >= 1.f)
    {
        resultColor.a = 1.f;
    }
    
    return resultColor;
}