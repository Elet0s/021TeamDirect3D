//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/PostProcessing/FinalPass" {
Properties {
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 45002
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
}
}
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 73575
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA" "FXAA_KEEP_ALPHA" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_INSTANCING_ENABLED" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FXAA_KEEP_ALPHA" "FXAA_LOW" "STEREO_DOUBLEWIDE_TARGET" }
"// shader disassembly not supported on DXBC"
}
}
}
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 154787
}
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 261448
}
}
}