#include "PreCompile.h"
#include "StageUI.h"


StageUI::StageUI() 
	: stagefontrenderer_(nullptr)
	, spacefontrenderer_(nullptr)
	, coinfontrenderer_(nullptr)
	, soulfontrenderer_(nullptr)
	, coinrenderer_(nullptr)
	, soulrenderer_(nullptr)
	, stageboxrenderer_(nullptr)
	, spaceboxrenderer_(nullptr)
	, coinboxrenderer_(nullptr)
	, soulboxrenderer_(nullptr)
{
}

StageUI::~StageUI() 
{
}

void StageUI::Start()
{

	

	{
		stagefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		spacefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		coinfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		soulfontrenderer_ = CreateComponent<GameEngineFontRenderer>();

		float X = 1260.f;
		float Size = 30.f;
		stagefontrenderer_->SetTextPosition(float4{ X,20.f });
		stagefontrenderer_->SetSize(Size);
		stagefontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		stagefontrenderer_->SetText("스테이지 : 0", "Free Pixel");
		stagefontrenderer_->ChangeCamera(CameraOrder::UICamera);

		spacefontrenderer_->SetTextPosition(float4{ X,80.f });
		spacefontrenderer_->SetSize(Size);
		spacefontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		spacefontrenderer_->SetText("공간 : 1 ", "Free Pixel");
		spacefontrenderer_->ChangeCamera(CameraOrder::UICamera);

		coinfontrenderer_->SetTextPosition(float4{ X,140.f });
		coinfontrenderer_->SetSize(Size);
		coinfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		coinfontrenderer_->SetText("100", "Free Pixel");
		coinfontrenderer_->ChangeCamera(CameraOrder::UICamera);

		soulfontrenderer_->SetTextPosition(float4{ X,200.f });
		soulfontrenderer_->SetSize(Size);
		soulfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		soulfontrenderer_->SetText("+ 0", "Free Pixel");
		soulfontrenderer_->ChangeCamera(CameraOrder::UICamera);
	}
	
	{
		stageboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		stageboxrenderer_->SetTexture("GradientRightToLeft.png");
		stageboxrenderer_->ChangeCamera(CameraOrder::UICamera);
		stageboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		stageboxrenderer_->GetTransform().SetWorldMove(float4{ 540.f, 320.f});

		spaceboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		spaceboxrenderer_->SetTexture("GradientRightToLeft.png");
		spaceboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		spaceboxrenderer_->GetTransform().SetWorldMove(float4{ 540.f, 260.f });
		spaceboxrenderer_->ChangeCamera(CameraOrder::UICamera);

		coinboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		coinboxrenderer_->SetTexture("GradientRightToLeft.png");
		coinboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		coinboxrenderer_->GetTransform().SetWorldMove(float4{ 540.f, 200.f });
		coinboxrenderer_->ChangeCamera(CameraOrder::UICamera);

		soulboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		soulboxrenderer_->SetTexture("GradientRightToLeft.png");
		soulboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		soulboxrenderer_->GetTransform().SetWorldMove(float4{ 540.f, 140.f });
		soulboxrenderer_->ChangeCamera(CameraOrder::UICamera);
	}

	{
		coinrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		coinrenderer_->SetTexture("SmallCoin.png");
		coinrenderer_->GetTransform().SetWorldScale(float4{ 32.f, 32.f});
		coinrenderer_->ChangeCamera(CameraOrder::UICamera);
		coinrenderer_->GetTransform().SetWorldMove(float4{ 460.f, 200.f , -1.f});

		soulrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		soulrenderer_->SetTexture("SoulCoin.png");
		soulrenderer_->GetTransform().SetWorldScale(float4{ 32.f, 32.f });
		soulrenderer_->ChangeCamera(CameraOrder::UICamera);
		soulrenderer_->GetTransform().SetWorldMove(float4{ 460.f, 140.f , -1.f });
	}


}

void StageUI::Update(float _deltaTime)
{

}

void StageUI::End()
{

}

void StageUI::SoulCoinRenderersOff()
{
	soulrenderer_->Off();
	soulboxrenderer_->Off();
	soulfontrenderer_->Off();
}

void StageUI::SoulCoinRenderersOn()
{
	soulrenderer_->On();
	soulboxrenderer_->On();
	soulfontrenderer_->On();
}
