//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/TemporalAA" {
Properties {
_StencilRef ("_StencilRef", Float) = 2
_StencilMask ("_StencilMask", Float) = 2
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
   Comp NotEqual
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 10678
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 70424
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "LOW_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "MEDIUM_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "HIGH_QUALITY" "ORTHOGRAPHIC" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "ANTI_RINGING" "ENABLE_ALPHA" "ENABLE_MV_REJECTION" "FORCE_BILINEAR_HISTORY" "ORTHOGRAPHIC" "POST_DOF" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}