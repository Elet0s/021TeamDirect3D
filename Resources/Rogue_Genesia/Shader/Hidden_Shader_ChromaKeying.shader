//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Shader/ChromaKeying" {
Properties {
}
SubShader {
 Pass {
  Name "ChromaKeying"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 61125
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