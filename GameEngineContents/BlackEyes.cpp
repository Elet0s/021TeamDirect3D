#include"PreCompile.h"
#include"BlackEyes.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

BlackEyes::BlackEyes()
{
	monsterScale_ = float4(140, 140, 1);
}
BlackEyes::~BlackEyes()
{

}

void BlackEyes::Start()
{
	monsterAnimation_.Initialize(0, 5, 0.1f, true);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 120.f, 70.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 5;
	monsterInfo_->hp_ = 10.f;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;

	monsterHp_ = CreateComponent<GameEngineTextureRenderer>();
	monsterHp_->SetTexture("DefaultUi.png");
	monsterHp_->GetPixelData().mulColor_ = float4::Green; //³ì»ö
	monsterHp_->GetTransform().SetWorldScale(-100.f, 10.f, 1.f);
	monsterHp_->ChangeCamera(CameraOrder::MidCamera);
	monsterHp_->SetRenderingOrder(15);
	monsterHp_->GetTransform().SetLocalPosition({ 0.f,100.f });

	monsterHpMax_ = CreateComponent<GameEngineTextureRenderer>();
	monsterHpMax_->SetTexture("DefaultUi.png");
	monsterHpMax_->GetPixelData().mulColor_ = float4::Black; //°ËÀº»ö
	monsterHpMax_->GetTransform().SetLocalScale(100, 10, 1);
	monsterHpMax_->ChangeCamera(CameraOrder::MidCamera);
	monsterHpMax_->SetRenderingOrder(15);
	monsterHpMax_->GetTransform().SetLocalPosition({ 0.f,100.f });

}
void BlackEyes::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	HpCheak();

	GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	//	monsterHpScore_->SetText(std::to_string(monsterInfo_->hp_), "Free Pixel");
	ReduceHP(_deltaTime);
}
void BlackEyes::End()
{

}

void BlackEyes::ReduceHP(float _deltaTime)
{

}