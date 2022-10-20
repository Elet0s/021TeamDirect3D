//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/DownsampleDepth" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  Cull Off
  GpuProgramID 54064
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "MIN_DOWNSAMPLE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MIN_DOWNSAMPLE" "OUTPUT_FIRST_MIP_OF_MIPCHAIN" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "CHECKERBOARD_DOWNSAMPLE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "CHECKERBOARD_DOWNSAMPLE" "OUTPUT_FIRST_MIP_OF_MIPCHAIN" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "MIN_DOWNSAMPLE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "MIN_DOWNSAMPLE" "OUTPUT_FIRST_MIP_OF_MIPCHAIN" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "CHECKERBOARD_DOWNSAMPLE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "CHECKERBOARD_DOWNSAMPLE" "OUTPUT_FIRST_MIP_OF_MIPCHAIN" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}