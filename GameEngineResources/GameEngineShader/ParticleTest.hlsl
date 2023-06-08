#include "TransformHeader.hlsli"
#include "RenderOption.hlsli"
#include "LightHeader.hlsli"

struct ParticleInfo
{
    float4 position_;
    float4 scale_;
    float4 direction_;
    float4 color_;
    
    int isAlive_; //0: ��ƼŬ ��Ȱ��ȭ��. 1: ��ƼŬ Ȱ��ȭ��.
    
    float currentTime_; //
    float maxTime_;     //
};

StructuredBuffer<ParticleInfo> allParticleInfos : register(t16);

struct Input
{
    uint instanceIndex_ : SV_InstanceID;
};
    
struct Output
{
    uint instanceIndex_ : SV_InstanceID;
};

struct ParticleOutput
{
    float4 position_ : SV_Position;
    float4 texcoord_ : TEXCOORD;
    float4 viewPosition_ : POSITION;
    uint instanceIndex_ : SV_InstanceID;
};
    
Output ParticleTest_VS(Input _input)
{
    Output result = (Output) 0.f;
    
    result.instanceIndex_ = _input.instanceIndex_;
    //�ν��Ͻ� �νĹ�ȣ�� ����.
 
    return result;
}

[maxvertexcount(6)] //[maxvertexcount(int NumVerts)] NumVerts������ŭ�� ������ �����ϰڴٴ� ����.
void ParticleTest_GS(point Output _input[1], inout TriangleStream<ParticleOutput> _output)
{
    uint instanceIndex = _input[0].instanceIndex_;
    
    if (0 == allParticleInfos[instanceIndex].isAlive_)
    {
        return;
    }
     
    float4 particlePosition = float4(0.f, 0.f, 0.f, 1.f);
    
    particlePosition = allParticleInfos[instanceIndex].position_;
    
    float4 viewPosition = mul(particlePosition, viewMatrix_);
    
    float4 scale = allParticleInfos[instanceIndex].scale_;
    
    
    float4 arrRect[4] =
    {
        float4(viewPosition.x - (scale.x / 2.f), viewPosition.y + (scale.y / 2.f), viewPosition.z, 1.f),    //0�� ��.
        float4(viewPosition.x + (scale.x / 2.f), viewPosition.y + (scale.y / 2.f), viewPosition.z, 1.f),    //1�� ��.
        float4(viewPosition.x + (scale.x / 2.f), viewPosition.y - (scale.y / 2.f), viewPosition.z, 1.f),    //2�� ��.
        float4(viewPosition.x - (scale.x / 2.f), viewPosition.y - (scale.y / 2.f), viewPosition.z, 1.f)     //3�� ��.
    };
    
    ParticleOutput result[4] =
    {
        (ParticleOutput) 0.f,
        (ParticleOutput) 0.f,
        (ParticleOutput) 0.f,
        (ParticleOutput) 0.f
    };
    
    for (int i = 0; i < 4; ++i)
    {
        result[i].instanceIndex_ = _input[0].instanceIndex_;
        result[i].viewPosition_ = arrRect[i];
        result[i].position_ = mul(arrRect[i], projectionMatrix_);
    }
    
    result[0].texcoord_ = float4(0.f, 0.f, 0.f, 0.f);
    result[1].texcoord_ = float4(1.f, 0.f, 0.f, 0.f);
    result[2].texcoord_ = float4(1.f, 1.f, 0.f, 0.f);
    result[3].texcoord_ = float4(0.f, 1.f, 0.f, 0.f);

    _output.Append(result[0]);
    _output.Append(result[1]);
    _output.Append(result[2]);
    _output.RestartStrip();
    
    _output.Append(result[0]);
    _output.Append(result[2]);
    _output.Append(result[3]);
    _output.RestartStrip();
}

float4 ParticleTest_PS(Output _input): SV_Target0
{
    return float4(1.f, 0.f, 1.f, 1.f);
}