#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "ClearLevel.h"
#include "Mouse.h"
#include "Player.h"
#include "SoulCardSelectBox.h"
#include "StageObject.h"
#include "ClearUIBox.h"

ClearUIBox::ClearUIBox() 
	:mainrenderer_(nullptr)
	, button1renderer_(nullptr)
	, button2renderer_(nullptr)
	, button3renderer_(nullptr)
	, button1FontRenderer_(nullptr)
	, button2FontRenderer_(nullptr)
	, button3FontRenderer_(nullptr)
	, button1On_(true)
	, button2On_(true)
	, gold_(0)
{
}

ClearUIBox::~ClearUIBox() 
{
}

void ClearUIBox::Start()
{
	mainrenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mainrenderer_->SetTexture("ClearUIBox.png");
	mainrenderer_->ScaleToTexture();
	mainrenderer_->ChangeCamera(CameraOrder::UICamera);
	mainrenderer_->GetTransform().SetWorldPosition(-350, 0, 0);

	mainrenderer_->GetPixelData().mulColor_.a = 0.85f;

	if (StageObject::GetNextStageInfo().stageType_ == StageType::Chest)
	{
		gold_ = 10000;
	}
	else
	{
		gold_ = 300;
	}

	{
		button1renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button1renderer_->SetTexture("Button_Default_State.png");
		button1renderer_->GetTransform().SetWorldPosition(-350, 220.f, -10.f);
		button1renderer_->ScaleToTexture();
		button1renderer_->ChangeCamera(CameraOrder::UICamera);


	}
	


	{
		button2renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button2renderer_->SetTexture("Button_Default_State.png");
		button2renderer_->GetTransform().SetWorldPosition(-350, 160.f, -10.f);
		button2renderer_->ScaleToTexture();
		button2renderer_->ChangeCamera(CameraOrder::UICamera);


	
	}

	{
		button1FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button1FontRenderer_->SetTextPosition(float4(90.f, 125.f, -1000.f));
		button1FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button1FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		button1FontRenderer_->SetSize(28.f);

		button1FontRenderer_->SetText(std::to_string(gold_) + " 골드");

		button2FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button2FontRenderer_->SetTextPosition(float4(90.f, 185.f, -2000.f));
		button2FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button2FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		button2FontRenderer_->SetSize(28.f);
		button2FontRenderer_->SetText("카드 선택");

		button3FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button3FontRenderer_->SetTextPosition(float4(1080.f, 630.f, -2000.f));
		button3FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button3FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Center);
		button3FontRenderer_->SetSize(30.f);
		button3FontRenderer_->SetText("다음 스테이지");
	}

	{
		button3renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button3renderer_->SetTexture("Button_Default_State_Stage.png");
		button3renderer_->ScaleToTexture();
		button3renderer_->GetTransform().SetWorldPosition(430.f, -291.f, -10.f);
		button3renderer_->ChangeCamera(CameraOrder::UICamera);


	}
}

void ClearUIBox::Update(float _deltaTime)
{
	if (true == button1renderer_->IsUpdate() &&
		true == GetLevel<ClearLevel>()->GetMousePointer()->IsPointing(button1renderer_->GetTransformData().worldWorldMatrix_, float4::Zero, true)
	)
	{
		button1renderer_->SetTexture("Button_Selected.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			GameEngineSound::SoundPlayOneshot("Menu_Confirm.wav");
			GameEngineSound::SoundPlayOneshot("GoldReward.wav");
			button1renderer_->Off();
			button1FontRenderer_->Off();
			button1On_ = false;
			PlayerInfo* pInfo = &Player::GetPlayerInst()->GetPlayerInfo();
			pInfo->gold_ += this->gold_;
			if (button2renderer_->IsUpdate())
			{
				button2FontRenderer_->SetTextPosition(float4(90.f, 125.f, -1000.f));
				button2renderer_->GetTransform().SetWorldMove(float4(0, 60, 0));
			}
			return;
		}
	}
	else
	{
		button1renderer_->SetTexture("Button_Default_State.png");
	}


	if (true == button2renderer_->IsUpdate() &&
		true == GetLevel<ClearLevel>()->GetMousePointer()->IsPointing(button2renderer_->GetTransformData().worldWorldMatrix_, float4::Zero, true)
	)
	{
		button2renderer_->SetTexture("Button_Selected.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			GameEngineSound::SoundPlayOneshot("Menu_Confirm.wav");
			GameEngineSound::SoundPlayOneshot("Level_Up.wav");
			RendererOff();
			button2On_ = false;
			soulCardSelectBox_ = GetLevel()->CreateActor<SoulCardSelectBox>();
		}
	}
	else
	{
		button2renderer_->SetTexture("Button_Default_State.png");
	}

	if (true == button3renderer_->IsUpdate() &&
		true == GetLevel<ClearLevel>()->GetMousePointer()->IsPointing(button3renderer_->GetTransformData().worldWorldMatrix_, float4::Zero, true)
	)
	{
		button3renderer_->SetTexture("Button_Selected_Stage.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			GEngine::ChangeLevel("WorldMap");
		}
	}
	else
	{
		button3renderer_->SetTexture("Button_Default_State_Stage.png");
	}

	if (soulCardSelectBox_ != nullptr && soulCardSelectBox_->IsDead())
	{
		soulCardSelectBox_ = nullptr;
		RendererOn();
	}

}


void ClearUIBox::RendererOn()
{
	mainrenderer_->On();
	button3FontRenderer_->On();
	button3renderer_->On();
	if (button1On_ == true)
	{
		button1FontRenderer_->On();
		button1renderer_->On();
	}

	if (button2On_ == true)
	{
		button2FontRenderer_->On();
		button2renderer_->On();
	}
}

void ClearUIBox::RendererOff()
{
	mainrenderer_->Off();
	button1FontRenderer_->Off();
	button1renderer_->Off();
	
	button2FontRenderer_->Off();
	button2renderer_->Off();

	button3FontRenderer_->Off();
	button3renderer_->Off();
	
}