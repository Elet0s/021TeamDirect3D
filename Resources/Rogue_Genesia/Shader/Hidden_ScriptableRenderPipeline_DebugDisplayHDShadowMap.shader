//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ScriptableRenderPipeline/DebugDisplayHDShadowMap" {
Properties {
}
SubShader {
 Pass {
  Name "RegularShadow"
  ZTest Off
  Cull Off
  GpuProgramID 45926
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
  Name "VarianceShadow"
  ZTest Off
  Cull Off
  GpuProgramID 98710
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