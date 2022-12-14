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
	timer_(0),
	angle_(0),
	duringtime_(0),
	consecutiveCounter_(0)
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
		spearWeaponInfo_.weaponAtk_ = 4.f;//Player::GetPlayerInst()->GetPlayerInfo().atk_ * currentlevel_ ;
		spearWeaponInfo_.weaponAtkSpeed_ = 2.f;//1?ʸ???

		spearWeaponInfo_.weaponPassAtk_ = 0;
		spearWeaponInfo_.weaponPassNum_ = 1;

		spearWeaponInfo_.weaponSize_ = 100;
		spearWeaponInfo_.weaponDuration_ = 100;
		spearWeaponInfo_.weaponSpeed_ = 1500.f;

		spearWeaponInfo_.weaponknockback_ = 100;

		spearWeaponInfo_.weaponProjectileNum_ = 30;
		spearWeaponInfo_.weponConsecutiveAtkNum_ = 3;
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
	timer_ += _deltaTime;
	duringtime_ += _deltaTime;
	if (timer_ > spearWeaponInfo_.weaponAtkSpeed_)
	{
		if (spearWeaponInfo_.weponConsecutiveAtkNum_ > consecutiveCounter_)
		{
			if (duringtime_ > 0.1f)
			{
				consecutiveCounter_ += 1;
				mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				playerPos_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				range_.x = mouseAimPos_.x - playerPos_.x;
				range_.y = mouseAimPos_.y - playerPos_.y;

				for (size_t i = 0; i < spearWeaponInfo_.weaponProjectileNum_; i++)
				{
					if (i == 0)
					{
						angle_ = 0;
					}
					else if (i % 2 == 0)
					{
						angle_ *= -1;
					}
					else if (i % 2 == 1)
					{
						if (angle_ < 0)
						{
							angle_ *= -1;
						}
						angle_ += 15;
					}
					std::shared_ptr<SpearProjectile> A = GetLevel()->CreateActor<SpearProjectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y,-219.f });
					A->ProjectileSet(spearWeaponInfo_.weaponAtk_, spearWeaponInfo_.weaponSpeed_, angle_);
				}
				duringtime_ = 0.f;
			}

		}
		else
		{
			consecutiveCounter_ = 0;
			timer_ = 0.f;
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