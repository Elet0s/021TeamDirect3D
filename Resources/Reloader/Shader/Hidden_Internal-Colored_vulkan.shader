//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-Colored" {
Properties {
_Color ("Color", Color) = (1,1,1,1)
_SrcBlend ("SrcBlend", Float) = 5
_DstBlend ("DstBlend", Float) = 10
_ZWrite ("ZWrite", Float) = 1
_ZTest ("ZTest", Float) = 4
_Cull ("Cull", Float) = 0
_ZBias ("ZBias", Float) = 0
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  ZTest Off
  ZWrite Off
  Cull Off
  GpuProgramID 18665
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