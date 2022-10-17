//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Custom/NormalMapSpriteShader" {
Properties {
_MainTex ("Sprite Texture", 2D) = "white" { }
_BumpMap ("Normalmap", 2D) = "bump" { }
_Color ("Tint", Color) = (1,1,1,1)
[MaterialToggle] PixelSnap ("Pixel snap", Float) = 0
_Cutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
}
SubShader {
 LOD 300
 Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
 Pass {
  Name "FORWARD"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "FORWARDBASE" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Front
  Lighting On
  GpuProgramID 46427
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "FORWARD"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "FORWARDADD" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Front
  Lighting On
  GpuProgramID 83609
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "PREPASS"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "PREPASSBASE" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Front
  Lighting On
  GpuProgramID 137072
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "PREPASS"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "PREPASSFINAL" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Front
  Lighting On
  GpuProgramID 240744
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DEFERRED"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DEFERRED" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Front
  Lighting On
  GpuProgramID 320075
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ShadowCaster"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "SHADOWCASTER" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  Cull Front
  Lighting On
  GpuProgramID 329291
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "Meta"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "META" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Off
  Lighting On
  GpuProgramID 448255
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "FORWARD"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "FORWARDBASE" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Lighting On
  GpuProgramID 474524
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "VERTEXLIGHT_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "FORWARD"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "FORWARDADD" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Lighting On
  GpuProgramID 579511
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "SPOT" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "POINT_COOKIE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRECTIONAL_COOKIE" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "PREPASS"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "PREPASSBASE" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Lighting On
  GpuProgramID 652189
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "PREPASS"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "PREPASSFINAL" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Lighting On
  GpuProgramID 702606
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DEFERRED"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DEFERRED" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Lighting On
  GpuProgramID 753316
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DUMMY" "LIGHTPROBE_SH" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DUMMY" "DYNAMICLIGHTMAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHTPROBE_SH" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DIRLIGHTMAP_COMBINED" "DYNAMICLIGHTMAP_ON" "PIXELSNAP_ON" "UNITY_HDR_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ShadowCaster"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "SHADOWCASTER" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  Lighting On
  GpuProgramID 837528
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "Meta"
  LOD 300
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "META" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "TransparentCutout" }
  ZWrite Off
  Cull Off
  Lighting On
  GpuProgramID 878789
Program "vp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "DUMMY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXELSNAP_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
}
Fallback "Transparent/Cutout/Diffuse"
}