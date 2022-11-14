#include "PreCompile.h"
#include "ContentsTextureShadowRenderer.h"

ContentsTextureShadowRenderer::ContentsTextureShadowRenderer():shadowColor_(float4::Red)
{
}

ContentsTextureShadowRenderer::~ContentsTextureShadowRenderer()
{
}

void ContentsTextureShadowRenderer::Start()
{
	//SetMesh("Rect");
	//SetMaterial("TextureShadow");
	//GetRenderUnit().GetShaderResourceHelper().SetConstantBuffer_Link("ShadowColor", shadowColor_);
	//GetRenderUnit().GetShaderResourceHelper().SetSampler("LINEARCLAMP", "LINEARCLAMP");
}

void ContentsTextureShadowRenderer::Update(float _deltaTime)
{
}

void ContentsTextureShadowRenderer::End()
{
}

//void ContentsTextureShadowRenderer::SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer)
//{
//	if (nullptr == _textureRenderer)
//	{
//		MsgBoxAssert("텍스처렌더러가 없습니다.");
//		return;
//	}
//
//	this->GetTransform().SetWorldPosition(_textureRenderer->GetTransform().GetWorldPosition());
//	GetRenderUnit().GetShaderResourceHelper().SetTexture("Tex",_textureRenderer->GetCurrentTexture());
//
//
//}
