#include "PreCompile.h"
#include "DashUI.h"
#include "Player.h"

DashUI::DashUI()
	: templaterenderer_(nullptr)
	, dashMaxCount_(0)
	, currentDashCount_(0)
{
}

DashUI::~DashUI() 
{
}


void DashUI::Start()
{
	templaterenderer_ = CreateComponent<GameEngineTextureRenderer>();
	templaterenderer_->GetTransform().SetWorldPosition(float4{ -500.f, -300.f });
	templaterenderer_->SetPivot(PivotMode::Left);
	templaterenderer_->ChangeCamera(CameraOrder::UICamera);
	TemplateSetting();
	DashRenderersSetting();
}

void DashUI::Update(float _deltaTime)
{
	DashRendererChange();
	PlayerInfo pInfo = Player::GetPlayerInst()->GetPlayerInfo();
	if (dashMaxCount_ != pInfo.dashFullCharge_)
	{
		dashMaxCount_ = pInfo.dashFullCharge_;
		for (size_t i = 0; i < dashMaxCount_; i++)
		{
			dashrenderers_[i]->On();
		}
	}
}

void DashUI::End()
{

}

void DashUI::TemplateSetting()
{
	PlayerInfo pInfo = Player::GetPlayerInst()->GetPlayerInfo();

	dashMaxCount_ = pInfo.dashFullCharge_;

	templaterenderer_->SetTexture("Dash_Template" + std::to_string(dashMaxCount_) + ".png");
	templaterenderer_->ScaleToTexture();
}


void DashUI::DashRenderersSetting()
{
	dashrenderers_.reserve(7);

	for (size_t i = 0; i < 8; i++)
	{
		std::shared_ptr<GameEngineTextureRenderer> texture = CreateComponent<GameEngineTextureRenderer>();
		texture->SetTexture("Dash_Ready.png");
		texture->ScaleToTexture();
		texture->SetPivot(PivotMode::Left);
		texture->GetTransform().SetWorldPosition(float4{ -480.f + 23.f * i, -300.f , -100.f});
		texture->Off();
		texture->ChangeCamera(CameraOrder::UICamera);
		dashrenderers_.push_back(texture);
	}

	for (size_t i = 0; i < dashMaxCount_; i++)
	{
		dashrenderers_[i]->On();
	}
}

void DashUI::DashRendererChange()
{
	PlayerInfo pInfo = Player::GetPlayerInst()->GetPlayerInfo();

	int EmptyCount = dashMaxCount_ - pInfo.dashCount_;

	for (size_t i = dashMaxCount_ - 1; i > dashMaxCount_ - EmptyCount; i--)
	{
		dashrenderers_[i]->SetTexture("Dash_Empty.png");
	}

	for (size_t i = 0 ; i < pInfo.dashCount_; i++)
	{
		dashrenderers_[i]->SetTexture("Dash_Ready.png");
	}
	
	if (EmptyCount != 0)
	{
 		dashrenderers_[dashMaxCount_ - EmptyCount]->SetTexture("Dash_Loading.png");
	}
}