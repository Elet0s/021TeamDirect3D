//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/ProjectileShader" {
Properties {
Color_a6f9248fcf3444b09647611c645d6b88 ("Tint", Color) = (0,0,0,0)
_MainTex ("_MainTex", 2D) = "white" { }
Texture2D_97137a3f25bd4a38884d8a88d31c617f ("Normal", 2D) = "bump" { }
Vector1_60d96646aea945c5b510913f1d9dc277 ("NormalIntensity", Range(0, 10)) = 0
Texture2D_feed567b1324422d8b9d39d387413ff1 ("Mask (MODS)", 2D) = "white" { }
Vector1_25fd8d96f63e44eca09e890f06da18a1 ("Metalness", Float) = 0
Vector1_1 ("AmbientOcclusion", Float) = 0
Vector1_2 ("Smoothness", Float) = 0
Vector1_53f9d082c1b540d8b5c0e36c1fb1a94b ("UvRotation", Range(0, 360)) = 45
Vector2_13d94e732b794795921ca9b5f51083b0 ("UvTile", Vector) = (0,0,0,0)
UvOffset ("UvOffset", Vector) = (0,0,0,0)
Vector1_f3232da2030046ab8ec0e1a18e433c81 ("RotationSpeed", Float) = 0
Vector1_d1a7049d72de4212b4e679eb0a4ff24b ("Scale", Float) = 1
_EmissionColor ("Color", Color) = (1,1,1,1)
_RenderQueueType ("Float", Float) = 1
[ToggleUI] _AddPrecomputedVelocity ("Boolean", Float) = 0
[ToggleUI] _DepthOffsetEnable ("Boolean", Float) = 0
[ToggleUI] _TransparentWritingMotionVec ("Boolean", Float) = 0
[ToggleUI] _AlphaCutoffEnable ("Boolean", Float) = 1
_TransparentSortPriority ("_TransparentSortPriority", Float) = 0
[ToggleUI] _UseShadowThreshold ("Boolean", Float) = 0
[ToggleUI] _DoubleSidedEnable ("Boolean", Float) = 0
[Enum(Flip, 0, Mirror, 1, None, 2)] _DoubleSidedNormalMode ("Float", Float) = 2
_DoubleSidedConstants ("Vector4", Vector) = (1,1,-1,0)
[ToggleUI] _TransparentDepthPrepassEnable ("Boolean", Float) = 0
[ToggleUI] _TransparentDepthPostpassEnable ("Boolean", Float) = 0
_SurfaceType ("Float", Float) = 0
_BlendMode ("Float", Float) = 0
_SrcBlend ("Float", Float) = 1
_DstBlend ("Float", Float) = 0
_AlphaSrcBlend ("Float", Float) = 1
_AlphaDstBlend ("Float", Float) = 0
[ToggleUI] _AlphaToMask ("Boolean", Float) = 0
[ToggleUI] _AlphaToMaskInspectorValue ("Boolean", Float) = 0
[ToggleUI] _ZWrite ("Boolean", Float) = 1
[ToggleUI] _TransparentZWrite ("Boolean", Float) = 0
_CullMode ("Float", Float) = 2
[ToggleUI] _EnableFogOnTransparent ("Boolean", Float) = 1
_CullModeForward ("Float", Float) = 2
[Enum(Front, 1, Back, 2)] _TransparentCullMode ("Float", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.OpaqueCullMode)] _OpaqueCullMode ("Float", Float) = 2
_ZTestDepthEqualForOpaque ("Float", Float) = 4
[Enum(UnityEngine.Rendering.CompareFunction)] _ZTestTransparent ("Float", Float) = 4
[ToggleUI] _TransparentBackfaceEnable ("Boolean", Float) = 0
[ToggleUI] _RequireSplitLighting ("Boolean", Float) = 0
[ToggleUI] _ReceivesSSR ("Boolean", Float) = 1
[ToggleUI] _ReceivesSSRTransparent ("Boolean", Float) = 0
[ToggleUI] _EnableBlendModePreserveSpecularLighting ("Boolean", Float) = 1
[ToggleUI] _SupportDecals ("Boolean", Float) = 1
_StencilRef ("Float", Float) = 0
_StencilWriteMask ("Float", Float) = 6
_StencilRefDepth ("Float", Float) = 8
_StencilWriteMaskDepth ("Float", Float) = 8
_StencilRefMV ("Float", Float) = 40
_StencilWriteMaskMV ("Float", Float) = 40
_StencilRefDistortionVec ("Float", Float) = 4
_StencilWriteMaskDistortionVec ("Float", Float) = 4
_StencilWriteMaskGBuffer ("Float", Float) = 14
_StencilRefGBuffer ("Float", Float) = 10
_ZTestGBuffer ("Float", Float) = 4
[ToggleUI] _RayTracing ("Boolean", Float) = 0
[Enum(None, 0, Box, 1, Sphere, 2, Thin, 3)] _RefractionModel ("Float", Float) = 0
unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
}
SubShader {
 Tags { "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ColorMask 0 0
  ZClip Off
  Cull Off
  GpuProgramID 36994
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "MotionVectors"
  Tags { "LIGHTMODE" = "MOTIONVECTORS" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   CompFront Always
   PassFront Replace
   FailFront Keep
   ZFailFront Keep
   CompBack Always
   PassBack Replace
   FailBack Keep
   ZFailBack Keep
  }
  GpuProgramID 272050
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   CompFront Always
   PassFront Replace
   FailFront Keep
   ZFailFront Keep
   CompBack Always
   PassBack Replace
   FailBack Keep
   ZFailBack Keep
  }
  GpuProgramID 521586
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "GBuffer"
  Tags { "LIGHTMODE" = "GBuffer" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ZTest Off
  Cull Off
  Stencil {
   WriteMask 0
   CompFront Always
   PassFront Replace
   FailFront Keep
   ZFailFront Keep
   CompBack Always
   PassBack Replace
   FailBack Keep
   ZFailBack Keep
  }
  GpuProgramID 547969
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
}
SubShader {
 Tags { "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
}
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "Rendering.HighDefinition.LitShaderGraphGUI"
}