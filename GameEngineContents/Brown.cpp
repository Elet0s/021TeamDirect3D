#include"PreCompile.h"
#include"Brown.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

Brown::Brown()
{

}
Brown::~Brown()
{

}
void Brown::Start()
{
	////////////Cut////////////

		GameEngineTexture::Cut("Brown.png", 8, 1);
	
		monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		monRenderer_->GetTransform().SetLocalScale(80, 80, 0);
		monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		monRenderer_->CreateFrameAnimation_CutTexture("Brown", FrameAnimation_Desc("Brown.png", 0, 7, 0.1f));
		monRenderer_->ChangeFrameAnimation("Brown");

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
void Brown::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));

}
void Brown::End()
{

}