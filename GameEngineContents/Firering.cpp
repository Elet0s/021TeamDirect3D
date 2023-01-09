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

}
Firering::~Firering()
{

}
void Firering::Init()
{

}
void Firering::Effect()
{

}
void Firering::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Cast_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(515, 515, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Cast_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(500, 500, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Cast_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(200, 200, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Cast_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(200, 200, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Cast_Circle_E.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(200, 200, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	fireringAuraCollision01_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision01_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision01_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision01_->GetTransform().SetWorldScale(230, 230, 0);

	fireringAuraCollision02_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision02_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision02_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision02_->GetTransform().SetWorldScale(200, 200, 0);

	fireringAuraCollision03_ = CreateComponent<GameEngineCollision>();
	fireringAuraCollision03_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	fireringAuraCollision03_->ChangeOrder(ObjectOrder::Projectile);
	fireringAuraCollision03_->GetTransform().SetWorldScale(200, 200, 0);

	Off();
}



void Firering::StateSet()
{
	if (nowLevel_ < 2)
	{
		fireringAuraWeaponInfo_.weaponAtk_ = 10.13f;
		fireringAuraWeaponInfo_.weaponAtkSpeed_ = 3.f;
		fireringAuraWeaponInfo_.weaponPassAtk_ = 0;
		fireringAuraWeaponInfo_.weaponPassNum_ = 2;

		fireringAuraWeaponInfo_.weaponSize_ = 100;
		fireringAuraWeaponInfo_.weaponDuration_ = 100;
		fireringAuraWeaponInfo_.weaponSpeed_ = 100;


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

void Firering::Update(float _deltaTime)
{
	StateSet();
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);

	fireringAuraCollision02_->GetTransform().SetWorldPosition(fireringAuraCollision01_->GetTransform().GetWorldPosition().x + 100.f, fireringAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	fireringAuraCollision03_->GetTransform().SetWorldPosition(fireringAuraCollision01_->GetTransform().GetWorldPosition().x - 100.f, fireringAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	atkTimer_ += _deltaTime;

	if (atkTimer_ > fireringAuraWeaponInfo_.weaponAtkSpeed_)
	{
		atkTimer_ = 0;
		fireringAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		fireringAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		fireringAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Firering::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
}
void Firering::End()
{

}
void Firering::RotateRenderer(float _deltaTime)
{
	if (addRadian_ < 360)
	{
		addRadian_ += 5 * _deltaTime;
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

CollisionReturn Firering::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= fireringAuraWeaponInfo_.weaponAtk_; //µ•πÃ¡ˆ¡‹
	return CollisionReturn::Continue;
}