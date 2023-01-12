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
	setAim_(false),
	timeer_(0),
	angle_()
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
	Shoothing(_deltaTime);
}
void Spear::End()
{

}

void Spear::StateSet()
{
	if (currentlevel_ < 2)
	{ 
		spearWeaponInfo_.weaponAtk_ = Player::GetPlayerInst()->GetPlayerInfo().atk_ * currentlevel_ ;
		spearWeaponInfo_.weaponAtkSpeed_ = 500.f;//1√ ∏∂¥Ÿ

		spearWeaponInfo_.weaponPassAtk_ = 0;
		spearWeaponInfo_.weaponPassNum_ = 1;

		spearWeaponInfo_.weaponSize_ = 100;
		spearWeaponInfo_.weaponDuration_ = 100;
		spearWeaponInfo_.weaponSpeed_ = 100;

		spearWeaponInfo_.weaponknockback_ = 100;

		spearWeaponInfo_.weaponProjectileNum_ = 2;
		spearWeaponInfo_.weponConsecutiveAtkNum_ = 2;
	}
	else if (currentlevel_< 3)
	{

	}
	else if (currentlevel_ < 4)
	{

	}
	else if (currentlevel_ < 5)
	{

	}
	else if (currentlevel_ < 6)
	{

	}
	else if (currentlevel_<7)
	{

	}
	else if (currentlevel_ < 8)
	{

	}
}

void Spear::Shoothing(float _deltaTime)
{
	timeer_ += _deltaTime;
	if (timeer_>1.f)
	{
		for (size_t i = 0; i < spearWeaponInfo_.weponConsecutiveAtkNum_; i++)
		{
			for (size_t i = 0; i < spearWeaponInfo_.weaponProjectileNum_; i++)
			{
				std::shared_ptr<SpearProjectile> A = GetLevel()->CreateActor<SpearProjectile>(ObjectOrder::Projectile);
				A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y });
				A->ProjectileSet(spearWeaponInfo_.weaponAtk_, spearWeaponInfo_.weaponAtkSpeed_);
				A->ProjectileAngleSet(30);
			}
			timeer_ = 0;
		}
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