//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/OpaqueAtmosphericScattering" {
Properties {
}
SubShader {
 Pass {
  Blend One SrcAlpha, Zero One
  ZTest Less
  ZWrite Off
  Cull Off
  GpuProgramID 33104
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
 Pass {
  Blend One SrcAlpha, Zero One
  ZTest Less
  ZWrite Off
  Cull Off
  GpuProgramID 130002
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
 Pass {
  ZTest Less
  ZWrite Off
  Cull Off
  GpuProgramID 168123
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
 Pass {
  ZTest Less
  ZWrite Off
  Cull Off
  GpuProgramID 234295
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