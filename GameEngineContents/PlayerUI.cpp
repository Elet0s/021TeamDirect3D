#include "PreCompile.h"
#include"PlayerUI.h"
#include"GlobalContentsValue.h"
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
PlayerUI::PlayerUI()
	:player_(),
	playerHpUi_(0),
	hpRedBar_(0),
	hpRedBarTregar_(false)
{

}
PlayerUI::~PlayerUI()
{

}
void PlayerUI::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistChildDirectory("ContentsResources");
	Dir.MoveToChild("ContentsResources");
	Dir.MoveToChild("UI");
	Dir.MoveToChild("PlayerUI");

	player_ = Player::GetPlayerWeakPtr();
	hpRedBar_ = player_.lock()->GetPlayerInfo().maxHp_;

	playerHpUi_ = CreateComponent<GameEngineTextureRenderer>();
	playerHpUi_->SetTexture("DefaultUi.png");
	playerHpUi_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f); //³ì»ö
	playerHpUi_->GetTransform().SetWorldScale(-100.f, 10.f, 1.f);

	playerHpMax_ = CreateComponent<GameEngineTextureRenderer>();
	playerHpMax_->SetTexture("DefaultUi.png");
	playerHpMax_->GetPixelData().mulColor_ = float4(0.0f, 0.0f, 0.0f, 1.0f); //°ËÀº»ö
	playerHpMax_->GetTransform().SetLocalScale(100, 10, 1);

	playerHpRed_ = CreateComponent<GameEngineTextureRenderer>();
	playerHpRed_->SetTexture("DefaultUi.png");
	playerHpRed_->GetPixelData().mulColor_ = float4(1.0f,0.0f,0.0f,1.0f);	//ºÓÀº»ö
	playerHpRed_->GetTransform().SetWorldScale(-100.f, 10.f, 1.f);
}
void PlayerUI::HitEffect()
{
	if (true == player_.lock()->collision_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Monster, CollisionType::CT_OBB2D))
	{
		playerHpUi_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 1.0f, 1.0f);//Èò»ö
	}
	else
	{
		playerHpUi_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);	//³ì»ö
	}
}
void PlayerUI::ReduceHP(float _deltaTime)
{

	if (player_.lock()->GetPlayerInfo().maxHp_> player_.lock()->GetPlayerInfo().hp_)
	{
		playerHpUi_->GetPixelData().slice_ = float4(1-(player_.lock()->GetPlayerInfo().hp_ / player_.lock()->GetPlayerInfo().maxHp_), 0.0f, 0.0f, 0.0f);
	}
	if (hpRedBar_ > player_.lock()->GetPlayerInfo().hp_)
	{
		hpRedBarTregar_ = true;
	}
	if (hpRedBarTregar_ == true)
	{
		if (hpRedBar_ > player_.lock()->GetPlayerInfo().hp_)
		{
			hpRedBar_ -= 1.0f* _deltaTime*15;
			playerHpRed_->GetPixelData().slice_ = float4(1-( hpRedBar_ / player_.lock()->GetPlayerInfo().maxHp_), 0.0f, 0.0f, 0.0f);
		}
		else if (hpRedBar_ <= player_.lock()->GetPlayerInfo().hp_)
		{
			hpRedBar_ = player_.lock()->GetPlayerInfo().hp_;
			hpRedBarTregar_ = false;
		}

	}
}
void PlayerUI::Update(float _deltaTime)
{
	playerHpUi_->GetTransform().SetWorldPosition(player_.lock()->GetTransform().GetWorldPosition().x, player_.lock()->GetTransform().GetWorldPosition().y + 100.0f, -100);
	playerHpMax_->GetTransform().SetWorldPosition(player_.lock()->GetTransform().GetWorldPosition().x, player_.lock()->GetTransform().GetWorldPosition().y + 100.0f, -98);
	playerHpRed_->GetTransform().SetWorldPosition(player_.lock()->GetTransform().GetWorldPosition().x, player_.lock()->GetTransform().GetWorldPosition().y + 100.0f, -99);

	HitEffect();
	ReduceHP(_deltaTime);
}
void PlayerUI::End()
{

}