//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ScriptableRenderPipeline/ShadowClear" {
Properties {
}
SubShader {
 Pass {
  Name "ClearShadow"
  ZTest Always
  Cull Off
  GpuProgramID 18572
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