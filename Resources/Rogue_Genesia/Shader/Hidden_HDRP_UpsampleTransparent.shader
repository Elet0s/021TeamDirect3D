//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/UpsampleTransparent" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  Blend One SrcAlpha, Zero One
  ZTest Off
  ZWrite Off
  Cull Off
  GpuProgramID 58699
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "BILINEAR" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "NEAREST_DEPTH" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "BILINEAR" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "NEAREST_DEPTH" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}