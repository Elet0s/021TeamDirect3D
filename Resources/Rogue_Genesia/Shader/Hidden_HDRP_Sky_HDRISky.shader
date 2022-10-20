//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/Sky/HDRISky" {
Properties {
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 7579
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
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
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZWrite Off
  Cull Off
  GpuProgramID 124487
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
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
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 157496
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
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
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Cull Off
  GpuProgramID 228346
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
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
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "SKY_MOTION" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
Local Keywords { "USE_FLOWMAP" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHADOW_MEDIUM" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}