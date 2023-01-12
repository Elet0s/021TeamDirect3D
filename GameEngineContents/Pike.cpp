#include"PreCompile.h"
#include"Pike.h"
#include"Player.h"
#include"Monster.h"
#include "TestLevel.h"
#include "PikeProjectile.h"
#include "Mouse.h"

Pike::Pike()
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
Pike::~Pike()
{

}
void Pike::Init()
{

}
void Pike::Effect()
{

}

void Pike::Start()
{
	Off();
}
void Pike::Update(float _deltaTime)
{
	StateSet();
	AimSet();
	Shoothing(_deltaTime);
}
void Pike::End()
{

}

void Pike::StateSet()
{
	if (currentlevel_ < 2)
	{
		pikeWeaponInfo_.weaponAtk_ = 4.f;//Player::GetPlayerInst()->GetPlayerInfo().atk_ * currentlevel_ ;
		pikeWeaponInfo_.weaponAtkSpeed_ = 2.f;//1√ ∏∂¥Ÿ

		pikeWeaponInfo_.weaponPassAtk_ = 0;
		pikeWeaponInfo_.weaponPassNum_ = 1;

		pikeWeaponInfo_.weaponSize_ = 100;
		pikeWeaponInfo_.weaponDuration_ = 100;
		pikeWeaponInfo_.weaponSpeed_ = 1500.f;

		pikeWeaponInfo_.weaponknockback_ = 100;

		pikeWeaponInfo_.weaponProjectileNum_ = 2;
		pikeWeaponInfo_.weponConsecutiveAtkNum_ = 2;
	}
	else if (currentlevel_ < 3)
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
	else if (currentlevel_ < 7)
	{

	}
	else if (currentlevel_ < 8)
	{

	}
}

void Pike::Shoothing(float _deltaTime)
{
	timer_ += _deltaTime;
	duringtime_ += _deltaTime;
	if (timer_ > pikeWeaponInfo_.weaponAtkSpeed_)
	{
		if (pikeWeaponInfo_.weponConsecutiveAtkNum_ > consecutiveCounter_)
		{
			if (duringtime_ > 0.1f)
			{
				consecutiveCounter_ += 1;
				mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				playerPos_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				range_.x = mouseAimPos_.x - playerPos_.x;
				range_.y = mouseAimPos_.y - playerPos_.y;

				for (size_t i = 0; i < pikeWeaponInfo_.weaponProjectileNum_; i++)
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
						angle_ += 5;
					}
					std::shared_ptr<PikeProjectile> A = GetLevel()->CreateActor<PikeProjectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y,-219.f });
					A->ProjectileSet(pikeWeaponInfo_.weaponAtk_, pikeWeaponInfo_.weaponSpeed_, angle_);
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

void Pike::ProjectileSort()
{
}

void Pike::RenderRotate()
{

}

void Pike::RangeCheak(float _deltaTime)
{

}

void Pike::AimSet()
{
	if (setAim_ == false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}