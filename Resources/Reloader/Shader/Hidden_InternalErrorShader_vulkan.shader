//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/InternalErrorShader" {
Properties {
}
SubShader {
 Pass {
  GpuProgramID 18613
Program "vp" {
SubProgram "vulkan " {
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
SubProgram "vulkan " {
Keywords { "UNITY_SINGLE_PASS_STEREO" }
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
SubProgram "vulkan " {
Keywords { "STEREO_INSTANCING_ON" }
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
SubProgram "vulkan " {
Keywords { "STEREO_MULTIVIEW_ON" }
"// shader disassembly not supported on SPIR-V
// https://github.com/KhronosGroup/SPIRV-Cross"
}
}
Program "fp" {
SubProgram "vulkan " {
""
}
SubProgram "vulkan " {
Keywords { "UNITY_SINGLE_PASS_STEREO" }
""
}
SubProgram "vulkan " {
Keywords { "STEREO_INSTANCING_ON" }
""
}
SubProgram "vulkan " {
Keywords { "STEREO_MULTIVIEW_ON" }
""
}
}
}
}
}