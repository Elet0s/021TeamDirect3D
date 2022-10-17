//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FrameDebuggerRenderTargetDisplay" {
Properties {
_MainTex ("", any) = "white" { }
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 51439
Program "vp" {
SubProgram "vulkan " {
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
}
Program "fp" {
SubProgram "vulkan " {
""
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 114367
Program "vp" {
SubProgram "vulkan " {
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
}
Program "fp" {
SubProgram "vulkan " {
""
}
}
}
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 175888
Program "vp" {
SubProgram "vulkan " {
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
}
Program "fp" {
SubProgram "vulkan " {
""
}
}
}
}
}