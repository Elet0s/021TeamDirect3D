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

	playerHpUi_ = CreateComponent<GameEngineTextureRenderer>();
	playerHpUi_->GetTransform().SetWorldScale(100, 100, 1);
	playerHpUi_->GetTransform().SetWorldPosition(player_.lock()->GetTransform().GetWorldPosition().x, player_.lock()->GetTransform().GetWorldPosition().y + 50.0f, -100);
	playerHpUi_->SetTexture("DefaultUi.png");



}
void PlayerUI::Update(float _deltaTime)
{

}
void PlayerUI::End()
{

}