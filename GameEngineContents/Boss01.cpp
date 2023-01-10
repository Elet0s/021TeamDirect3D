#include"PreCompile.h"
#include"Boss01.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"
#include "Projectile.h"

std::vector<std::shared_ptr<Projectile>> Boss01::monsterProjectile_;

Boss01::Boss01()
:bossPattern_()
{
	monsterScale_ = float4(300.f, 300.f, 1.f);
}
Boss01::~Boss01()
{

}

void Boss01::Start()
{
	monsterAnimation_.Initialize(0, 5, 0.1f, true);

	bossPattern_ = BossPattern::none;
	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);

	monsterInfo_->atk_ = 5;
	monsterInfo_->hp_ = 10;
	monsterInfo_->maxHp_ = 10;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;

	/// /////////////////////////////////////////////////////////////////////////////////////////////

	monsterHp_ = CreateComponent<GameEngineTextureRenderer>();
	monsterHp_->SetTexture("DefaultUi.png");
	monsterHp_->GetPixelData().mulColor_ = float4::Green; //³ì»ö
	monsterHp_->GetTransform().SetWorldScale(-130.f, 15.f, 1.f);
	monsterHp_->ChangeCamera(CameraOrder::MidCamera);
	monsterHp_->SetRenderingOrder(15);
	monsterHp_->GetTransform().SetLocalPosition({ 0.f,100.f });

	monsterHpMax_ = CreateComponent<GameEngineTextureRenderer>();
	monsterHpMax_->SetTexture("DefaultUi.png");
	monsterHpMax_->GetPixelData().mulColor_ = float4::Black; //°ËÀº»ö
	monsterHpMax_->GetTransform().SetLocalScale(130, 15, 1);
	monsterHpMax_->ChangeCamera(CameraOrder::MidCamera);
	monsterHpMax_->SetRenderingOrder(15);
	monsterHpMax_->GetTransform().SetLocalPosition({ 0.f,100.f });

	monsterHpScore_ = CreateComponent<GameEngineFontRenderer>();
	monsterHpScore_->SetSize(20.f);
	monsterHpScore_->SetLeftAndRightSort(LeftAndRightSort::Center);
	monsterHpScore_->SetText(std::to_string(static_cast <int>(monsterInfo_->hp_)), "¸¼À½");
	monsterHpScore_->SetPositionMode(FontPositionMode::World);
	monsterHpScore_->ChangeCamera(CameraOrder::MidCamera);
	monsterHpScore_->GetTransform().SetLocalPosition({ 0.f,115.f,0.f });

	monsterProjectile_.reserve(50);
	for (size_t i = 0; i < 50; i++)
	{
		std::shared_ptr<Projectile> A = GetLevel()->CreateActor<Projectile>(ObjectOrder::Projectile);
		monsterProjectile_.push_back(A);
	}

}
void Boss01::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);
	if (bossPattern_ == BossPattern::none)
	{
		Chaseplayer(_deltaTime);
	}
	else
	{
		PatternMove(_deltaTime);
	}
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	HpCheak();

	GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	monsterHpScore_->SetText(std::to_string(static_cast <int>(monsterInfo_->hp_)), "¸¼À½");
	ReduceHP();
}
void Boss01::End()
{

}

void Boss01::PatternMove(float _deltaTime)
{
	if (bossPattern_ == BossPattern::Dormammu)
	{

	}
	else if (bossPattern_ == BossPattern::Shooting)
	{

	}
}