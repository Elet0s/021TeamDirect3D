//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/DefaultEntityShader" {
Properties {
SpriteSheetSize ("SpriteSheetSize", Vector) = (8,1,0,0)
SpriteSheetAnimation ("SpriteSheetAnimation", Vector) = (8,0,0,0)
SpriteSheet ("SpriteSheet", 2D) = "white" { }
Vector1_74b68c0231f64893b502ccb2aca96f97 ("AlphaClip", Float) = 0.5
AnimationSpeed ("AnimationSpeed", Float) = 1
[ToggleUI] LoopAnimation ("LoopAnimation", Float) = 1
AnimationDuration ("AnimationDuration", Float) = 0
AnimationStartTime ("AnimationStartTime", Float) = 0
AnimationOffset ("offset", Float) = 0
Vector1_22c2422ada0e4084b59ff90d6cb1eed7 ("Zoom", Float) = 1
[ToggleUI] takeDamage ("takeDamage", Float) = 0
TakeDamageWhiteness ("TakeDamageWhiteness", Float) = 0.85
[ToggleUI] dying ("Dying", Float) = 0
dyingTime ("DyingTime", Float) = 0
DyingDuration ("DyingDuration", Float) = 0.25
Health_Percent ("HealthPercent", Float) = 0.5
DamageColor ("DamageColor", Color) = (1,0,0,1)
Vector1_b0f1d44ee07c4e0b89f14cfd2dee99d9 ("Emissive", Float) = 0
outlineSize ("outlineSize", Float) = 0
outlineColor ("outlineColor", Color) = (0,0,0,0)
[ToggleUI] UseAura ("UseAura", Float) = 0
outlineSize_2 ("Aura_TimeScale", Float) = 3
outlineSize_1 ("AuraIOffset", Float) = 0
outlineSize_3 ("AuraScale", Float) = -0.1
outlineColor_1 ("Aura_Color", Color) = (0.08627451,0,0,1)
[ToggleUI] OnFire ("OnFire", Float) = 0
outlineSize_4 ("Fire_Offset", Float) = 0
outlineSize_5 ("FireScale", Float) = -0.05
outlineColor_2 ("Fire_Color", Color) = (1.498039,0.1960784,0,1)
[ToggleUI] CustomEffect ("CustomEffect", Float) = 0
CustomEffectColor ("CustomEffectColor", Color) = (1,0.3803922,0,0.1019608)
_SampleTexture2D_d7cd9e4b0b0d40a684f292f74d5ab081_Texture_1 ("Texture2D", 2D) = "white" { }
_SampleTexture2D_2c46b201f3364a7685981f7f77774305_Texture_1 ("Texture2D", 2D) = "white" { }
_EmissionColor ("Color", Color) = (1,1,1,1)
_RenderQueueType ("Float", Float) = 1
[ToggleUI] _AddPrecomputedVelocity ("Boolean", Float) = 0
[ToggleUI] _DepthOffsetEnable ("Boolean", Float) = 0
[ToggleUI] _TransparentWritingMotionVec ("Boolean", Float) = 0
[ToggleUI] _AlphaCutoffEnable ("Boolean", Float) = 1
_TransparentSortPriority ("_TransparentSortPriority", Float) = 0
[ToggleUI] _UseShadowThreshold ("Boolean", Float) = 0
[ToggleUI] _DoubleSidedEnable ("Boolean", Float) = 1
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
[ToggleUI] _SupportDecals ("Boolean", Float) = 0
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
 Tags { "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ColorMask 0 0
  ZClip Off
  Cull Off
  GpuProgramID 22977
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "MotionVectors"
  Tags { "LIGHTMODE" = "MOTIONVECTORS" "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 264936
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 508905
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "GBuffer"
  Tags { "LIGHTMODE" = "GBuffer" "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 552540
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_BLENDMODE_OFF" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
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
 Tags { "QUEUE" = "AlphaTest+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
}
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "Rendering.HighDefinition.LitShaderGraphGUI"
}