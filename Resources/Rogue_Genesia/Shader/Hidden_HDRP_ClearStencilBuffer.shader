//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/ClearStencilBuffer" {
Properties {
_StencilMask ("_StencilMask", Float) = 63
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ColorMask 0 0
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 25998
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