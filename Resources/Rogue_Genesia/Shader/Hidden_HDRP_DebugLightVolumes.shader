//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/DebugLightVolumes" {
Properties {
_Color ("Color", Color) = (1,1,1,1)
_Range ("Range", Vector) = (1,1,1,1)
_Offset ("Offset", Vector) = (1,1,1,1)
}
SubShader {
 Pass {
  Blend One One, One One
  ZWrite Off
  GpuProgramID 61629
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
  Blend One One, One One
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 119286
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