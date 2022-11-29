#include"PreCompile.h"
#include"Green.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

Green::Green()
{

}
Green::~Green()
{

}
void Green::Start()
{
	////////////Cut////////////
	GameEngineTexture::Cut("Green.png", 8, 1);



	monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	monRenderer_->GetTransform().SetLocalScale(80, 80, 0);
	monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monRenderer_->CreateFrameAnimation_CutTexture("Green", FrameAnimation_Desc("Green.png", 0, 7, 0.1f));
	monRenderer_->ChangeFrameAnimation("Green");

	shadowRenderer_ = CreateComponent<Texture2DShadowRenderer>();
	shadowRenderer_->SetTextureRenderer(monRenderer_);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 35.f, 35.f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 0;
	monsterInfo_->hp_ = 10;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 50;
	monsterInfo_->giveExp_ = 5;

	//SummonMon();

}
void Green::Update(float _deltaTime)
{
	
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	Chaseplayer(_deltaTime);
}
void Green::End()
{

}