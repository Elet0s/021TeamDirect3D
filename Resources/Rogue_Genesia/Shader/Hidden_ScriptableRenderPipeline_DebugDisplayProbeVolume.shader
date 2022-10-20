//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ScriptableRenderPipeline/DebugDisplayProbeVolume" {
Properties {
}
SubShader {
 Pass {
  Name "ProbeVolume"
  ZTest Off
  Cull Off
  GpuProgramID 17047
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