#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
#include "Monster.h"

DeathAura::DeathAura()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
	, atkTimer_(0)
{
	name_ = "죽음의 오라";
	SetName(std::string_view("DeathAura"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}

DeathAura::~DeathAura()
{
}



void DeathAura::Init()
{
	StateSet();
	std::string sDamege = std::to_string(deathAuraWeaponInfo_.weaponAtk_ ).substr(0, std::to_string(deathAuraWeaponInfo_.weaponAtk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(deathAuraWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(deathAuraWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sRange = std::to_string(deathAuraWeaponInfo_.weaponSize_).substr(0, std::to_string(deathAuraWeaponInfo_.weaponSize_).find(".") + 3);

	etc_ = "범위 내의 근처 적에게 지속\n피해를 입힙니다\n치명타가 발생하지 않습니다\n" + sDamege + " 의 피해\n" + sAttackSpeed + "초 마다 공격\n범위 "
		+ sRange + "m ";
}

void DeathAura::Effect()
{
	currentlevel_ += 1;
}

void  DeathAura::StateSet()
{
	PlayerInfo* Info_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	deathAuraWeaponInfo_.weaponAtk_ = 1.f + (1.f * currentlevel_) * (Info_->atk_ * PInfo_->atkMultiple_Result / 100.f);
	deathAuraWeaponInfo_.weaponAtkSpeed_ = 0.3f * (Info_->attackSpeed_ * PInfo_->attackSpeed_Result / 100.f);//1초마다

	deathAuraWeaponInfo_.weaponPassAtk_ = 0;
	deathAuraWeaponInfo_.weaponPassNum_ = 2;

	deathAuraWeaponInfo_.weaponRange_ = 1.f + (0.5f * currentlevel_) * (Info_->atk_Range_/ 100);
	deathAuraWeaponInfo_.weaponDuration_ = 100 * Info_->projectileduration_ * PInfo_->projectileDuration_Result / 100; ;
	deathAuraWeaponInfo_.weaponSpeed_ = 100.f * Info_->projectilespeed_ * PInfo_->projectileSpeed_Result / 100;


}
void DeathAura::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Death_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(153.f, 153.f, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererA_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererA_->Off();

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Death_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(150.f, 150.f, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererB_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererB_->Off();

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Death_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(145.f, 145.f, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererC_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererC_->Off();

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Death_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(145.f, 145.f, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererD_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererD_->Off();

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Death_Circle_Center.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(145.f, 145.f, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleCenterRenderer_->ChangeCamera(CameraOrder::MidCamera);
	circleCenterRenderer_->Off();

	deathAuraCollision01_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision01_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision01_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision01_->GetTransform().SetWorldScale(69.f, 69.f, 0);
	deathAuraCollision01_->SetCollisionMode(CollisionMode::Multiple);

	deathAuraCollision02_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision02_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision02_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision02_->GetTransform().SetWorldScale(69.f, 69.f, 0);
	deathAuraCollision02_->SetCollisionMode(CollisionMode::Multiple);

	deathAuraCollision03_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision03_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision03_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision03_->GetTransform().SetWorldScale(69.f, 69.f, 0);
	deathAuraCollision03_->SetCollisionMode(CollisionMode::Multiple);

	Off();
}
void DeathAura::Update(float _deltaTime)
{
	StateSet();
	GetTransform().SetWorldPosition(Player::GetPlayerInst().GetTransform().GetWorldPosition().x, Player::GetPlayerInst().GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);
	GetTransform().SetWorldScale({ deathAuraWeaponInfo_.weaponRange_ });
	deathAuraCollision02_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x + 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	deathAuraCollision03_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x - 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	atkTimer_ += _deltaTime;

	if (atkTimer_ > deathAuraWeaponInfo_.weaponAtkSpeed_)
	{
		if (deathAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{
			atkTimer_ = 0;
			deathAuraCollision01_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
		else	 if (deathAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{

			deathAuraCollision02_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
		else if (deathAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{
			deathAuraCollision03_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
	}
}
void DeathAura::RotateRenderer(float _deltaTime)
{

	if (addRadian_ < 360)
	{
		addRadian_ += 10 * _deltaTime;
	}
	else
	{
		addRadian_ = 0;
	}

	circleRendererA_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererB_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleRendererC_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererD_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleCenterRenderer_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	if (circleRendererA_->IsUpdate() == false)
	{
		circleRendererA_->On();
		circleRendererB_->On();
		circleRendererC_->On();
		circleRendererD_->On();
		circleCenterRenderer_->On();
	}
}
void DeathAura::End()
{

}

CollisionReturn DeathAura::DeatAuraToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other) // 발사체 부딪히면
{
	dynamic_cast<Monster*>(_Other->GetActor())->flash_ = true;
	dynamic_cast<Monster*>(_Other->GetActor())->GetMonsterInfo().hp_ -= deathAuraWeaponInfo_.weaponAtk_; //데미지줌
	return CollisionReturn::Continue;
}