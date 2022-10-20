//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/VFX/DesertFoliageSpawner/System (3)/Output Particle Lit Quad" {
Properties {
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "False" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "DepthOnly" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  GpuProgramID 116088
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "WRITE_NORMAL_BUFFER" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "WRITE_NORMAL_BUFFER" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "GBuffer" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  Stencil {
   Ref 2
   WriteMask 6
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 189727
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHT_LAYERS" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "LIGHT_LAYERS" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "Forward" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  Cull Off
  GpuProgramID 239536
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Tags { "IGNOREPROJECTOR" = "False" "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Geometry+450" "RenderType" = "Opaque" }
  ZClip Off
  Cull Off
  GpuProgramID 321430
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