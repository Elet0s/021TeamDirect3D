//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/SimpleFlipbook" {
Properties {
SpriteSheetSize ("SpriteSheetSize", Vector) = (8,1,0,0)
SpriteSheetAnimation ("SpriteSheetAnimation", Vector) = (8,0,0,0)
SpriteSheet ("SpriteSheet", 2D) = "white" { }
Vector1_74b68c0231f64893b502ccb2aca96f97 ("AlphaClip", Float) = 0.5
AnimationSpeed ("AnimationSpeed", Float) = 1
Vector1_22c2422ada0e4084b59ff90d6cb1eed7 ("Zoom", Float) = 1
AnimationStartTime ("AnimationStartTime", Float) = 0
AnimationDuration ("AnimationDuration", Float) = 0.25
Alpha ("Alpha", Float) = 1
_Color ("Color", Color) = (1,1,1,0)
Color_2dcd309008394dff8df70ed0e48ed901 ("Emissive", Color) = (0,0,0,0)
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
  GpuProgramID 42352
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
  GpuProgramID 316793
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "TransparentDepthPrepass"
  Tags { "LIGHTMODE" = "TransparentDepthPrepass" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 373646
Program "vp" {
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
  GpuProgramID 483579
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
  GpuProgramID 569256
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "Forward"
  Tags { "LIGHTMODE" = "Forward" "QUEUE" = "AlphaTest+25" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Blend 0 Zero Zero, Zero Zero
  ColorMask 0 1
  ZTest Off
  ZWrite Off
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
  GpuProgramID 646379
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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