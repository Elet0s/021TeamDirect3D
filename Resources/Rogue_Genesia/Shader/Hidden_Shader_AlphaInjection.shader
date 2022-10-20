//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Shader/AlphaInjection" {
Properties {
}
SubShader {
 Pass {
  Name "AlphaInjection"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 53302
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}