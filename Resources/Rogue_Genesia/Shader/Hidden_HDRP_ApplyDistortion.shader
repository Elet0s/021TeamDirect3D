//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/ApplyDistortion" {
Properties {
_StencilRef ("_StencilRef", Float) = 2
_StencilMask ("_StencilMask", Float) = 2
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Less
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   WriteMask 0
   Comp Equal
   Pass Zero
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 49467
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}