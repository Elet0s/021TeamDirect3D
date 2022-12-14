#include"PreCompile.h"
#include"FlyingEyes.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

FlyingEyes::FlyingEyes()
{
	monsterScale_ = float4(70, 70, 1);
}
FlyingEyes::~FlyingEyes()
{

}
void FlyingEyes::Start()
{
	////////////Cut////////////
	//GameEngineTexture::Cut("flyingEyes.png", 10, 1);
	


	//monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	//monRenderer_->GetTransform().SetLocalScale(70, 70, 0);
	//monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	//monRenderer_->CreateFrameAnimation_CutTexture("flyingEyes", FrameAnimation_Desc("flyingEyes.png", 0, 5, 0.1f));
	//monRenderer_->ChangeFrameAnimation("flyingEyes");

	//shadowRenderer_ = CreateComponent<Texture2DShadowRenderer>();
	//shadowRenderer_->SetTextureRenderer(monRenderer_);

	monsterAnimation_.Initialize(0, 5, 0.1f, true);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 50.0f, 25.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 0;
	monsterInfo_->hp_ = 10;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;
}
void FlyingEyes::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
}
void FlyingEyes::End()
{

}