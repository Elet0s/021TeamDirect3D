//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/CombineLighting" {
Properties {
_StencilMask ("_StencilMask", Float) = 7
_StencilRef ("_StencilRef", Float) = 1
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  Blend One One, One One
  ZTest Less
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 2653
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
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  Blend One One, One One
  ZTest Less
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 66877
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