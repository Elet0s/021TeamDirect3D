#include"PreCompile.h"
#include"Firering.h"
#include"Player.h"
#include"Monster.h"

Firering::Firering()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
	, atkTimer_(0)
{
	name_ = "화염반지";
	SetName(std::string_view("Firering"));
	myRank_ = Rank::Epic;
	maxLevel_ = 7;
}
Firering::~Firering()
{

}
void Firering::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(fireringAuraWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(fireringAuraWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(fireringAuraWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sRange = std::to_string(fireringAuraWeaponInfo_.weaponRange_).substr(0, std::to_string(fireringAuraWeaponInfo_.weaponRange_).find(".") + 3);

	etc_ = "범위 피해를 입힙니다\n치명타가 발생하지 않습니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n범위" + sRange + "m ";
}
void Firering::Effect()
{
	currentlevel_ += 1;
}
void Firering::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Cast_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(103.f, 103.f, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
	circleRendererA_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererA_->Off();

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Cast_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(100.f, 100.f, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
	circleRendererB_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererB_->Off();

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Cast_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(20.f, 20.f, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
	circleRendererC_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererC_->Off();

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Cast_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(40.f, 40.f, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
	circleRendererD_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererD_->Off();

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Cast_Circle_E.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(40.f, 40.f, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
	circleCenterRenderer_->ChangeCamera(CameraOrder::MidCamera);
	circleCenterRenderer_->Off();

	fireringAuraCollision01_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision01_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision01_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision01_->SetCollisionMode(CollisionMode::Single);
	fireringAuraCollision01_->GetTransform().SetWorldScale(46.f, 46.f, 0);

	fireringAuraCollision02_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision02_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision02_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision02_->SetCollisionMode(CollisionMode::Single);
	fireringAuraCollision02_->GetTransform().SetWorldScale(40.f, 40.f, 0);

	fireringAuraCollision03_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision03_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision03_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision03_->SetCollisionMode(CollisionMode::Single);
	fireringAuraCollision03_->GetTransform().SetWorldScale(40.f, 40.f, 0);

	Off();
}



void Firering::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	fireringAuraWeaponInfo_.weaponAtk_ = round((3.f + currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	fireringAuraWeaponInfo_.weaponAtkSpeed_ = round(200.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result));
	fireringAuraWeaponInfo_.weaponPassAtk_ = 0;
	fireringAuraWeaponInfo_.weaponRange_ = 4.6f + (0.2f * currentlevel_) * Info->atk_Range_;

	fireringAuraWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	fireringAuraWeaponInfo_.weaponSize_ = 100 * Info->projectileSize_ * PInfo->projectileSize_Result;
	fireringAuraWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result;
	fireringAuraWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;
	
}

void Firering::Update(float _deltaTime)
{
	StateSet();
	GetTransform().SetWorldScale(fireringAuraWeaponInfo_.weaponRange_);
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);

	fireringAuraCollision02_->GetTransform().SetWorldPosition(fireringAuraCollision01_->GetTransform().GetWorldPosition().x + 100.f, fireringAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	fireringAuraCollision03_->GetTransform().SetWorldPosition(fireringAuraCollision01_->GetTransform().GetWorldPosition().x - 100.f, fireringAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	atkTimer_ += _deltaTime;


		if  (atkTimer_ < fireringAuraWeaponInfo_.weaponAtkSpeed_ / 2)
		{
			circleRendererA_->GetPixelData().mulColor_ -= float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererB_->GetPixelData().mulColor_ -= float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererC_->GetPixelData().mulColor_ -= float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererD_->GetPixelData().mulColor_ -= float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleCenterRenderer_->GetPixelData().mulColor_ -= float4(0.0f, 0.0f, 0.0f, 0.1f);
		}
		else if (atkTimer_ > fireringAuraWeaponInfo_.weaponAtkSpeed_ / 2)
		{
			circleRendererA_->GetPixelData().mulColor_ += float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererB_->GetPixelData().mulColor_ += float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererC_->GetPixelData().mulColor_ += float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleRendererD_->GetPixelData().mulColor_ += float4(0.0f, 0.0f, 0.0f, 0.1f);
			circleCenterRenderer_->GetPixelData().mulColor_ += float4(0.0f, 0.0f, 0.0f, 0.1f);
		}

	 if (atkTimer_ > fireringAuraWeaponInfo_.weaponAtkSpeed_)
	{
		circleRendererA_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.f);
		circleRendererB_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.f);
		circleRendererC_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.f);
		circleRendererD_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.f);
		circleCenterRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.f);
		atkTimer_ = 0;

		if (fireringAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D) == true)
		{
			fireringAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::FireringToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
		else if (fireringAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D) == true)
		{
			fireringAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::FireringToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
		else if (fireringAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D) == true)
		{
			fireringAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::FireringToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
	}
}
void Firering::End()
{

}
void Firering::RotateRenderer(float _deltaTime)
{
	if (addRadian_ < 360)
	{
		addRadian_ += 100 * _deltaTime;
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
	if (circleRendererA_->IsUpdate() ==false)
	{
		circleRendererA_->On();
		circleRendererB_->On();
		circleRendererC_->On();
		circleRendererD_->On();
		circleCenterRenderer_->On();
	}


}

CollisionReturn Firering::FireringToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= fireringAuraWeaponInfo_.weaponAtk_; //데미지줌
	return CollisionReturn::Continue;
}