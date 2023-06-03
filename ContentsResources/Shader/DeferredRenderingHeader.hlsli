struct DeferredRenderingOutput
{
    float4 color_ : SV_Target0; //기본 색상.
    float4 viewPosition_ : SV_Target1; //뷰공간에서의 위치.
    float4 viewNormal_ : SV_Target2; //뷰공간에서의 법선벡터.
    float4 objectDepth_ : SV_Target3; //오브젝트의 깊이값.
};