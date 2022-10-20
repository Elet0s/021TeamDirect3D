//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/CustomPassUtils" {
Properties {
}
SubShader {
 Pass {
  Name "Copy"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 52279
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
  Name "Downsample"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 85065
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
  Name "HorizontalBlur"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 131599
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
  Name "VerticalBlur"
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 245807
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