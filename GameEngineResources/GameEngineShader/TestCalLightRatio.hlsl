//블러 적용할 것.

struct Input
{
    float4 position_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    float4 position_ : SV_Position;
    float4 texcoord_ : TEXCOORD;
};

Output TestCalLightRatio_VS(Input _input)
{
    Output result = (Output) 0;
    result.position_ = _input.position_;
    result.texcoord_ = _input.texcoord_;
    return result;
}

Texture2D ObjectDepthTexture : register(t0);
Texture2D ShadowDepthTexture : register(t1);
SamplerState POINTCLAMP : register(s0);


[numthreads(4, 4, 4)]
void TestCalLightRatio_CS(uint3 _dispatchThreadID : SV_DispatchThreadID)
{
    //float4 objectDepth = ObjectDepthTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    //float4 shadowDepth = ShadowDepthTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    
    
    
    
}


float4 TestCalLightRatio_PS(Output _input) : SV_Target0
{
    float4 result = float4(1.f, 0.f, 0.f, 1.f);
    
    float4 objectDepth = ObjectDepthTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 shadowDepth = ShadowDepthTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    if (objectDepth.r - 0.02f > shadowDepth.r)
    {
        result.r *= 0.5f;
        //그림자깊이값이 오브젝트깊이값보다 더 작으면 그림자 픽셀이므로 적용될 디퓨즈라이트를 절반만 적용되게 한다.
    }
    
    return result;
}