//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/Material/Decal/DecalNormalBuffer" {
Properties {
_DecalNormalBufferStencilRef ("_DecalNormalBufferStencilRef", Float) = 0
_DecalNormalBufferStencilReadMask ("_DecalNormalBufferStencilReadMask", Float) = 0
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   WriteMask 0
   Comp Equal
   Pass Zero
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 12952
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