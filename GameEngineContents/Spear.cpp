#include"PreCompile.h"
#include"Spear.h"
#include "Player.h"


Spear::Spear()
	: damege_(0.75f)
	, attackSpeed_(0.25f)
	, rangeSize_(2.0f)
	, spearCol_()
{

}
Spear::~Spear()
{

}

void Spear::Init()
{
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(damege_ * PlayerInfo_->atk_).substr(0, std::to_string(damege_ * PlayerInfo_->atk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(attackSpeed_ * PlayerInfo_->pushSpeed_).substr(0, std::to_string(attackSpeed_ * PlayerInfo_->pushSpeed_).find(".") + 3);
	std::string sRange = std::to_string(rangeSize_* PlayerInfo_->range_).substr(0, std::to_string(rangeSize_ * PlayerInfo_->range_).find(".") + 3);

	etc_ = "범위 내의 근처 적에게 지속\n피해를 입힙니다\n치명타가 발생하지 않습니다\n" + sDamege + " 의 피해\n" + sAttackSpeed + "초 마다 공격\n범위 "
		+ sRange + "m ";
}
void Spear::Effect()
{

}

void Spear::Start()
{
	spearRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	spearRenderer_->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
	spearRenderer_->GetTransform().SetWorldScale(100, 100, 0);
	spearRenderer_->SetTexture("Spear.png");


	referenceVector_ = GetTransform().GetUpVector();


	//spearCol_ = CreateComponent<GameEngineCollision>();
	//spearCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	//spearCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	//spearCol_->ChangeOrder(ObjectOrder::Monster);
	Death(2.0f);
}
void Spear::Update(float _deltaTime)
{
	Left(_deltaTime);
}
void Spear::End()
{

}
void Spear::Left(float _deltaTime)
{
	float a = GameEngineRandom::mainRandom_.RandomFloat(100.f,500.f);
	GetTransform().SetWorldLeftMove(a, _deltaTime);
}