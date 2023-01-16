#include "PreCompile.h"
#include "GameEngineBlur.h"

GameEngineBlur::GameEngineBlur() 
	: copiedRenderTarget_(nullptr)
{
}

GameEngineBlur::~GameEngineBlur()
{
	if (nullptr != copiedRenderTarget_)
	{
		delete copiedRenderTarget_;
		copiedRenderTarget_ = nullptr;
	}
}

void GameEngineBlur::EffectInit()
{
	copiedRenderTarget_ = GameEngineRenderTarget::Create();
	copiedRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);

	effectUnit_.SetMaterial("Blur");
	effectUnit_.SetMesh("Fullrect");
	effectUnit_.GetShaderResourceHelper().SetConstantBuffer_New(
		"WindowScale",
		GameEngineWindow::GetInst().GetScale()
	);
}

void GameEngineBlur::Effect(GameEngineRenderTarget* _renderTarget)
{
	copiedRenderTarget_->Copy(_renderTarget);

	effectUnit_.GetShaderResourceHelper().SetTexture("Tex", copiedRenderTarget_->GetRenderTargetTexture(0));

	_renderTarget->Clear();
	_renderTarget->SetRenderTarget();
	_renderTarget->Effect(this->effectUnit_);
}
