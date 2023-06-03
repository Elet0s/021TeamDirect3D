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
    //일반 float4x4를 그냥 넣으면 DirectX의 기본 설정인 열 중심의 전치된 행렬로 들어오므로,
    // 그걸 방지하기 위해 굳이 구조체를 만들어서 넣어준다.
    float4x4 matrix_;
};

StructuredBuffer<AnimationMatrix> ArrAnimationMatrix : register(t11);

// inout c++로 치면 레퍼런스
// float4&
void Skinning(inout float4 _Pos, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AnimationMatrix> _ArrMatrix)
{
    float4 CalPos = (float4) 0.0f;
    // _Weight[3] = 1.0f - _Weight[0] - _Weight[1] - _Weight[2];

    for (int i = 0; i < 4; ++i)
    {
        AnimationMatrix Mat = _ArrMatrix[_Index[i]];
        CalPos += _Weight[i] * mul(_Pos, Mat.matrix_);
    }

    _Pos = CalPos;
}

Output TextureAnimation_VS(Input _input)
{
    Output newOutput = (Output) 0;

    newOutput.POSITION = _input.POSITION;
    Skinning(newOutput.POSITION, _input.BLENDWEIGHT, _input.BLENDINDICES, ArrAnimationMatrix);
    newOutput.POSITION.w = 1.0f;
    newOutput.POSITION = mul(newOutput.POSITION, worldViewProjectionMatrix_);
    newOutput.TEXCOORD = _input.TEXCOORD;


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
    
    if (resultColor.a >= 1.f)
    {
        resultColor.a = 1.f;
    }

    return resultColor;
}