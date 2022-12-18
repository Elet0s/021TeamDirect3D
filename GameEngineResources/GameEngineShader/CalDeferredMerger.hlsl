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

// 그래픽카드에서 이뤄지는것.
Output CalDeferredMerger_VS(Input _input)
{
    Output result = (Output) 0;
    result.position_ = _input.position_;
    result.texcoord_ = _input.texcoord_;
    return result;
}

Texture2D ColorTexture : register(t0);
Texture2D DiffuseLightTexture : register(t1);
Texture2D SpecularLightTexture : register(t2);
Texture2D AmbientLightTexture : register(t3);
SamplerState POINTCLAMP : register(s0);

float4 CalDeferredMerger_PS(Output _input) : SV_Target0
{
    float4 color = ColorTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 diffuseLight = DiffuseLightTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 specularLight = SpecularLightTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    float4 ambientLight = AmbientLightTexture.Sample(POINTCLAMP, _input.texcoord_.xy);
    
    if (0 == color.a)
    {
        clip(-1);
    }
    
    float4 lightEffectResult = color * (diffuseLight + specularLight) + ambientLight;
    lightEffectResult.w = 1.0f;
    
    return lightEffectResult;
}