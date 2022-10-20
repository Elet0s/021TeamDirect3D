//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/BlitColorAndDepth" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 50310
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  Cull Off
  GpuProgramID 123676
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "BLIT_SINGLE_SLICE" "DISABLE_TEXTURE2D_X_ARRAY" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}