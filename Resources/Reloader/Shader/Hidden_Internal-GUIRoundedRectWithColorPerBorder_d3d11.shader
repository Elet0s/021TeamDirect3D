//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-GUIRoundedRectWithColorPerBorder" {
Properties {
_MainTex ("Texture", any) = "white" { }
_SrcBlend ("SrcBlend", Float) = 5
_DstBlend ("DstBlend", Float) = 10
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 54034
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
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 98697
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
Fallback "Hidden/Internal-GUITextureClip"
}