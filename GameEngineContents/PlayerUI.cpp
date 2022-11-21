#include "PreCompile.h"
#include"PlayerUI.h"
#include"GlobalContentsValue.h"
#include "Player.h"
PlayerUI::PlayerUI()
	:player_(),
	playerHpUi_(0)
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
	this->SetParent(player_.lock()->CastThis<Player>());
	playerHpUi_ = CreateComponent<GameEngineTextureRenderer>();
	playerHpUi_->GetTransform().SetWorldScale(100, 10, 1);
	playerHpUi_->SetTexture("DefaultUi.png");
	//playerHpUi_->GetPixelData().mulColor_ = float4(1.0f,0.0f,0.0f,1.0f);	//ºÓÀº»ö
	//playerHpUi_->GetPixelData().mulColor_ = float4(0.0f,1.0f,0.0f,1.0f);	//³ì»ö
	//playerHpUi_->GetPixelData().mulColor_ = float4(1.0f,1.0f,1.0f,1.0f); //Èò»ö
	//playerHpUi_->GetPixelData().mulColor_ = float4(0.0f, 0.0f, 0.0f, 1.0f); //°ËÀº»ö
	playerHpUi_->GetPixelData().slice_ = float4(0.5f,0.0f,0.0f,0.0f);
}
void PlayerUI::Update(float _deltaTime)
{
	playerHpUi_->GetTransform().SetWorldPosition(player_.lock()->GetTransform().GetWorldPosition().x, player_.lock()->GetTransform().GetWorldPosition().y + 100.0f, -100);
}
void PlayerUI::End()
{

}