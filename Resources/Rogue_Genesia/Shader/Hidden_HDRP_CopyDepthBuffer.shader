//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/CopyDepthBuffer" {
Properties {
_FlipY ("FlipY", Float) = 0
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Name "Copy Depth"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ColorMask 0 0
  ZTest Always
  Cull Off
  GpuProgramID 65229
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