#include "PreCompile.h"
#include "Texture2DShadowRenderer.h"

Texture2DShadowRenderer::Texture2DShadowRenderer(): isAnimation_(false)
{
}

Texture2DShadowRenderer::~Texture2DShadowRenderer()
{
}

void Texture2DShadowRenderer::Start()
{
	GameEngineRenderer::Start();
	SetMesh("Rect");
	SetMaterial("DeferredShadowRendering");
	SetShadowRendering();
	GetShaderResourceHelper().SetSampler("POINTCLAMP", "POINTCLAMP");
}

void Texture2DShadowRenderer::Update(float _deltaTime)
{
	if (true == isAnimation_)
		//부모 텍스처렌더러가 애니메이션일때만 업데이트를 한다.
	{
		GetShaderResourceHelper().SetConstantBuffer_Link(
			"AtlasData", parentTextureRenderer_->GetAtlasData());
		GetShaderResourceHelper().SetTexture(
			"Tex", parentTextureRenderer_->GetCurrentTexture());

		if (0.f >= parentTextureRenderer_->GetTransform().GetWorldScale().x)
			//부모 텍스처렌더러가 좌우반전되면 vertexInversion_에 -1을 넣어서 버텍스셰이더로 전달한다.
		{
			renderOptionInst_.vertexInversion_ = -1;
		}
		else
		{
			renderOptionInst_.vertexInversion_ = 1;
		}

		if (1.f != renderOptionInst_.vertexInversion_ && -1.f != renderOptionInst_.vertexInversion_)
		{
			MsgBoxAssert("VertexInversion은 1과 -1만 허용됩니다.");
			return;
		}
	}
}

void Texture2DShadowRenderer::End()
{
}

void Texture2DShadowRenderer::SetTextureRenderer(GameEngineTextureRenderer* _textureRenderer)
{
	if (nullptr == _textureRenderer)
	{
		MsgBoxAssert("텍스처렌더러가 없습니다.");
		return;
	}

	this->SetParent(_textureRenderer);
	parentTextureRenderer_ = _textureRenderer;
	SetRenderingOrder(parentTextureRenderer_->GetRenderingOrder() + 2);

	GetShaderResourceHelper().SetConstantBuffer_Link(
		"AtlasData", parentTextureRenderer_->GetAtlasData());
	GetShaderResourceHelper().SetTexture(
		"Tex", parentTextureRenderer_->GetCurrentTexture());

	if (true == parentTextureRenderer_->IsCurAnimation())
	{
		isAnimation_ = true;
	}
}

void Texture2DShadowRenderer::SetShadowAngle(float _angle /*= 30.f*/)
{
	renderOptionInst_.shadowAngle_ = _angle;	//그림자 기본값 30도.
	GetShaderResourceHelper().SetConstantBuffer_Link("RenderOption", renderOptionInst_);
}