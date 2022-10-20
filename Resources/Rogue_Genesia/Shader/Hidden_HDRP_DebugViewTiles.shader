//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/HDRP/DebugViewTiles" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "HDRenderPipeline" }
 Pass {
  Tags { "RenderPipeline" = "HDRenderPipeline" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 35619
Program "vp" {
SubProgram "d3d11 " {
Keywords { "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_FPTL_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_LIGHT_CATEGORIES" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "DISABLE_TILE_MODE" "IS_DRAWPROCEDURALINDIRECT" "SHOW_FEATURE_VARIANTS" "USE_CLUSTERED_LIGHTLIST" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}