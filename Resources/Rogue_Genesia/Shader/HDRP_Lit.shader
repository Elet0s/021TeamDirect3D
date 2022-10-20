//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "HDRP/Lit" {
Properties {
_BaseColor ("BaseColor", Color) = (1,1,1,1)
_BaseColorMap ("BaseColorMap", 2D) = "white" { }
_BaseColorMap_MipInfo ("_BaseColorMap_MipInfo", Vector) = (0,0,0,0)
_Metallic ("_Metallic", Range(0, 1)) = 0
_Smoothness ("Smoothness", Range(0, 1)) = 0.5
_MaskMap ("MaskMap", 2D) = "white" { }
_MetallicRemapMin ("MetallicRemapMin", Float) = 0
_MetallicRemapMax ("MetallicRemapMax", Float) = 1
_SmoothnessRemapMin ("SmoothnessRemapMin", Float) = 0
_SmoothnessRemapMax ("SmoothnessRemapMax", Float) = 1
_AORemapMin ("AORemapMin", Float) = 0
_AORemapMax ("AORemapMax", Float) = 1
_NormalMap ("NormalMap", 2D) = "bump" { }
_NormalMapOS ("NormalMapOS", 2D) = "white" { }
_NormalScale ("_NormalScale", Range(0, 8)) = 1
_BentNormalMap ("_BentNormalMap", 2D) = "bump" { }
_BentNormalMapOS ("_BentNormalMapOS", 2D) = "white" { }
_HeightMap ("HeightMap", 2D) = "black" { }
_HeightAmplitude ("Height Amplitude", Float) = 0.02
_HeightCenter ("Height Center", Range(0, 1)) = 0.5
[Enum(MinMax, 0, Amplitude, 1)] _HeightMapParametrization ("Heightmap Parametrization", Float) = 0
_HeightOffset ("Height Offset", Float) = 0
_HeightMin ("Heightmap Min", Float) = -1
_HeightMax ("Heightmap Max", Float) = 1
_HeightTessAmplitude ("Amplitude", Float) = 2
_HeightTessCenter ("Height Center", Range(0, 1)) = 0.5
_HeightPoMAmplitude ("Height Amplitude", Float) = 2
_DetailMap ("DetailMap", 2D) = "linearGrey" { }
_DetailAlbedoScale ("_DetailAlbedoScale", Range(0, 2)) = 1
_DetailNormalScale ("_DetailNormalScale", Range(0, 2)) = 1
_DetailSmoothnessScale ("_DetailSmoothnessScale", Range(0, 2)) = 1
_TangentMap ("TangentMap", 2D) = "bump" { }
_TangentMapOS ("TangentMapOS", 2D) = "white" { }
_Anisotropy ("Anisotropy", Range(-1, 1)) = 0
_AnisotropyMap ("AnisotropyMap", 2D) = "white" { }
_SubsurfaceMask ("Subsurface Radius", Range(0, 1)) = 1
_SubsurfaceMaskMap ("Subsurface Radius Map", 2D) = "white" { }
_Thickness ("Thickness", Range(0, 1)) = 1
_ThicknessMap ("Thickness Map", 2D) = "white" { }
_ThicknessRemap ("Thickness Remap", Vector) = (0,1,0,0)
_IridescenceThickness ("Iridescence Thickness", Range(0, 1)) = 1
_IridescenceThicknessMap ("Iridescence Thickness Map", 2D) = "white" { }
_IridescenceThicknessRemap ("Iridescence Thickness Remap", Vector) = (0,1,0,0)
_IridescenceMask ("Iridescence Mask", Range(0, 1)) = 1
_IridescenceMaskMap ("Iridescence Mask Map", 2D) = "white" { }
_CoatMask ("Coat Mask", Range(0, 1)) = 0
_CoatMaskMap ("CoatMaskMap", 2D) = "white" { }
[ToggleUI] _EnergyConservingSpecularColor ("_EnergyConservingSpecularColor", Float) = 1
_SpecularColor ("SpecularColor", Color) = (1,1,1,1)
_SpecularColorMap ("SpecularColorMap", 2D) = "white" { }
[Enum(Off, 0, From Ambient Occlusion, 1, From Bent Normals, 2)] _SpecularOcclusionMode ("Specular Occlusion Mode", Float) = 1
_EmissiveColor ("EmissiveColor", Color) = (0,0,0,1)
_EmissiveColorLDR ("EmissiveColor LDR", Color) = (0,0,0,1)
_EmissiveColorMap ("EmissiveColorMap", 2D) = "white" { }
[ToggleUI] _AlbedoAffectEmissive ("Albedo Affect Emissive", Float) = 0
_EmissiveIntensityUnit ("Emissive Mode", Float) = 0
[ToggleUI] _UseEmissiveIntensity ("Use Emissive Intensity", Float) = 0
_EmissiveIntensity ("Emissive Intensity", Float) = 1
_EmissiveExposureWeight ("Emissive Pre Exposure", Range(0, 1)) = 1
[ToggleUI] _UseShadowThreshold ("_UseShadowThreshold", Float) = 0
[ToggleUI] _AlphaCutoffEnable ("Alpha Cutoff Enable", Float) = 0
_AlphaCutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
_AlphaCutoffShadow ("_AlphaCutoffShadow", Range(0, 1)) = 0.5
_AlphaCutoffPrepass ("_AlphaCutoffPrepass", Range(0, 1)) = 0.5
_AlphaCutoffPostpass ("_AlphaCutoffPostpass", Range(0, 1)) = 0.5
[ToggleUI] _TransparentDepthPrepassEnable ("_TransparentDepthPrepassEnable", Float) = 0
[ToggleUI] _TransparentBackfaceEnable ("_TransparentBackfaceEnable", Float) = 0
[ToggleUI] _TransparentDepthPostpassEnable ("_TransparentDepthPostpassEnable", Float) = 0
_TransparentSortPriority ("_TransparentSortPriority", Float) = 0
[Enum(None, 0, Box, 1, Sphere, 2, Thin, 3)] _RefractionModel ("Refraction Model", Float) = 0
_Ior ("Index Of Refraction", Range(1, 2.5)) = 1.5
_TransmittanceColor ("Transmittance Color", Color) = (1,1,1,1)
_TransmittanceColorMap ("TransmittanceColorMap", 2D) = "white" { }
_ATDistance ("Transmittance Absorption Distance", Float) = 1
[ToggleUI] _TransparentWritingMotionVec ("_TransparentWritingMotionVec", Float) = 0
_StencilRef ("_StencilRef", Float) = 0
_StencilWriteMask ("_StencilWriteMask", Float) = 3
_StencilRefGBuffer ("_StencilRefGBuffer", Float) = 2
_StencilWriteMaskGBuffer ("_StencilWriteMaskGBuffer", Float) = 3
_StencilRefDepth ("_StencilRefDepth", Float) = 0
_StencilWriteMaskDepth ("_StencilWriteMaskDepth", Float) = 8
_StencilRefMV ("_StencilRefMV", Float) = 32
_StencilWriteMaskMV ("_StencilWriteMaskMV", Float) = 32
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
_CullModeForward ("__cullmodeForward", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.TransparentCullMode)] _TransparentCullMode ("_TransparentCullMode", Float) = 2
[Enum(UnityEditor.Rendering.HighDefinition.OpaqueCullMode)] _OpaqueCullMode ("_OpaqueCullMode", Float) = 2
_ZTestDepthEqualForOpaque ("_ZTestDepthEqualForOpaque", Float) = 4
_ZTestGBuffer ("_ZTestGBuffer", Float) = 4
[Enum(UnityEngine.Rendering.CompareFunction)] _ZTestTransparent ("Transparent ZTest", Float) = 4
[ToggleUI] _EnableFogOnTransparent ("Enable Fog", Float) = 1
[ToggleUI] _EnableBlendModePreserveSpecularLighting ("Enable Blend Mode Preserve Specular Lighting", Float) = 1
[ToggleUI] _DoubleSidedEnable ("Double sided enable", Float) = 0
[Enum(Flip, 0, Mirror, 1, None, 2)] _DoubleSidedNormalMode ("Double sided normal mode", Float) = 1
_DoubleSidedConstants ("_DoubleSidedConstants", Vector) = (1,1,-1,0)
[Enum(UV0, 0, UV1, 1, UV2, 2, UV3, 3, Planar, 4, Triplanar, 5)] _UVBase ("UV Set for base", Float) = 0
_TexWorldScale ("Scale to apply on world coordinate", Float) = 1
_InvTilingScale ("Inverse tiling scale = 2 / (abs(_BaseColorMap_ST.x) + abs(_BaseColorMap_ST.y))", Float) = 1
_UVMappingMask ("_UVMappingMask", Color) = (1,0,0,0)
[Enum(TangentSpace, 0, ObjectSpace, 1)] _NormalMapSpace ("NormalMap space", Float) = 0
[Enum(Subsurface Scattering, 0, Standard, 1, Anisotropy, 2, Iridescence, 3, Specular Color, 4, Translucent, 5)] _MaterialID ("MaterialId", Float) = 1
[ToggleUI] _TransmissionEnable ("_TransmissionEnable", Float) = 1
[Enum(None, 0, Vertex displacement, 1, Pixel displacement, 2)] _DisplacementMode ("DisplacementMode", Float) = 0
[ToggleUI] _DisplacementLockObjectScale ("displacement lock object scale", Float) = 1
[ToggleUI] _DisplacementLockTilingScale ("displacement lock tiling scale", Float) = 1
[ToggleUI] _DepthOffsetEnable ("Depth Offset View space", Float) = 0
[ToggleUI] _EnableGeometricSpecularAA ("EnableGeometricSpecularAA", Float) = 0
_SpecularAAScreenSpaceVariance ("SpecularAAScreenSpaceVariance", Range(0, 1)) = 0.1
_SpecularAAThreshold ("SpecularAAThreshold", Range(0, 1)) = 0.2
_PPDMinSamples ("Min sample for POM", Range(1, 64)) = 5
_PPDMaxSamples ("Max sample for POM", Range(1, 64)) = 15
_PPDLodThreshold ("Start lod to fade out the POM effect", Range(0, 16)) = 5
_PPDPrimitiveLength ("Primitive length for POM", Float) = 1
_PPDPrimitiveWidth ("Primitive width for POM", Float) = 1
_InvPrimScale ("Inverse primitive scale for non-planar POM", Vector) = (1,1,0,0)
[Enum(UV0, 0, UV1, 1, UV2, 2, UV3, 3)] _UVDetail ("UV Set for detail", Float) = 0
_UVDetailsMappingMask ("_UVDetailsMappingMask", Color) = (1,0,0,0)
[ToggleUI] _LinkDetailsWithBase ("LinkDetailsWithBase", Float) = 1
[Enum(Use Emissive Color, 0, Use Emissive Mask, 1)] _EmissiveColorMode ("Emissive color mode", Float) = 1
[Enum(UV0, 0, UV1, 1, UV2, 2, UV3, 3, Planar, 4, Triplanar, 5, Same as Base, 6)] _UVEmissive ("UV Set for emissive", Float) = 0
_TexWorldScaleEmissive ("Scale to apply on world coordinate", Float) = 1
_UVMappingMaskEmissive ("_UVMappingMaskEmissive", Color) = (1,0,0,0)
_EmissionColor ("Color", Color) = (1,1,1,1)
_MainTex ("Albedo", 2D) = "white" { }
_Color ("Color", Color) = (1,1,1,1)
_Cutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
[ToggleUI] _SupportDecals ("Support Decals", Float) = 1
[ToggleUI] _ReceivesSSR ("Receives SSR", Float) = 1
[ToggleUI] _ReceivesSSRTransparent ("Receives SSR Transparent", Float) = 0
[ToggleUI] _AddPrecomputedVelocity ("AddPrecomputedVelocity", Float) = 0
[ToggleUI] _RayTracing ("Ray Tracing (Preview)", Float) = 0
_DiffusionProfile ("Obsolete, kept for migration purpose", Float) = 0
_DiffusionProfileAsset ("Diffusion Profile Asset", Vector) = (0,0,0,0)
_DiffusionProfileHash ("Diffusion Profile Hash", Float) = 0
unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
 Pass {
  Name "GBuffer"
  Tags { "LIGHTMODE" = "GBuffer" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ZTest Off
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 181526
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ColorMask 0 0
  ZClip Off
  Cull Off
  GpuProgramID 286609
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 337621
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "MotionVectors"
  Tags { "LIGHTMODE" = "MOTIONVECTORS" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 443989
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_ADD_PRECOMPUTED_VELOCITY" "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_MAPPING_PLANAR" "_MASKMAP" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_MATERIAL_FEATURE_SUBSURFACE_SCATTERING" "_MATERIAL_FEATURE_TRANSMISSION" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" }
Local Keywords { "_ALPHATEST_ON" "_DISABLE_SSR_TRANSPARENT" "_EMISSIVE_COLOR_MAP" "_MASKMAP" "_MATERIAL_FEATURE_CLEAR_COAT" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "TransparentDepthPrepass"
  Tags { "LIGHTMODE" = "TransparentDepthPrepass" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 467910
Program "vp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "Forward"
  Tags { "LIGHTMODE" = "Forward" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  Blend 0 Zero Zero, Zero Zero
  ColorMask 0 1
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
  GpuProgramID 625559
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "INSTANCING_ON" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "DIRLIGHTMAP_COMBINED" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "INSTANCING_ON" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DECALS_4RT" "SCREEN_SPACE_SHADOWS_ON" "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "TransparentDepthPostpass"
  Tags { "LIGHTMODE" = "TransparentDepthPostpass" "RenderPipeline" = "HDRenderPipeline" "RenderType" = "HDLitShader" }
  ColorMask 0 0
  Cull Off
  GpuProgramID 696409
Program "vp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SURFACE_TYPE_TRANSPARENT" }
Local Keywords { "_DISABLE_DECALS" "_DISABLE_SSR_TRANSPARENT" "_DOUBLESIDED_ON" "_MATERIAL_FEATURE_IRIDESCENCE" "_NORMALMAP_TANGENT_SPACE" }
"// shader disassembly not supported on DXBC"
}
}
}
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
}
CustomEditor "Rendering.HighDefinition.LitGUI"
}