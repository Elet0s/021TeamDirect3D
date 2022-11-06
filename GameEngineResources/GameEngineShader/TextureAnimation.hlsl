#include "TransformHeader.hlsli"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct AnimationMatrix
{
    float4x4 matrix_;
};

StructuredBuffer<AnimationMatrix> ArrAnimationMatrix : register(t11);

Output TextureAnimation_VS(Input _input)
{
    Output newOutput = (Output) 0;

    newOutput.POSITION = mul(_input.POSITION, ArrAnimationMatrix[_input.BLENDINDICES[0]].matrix_);
    newOutput.POSITION = mul(newOutput.POSITION, worldViewProjectionMatrix_);
    newOutput.TEXCOORD = newOutput.TEXCOORD;


    return newOutput;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 TextureAnimation_PS(Output _input) : SV_Target0
{
    float4 resultColor = DiffuseTexture.Sample(LINEARWRAP, _input.TEXCOORD.xy);

    if (resultColor.a <= 0.f)
    {
        clip(-1);
    }
    
    if (resultColor.a > 1.f)
    {
        resultColor.a = 1.f;
    }

    return resultColor;
}