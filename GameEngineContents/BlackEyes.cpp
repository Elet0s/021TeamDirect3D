#include"PreCompile.h"
#include"BlackEyes.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

BlackEyes::BlackEyes()
{

}
BlackEyes::~BlackEyes()
{

}

void BlackEyes::Start()
{
	////////////Cut////////////
	GameEngineTexture::Cut("BlackEyes.png", 6, 1);

	monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	monRenderer_->GetTransform().SetLocalScale(70, 70, 0);
	monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monRenderer_->CreateFrameAnimation_CutTexture("BlackEyes", FrameAnimation_Desc("BlackEyes.png", 0, 5, 0.1f));
	monRenderer_->ChangeFrameAnimation("BlackEyes");

	shadowRenderer_ = CreateComponent<Texture2DShadowRenderer>();
	shadowRenderer_->SetTextureRenderer(monRenderer_);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 50.0f, 50.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 5;
	monsterInfo_->hp_ = 10;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;

	//SummonMon();
}
void BlackEyes::Update(float _deltaTime)
{

	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));

}
void BlackEyes::End()
{

}