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
	name_ = "대검";
	SetName(std::string_view("Cleaver"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 7;
}
Cleaver::~Cleaver()
{

}
void Cleaver::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(cleaverWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(cleaverWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(cleaverWeaponInfo_.weaponAtkSpeed_).find(".") + 3);

	
	etc_ = "조준된 방향으로\n 적을 밀어내는\n약하지만 큰\n투사체를 발사합니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격 ";
}
void Cleaver::Effect()
{
	currentlevel_ += 1;
}

void Cleaver::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	cleaverWeaponInfo_.weaponAtk_ = round((1.f + 2.f * currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	cleaverWeaponInfo_.weaponAtkSpeed_ = (200.f - (currentlevel_ * 25.f))  / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	cleaverWeaponInfo_.weaponPassAtk_ = 0;
	cleaverWeaponInfo_.weaponRange_ = 1.f * Info->projectileSize_;
	cleaverWeaponInfo_.weaponProjectileNum_ = 3 + Info->addProjectile_;
	cleaverWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	cleaverWeaponInfo_.weaponSize_ = 100 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	cleaverWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100; ;
	cleaverWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;

	
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
		CleaverWeaponInfo_.weaponAtkSpeed_ = 2.f;//1초마다

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