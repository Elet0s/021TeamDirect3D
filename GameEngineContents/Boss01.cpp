#include"PreCompile.h"
#include"Boss01.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"
#include "Projectile.h"
#include"MagicCircle.h"

Boss01::Boss01()
	:idleTime_(0),
	collingTime01_(0.f),
	collingTime02_(0.f),
	collingTime03_(0.f),
	telleportCount_(0),
	shootingCount_(0),
	shootingEnd_(false),
	delay_(0.f)
{
	monsterScale_ = float4(300.f, 300.f, 1.f);
}
Boss01::~Boss01()
{

}

void Boss01::Start()
{
	monsterAnimation_.Initialize(0, 5, 0.1f, true);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	monCollision_->GetTransform().SetLocalScale({ 100.f, 230.f, 1.f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);
	monCollision_->SetCollisionMode(CollisionMode::Multiple);

	monsterInfo_->atk_ = 0.3f;
	monsterInfo_->hp_ = 1000.f;
	monsterInfo_->maxHp_ = 1000.f;
	monsterInfo_->baseSpeed_ = 150;
	monsterInfo_->giveExp_ = 5;
	telleportCount_ = 1;
	monsterInfo_->monsterType_ = MonsterType::Boss;
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

}
void Boss01::Update(float _deltaTime)
{
	Monster::Update(_deltaTime);

	if (monsterInfo_->bossPattern_ == BossPattern::none)
	{
		Chaseplayer(_deltaTime);
	}
	else
	{
		PatternMove(_deltaTime);
	}
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Monster::MonsterToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	BossHp();
	monsterHpScore_->SetText(std::to_string(static_cast <int>(monsterInfo_->hp_)), "¸¼À½");
	ReduceHP();
}
void Boss01::End()
{

}
void Boss01::BossHp()
{
	if (monsterInfo_->hp_ <= 0)
	{
		GEngine::ChangeLevel("End");
	}
}
void Boss01::Relocation()
{
	if (telleportCount_ > 0)
	{


		telleportCount_ -= 1;
		std::shared_ptr<MagicCircle> A = GetLevel()->CreateActor<MagicCircle>(ObjectOrder::UI);
		A->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,GetTransform().GetWorldPosition().y - 110.f });

		float4 CameraPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
		float4 monsterPosition_ = GameEngineRandom::mainRandom_.RandomFloat4(
			float4(CameraPos.x - 960, CameraPos.y - 540),
			float4(CameraPos.x + 960, CameraPos.y + 540)
		);
		monsterPosition_.z = -199.f;

		if (monsterPosition_.x > CameraPos.x + 480 || monsterPosition_.x < CameraPos.x - 480)
		{
			GetTransform().SetWorldPosition(monsterPosition_);

			allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_
			);

			allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_.x,
				monsterPosition_.y,
				monsterPosition_.z + 2.f
			);
		}
		else if (monsterPosition_.y > CameraPos.y + 270 || monsterPosition_.y < CameraPos.y - 270)
		{
			GetTransform().SetWorldPosition(monsterPosition_);

			allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_
			);

			allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_.x,
				monsterPosition_.y,
				monsterPosition_.z + 2.f
			);
		}
		std::shared_ptr<MagicCircle> B = GetLevel()->CreateActor<MagicCircle>(ObjectOrder::UI);
		B->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,GetTransform().GetWorldPosition().y -109.f });
	}
}

void Boss01::PatternMove(float _deltaTime)
{
	collingTime01_ += _deltaTime;
	collingTime02_ += _deltaTime;
	collingTime03_ += _deltaTime;
	if (monsterInfo_->bossPattern_ == BossPattern::Dormammu1)
	{
		Relocation();
		if (telleportCount_ == 0)
		{
			collingTime01_ = 0.f;
			monsterInfo_->bossPattern_ = BossPattern::none;
		}
	}
	else if (monsterInfo_->bossPattern_ == BossPattern::Shooting)
	{
		if (shootingEnd_ == false)
		{
			monsterAnimation_.Initialize(0, 0, 0.f, false);
			delay_ += _deltaTime;
			if (shootingCount_ < 100)
			{
				if (delay_ > 0.02f)
				{
					std::shared_ptr<Projectile> A = GetLevel()->CreateActor<Projectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,GetTransform().GetWorldPosition().y });
					A->ProjectileSet(monsterInfo_->atk_);
					shootingCount_ += 1;
					delay_ = 0;
				}
			}
			else if (shootingCount_ == 100)
			{
				shootingCount_ = 0;
				shootingEnd_ = true;
			}

		}
		else	 if (shootingEnd_ == true)
		{
			monsterAnimation_.Initialize(0, 5, 0.1f, true);
			shootingEnd_ = false;
			collingTime02_ = 0.f;
			monsterInfo_->bossPattern_ = BossPattern::none;
		}
	}
	else if ((monsterInfo_->bossPattern_ == BossPattern::Dormammu2))
	{
		Relocation();
		if (telleportCount_ == 0)
		{
			collingTime03_ = 0.f;
			monsterInfo_->bossPattern_ = BossPattern::none;
		}
	}
	else if (monsterInfo_->bossPattern_ == BossPattern::Idle)
	{
		monsterAnimation_.Initialize(0, 0, 0.f, false);
		if (collingTime01_ > 3.f)
		{
			monsterAnimation_.Initialize(0, 5, 0.1f, true);
			monsterInfo_->bossPattern_= BossPattern::Dormammu1;
			telleportCount_ = 1;
		}
		else if (collingTime02_>5.f)
		{
			monsterAnimation_.Initialize(0, 5, 0.1f, true);
			monsterInfo_->bossPattern_ =BossPattern::Shooting;

		}
		else if (collingTime03_ > 8.f)
		{
			monsterAnimation_.Initialize(0, 5, 0.1f, true);
			monsterInfo_->bossPattern_ = BossPattern::Dormammu2;
			telleportCount_ = 3;
		}

	}
}