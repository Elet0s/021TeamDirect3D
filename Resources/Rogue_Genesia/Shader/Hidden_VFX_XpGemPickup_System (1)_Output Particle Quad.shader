//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/VFX/XpGemPickup/System (1)/Output Particle Quad" {
Properties {
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "False" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "DepthForwardOnly" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  GpuProgramID 73119
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
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "MOTIONVECTORS" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  Stencil {
   Ref 32
   WriteMask 40
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 182593
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
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "ForwardOnly" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  GpuProgramID 217277
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
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  ZClip Off
  Cull Off
  GpuProgramID 283183
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