//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/CopyStencilBuffer" {
Properties {
_StencilRef ("_StencilRef", Float) = 1
_StencilMask ("_StencilMask", Float) = 7
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Name "Pass 0 - Copy stencilRef to output"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 40393
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
 Pass {
  Name "Pass 1 - Write 1 if value different from stencilRef to output"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp NotEqual
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 87466
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
 Pass {
  Name "Pass 2 - Export HTILE for stencilRef to output"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ColorMask 0 0
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 140277
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
 Pass {
  Name "Pass 3 - Initialize Stencil UAV copy with 1 if value different from stencilRef to output"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp NotEqual
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 223820
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
 Pass {
  Name "Pass 4 - Update Stencil UAV copy with Stencil Ref"
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   Comp Equal
   Pass Keep
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 309533
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