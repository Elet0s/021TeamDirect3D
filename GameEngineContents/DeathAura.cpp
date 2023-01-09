#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
#include "Monster.h"
//#include <memory>

DeathAura::DeathAura()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
	, atkTimer_(0)
{

}

DeathAura::~DeathAura()
{
}



void DeathAura::Init()
{
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(damege * PlayerInfo_->atk_).substr(0, std::to_string(damege * PlayerInfo_->atk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).substr(0, std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).find(".") + 3);
	std::string sRange = std::to_string(rangeSize * PlayerInfo_->atk_Range_).substr(0, std::to_string(rangeSize * PlayerInfo_->atk_Range_).find(".") + 3);

	etc_ = "범위 내의 근처 적에게 지속\n피해를 입힙니다\n치명타가 발생하지 않습니다\n" + sDamege + " 의 피해\n" + sAttackSpeed + "초 마다 공격\n범위 "
		+ sRange + "m ";
}

void DeathAura::Effect()
{
	currentlevel_ += 1;
	if (currentlevel_ >= 5)
	{
		damege += 0.75f;
		rangeSize += 0.25f;
	}

	else if (currentlevel_ % 2 == 0)
	{
		damege += 0.38f;
		rangeSize += 0.5f;
	}

	else if (currentlevel_ % 2 == 1)
	{
		damege += 0.37f;
		rangeSize += 0.5f;
	}
}

void  DeathAura::StateSet()
{
	if (nowLevel_ < 2)
	{
		deathAuraWeaponInfo_.weaponAtk_ = 0.13f;
		deathAuraWeaponInfo_.weaponAtkSpeed_ = 0.3f;//1초마다

		deathAuraWeaponInfo_.weaponPassAtk_ = 0;
		deathAuraWeaponInfo_.weaponPassNum_ = 2;

		deathAuraWeaponInfo_.weaponSize_ = 100;
		deathAuraWeaponInfo_.weaponDuration_ = 100;
		deathAuraWeaponInfo_.weaponSpeed_ = 100;


	}
	else if (nowLevel_ < 3)
	{


	}
	else if (nowLevel_ < 4)
	{

	}
	else if (nowLevel_ < 5)
	{

	}
	else if (nowLevel_ < 6)
	{
	}
}
void DeathAura::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Death_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(515, 515, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Death_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(500, 500, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Death_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(475, 475, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Death_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(475, 475, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Death_Circle_Center.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(475, 475, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	deathAuraCollision01_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision01_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision01_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision01_->GetTransform().SetWorldScale(230, 230, 0);

	deathAuraCollision02_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision02_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision02_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision02_->GetTransform().SetWorldScale(200, 200, 0);

	deathAuraCollision03_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision03_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision03_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision03_->GetTransform().SetWorldScale(200, 200, 0);

	Off();
}
void DeathAura::Update(float _deltaTime)
{
	StateSet();
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);

	deathAuraCollision02_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x + 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	deathAuraCollision03_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x - 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	atkTimer_ += _deltaTime;

	if (atkTimer_ > deathAuraWeaponInfo_.weaponAtkSpeed_)
	{
		atkTimer_ = 0;
		deathAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&DeathAura::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		deathAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&DeathAura::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		deathAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&DeathAura::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

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
}
void DeathAura::End()
{

}

CollisionReturn DeathAura::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // 발사체 부딪히면
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= deathAuraWeaponInfo_.weaponAtk_; //데미지줌
	return CollisionReturn::Continue;
}