#include "PreCompile.h"
#include "StageUI.h"
#include "StageObject.h"
#include "Monster.h"
#include "TestLevel.h"
#include "Player.h"


StageUI::StageUI()
	: stagefontrenderer_(nullptr)
	, spacefontrenderer_(nullptr)
	, coinfontrenderer_(nullptr)
	, killcountfontrenderer_(nullptr)
	, timerfontRenderer_(nullptr)
	, coinrenderer_(nullptr)
	, stageboxrenderer_(nullptr)
	, spaceboxrenderer_(nullptr)
	, coinboxrenderer_(nullptr)
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

	// ���� ������
	{
		stagefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		spacefontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		coinfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		killcountfontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		elitekillFontrenderer_ = CreateComponent<GameEngineFontRenderer>();
		timerfontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		float X = 1260.f;
		float Size = 30.f;
		stagefontrenderer_->SetTextPosition(float4{ X,20.f });
		stagefontrenderer_->SetSize(Size);
		stagefontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		stagefontrenderer_->SetText("�������� : 0", "Free Pixel");
		stagefontrenderer_->ChangeCamera(CameraOrder::UICamera);

		spacefontrenderer_->SetTextPosition(float4{ X,80.f });
		spacefontrenderer_->SetSize(Size);
		spacefontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		spacefontrenderer_->SetText("���� : 1/1 ", "Free Pixel");
		spacefontrenderer_->ChangeCamera(CameraOrder::UICamera);

		coinfontrenderer_->SetTextPosition(float4{ X,140.f });
		coinfontrenderer_->SetSize(Size);
		coinfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		coinfontrenderer_->SetText("100", "Free Pixel");
		coinfontrenderer_->ChangeCamera(CameraOrder::UICamera);

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

	}

	{
		coinrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		coinrenderer_->SetTexture("SmallCoin.png");
		coinrenderer_->GetTransform().SetWorldScale(float4{ 32.f, 32.f });
		coinrenderer_->ChangeCamera(CameraOrder::UICamera);
		coinrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 200.f , -1.f });
	}

	// ���������� ������ 
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
			killcountfontrenderer_->SetText("�������� �������: " + std::to_string(num));
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
	case UIType::Shop:
		WorldSetting();
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
	coinrenderer_->Off();
	stageboxrenderer_->Off();
	spaceboxrenderer_->Off();
	coinboxrenderer_->Off();
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
	coinrenderer_->On();
	stageboxrenderer_->On();
	spaceboxrenderer_->On();
	coinboxrenderer_->On();

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
	goalCount_ = StageObject::GetNextStageInfo().killCount_;
	stagefontrenderer_->SetText("�������� : " + std::to_string(Pinfo.stage_), "Free Pixel");
	
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
		elitekillFontrenderer_->SetTextPosition(float4{ 30.f, 44.f });
		elitekillFontrenderer_->SetSize(18.f);
		elitekillFontrenderer_->SetText("����Ʈ�� ��������");
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 350.f, 50.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ -464.f, 318.f });

	}
	else if (StageObject::GetNextStageInfo().combatType_ == CombatType::TimeAttack)
	{
		elitekillFontrenderer_->On();
		elitekillFontrenderer_->SetTextPosition(float4{ 30.f, 44.f });
		elitekillFontrenderer_->SetSize(20.f);
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

	coinfontrenderer_->SetTextPosition(float4{ 1260.f,20.f });
	coinrenderer_->GetTransform().SetWorldPosition(float4{ 460.f, 320.f , -1.f });
	coinboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 320.f });
	coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
	if (StageObject::GetNextStageInfo().stageType_ != StageType::Chest)
	{
		killcountfontrenderer_->On();
		killcountboxrenderer_->On();
		timerfontRenderer_->On();
		timerboxrenderer_->On();

		

		killcountfontrenderer_->SetTextPosition(float4{ 1260.f, 80.f });
		killcountfontrenderer_->SetLeftAndRightSort(LeftAndRightSort::Right);
		killcountfontrenderer_->SetSize(24.f);
		killcountfontrenderer_->SetColor(float4::White);
		killcountfontrenderer_->SetText("óġ�� ��:\n" + std::to_string(Pinfo.targetScore_), "����");
		killcountboxrenderer_->SetTexture("GradientRightToLeft.png");
		killcountboxrenderer_->GetTransform().SetWorldScale(float4{ 200.f, 64.f ,1.f });
		killcountboxrenderer_->GetTransform().SetWorldPosition(float4{ 540.f, 250.f });

		TimeSet();
	}
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
		if (StageObject::GetNextStageInfo().combatType_ == CombatType::Kill)
		{
			killcountfontrenderer_->SetText("óġ�� ����: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
			if (Pinfo.targetScore_ >= goalCount_)
			{
				IsClear_ = true;
				Monster::UnsummonAllMonsters();
			}
		}
		
		else if (StageObject::GetNextStageInfo().combatType_ == CombatType::EilteKill)
		{
			killcountfontrenderer_->SetText("óġ�� ����: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
			
			if (Pinfo.targetScore_ >= goalCount_)
			{
				IsClear_ = true;
				Monster::UnsummonAllMonsters();
			}
		}
		else if (StageObject::GetNextStageInfo().combatType_ == CombatType::TimeAttack)
		{
			killcountfontrenderer_->SetText("óġ�� ����: " + std::to_string(Pinfo.targetScore_) + " / " + std::to_string(goalCount_));
			TimeCounter();
			if (Pinfo.stageTimer_ >= 90.f)
			{
				IsClear_ = true;
				Monster::UnsummonAllMonsters();
			}
		}
		break;
	case UIType::Claer:
		coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
		break;
	case UIType::Shop:
		coinfontrenderer_->SetText(std::to_string(Pinfo.gold_), "Free Pixel");
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

	Time_all = Pinfo.stageTimer_; // ���� ���������� ���۵ǰ� ����� �ð��� ���Ѵ�

	Time_m = static_cast<int>(Time_all) / 60;		// �� �ð��� �ʷ� �ٲ۵ڿ� 60���� ������ ���� ���Ѵ�
	Time_s = static_cast<int>(Time_all) - (60 * Time_m);

	std::string num_s = std::to_string(Time_s);
	 // ���ڸ��� ����ϱ� ���� ���� �ڸ����� ������ ���� �ڸ��� 0���� ä���.

	std::string num_m = std::to_string(Time_m);

	std::string TimeString = num_m + ":" + num_s;

	timerfontRenderer_->SetText("���� �ð�:\n" + TimeString, "����");
}

void StageUI::TimeCounter()
{
	PlayerInfo Pinfo = Player::GetPlayerInst()->GetPlayerInfo();

	float Time_all;
	int Time_s;
	int Time_m;

	Time_all = Pinfo.stageTimer_; // ���� ���������� ���۵ǰ� ����� �ð��� ���Ѵ�

	Time_m = static_cast<int>(Time_all) / 60;		// �� �ð��� �ʷ� �ٲ۵ڿ� 3600���� ������ ���� ���Ѵ�
	Time_s = static_cast<int>(Time_all) - (60 * Time_m);


	std::string num_s = std::to_string(Time_s);
	num_s = std::string(2 - std::min<size_t>(2, num_s.length()), '0') + num_s; // ���ڸ��� ����ϱ� ���� ���� �ڸ����� ������ ���� �ڸ��� 0���� ä���.

	std::string num_m = std::to_string(Time_m);
	num_m = std::string(2 - std::min<size_t>(2, num_m.length()), '0') + num_m;

	std::string TimeString = num_m + ":" + num_s;

	elitekillFontrenderer_->SetText("����:" + TimeString + " / 01:30");
}