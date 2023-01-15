#include "PreCompile.h"
#include "ShopLevel.h"
#include "Player.h"
#include "Mouse.h"
#include "ShopButton.h"


ShopButton::ShopButton() 
	: renderer_(nullptr)
	, click_(nullptr)
	, fontRenderer_(nullptr)
	, price_(0)
	, IsApper(true)
	, soundCheck_(false)
{
}

ShopButton::~ShopButton() 
{
}

void ShopButton::Start()
{
	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->ChangeCamera(CameraOrder::UICamera);
	renderer_->SetTexture("Button_Default_State_Shop.png");
	renderer_->ScaleToTexture();
	fontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	fontRenderer_->SetSize(32.f);
	fontRenderer_->SetPositionMode(FontPositionMode::World);
	fontRenderer_->ChangeCamera(CameraOrder::UICamera);
	fontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
	fontRenderer_->GetTransform().SetLocalPosition(float4(-270.f, 18.f, -1.f));

	{
		std::shared_ptr<GameEngineTextureRenderer> renderer = CreateComponent<GameEngineTextureRenderer>();
		renderer->ChangeCamera(CameraOrder::UICamera);
		renderer->GetTransform().SetWorldScale(float4{ 32.f, 32.f });
		renderer->GetTransform().SetLocalPosition(float4(160.f, 0.f, -1.f));
		renderer->SetTexture("smallCoin.png");
	}

	PricefontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PricefontRenderer_->SetSize(32.f);
	PricefontRenderer_->SetPositionMode(FontPositionMode::World);
	PricefontRenderer_->ChangeCamera(CameraOrder::UICamera);
	PricefontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
	PricefontRenderer_->GetTransform().SetLocalPosition(float4(180.f, 18.f, -1.f));
}

void ShopButton::Update(float _deltaTime)
{
	PlayerInfo* PInfo = &Player::GetPlayerInst()->GetPlayerInfo();
	if (true == GetLevel<ShopLevel>()->GetMousePointer()->IsPointing(renderer_->GetTransformData().worldWorldMatrix_, float4(0.f, 0.0f, 0.f, 0.f),true))
	{
		if (soundCheck_ == false)
		{
			GameEngineSound::SoundPlayOneshot("Menu_Cycle.wav");
			soundCheck_ = true;
		}
		if (price_ <= PInfo->gold_)
		{

			renderer_->SetTexture("Button_Selected_Shop.png");
			if (GameEngineInput::GetInst().IsDown("Click"))
			{
				GameEngineSound::SoundPlayOneshot("Menu_Confirm.wav");
				Off();
				PInfo->gold_ -= static_cast<int>(price_);
				IsApper = false;
				click_();
			}
		}
		else if (price_ > PInfo->gold_)
		{
			renderer_->SetTexture("Button_Selected_disabled_Shop.png");
		}
	}
	else
	{
		soundCheck_ = false;
		if (price_ <= PInfo->gold_)
		{
			renderer_->SetTexture("Button_Default_State_Shop.png");
		}
		else if (price_ > PInfo->gold_)
		{
			renderer_->SetTexture("Button_Disabled_Shop.png");
		}
	}
}

void ShopButton::End()
{

}

void ShopButton::SetText(const std::string& _str)
{
	if (fontRenderer_ != nullptr)
	{
		fontRenderer_->SetText(_str);
	}
}

void ShopButton::SetPrice(size_t _price)
{
	price_ = _price;
	PricefontRenderer_->SetText(std::to_string(price_));
}