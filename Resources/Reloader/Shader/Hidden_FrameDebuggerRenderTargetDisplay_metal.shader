//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FrameDebuggerRenderTargetDisplay" {
Properties {
_MainTex ("", any) = "white" { }
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 51439
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
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float3 TEXCOORD0 [[ attribute(1) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]];
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
    output.TEXCOORD0.xyz = input.TEXCOORD0.xyz;
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
struct FGlobals_Type
{
    float4 _Channels;
    float4 _Levels;
    int _UndoOutputSRGB;
};

struct Mtl_FragmentIn
{
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    constant FGlobals_Type& FGlobals [[ buffer(0) ]],
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float4 u_xlat0;
    float3 u_xlat1;
    float3 u_xlat2;
    float u_xlat4;
    bool u_xlatb4;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy);
    u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
    u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
    u_xlat0 = u_xlat0 / u_xlat1.xxxx;
    u_xlat0 = u_xlat0 * FGlobals._Channels;
    u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
    u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
    u_xlatb4 = u_xlat4==1.0;
    u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
    u_xlat1.xyz = u_xlat0.xyz;
    u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
    u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
    u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
    u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
    output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
    output.SV_Target0.w = u_xlat0.w;
    return output;
}
"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 114367
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
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float3 TEXCOORD0 [[ attribute(1) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]];
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
    output.TEXCOORD0.xyz = input.TEXCOORD0.xyz;
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
struct FGlobals_Type
{
    float4 _Channels;
    float4 _Levels;
    int _UndoOutputSRGB;
};

struct Mtl_FragmentIn
{
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    constant FGlobals_Type& FGlobals [[ buffer(0) ]],
    sampler sampler_MainTex [[ sampler (0) ]],
    texturecube<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float4 u_xlat0;
    float3 u_xlat1;
    float3 u_xlat2;
    float u_xlat4;
    bool u_xlatb4;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xyz);
    u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
    u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
    u_xlat0 = u_xlat0 / u_xlat1.xxxx;
    u_xlat0 = u_xlat0 * FGlobals._Channels;
    u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
    u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
    u_xlatb4 = u_xlat4==1.0;
    u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
    u_xlat1.xyz = u_xlat0.xyz;
    u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
    u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
    u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
    u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
    output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
    output.SV_Target0.w = u_xlat0.w;
    return output;
}
"
}
}
}
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 175888
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
};

struct Mtl_VertexIn
{
    float4 POSITION0 [[ attribute(0) ]] ;
    float3 TEXCOORD0 [[ attribute(1) ]] ;
};

struct Mtl_VertexOut
{
    float4 mtl_Position [[ position ]];
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]];
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
    output.TEXCOORD0.xyz = input.TEXCOORD0.xyz;
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
struct FGlobals_Type
{
    float4 _Channels;
    float4 _Levels;
    int _UndoOutputSRGB;
};

struct Mtl_FragmentIn
{
    float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
};

struct Mtl_FragmentOut
{
    float4 SV_Target0 [[ color(xlt_remap_o[0]) ]];
};

fragment Mtl_FragmentOut xlatMtlMain(
    constant FGlobals_Type& FGlobals [[ buffer(0) ]],
    sampler sampler_MainTex [[ sampler (0) ]],
    texture2d_array<float, access::sample > _MainTex [[ texture(0) ]] ,
    Mtl_FragmentIn input [[ stage_in ]])
{
    Mtl_FragmentOut output;
    float4 u_xlat0;
    float3 u_xlat1;
    float3 u_xlat2;
    float u_xlat4;
    bool u_xlatb4;
    u_xlat0 = _MainTex.sample(sampler_MainTex, input.TEXCOORD0.xy, round(input.TEXCOORD0.z));
    u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
    u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
    u_xlat0 = u_xlat0 / u_xlat1.xxxx;
    u_xlat0 = u_xlat0 * FGlobals._Channels;
    u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
    u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
    u_xlatb4 = u_xlat4==1.0;
    u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
    u_xlat1.xyz = u_xlat0.xyz;
    u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
    u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
    u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
    u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
    output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
    output.SV_Target0.w = u_xlat0.w;
    return output;
}
"
}
}
}
}
}