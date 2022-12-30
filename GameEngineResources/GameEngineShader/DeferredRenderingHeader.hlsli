struct DeferredRenderingOutput
{
    float4 color_ : SV_Target0;
    float4 viewPosition_ : SV_Target1;
    float4 viewNormal_ : SV_Target2;
    float4 objectDepth_ : SV_Target3;
};