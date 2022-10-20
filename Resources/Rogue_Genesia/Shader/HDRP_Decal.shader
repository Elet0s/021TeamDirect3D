//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "HDRP/Decal" {
Properties {
_BaseColor ("_BaseColor", Color) = (1,1,1,1)
_BaseColorMap ("BaseColorMap", 2D) = "white" { }
_NormalMap ("NormalMap", 2D) = "bump" { }
_MaskMap ("MaskMap", 2D) = "white" { }
_DecalBlend ("_DecalBlend", Range(0, 1)) = 0.5
_NormalBlendSrc ("_NormalBlendSrc", Float) = 0
_MaskBlendSrc ("_MaskBlendSrc", Float) = 1
[Enum(Depth Bias, 0, View Bias, 1)] _DecalMeshBiasType ("_DecalMeshBiasType", Float) = 0
_DecalMeshDepthBias ("_DecalMeshDepthBias", Float) = 0
_DecalMeshViewBias ("_DecalMeshViewBias", Float) = 0
_DrawOrder ("_DrawOrder", Float) = 0
_EmissiveColor ("EmissiveColor", Color) = (0,0,0,1)
_EmissiveColorLDR ("EmissiveColor LDR", Color) = (0,0,0,1)
_EmissiveColorHDR ("EmissiveColor HDR", Color) = (0,0,0,1)
_EmissiveColorMap ("EmissiveColorMap", 2D) = "white" { }
_EmissiveIntensityUnit ("Emissive Mode", Float) = 0
[ToggleUI] _UseEmissiveIntensity ("Use Emissive Intensity", Float) = 0
_EmissiveIntensity ("Emissive Intensity", Float) = 1
_EmissiveExposureWeight ("Emissive Pre Exposure", Range(0, 1)) = 1
_MetallicRemapMin ("_MetallicRemapMin", Range(0, 1)) = 0
_MetallicRemapMax ("_MetallicRemapMax", Range(0, 1)) = 1
_SmoothnessRemapMin ("SmoothnessRemapMin", Float) = 0
_SmoothnessRemapMax ("SmoothnessRemapMax", Float) = 1
_AORemapMin ("AORemapMin", Float) = 0
_AORemapMax ("AORemapMax", Float) = 1
_DecalMaskMapBlueScale ("_DecalMaskMapBlueScale", Range(0, 1)) = 1
_Smoothness ("_Smoothness", Range(0, 1)) = 0.5
_Metallic ("_Metallic", Range(0, 1)) = 0
_AO ("_AO", Range(0, 1)) = 1
[ToggleUI] _AffectAlbedo ("Boolean", Float) = 1
[ToggleUI] _AffectNormal ("Boolean", Float) = 1
[ToggleUI] _AffectAO ("Boolean", Float) = 0
[ToggleUI] _AffectMetal ("Boolean", Float) = 1
[ToggleUI] _AffectSmoothness ("Boolean", Float) = 1
[ToggleUI] _AffectEmission ("Boolean", Float) = 0
_DecalStencilRef ("_DecalStencilRef", Float) = 16
_DecalStencilWriteMask ("_DecalStencilWriteMask", Float) = 16
_DecalColorMask0 ("_DecalColorMask0", Float) = 0
_DecalColorMask1 ("_DecalColorMask1", Float) = 0
_DecalColorMask2 ("_DecalColorMask2", Float) = 0
_DecalColorMask3 ("_DecalColorMask3", Float) = 0
_Unity_Identify_HDRP_Decal ("_Unity_Identify_HDRP_Decal", Float) = 1
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Name "DBufferProjector"
  Tags { "LIGHTMODE" = "DBufferProjector" "RenderPipeline" = "HDRenderPipeline" }
  Blend 0 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 0
  Blend 1 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 1
  Blend 2 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 2
  Blend 3 Zero OneMinusSrcColor, Zero OneMinusSrcColor
  ColorMask 0 3
  ZTest Greater
  ZWrite Off
  Cull Front
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 47877
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DecalProjectorForwardEmissive"
  Tags { "LIGHTMODE" = "DecalProjectorForwardEmissive" "RenderPipeline" = "HDRenderPipeline" }
  Blend 0 SrcAlpha One, SrcAlpha One
  ZTest Greater
  ZWrite Off
  Cull Front
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 73813
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DBufferMesh"
  Tags { "LIGHTMODE" = "DBufferMesh" "RenderPipeline" = "HDRenderPipeline" }
  Blend 0 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 0
  Blend 1 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 1
  Blend 2 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
  ColorMask 0 2
  Blend 3 Zero OneMinusSrcColor, Zero OneMinusSrcColor
  ColorMask 0 3
  ZWrite Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 179572
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DecalMeshForwardEmissive"
  Tags { "LIGHTMODE" = "DecalMeshForwardEmissive" "RenderPipeline" = "HDRenderPipeline" }
  Blend 0 SrcAlpha One, SrcAlpha One
  ZWrite Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 252707
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_COLORMAP" "_MASKMAP" "_MATERIAL_AFFECTS_ALBEDO" "_MATERIAL_AFFECTS_MASKMAP" "_MATERIAL_AFFECTS_NORMAL" "_NORMALMAP" }
"// shader disassembly not supported on DXBC"
}
}
}
}
CustomEditor "Rendering.HighDefinition.DecalUI"
}