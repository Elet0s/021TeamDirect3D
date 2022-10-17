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
SubProgram "gles " {
"#ifdef VERTEX
#version 100

uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
attribute highp vec4 in_POSITION0;
attribute highp vec3 in_TEXCOORD0;
varying highp vec3 vs_TEXCOORD0;
vec4 u_xlat0;
vec4 u_xlat1;
void main()
{
    u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
    u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
    u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
    u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
    u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
    gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
    vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
    return;
}

#endif
#ifdef FRAGMENT
#version 100

#ifdef GL_FRAGMENT_PRECISION_HIGH
    precision highp float;
#else
    precision mediump float;
#endif
precision highp int;
uniform 	mediump vec4 _Channels;
uniform 	mediump vec4 _Levels;
uniform 	int _UndoOutputSRGB;
uniform highp sampler2D _MainTex;
varying highp vec3 vs_TEXCOORD0;
#define SV_Target0 gl_FragData[0]
vec4 u_xlat0;
mediump vec4 u_xlat16_0;
mediump vec3 u_xlat16_1;
vec3 u_xlat2;
mediump vec3 u_xlat16_2;
bool u_xlatb2;
mediump float u_xlat16_4;
void main()
{
    u_xlat0 = texture2D(_MainTex, vs_TEXCOORD0.xy);
    u_xlat16_0 = u_xlat0 + (-_Levels.xxxx);
    u_xlat16_1.x = (-_Levels.x) + _Levels.y;
    u_xlat16_0 = u_xlat16_0 / u_xlat16_1.xxxx;
    u_xlat16_0 = u_xlat16_0 * _Channels;
    u_xlat16_1.x = dot(u_xlat16_0, vec4(1.0, 1.0, 1.0, 1.0));
    u_xlat16_4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
    u_xlatb2 = u_xlat16_4==1.0;
    u_xlat16_0 = (bool(u_xlatb2)) ? u_xlat16_1.xxxx : u_xlat16_0;
    u_xlat16_1.xyz = u_xlat16_0.xyz;
    u_xlat16_1.xyz = clamp(u_xlat16_1.xyz, 0.0, 1.0);
    u_xlat16_2.xyz = u_xlat16_1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
    u_xlat16_2.xyz = u_xlat16_1.xyz * u_xlat16_2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
    u_xlat2.xyz = u_xlat16_1.xyz * u_xlat16_2.xyz;
    SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat16_0.xyz;
    SV_Target0.w = u_xlat16_0.w;
    return;
}

#endif
"
}
}
Program "fp" {
SubProgram "gles " {
""
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 114367
Program "vp" {
SubProgram "gles " {
"#ifdef VERTEX
#version 100

uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
attribute highp vec4 in_POSITION0;
attribute highp vec3 in_TEXCOORD0;
varying highp vec3 vs_TEXCOORD0;
vec4 u_xlat0;
vec4 u_xlat1;
void main()
{
    u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
    u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
    u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
    u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
    u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
    u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
    u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
    gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
    vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
    return;
}

#endif
#ifdef FRAGMENT
#version 100

#ifdef GL_FRAGMENT_PRECISION_HIGH
    precision highp float;
#else
    precision mediump float;
#endif
precision highp int;
uniform 	mediump vec4 _Channels;
uniform 	mediump vec4 _Levels;
uniform 	int _UndoOutputSRGB;
uniform highp samplerCube _MainTex;
varying highp vec3 vs_TEXCOORD0;
#define SV_Target0 gl_FragData[0]
vec4 u_xlat0;
mediump vec4 u_xlat16_0;
mediump vec3 u_xlat16_1;
vec3 u_xlat2;
mediump vec3 u_xlat16_2;
bool u_xlatb2;
mediump float u_xlat16_4;
void main()
{
    u_xlat0 = textureCube(_MainTex, vs_TEXCOORD0.xyz);
    u_xlat16_0 = u_xlat0 + (-_Levels.xxxx);
    u_xlat16_1.x = (-_Levels.x) + _Levels.y;
    u_xlat16_0 = u_xlat16_0 / u_xlat16_1.xxxx;
    u_xlat16_0 = u_xlat16_0 * _Channels;
    u_xlat16_1.x = dot(u_xlat16_0, vec4(1.0, 1.0, 1.0, 1.0));
    u_xlat16_4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
    u_xlatb2 = u_xlat16_4==1.0;
    u_xlat16_0 = (bool(u_xlatb2)) ? u_xlat16_1.xxxx : u_xlat16_0;
    u_xlat16_1.xyz = u_xlat16_0.xyz;
    u_xlat16_1.xyz = clamp(u_xlat16_1.xyz, 0.0, 1.0);
    u_xlat16_2.xyz = u_xlat16_1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
    u_xlat16_2.xyz = u_xlat16_1.xyz * u_xlat16_2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
    u_xlat2.xyz = u_xlat16_1.xyz * u_xlat16_2.xyz;
    SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat16_0.xyz;
    SV_Target0.w = u_xlat16_0.w;
    return;
}

#endif
"
}
}
Program "fp" {
SubProgram "gles " {
""
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
}
Program "fp" {
}
}
}
}