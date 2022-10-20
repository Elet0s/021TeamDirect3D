//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/Deferred" {
Properties {
_StencilMask ("_StencilMask", Float) = 6
_StencilRef ("", Float) = 0
_StencilCmp ("", Float) = 3
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Disabled
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 21405
Program "vp" {
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}