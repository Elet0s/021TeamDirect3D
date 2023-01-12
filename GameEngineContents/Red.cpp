#include"PreCompile.h"
#include"Red.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

Red::Red()
{
	monsterScale_ = float4(70, 70, 1);
}
Red::~Red()
{

}

void Red::Start()
{
	monsterAnimation_.Initialize(0, 5, 0.1f, true);


	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 40.f, 40.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);
	monCollision_->SetCollisionMode(CollisionMode::Multiple);

	monsterInfo_->atk_ = 5;
	monsterInfo_->hp_ = 20;
	monsterInfo_->maxHp_ = 20;
	monsterInfo_->baseSpeed_ = 75;
	monsterInfo_->giveExp_ = 5;
	monsterInfo_->monsterType_ = MonsterType::Red;
}
void Red::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	HpCheak();
}
void Red::End()
{

}