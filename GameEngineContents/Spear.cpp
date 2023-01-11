#include"PreCompile.h"
#include"Spear.h"
#include"Player.h"
#include"Monster.h"
#include "TestLevel.h"
#include "SpearProjectile.h"
#include "Mouse.h"
Spear::Spear()
	:
	referenceVector_(),
	resultCos_(),
	Shooting_(false),
	range_(),
	setAim_(false)
{

}
Spear::~Spear()
{

}
void Spear::Init()
{

}
void Spear::Effect()
{

}

void Spear::Start()
{
	Off();
}
void Spear::Update(float _deltaTime)
{
	StateSet();
	AimSet();
	SerchTarget(_deltaTime);
}
void Spear::End()
{

}

void Spear::StateSet()
{
	if (nowLevel_ < 2)
	{ 
		spearWeaponInfo_.weaponAtk_ = 1.f;
		spearWeaponInfo_.weaponAtkSpeed_ = 100.f;//1ÃÊ¸¶´Ù

		spearWeaponInfo_.weaponPassAtk_ = 0;
		spearWeaponInfo_.weaponPassNum_ = 1;

		spearWeaponInfo_.weaponSize_ = 100;
		spearWeaponInfo_.weaponDuration_ = 100;
		spearWeaponInfo_.weaponSpeed_ = 100;

		spearWeaponInfo_.weaponknockback_ = 100;

		spearWeaponInfo_.weaponProjectileNum_ = 2;
		spearWeaponInfo_.weponConsecutiveAtkNum_ = 2;
	}
	else if (nowLevel_< 3)
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
	else if (nowLevel_<7)
	{

	}
	else if (nowLevel_ < 8)
	{

	}
}

void Spear::SerchTarget(float _deltaTime)
{
	if (Shooting_ == false)
	{

		std::shared_ptr<SpearProjectile> A = GetLevel()->CreateActor<SpearProjectile>(ObjectOrder::Projectile);
		A->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,GetTransform().GetWorldPosition().y });
		A->ProjectileSet(spearWeaponInfo_.weaponAtk_, spearWeaponInfo_.weaponAtkSpeed_);
		Shooting_ = true;
	}


}

void Spear::ProjectileSort()
{
}

void Spear::RenderRotate()
{

}

void Spear::RangeCheak(float _deltaTime)
{

}

void Spear::AimSet()
{
	if (setAim_ ==false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}