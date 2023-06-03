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

Output Blur_VS(Input _input)
{
    Output result = (Output) 0;
    result.pos_ = _input.pos_;
    result.tex_ = _input.tex_;
    return result;
}

static float Gaussian[5][5] = 
{
    { 1.f, 4.f, 6.f, 4.f, 1.f },
    { 4.f, 16.f, 24.f, 16.f, 4.f },
    { 6.f, 24.f, 36.f, 24.f, 6.f},
    { 4.f, 16.f, 24.f, 16.f, 4.f },
    { 1.f, 4.f, 6.f, 4.f, 1.f }
};

cbuffer WindowScale : register(b0)
{
    float4 windowScale_;
}

Texture2D Tex : register(t0);
SamplerState POINTWRAP : register(s0);

float4 Blur_PS(Output _input) : SV_Target0
{
    float2 pixelUVSize = float2(1.f / windowScale_.x, 1.f / windowScale_.y);
    //float2 pixelUVSize = float2(1.f / 1280.f, 1.f / 720.f);
    float2 centerPixelUV = _input.tex_.xy;
    float2 startUV = centerPixelUV - (pixelUVSize * 2.f);
    float2 currentUV = startUV;
    
    float4 resultColor = (float4) 0.f;
    
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            resultColor += Tex.Sample(POINTWRAP, currentUV) * Gaussian[y][x];
            currentUV.x += pixelUVSize.x;
        }
        currentUV.x = startUV.x;
        currentUV.y += pixelUVSize.y;
    }
    
    resultColor /= 256.f;
    
    if (resultColor.a <= 0.f)
    {
        clip(-1);
    }
    
    return resultColor;
}