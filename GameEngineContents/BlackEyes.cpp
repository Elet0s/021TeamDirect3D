#include"PreCompile.h"
#include"BlackEyes.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

BlackEyes::BlackEyes()
{
	monsterScale_ = float4(70, 70, 1);
}
BlackEyes::~BlackEyes()
{

}

void BlackEyes::Start()
{
	monsterAnimation_.Initialize(0, 5, 0.1f, true);


	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 5;
	monsterInfo_->hp_ = 10.f;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;
}
void BlackEyes::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	HpCheak();
}
void BlackEyes::End()
{

}

void BlackEyes::HpCheak()
{
	if (monsterInfo_->hp_ < 0)
	{
		dropMonsterItemObject_->CreateItemObject(GetLevel(), this->GetTransform().GetWorldPosition());
		this->Unsummon();
	}
}