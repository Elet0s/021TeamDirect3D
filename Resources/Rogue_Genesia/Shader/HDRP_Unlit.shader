//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "HDRP/Unlit" {
Properties {
_UnlitColor ("Color", Color) = (1,1,1,1)
_UnlitColorMap ("ColorMap", 2D) = "white" { }
_EmissiveColor ("EmissiveColor", Color) = (0,0,0,1)
_EmissiveColorMap ("EmissiveColorMap", 2D) = "white" { }
_EmissiveColorLDR ("EmissiveColor LDR", Color) = (0,0,0,1)
[ToggleUI] _AlbedoAffectEmissive ("Albedo Affect Emissive", Float) = 0
_EmissiveIntensityUnit ("Emissive Mode", Float) = 0
[ToggleUI] _UseEmissiveIntensity ("Use Emissive Intensity", Float) = 0
_EmissiveIntensity ("Emissive Intensity", Float) = 1
_EmissiveExposureWeight ("Emissive Pre Exposure", Range(0, 1)) = 1
_DistortionVectorMap ("DistortionVectorMap", 2D) = "black" { }
[ToggleUI] _DistortionEnable ("Enable Distortion", Float) = 0
[ToggleUI] _DistortionOnly ("Distortion Only", Float) = 0
[ToggleUI] _DistortionDepthTest ("Distortion Depth Test Enable", Float) = 1
[Enum(Add, 0, Multiply, 1, Replace, 2)] _DistortionBlendMode ("Distortion Blend Mode", Float) = 0
_DistortionSrcBlend ("Distortion Blend Src", Float) = 0
_DistortionDstBlend ("Distortion Blend Dst", Float) = 0
_DistortionBlurSrcBlend ("Distortion Blur Blend Src", Float) = 0
_DistortionBlurDstBlend ("Distortion Blur Blend Dst", Float) = 0
_DistortionBlurBlendMode ("Distortion Blur Blend Mode", Float) = 0
_DistortionScale ("Distortion Scale", Float) = 1
_DistortionVectorScale ("Distortion Vector Scale", Float) = 2
_DistortionVectorBias ("Distortion Vector Bias", Float) = -1
_DistortionBlurScale ("Distortion Blur Scale", Float) = 1
_DistortionBlurRemapMin ("DistortionBlurRemapMin", Float) = 0
_DistortionBlurRemapMax ("DistortionBlurRemapMax", Float) = 1
[ToggleUI] _AlphaCutoffEnable ("Alpha Cutoff Enable", Float) = 0
_AlphaCutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
_TransparentSortPriority ("_TransparentSortPriority", Float) = 0
_SurfaceType ("__surfacetype", Float) = 0
_BlendMode ("__blendmode", Float) = 0
_SrcBlend ("__src", Float) = 1
_DstBlend ("__dst", Float) = 0
_AlphaSrcBlend ("__alphaSrc", Float) = 1
_AlphaDstBlend ("__alphaDst", Float) = 0
[ToggleUI] _AlphaToMaskInspectorValue ("_AlphaToMaskInspectorValue", Float) = 0
[ToggleUI] _AlphaToMask ("__alphaToMask", Float) = 0
[ToggleUI] _ZWrite ("__zw", Float) = 1
[ToggleUI] _TransparentZWrite ("_TransparentZWrite", Float) = 0
_CullMode ("__cullmode", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.TransparentCullMode)] _TransparentCullMode ("_TransparentCullMode", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.OpaqueCullMode)] _OpaqueCullMode ("_OpaqueCullMode", Float) = 2
_ZTestModeDistortion ("_ZTestModeDistortion", Float) = 8
[Enum(UnityEngine.Rendering.CompareFunction)] _ZTestTransparent ("Transparent ZTest", Float) = 4
_ZTestDepthEqualForOpaque ("_ZTestDepthEqualForOpaque", Float) = 4
[ToggleUI] _EnableFogOnTransparent ("Enable Fog", Float) = 0
[ToggleUI] _DoubleSidedEnable ("Double sided enable", Float) = 0
_StencilRef ("_StencilRef", Float) = 0
_StencilWriteMask ("_StencilWriteMask", Float) = 3
_StencilRefDepth ("_StencilRefDepth", Float) = 0
_StencilWriteMaskDepth ("_StencilWriteMaskDepth", Float) = 8
_StencilRefMV ("_StencilRefMV", Float) = 32
_StencilWriteMaskMV ("_StencilWriteMaskMV", Float) = 32
[ToggleUI] _AddPrecomputedVelocity ("AddPrecomputedVelocity", Float) = 0
_StencilRefDistortionVec ("_StencilRefDistortionVec", Float) = 2
_StencilWriteMaskDistortionVec ("_StencilWriteMaskDistortionVec", Float) = 2
_EmissionColor ("Color", Color) = (1,1,1,1)
_IncludeIndirectLighting ("_IncludeIndirectLighting", Float) = 1
_MainTex ("Albedo", 2D) = "white" { }
_Color ("Color", Color) = (1,1,1,1)
_Cutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
_UnlitColorMap_MipInfo ("_UnlitColorMap_MipInfo", Vector) = (0,0,0,0)
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
 Pass {
  Name "DepthForwardOnly"
  Tags { "LIGHTMODE" = "DepthForwardOnly" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 72404
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "MotionVectors"
  Tags { "LIGHTMODE" = "MOTIONVECTORS" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 172765
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ForwardOnly"
  Tags { "LIGHTMODE" = "ForwardOnly" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
  Blend Zero Zero, Zero Zero
  ZTest Off
  ZWrite Off
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 231026
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
  ColorMask 0 0
  ZClip Off
  Cull Off
  GpuProgramID 331337
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DistortionVectors"
  Tags { "LIGHTMODE" = "DistortionVectors" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDUnlitShader" }
  Blend Zero Zero, Zero Zero
  ZTest Off
  ZWrite Off
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 398407
Program "vp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_EMISSIVE_COLOR_MAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_ENABLE_FOG_ON_TRANSPARENT" }
"// shader disassembly not supported on DXBC"
}
}
}
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
}
CustomEditor "Rendering.HighDefinition.UnlitGUI"
}