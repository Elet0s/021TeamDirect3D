#include "PreCompile.h"
#include "StageUI.h"
#include "Player.h"


StageUI::StageUI() 
	: stagefontrenderer_(nullptr)
	, spacefontrenderer_(nullptr)
	, coinfontrenderer_(nullptr)
	, soulfontrenderer_(nullptr)
	, killcountfontrenderer_(nullptr)
	, coinrenderer_(nullptr)
	, soulrenderer_(nullptr)
	, stageboxrenderer_(nullptr)
	, spaceboxrenderer_(nullptr)
	, coinboxrenderer_(nullptr)
	, soulboxrenderer_(nullptr)
	, killcountboxrenderer_(nullptr)
	, goalCount_(0)
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
		killcountfontrenderer_ = CreateComponent<GameEngineFontRenderer>();

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
		spacefontrenderer_->SetText("진영 : 1/1 ", "Free Pixel");
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
		killcountfontrenderer_->SetTextPosition(float4{ 30.f, 20.f });
		killcountfontrenderer_->SetSize(20.f);
		killcountfontrenderer_->SetColor(float4::Yellow);
		killcountfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		killcountfontrenderer_->ChangeCamera(CameraOrder::UICamera);

		killcountboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		killcountboxrenderer_->SetTexture("GradientMainMenu.png");
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 30.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldMove(float4{ -464.f, 328.f });
		killcountboxrenderer_->ChangeCamera(CameraOrder::UICamera);
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
	UIUpdate();
}

void StageUI::End()
{

}

void StageUI::SetUI(UIType _type)
{
	AllOff();
	switch (_type)
	{
	case UIType::World:
		WorldSetting();
		break;
	case UIType::Stage:
		StageSetting();
		break;
	case UIType::Claer:
		break;
	default:
		break;
	}
	mytype_ = _type;
}

void StageUI::AllOff()
{
	stagefontrenderer_->Off();
	spacefontrenderer_->Off();
	coinfontrenderer_->Off();
	soulfontrenderer_->Off();
	coinrenderer_->Off();
	soulrenderer_->Off();
	stageboxrenderer_->Off();
	spaceboxrenderer_->Off();
	coinboxrenderer_->Off();
	soulboxrenderer_->Off();
	killcountfontrenderer_->Off();
	killcountboxrenderer_->Off();
}

void StageUI::WorldSetting()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();
	stagefontrenderer_->On();
	spacefontrenderer_->On();
	coinfontrenderer_->On();
	soulfontrenderer_->On();
	coinrenderer_->On();
	soulrenderer_->On();
	stageboxrenderer_->On();
	spaceboxrenderer_->On();
	coinboxrenderer_->On();
	soulboxrenderer_->On();

	SetCoinText(std::to_string(Pinfo.gold_));
	SetStageText(std::to_string(Pinfo.stage_));
}

void StageUI::StageSetting()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();

	stagefontrenderer_->On();
	spacefontrenderer_->On();
	coinfontrenderer_->On();
	coinrenderer_->On();
	stageboxrenderer_->On();
	spaceboxrenderer_->On();
	coinboxrenderer_->On();
	killcountfontrenderer_->On();
	killcountboxrenderer_->On();
	goalCount_ = 10;
	coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
	stagefontrenderer_->SetText("스테이지 : " + std::to_string(Pinfo.stage_), "Free Pixel");
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


void StageUI::UIUpdate()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();
	switch (mytype_)
	{
	case UIType::World:
		break;
	case UIType::Stage:
		coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
		killcountfontrenderer_->SetText("처치한 몬스터: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
		if (Pinfo.targetScore_ >= goalCount_)
		{
			GEngine::ChangeLevel("Clear");
		}
		break;
	case UIType::Claer:
		break;
	default:
		break;
	}
}