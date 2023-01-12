#include"PreCompile.h"
#include"Cleaver.h"
#include"Player.h"
#include"Monster.h"
#include "TestLevel.h"
#include "CleaverProjectile.h"
#include "Mouse.h"
Cleaver::Cleaver()
	:
	referenceVector_(),
	resultCos_(),
	Shooting_(false),
	range_(),
	setAim_(false),
	timer_(0),
	angle_(0),
	duringtime_(0),
	consecutiveCounter_(0),
	consecutiveAngle_(0)
{

}
Cleaver::~Cleaver()
{

}
void Cleaver::Init()
{

}
void Cleaver::Effect()
{

}

void Cleaver::Start()
{
	Off();
}
void Cleaver::Update(float _deltaTime)
{
	StateSet();
	AimSet();
	Shoothing(_deltaTime);
}
void Cleaver::End()
{

}

void Cleaver::StateSet()
{
	if (currentlevel_ < 2)
	{
		CleaverWeaponInfo_.weaponAtk_ = 4.f;//Player::GetPlayerInst()->GetPlayerInfo().atk_ * currentlevel_ ;
		CleaverWeaponInfo_.weaponAtkSpeed_ = 2.f;//1√ ∏∂¥Ÿ

		CleaverWeaponInfo_.weaponPassAtk_ = 0;
		CleaverWeaponInfo_.weaponPassNum_ = 1;

		CleaverWeaponInfo_.weaponSize_ = 100;
		CleaverWeaponInfo_.weaponDuration_ = 100;
		CleaverWeaponInfo_.weaponSpeed_ = 300.f;

		CleaverWeaponInfo_.weaponknockback_ = 100;

		CleaverWeaponInfo_.weaponProjectileNum_ = 1;
		CleaverWeaponInfo_.weponConsecutiveAtkNum_ = 1;
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

void Cleaver::Shoothing(float _deltaTime)
{
	timer_ += _deltaTime;
	duringtime_ += _deltaTime;
	if (timer_ > CleaverWeaponInfo_.weaponAtkSpeed_)
	{
		if (CleaverWeaponInfo_.weponConsecutiveAtkNum_ > consecutiveCounter_)
		{
			if (duringtime_ > 0.1f)
			{
				consecutiveCounter_ += 1;
				mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				playerPos_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				range_.x = mouseAimPos_.x - playerPos_.x;
				range_.y = mouseAimPos_.y - playerPos_.y;
				consecutiveAngle_ = 360.f / CleaverWeaponInfo_.weaponProjectileNum_;
				for (size_t i = 0; i < CleaverWeaponInfo_.weaponProjectileNum_; i++)
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
						angle_ += consecutiveAngle_;
					}
					std::shared_ptr<CleaverProjectile> A = GetLevel()->CreateActor<CleaverProjectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y,-219.f });
					A->ProjectileSet(CleaverWeaponInfo_.weaponAtk_, CleaverWeaponInfo_.weaponSpeed_, angle_);
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

void Cleaver::ProjectileSort()
{
}

void Cleaver::RenderRotate()
{

}

void Cleaver::RangeCheak(float _deltaTime)
{

}

void Cleaver::AimSet()
{
	if (setAim_ == false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}