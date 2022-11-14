#include "PreCompile.h"
#include "Texture2DShadowRenderer.h"

Texture2DShadowRenderer::Texture2DShadowRenderer()
{
}

Texture2DShadowRenderer::~Texture2DShadowRenderer()
{
}

void Texture2DShadowRenderer::Start()
{
	GameEngineRenderer::Start();
	SetMesh("Rect");
	SetMaterial("Texture2DShadow");

	GetShaderResourceHelper().SetTexture("Tex", "tree_Group_A.png");
	GetShaderResourceHelper().SetSampler("POINTCLAMP", "POINTCLAMP");

}

void Texture2DShadowRenderer::Update(float _deltaTime)
{
}

void Texture2DShadowRenderer::End()
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
