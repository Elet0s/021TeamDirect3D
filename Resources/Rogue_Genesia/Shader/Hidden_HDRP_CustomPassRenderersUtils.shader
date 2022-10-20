//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/CustomPassRenderersUtils" {
Properties {
}
SubShader {
 Pass {
  Name "DepthToColorPass"
  Tags { "LIGHTMODE" = "DepthToColorPass" }
  ZWrite Off
  GpuProgramID 34336
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
  Name "DepthPass"
  Tags { "LIGHTMODE" = "DepthPass" }
  ColorMask 0 0
  GpuProgramID 130858
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
  Name "NormalToColorPass"
  Tags { "LIGHTMODE" = "NormalToColorPass" }
  ZWrite Off
  GpuProgramID 174441
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
  Name "TangentToColorPass"
  Tags { "LIGHTMODE" = "TangentToColorPass" }
  ZWrite Off
  GpuProgramID 260386
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