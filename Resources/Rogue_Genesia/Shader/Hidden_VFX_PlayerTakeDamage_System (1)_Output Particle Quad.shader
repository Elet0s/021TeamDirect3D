//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/VFX/PlayerTakeDamage/System (1)/Output Particle Quad" {
Properties {
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent+0" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "ForwardOnly" "QUEUE" = "Transparent+0" "RenderType" = "Transparent" }
  Blend 0 SrcAlpha One, SrcAlpha One
  Blend 1 SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZWrite Off
  Cull Off
  GpuProgramID 107975
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
  Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent+0" "RenderType" = "Transparent" }
  Blend 1 SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZClip Off
  Cull Off
  GpuProgramID 168400
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