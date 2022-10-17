//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "GUI/Text Shader" {
Properties {
_MainTex ("Font Texture", 2D) = "white" { }
_Color ("Text Color", Color) = (1,1,1,1)
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 33352
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