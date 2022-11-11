#include "PreCompile.h"
#include "GameEngineFontRenderer.h"
#include "GameEngineFont.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineBlend.h"
#include "GameEngineCamera.h"

std::shared_ptr<GameEngineRenderTarget> GameEngineFontRenderer::fontTarget_ = nullptr;

GameEngineFontRenderer::GameEngineFontRenderer()
	:font_(nullptr),
	fontSize_(20.f),
	fontColor_(float4::White),
	textPosition_(float4::Zero),
	lr_(LeftAndRightSort::Left),
	tb_(TopAndBotSort::Top),
	mode_(FontPositionMode::Window)
{
}

GameEngineFontRenderer::~GameEngineFontRenderer()
{
}

void GameEngineFontRenderer::SetText(const std::string_view& _text, const std::string_view& _font /*= "돋움"*/)
{
	text_ = _text;
	font_ = GameEngineFont::Find(_font);

	if (nullptr == font_)
	{
		MsgBoxAssertString(std::string(_font) + ": 그런 이름의 폰트가 없습니다.");
		return;
	}
}

void GameEngineFontRenderer::Start()
{
	if (nullptr == fontTarget_)
	{
		fontTarget_ = GameEngineRenderTarget::Create("Font Target");
		fontTarget_->CreateRenderTargetTexture(GameEngineWindow::GetScale(), float4::Zero);
	}

	PushRendererToMainCamera();
}

void GameEngineFontRenderer::Render(float _deltaTime)
{
	if (nullptr == font_)
	{
		return;
	}

	float4 position = float4::Zero;
	if (FontPositionMode::World == mode_)
	{
		position = this->GetTransform().GetWorldPosition();
		position *= camera_.lock()->GetViewMatrix();
		position *= camera_.lock()->GetProjectionMatrix();

		float4 windowSize = GameEngineWindow::GetScale();

		float4x4 viewPortMatrix;
		viewPortMatrix.Viewport(windowSize.x, windowSize.y, 0.f, 0.f, 0.f, 1.f);

		position *= viewPortMatrix;
	}
	else if (FontPositionMode::Window == mode_)
	{
		position = textPosition_;
	}

	fontTarget_->Clear();
	fontTarget_->Setting();
	font_->FontDraw(text_, fontSize_, position, fontColor_,
		static_cast<int>(lr_) | static_cast<int>(tb_));
	GameEngineMaterial::AllShaderReset();

	camera_.lock()->GetCameraRenderTarget()->Merge(fontTarget_);
}
