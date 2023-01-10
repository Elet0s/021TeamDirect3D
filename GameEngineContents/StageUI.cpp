#include "PreCompile.h"
#include "StageUI.h"
#include "TestLevel.h"
#include "Player.h"


StageUI::StageUI()
	: stagefontrenderer_(nullptr)
	, spacefontrenderer_(nullptr)
	, coinfontrenderer_(nullptr)
	, soulfontrenderer_(nullptr)
	, killcountfontrenderer_(nullptr)
	, timerfontRenderer_(nullptr)
	, coinrenderer_(nullptr)
	, soulrenderer_(nullptr)
	, stageboxrenderer_(nullptr)
	, spaceboxrenderer_(nullptr)
	, coinboxrenderer_(nullptr)
	, soulboxrenderer_(nullptr)
	, killcountboxrenderer_(nullptr)
	, timerboxrenderer_(nullptr)
	, IsClear_(false)
	, time_(6.0f)
	, goalCount_(0)
{
}

StageUI::~StageUI() 
{
}

void StageUI::Start()
{

	// 공용 렌더러
	{
		stagefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		spacefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		coinfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		soulfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		killcountfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		elitekillFontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		timerfontRenderer_ = CreateComponent<GameEngineFontRenderer>();
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
		stageboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		stageboxrenderer_->SetTexture("GradientRightToLeft.png");
		stageboxrenderer_->ChangeCamera(CameraOrder::UICamera);
		stageboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		stageboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 320.f });

		spaceboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		spaceboxrenderer_->SetTexture("GradientRightToLeft.png");
		spaceboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		spaceboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 260.f });
		spaceboxrenderer_->ChangeCamera(CameraOrder::UICamera);

		coinboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		coinboxrenderer_->SetTexture("GradientRightToLeft.png");
		coinboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 50.f ,1.f });
		coinboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 200.f });
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
		coinrenderer_->GetTransform().SetWorldScale(float4{ 32.f, 32.f });
		coinrenderer_->ChangeCamera(CameraOrder::UICamera);
		coinrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 200.f , -1.f });

		soulrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		soulrenderer_->SetTexture("SoulCoin.png");
		soulrenderer_->GetTransform().SetWorldScale(float4{ 32.f, 32.f });
		soulrenderer_->ChangeCamera(CameraOrder::UICamera);
		soulrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 140.f , -1.f });
	}

	// 스테이지용 랜더러 
	{
		killcountfontrenderer_->SetTextPosition(float4{ 30.f, 20.f });
		killcountfontrenderer_->SetSize(20.f);
		killcountfontrenderer_->SetColor(float4::Yellow);
		killcountfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		killcountfontrenderer_->ChangeCamera(CameraOrder::UICamera);

		elitekillFontrenderer_->SetTextPosition(float4{ 70.f, 44.f });
		elitekillFontrenderer_->SetSize(18.f);
		elitekillFontrenderer_->SetColor(float4::Yellow);
		elitekillFontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		elitekillFontrenderer_->ChangeCamera(CameraOrder::UICamera);

		killcountboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		killcountboxrenderer_->SetTexture("GradientMainMenu.png");
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 30.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ -464.f, 328.f });
		killcountboxrenderer_->ChangeCamera(CameraOrder::UICamera);
	}
	
	

	{
		

		timerfontRenderer_->SetTextPosition(float4{ 1260.f, 160.f });
		timerfontRenderer_->SetSize(24.f);
		timerfontRenderer_->SetColor(float4::White);
		timerfontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		timerfontRenderer_->ChangeCamera(CameraOrder::UICamera);

		timerboxrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		timerboxrenderer_->SetTexture("GradientRightToLeft.png");
		timerboxrenderer_->GetTransform().SetWorldScale(200.f, 64.f, 1.f);
		timerboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 170.f });
		timerboxrenderer_->ChangeCamera(CameraOrder::UICamera);
	}
}

void StageUI::Update(float _deltaTime)
{
	if (IsClear_ == false)
	{
		UIUpdate();
	}
	else
	{
		time_ -= _deltaTime;
		if (time_ < 4.5f)
		{
			int num = static_cast<int>(time_);
			elitekillFontrenderer_->Off();
			killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 30.f ,1.f });
			killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ -464.f, 328.f });
			killcountfontrenderer_->SetText("스테이지 종료까지: " + std::to_string(num));
			killcountfontrenderer_->SetColor(float4::White);
			if (time_ < 0.f)
			{
				time_ = 4.0f;
				IsClear_ = false;
				killcountfontrenderer_->SetColor(float4::Yellow);
				GEngine::ChangeLevel("Clear");
			}
		}
	}
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
		ClearSetting();
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
	elitekillFontrenderer_->Off();
	timerboxrenderer_->Off();
	timerfontRenderer_->Off();
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
	Player::GetPlayerInst()->ResetScore();
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
	stagefontrenderer_->SetText("스테이지 : " + std::to_string(Pinfo.stage_), "Free Pixel");
	
	coinfontrenderer_->SetTextPosition(float4{ 1260.f,140.f });
	coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
	coinrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 200.f , -1.f });
	coinboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 200.f });

	killcountfontrenderer_->SetTextPosition(float4{ 30.f, 20.f });
	killcountfontrenderer_->SetSize(20.f);
	killcountfontrenderer_->SetColor(float4::Yellow);
	killcountfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
	killcountboxrenderer_->SetTexture("GradientMainMenu.png");
	if (GetLevel<TestLevel>()->GetCombatType() == CombatType::EilteKill)
	{
		elitekillFontrenderer_->On();
		elitekillFontrenderer_->SetText("엘리트를 잡으세요");
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 50.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ -464.f, 318.f });

	}
	else
	{
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 30.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ -464.f, 328.f });
	}
}

void StageUI::ClearSetting()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();

	
	coinfontrenderer_->On();
	coinrenderer_->On();
	coinboxrenderer_->On();

	killcountfontrenderer_->On();
	killcountboxrenderer_->On();
	timerfontRenderer_->On();
	timerboxrenderer_->On();
	
	coinfontrenderer_->SetTextPosition(float4{ 1260.f,20.f });
	coinrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 320.f , -1.f });
	coinboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 320.f });
	coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");

	killcountfontrenderer_->SetTextPosition(float4{ 1260.f, 80.f });
	killcountfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
	killcountfontrenderer_->SetSize(24.f);
	killcountfontrenderer_->SetColor(float4::White);
	killcountfontrenderer_->SetText("처치한 적:\n" + std::to_string(Pinfo.targetScore_),"맑음");
	killcountboxrenderer_->SetTexture("GradientRightToLeft.png");
	killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 64.f ,1.f });
	killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 250.f });

	TimeSet();
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
		if (GetLevel<TestLevel>()->GetCombatType() == CombatType::Kill)
		{
			killcountfontrenderer_->SetText("처치한 몬스터: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
			if (Pinfo.targetScore_ >= goalCount_)
			{
				IsClear_ = true;
			}
		}
		
		if (GetLevel<TestLevel>()->GetCombatType() == CombatType::EilteKill)
		{
			killcountfontrenderer_->SetText("처치한 몬스터: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
			
			if (Pinfo.targetScore_ >= goalCount_)
			{
				IsClear_ = true;
			}
		}
		break;
	default:
		break;
	}
}

void StageUI::TimeSet()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();

	float Time_all;
	int Time_s;
	int Time_m;

	Time_all = Pinfo.stageTimer_; // 현재 스테이지가 시작되고 경과한 시간을 구한다

	Time_m = static_cast<int>(Time_all) / 60;		// 총 시간을 초로 바꾼뒤에 3600으로 나눠서 분을 구한다
	Time_s = static_cast<int>(Time_all) - (60 * Time_m);

	std::string num_s = std::to_string(Time_s);
	 // 세자리를 출력하기 위해 초의 자릿수를 구한후 남은 자리를 0으로 채운다.

	std::string num_m = std::to_string(Time_m);

	std::string TimeString = num_m + ":" + num_s;

	timerfontRenderer_->SetText("생존 시간:\n" + TimeString, "맑음");
}