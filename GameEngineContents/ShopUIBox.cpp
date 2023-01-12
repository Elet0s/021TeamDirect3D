#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "ShopLevel.h"
#include "Mouse.h"
#include "Player.h"
#include "SoulCardSelectBox.h"
#include "StageObject.h"
#include "ShopUIBox.h"
#include "ShopButton.h"

ShopUIBox::ShopUIBox()
	: mainrenderer_(nullptr)
{
}


ShopUIBox::~ShopUIBox()
{
}

void ShopUIBox::Start()
{
	mainrenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mainrenderer_->SetTexture("ShopUIBox.png");
	mainrenderer_->ScaleToTexture();
	mainrenderer_->ChangeCamera(CameraOrder::UICamera);
	mainrenderer_->GetTransform().SetWorldPosition(-300, 0, 0);

	mainrenderer_->GetPixelData().mulColor_.a = 0.85f;
	
	buttons_.reserve(4);

	std::shared_ptr<ShopButton> button1_ = GetLevel()->CreateActor<ShopButton>();
	button1_->GetTransform().SetWorldPosition(-300, 200, -1.f);
	button1_->SetText("HP 회복");
	button1_->SetPrice(1000);
	button1_->CreateClickEvent(
		[=]()
		{
			PlayerInfo* Pinfo = &Player::GetPlayerInst()->GetPlayerInfo();
			Pinfo->hp_ = Pinfo->maxHp_;
			
		}
	);
	buttons_.push_back(button1_); //0 

	std::shared_ptr<ShopButton>button2_ = GetLevel()->CreateActor<ShopButton>();
	button2_->GetTransform().SetWorldPosition(-300, 120, -1.f);
	button2_->SetText("카드 뽑기");
	button2_->SetPrice(3000);
	button2_->CreateClickEvent(
		[=]()
		{
			RenderOff();
			soulCardSelectBox_ = GetLevel()->CreateActor<SoulCardSelectBox>();
		
		}
	);
	buttons_.push_back(button2_); // 1

	std::shared_ptr<ShopButton>button3_ = GetLevel()->CreateActor<ShopButton>();
	button3_->GetTransform().SetWorldPosition(-300, 40, -1.f);
	button3_->SetText("으아아아");
	button3_->SetPrice(1000);
	button3_->CreateClickEvent(
		[=]()
		{
			PlayerInfo* Pinfo = &Player::GetPlayerInst()->GetPlayerInfo();
			Pinfo->hp_ = Pinfo->maxHp_;
			
		}
	);
	buttons_.push_back(button3_);  //2

	std::shared_ptr<ShopButton> button4_ = GetLevel()->CreateActor<ShopButton>();
	button4_->GetTransform().SetWorldPosition(-300, -40, -1.f);
	button4_->SetText("상점 초기화");
	button4_->SetPrice(5000);
	button4_->CreateClickEvent(
		[=]()
		{
			ShopReset();
		}
	);
	buttons_.push_back(button4_);  //3


	{
		buttonrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		buttonrenderer_->SetTexture("Button_Default_State_Stage.png");
		buttonrenderer_->ScaleToTexture();
		buttonrenderer_->GetTransform().SetWorldPosition(430.f, -291.f, -10.f);
		buttonrenderer_->ChangeCamera(CameraOrder::UICamera);

		buttonFontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		buttonFontRenderer_->SetTextPosition(float4(1080.f, 630.f, -2000.f));
		buttonFontRenderer_->ChangeCamera(CameraOrder::UICamera);
		buttonFontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Center);
		buttonFontRenderer_->SetSize(30.f);
		buttonFontRenderer_->SetText("다음 스테이지");
	}
}

void ShopUIBox::Update(float _deltaTime)
{
	
	if (true == buttonrenderer_->IsUpdate() &&
		true == GetLevel<ShopLevel>()->GetMousePointer()->IsPointing(buttonrenderer_->GetTransformData().worldWorldMatrix_, float4::Zero, true)
		)
	{
		buttonrenderer_->SetTexture("Button_Selected_Stage.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			GEngine::ChangeLevel("WorldMap");
		}
	}

	if (nullptr != soulCardSelectBox_ && soulCardSelectBox_->IsDead() == true)
	{
		RenderOn();
		soulCardSelectBox_ = nullptr;
	}

}


void ShopUIBox::LevelStartEvent()
{
	ShopReset();
}

void ShopUIBox::RenderOn()
{
	mainrenderer_->On();

	for (std::shared_ptr<ShopButton> button : buttons_)
	{
		if (true == button->GetIsApper())
		{
			button->On();
		}
	}

}

void ShopUIBox::RenderOff()
{
	mainrenderer_->Off();
	for (std::shared_ptr<ShopButton> button : buttons_)
	{
		button->Off();
	}
}

void ShopUIBox::ShopReset()
{
	for (std::shared_ptr<ShopButton> button : buttons_)
	{
		button->SetIsApper(true);
	}
	mainrenderer_->On();

	for (std::shared_ptr<ShopButton> button : buttons_)
	{
		button->On();
	}

	for (size_t i = 0; i < 4; i++)
	{
		buttons_[i]->GetTransform().SetWorldPosition(-300, 200.f - 80.f * i, -1.f);
	}
}

