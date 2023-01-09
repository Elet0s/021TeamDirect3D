#include "PreCompile.h"
#include "GameEngineBlur.h"
#include "GameEngineRenderTarget.h"

GameEngineBlur::GameEngineBlur() 
	: copiedRenderTarget_(nullptr),
	effectUnit_(std::make_shared<GameEngineRenderUnit>())
{
}

GameEngineBlur::~GameEngineBlur()
{
	//if (nullptr != copiedRenderTarget_)
	//{
	//	delete copiedRenderTarget_;
	//	copiedRenderTarget_ = nullptr;
	//}
}

void GameEngineBlur::EffectInit()
{
	copiedRenderTarget_ = GameEngineRenderTarget::Create();
	copiedRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);

	effectUnit_->SetMaterial("Blur");
	effectUnit_->SetMesh("Fullrect");
	effectUnit_->GetShaderResourceHelper().SetConstantBuffer_New(
		"WindowScale",
		GameEngineWindow::GetInst()->GetScale()
	);
}

void GameEngineBlur::Effect(std::shared_ptr<GameEngineRenderTarget> _renderTarget)
{
	copiedRenderTarget_->Copy(_renderTarget);

	effectUnit_->GetShaderResourceHelper().SetTexture("Tex", copiedRenderTarget_->GetRenderTargetTexture(0));

	_renderTarget->Clear();
	_renderTarget->SetRenderTarget();
	_renderTarget->Effect(this->effectUnit_);
}
