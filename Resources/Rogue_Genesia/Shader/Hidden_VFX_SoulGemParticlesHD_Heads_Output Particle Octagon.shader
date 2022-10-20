//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/VFX/SoulGemParticlesHD/Heads/Output Particle Octagon" {
Properties {
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent+0" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "ForwardOnly" "QUEUE" = "Transparent+0" "RenderType" = "Transparent" }
  Blend SrcAlpha One, SrcAlpha One
  ZWrite Off
  Cull Off
  GpuProgramID 124016
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