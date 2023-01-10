#include"PreCompile.h"
#include"Green.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

Green::Green()
{
	monsterScale_ = float4(80, 80, 1);
}
Green::~Green()
{

}
void Green::Start()
{
	monsterAnimation_.Initialize(0, 7, 0.1f, true);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 35.f, 35.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 0;
	monsterInfo_->hp_ = 10.f;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 50;
	monsterInfo_->giveExp_ = 5;
}
void Green::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	HpCheak();
}
void Green::End()
{

}
