//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/ScreenSpaceShadows" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Off
  ZWrite Off
  Cull Off
  GpuProgramID 7647
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}