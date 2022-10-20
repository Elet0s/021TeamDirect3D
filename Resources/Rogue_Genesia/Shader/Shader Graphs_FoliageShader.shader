//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/FoliageShader" {
Properties {
Color_412d1764b39e41e08ac08f13bde3ab8f ("Tint", Color) = (1,1,1,0)
Vector1_6ed3ab89f4a54be8ab97c6a29b6b8a10 ("AlphClipThreashol", Float) = 0.5
Texture2D_7d4129c4688c44ceb20a8605f5fe6857 ("FoliageTexture", 2D) = "white" { }
Vector1_4e7402f72bdd4768a80d242e5ec88e88 ("Smoothness", Float) = 0
Texture2D_ee9bc1dd4d7d467799da5f386d7f38ea ("Normal", 2D) = "white" { }
Texture2D_dc864dc548db4904a11c70a20cfb6041 ("WindNoise", 2D) = "white" { }
Texture2D_7ab62f29e8e4470c98e41d5fc74f33c2 ("WindMask", 2D) = "white" { }
Vector1_06edc543371047c2bb8be3f25896e821 ("WindScale", Float) = 2
Vector2_b63a0967c8124c3b889187ea2bcaa0b4 ("WindSpeed", Vector) = (6,6,0,0)
Vector1_70ac28a97f1c420d8a4bd8b67c9edda9 ("WindIntensity", Float) = 0.3
Vector3_c585f28e93424236bfcc304c23dea597 ("WindIntensityVector", Vector) = (1,0.25,1,0)
[DiffusionProfile] DiffusionProfile_30ab7607401a4bed96dffbd79083c4ef ("Diffusion Profile", Float) = 0
DiffusionProfile_30ab7607401a4bed96dffbd79083c4ef_Asset ("Diffusion Profile", Vector) = (0,0,0,0)
Vector1_c00b2332eba34c41a2c8a56fef9cc1e8 ("Thickness", Float) = 0
Texture2D_00b7b245f0264b468df5a15acff3163a ("ThicknessMap", 2D) = "white" { }
_EmissionColor ("Color", Color) = (1,1,1,1)
_RenderQueueType ("Float", Float) = 4
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
_SurfaceType ("Float", Float) = 1
_BlendMode ("Float", Float) = 0
_SrcBlend ("Float", Float) = 1
_DstBlend ("Float", Float) = 0
_AlphaSrcBlend ("Float", Float) = 1
_AlphaDstBlend ("Float", Float) = 0
[ToggleUI] _AlphaToMask ("Boolean", Float) = 1
[ToggleUI] _AlphaToMaskInspectorValue ("Boolean", Float) = 1
[ToggleUI] _ZWrite ("Boolean", Float) = 1
[ToggleUI] _TransparentZWrite ("Boolean", Float) = 1
_CullMode ("Float", Float) = 2
[ToggleUI] _EnableFogOnTransparent ("Boolean", Float) = 1
_CullModeForward ("Float", Float) = 2
[Enum(Front, 1, Back, 2)] _TransparentCullMode ("Float", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.OpaqueCullMode)] _OpaqueCullMode ("Float", Float) = 2
_ZTestDepthEqualForOpaque ("Float", Float) = 4
[Enum(UnityEngine.Rendering.CompareFunction)] _ZTestTransparent ("Float", Float) = 4
[ToggleUI] _TransparentBackfaceEnable ("Boolean", Float) = 0
[ToggleUI] _RequireSplitLighting ("Boolean", Float) = 1
[ToggleUI] _ReceivesSSR ("Boolean", Float) = 0
[ToggleUI] _ReceivesSSRTransparent ("Boolean", Float) = 0
[ToggleUI] _EnableBlendModePreserveSpecularLighting ("Boolean", Float) = 1
[ToggleUI] _SupportDecals ("Boolean", Float) = 0
_StencilRef ("Float", Float) = 4
_StencilWriteMask ("Float", Float) = 6
_StencilRefDepth ("Float", Float) = 0
_StencilWriteMaskDepth ("Float", Float) = 8
_StencilRefMV ("Float", Float) = 32
_StencilWriteMaskMV ("Float", Float) = 40
_StencilRefDistortionVec ("Float", Float) = 4
_StencilWriteMaskDistortionVec ("Float", Float) = 4
_StencilWriteMaskGBuffer ("Float", Float) = 14
_StencilRefGBuffer ("Float", Float) = 6
_ZTestGBuffer ("Float", Float) = 4
[ToggleUI] _RayTracing ("Boolean", Float) = 0
[Enum(None, 0, Box, 1, Sphere, 2, Thin, 3)] _RefractionModel ("Float", Float) = 0
unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
}
SubShader {
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ColorMask 0 0
  ZClip Off
  Cull Off
  GpuProgramID 19631
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "MotionVectors"
  Tags { "LIGHTMODE" = "MOTIONVECTORS" "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 296750
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 488808
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_ALPHATOMASK_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "GBuffer"
  Tags { "LIGHTMODE" = "GBuffer" "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
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
  GpuProgramID 554892
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR" "_DISABLE_SSR_TRANSPARENT" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_BLENDMODE_OFF" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_REFRACTION_OFF" }
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
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
}
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "Rendering.HighDefinition.LitShaderGraphGUI"
}