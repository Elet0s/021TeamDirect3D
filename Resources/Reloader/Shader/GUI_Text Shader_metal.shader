//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "GUI/Text Shader" {
Properties {
_MainTex ("Font Texture", 2D) = "white" { }
_Color ("Text Color", Color) = (1,1,1,1)
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 33352
Program "vp" {
SubProgram "metal " {
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

struct VGlobals_Type
{
    float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
    float4 hlslcc_mtx4x4unity_MatrixVP[4];
    float4 _MainTex_ST;
    float4 _Color;
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float4 COLOR0 [[ attribute(1) ]] ;
    float2 TEXCOORD0 [[ attribute(2) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float4 COLOR0 [[ user(COLOR0) ]];
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]];
};

vertex Mtl_VertexOut xlatMtlMain(
    constant VGlobals_Type& VGlobals [[ buffer(0) ]],
    Mtl_VertexIn input [[ stage_in ]])
{
    Mtl_VertexOut output;
    float4 u_xlat0;
    float4 u_xlat1;
    u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
    u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
    output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
    output.COLOR0 = input.COLOR0 * VGlobals._Color;
    output.TEXCOORD0.xy = fma(input.TEXCOORD0.xy, VGlobals._MainTex_ST.xy, VGlobals._MainTex_ST.zw);
    return output;
}
"
}
SubProgram "metal " {
Keywords { "UNITY_SINGLE_PASS_STEREO" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

struct VGlobals_Type
{
    float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
    float4 _MainTex_ST;
    float4 _Color;
};

struct UnityStereoGlobals_Type
{
    float4 hlslcc_mtx4x4unity_StereoMatrixP[8];
    float4 hlslcc_mtx4x4unity_StereoMatrixV[8];
    float4 hlslcc_mtx4x4unity_StereoMatrixInvV[8];
    float4 hlslcc_mtx4x4unity_StereoMatrixVP[8];
    float4 hlslcc_mtx4x4unity_StereoCameraProjection[8];
    float4 hlslcc_mtx4x4unity_StereoCameraInvProjection[8];
    float4 hlslcc_mtx4x4unity_StereoWorldToCamera[8];
    float4 hlslcc_mtx4x4unity_StereoCameraToWorld[8];
    float3 unity_StereoWorldSpaceCameraPos[2];
    float4 unity_StereoScaleOffset[2];
};

struct UnityStereoEyeIndex_Type
{
    int unity_StereoEyeIndex;
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float4 COLOR0 [[ attribute(1) ]] ;
    float2 TEXCOORD0 [[ attribute(2) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float4 COLOR0 [[ user(COLOR0) ]];
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]];
};

vertex Mtl_VertexOut xlatMtlMain(
    constant VGlobals_Type& VGlobals [[ buffer(0) ]],
    constant UnityStereoGlobals_Type& UnityStereoGlobals [[ buffer(1) ]],
    constant UnityStereoEyeIndex_Type& UnityStereoEyeIndex [[ buffer(2) ]],
    Mtl_VertexIn input [[ stage_in ]])
{
    Mtl_VertexOut output;
    float4 u_xlat0;
    int u_xlati1;
    float4 u_xlat2;
    u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
    u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlati1 = UnityStereoEyeIndex.unity_StereoEyeIndex << 0x2;
    u_xlat2 = u_xlat0.yyyy * UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
    u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1], u_xlat0.xxxx, u_xlat2);
    u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)], u_xlat0.zzzz, u_xlat2);
    output.mtl_Position = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)], u_xlat0.wwww, u_xlat2);
    output.COLOR0 = input.COLOR0 * VGlobals._Color;
    output.TEXCOORD0.xy = fma(input.TEXCOORD0.xy, VGlobals._MainTex_ST.xy, VGlobals._MainTex_ST.zw);
    return output;
}
"
}
SubProgram "metal " {
Keywords { "STEREO_INSTANCING_ON" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

struct VGlobals_Type
{
    float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
    float4 hlslcc_mtx4x4unity_MatrixVP[4];
    float4 _MainTex_ST;
    float4 _Color;
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float4 COLOR0 [[ attribute(1) ]] ;
    float2 TEXCOORD0 [[ attribute(2) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float4 COLOR0 [[ user(COLOR0) ]];
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]];
};

vertex Mtl_VertexOut xlatMtlMain(
    constant VGlobals_Type& VGlobals [[ buffer(0) ]],
    Mtl_VertexIn input [[ stage_in ]])
{
    Mtl_VertexOut output;
    float4 u_xlat0;
    float4 u_xlat1;
    u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
    u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
    output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
    output.COLOR0 = input.COLOR0 * VGlobals._Color;
    output.TEXCOORD0.xy = fma(input.TEXCOORD0.xy, VGlobals._MainTex_ST.xy, VGlobals._MainTex_ST.zw);
    return output;
}
"
}
SubProgram "metal " {
Keywords { "STEREO_MULTIVIEW_ON" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

struct VGlobals_Type
{
    float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
    float4 hlslcc_mtx4x4unity_MatrixVP[4];
    float4 _MainTex_ST;
    float4 _Color;
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float4 COLOR0 [[ attribute(1) ]] ;
    float2 TEXCOORD0 [[ attribute(2) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float4 COLOR0 [[ user(COLOR0) ]];
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]];
};

vertex Mtl_VertexOut xlatMtlMain(
    constant VGlobals_Type& VGlobals [[ buffer(0) ]],
    Mtl_VertexIn input [[ stage_in ]])
{
    Mtl_VertexOut output;
    float4 u_xlat0;
    float4 u_xlat1;
    u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
    u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
    u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
    u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
    output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
    output.COLOR0 = input.COLOR0 * VGlobals._Color;
    output.TEXCOORD0.xy = fma(input.TEXCOORD0.xy, VGlobals._MainTex_ST.xy, VGlobals._MainTex_ST.zw);
    return output;
}
"
}
}
Program "fp" {
SubProgram "metal " {
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

#ifndef XLT_REMAP_O
	#define XLT_REMAP_O {0, 1, 2, 3, 4, 5, 6, 7}
#endif
constexpr constant uint xlt_remap_o[] = XLT_REMAP_O;
struct Mtl_FragmentIn
{
    float4 COLOR0 [[ user(COLOR0) ]] ;
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float u_xlat0;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy).w;
    output.SV_Target0.w = u_xlat0 * input.COLOR0.w;
    output.SV_Target0.xyz = input.COLOR0.xyz;
    return output;
}
"
}
SubProgram "metal " {
Keywords { "UNITY_SINGLE_PASS_STEREO" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

#ifndef XLT_REMAP_O
	#define XLT_REMAP_O {0, 1, 2, 3, 4, 5, 6, 7}
#endif
constexpr constant uint xlt_remap_o[] = XLT_REMAP_O;
struct Mtl_FragmentIn
{
    float4 COLOR0 [[ user(COLOR0) ]] ;
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float u_xlat0;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy).w;
    output.SV_Target0.w = u_xlat0 * input.COLOR0.w;
    output.SV_Target0.xyz = input.COLOR0.xyz;
    return output;
}
"
}
SubProgram "metal " {
Keywords { "STEREO_INSTANCING_ON" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

#ifndef XLT_REMAP_O
	#define XLT_REMAP_O {0, 1, 2, 3, 4, 5, 6, 7}
#endif
constexpr constant uint xlt_remap_o[] = XLT_REMAP_O;
struct Mtl_FragmentIn
{
    float4 COLOR0 [[ user(COLOR0) ]] ;
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float u_xlat0;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy).w;
    output.SV_Target0.w = u_xlat0 * input.COLOR0.w;
    output.SV_Target0.xyz = input.COLOR0.xyz;
    return output;
}
"
}
SubProgram "metal " {
Keywords { "STEREO_MULTIVIEW_ON" }
"#include <metal_stdlib>
#include <metal_texture>
using namespace metal;

#if !(__HAVE_FMA__)
#define fma(a,b,c) ((a) * (b) + (c))
#endif

#ifndef XLT_REMAP_O
	#define XLT_REMAP_O {0, 1, 2, 3, 4, 5, 6, 7}
#endif
constexpr constant uint xlt_remap_o[] = XLT_REMAP_O;
struct Mtl_FragmentIn
{
    float4 COLOR0 [[ user(COLOR0) ]] ;
    float2 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float u_xlat0;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy).w;
    output.SV_Target0.w = u_xlat0 * input.COLOR0.w;
    output.SV_Target0.xyz = input.COLOR0.xyz;
    return output;
}
"
}
}
}
}
}