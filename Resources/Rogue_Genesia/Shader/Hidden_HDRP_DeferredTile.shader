//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/DeferredTile" {
Properties {
_StencilMask ("_StencilMask", Float) = 6
_StencilRef ("_StencilRef", Float) = 0
_StencilCmp ("_StencilCmp", Float) = 3
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Name "Pass 0 - Shader Variants (tiling)"
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
  GpuProgramID 57217
Program "vp" {
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT28" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT27" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT26" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT25" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT24" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT23" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT22" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT21" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT20" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT19" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT18" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT17" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT16" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT15" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT14" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT13" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT12" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT11" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT10" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT9" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT8" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT7" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT6" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT5" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT4" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT3" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT1" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT0" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT0" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT1" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT3" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT4" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT5" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT6" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT7" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT8" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT9" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT10" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT11" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT12" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT13" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT14" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT15" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT16" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT17" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT18" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT19" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT20" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT21" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT22" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT23" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT24" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT25" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT26" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT27" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT28" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT28" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT27" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT26" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT25" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT24" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT23" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT22" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT21" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT20" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT19" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT18" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT17" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT16" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT15" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT14" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT13" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT12" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT11" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT10" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT9" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT8" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT7" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT6" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT5" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT4" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT3" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT1" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "OUTPUT_SPLIT_LIGHTING" "SHADOW_MEDIUM" }
Local Keywords { "VARIANT0" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT0" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT1" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT3" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT4" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT5" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT6" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT7" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT8" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT9" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT10" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT11" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT12" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT13" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT14" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT15" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT16" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT17" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT18" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT19" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT20" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT21" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT22" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT23" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT24" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT25" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT26" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT27" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" }
Local Keywords { "VARIANT28" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "Pass 1 - Debug (fullscreen)"
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
  GpuProgramID 66274
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