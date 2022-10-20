//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ScriptableRenderPipeline/ShadowBlit" {
Properties {
}
SubShader {
 Pass {
  Name "BlitShadows"
  ZTest Always
  Cull Off
  GpuProgramID 45829
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