#include"PreCompile.h"
#include"Kunai.h"
#include"Player.h"
#include"Monster.h"
#include "TestLevel.h"
#include "KunaiProjectile.h"
#include "Mouse.h"
Kunai::Kunai()
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
	name_ = "쿠나이";
	SetName(std::string_view("Kunai"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}
Kunai::~Kunai()
{

}
void Kunai::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(kunaiWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(kunaiWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(kunaiWeaponInfo_.weaponAtkSpeed_).find(".") + 3);


	etc_ = "자신의 주변으로\n쿠나이를 던집니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n투사체 " + std::to_string(kunaiWeaponInfo_.weaponProjectileNum_) + " 개 ";
}
void Kunai::Effect()
{
	currentlevel_ += 1;
}

void Kunai::Start()
{
	Off();
}
void Kunai::Update(float _deltaTime)
{
	StateSet();
	AimSet();
	Shoothing(_deltaTime);
}
void Kunai::End()
{

}

void Kunai::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	kunaiWeaponInfo_.weaponAtk_ = round((2.f + 3.f * currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	kunaiWeaponInfo_.weaponAtkSpeed_ = 100.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	kunaiWeaponInfo_.weaponPassAtk_ = 0;
	kunaiWeaponInfo_.weaponRange_ = 1.f * Info->projectileSize_;
	kunaiWeaponInfo_.weaponProjectileNum_ = 3 + currentlevel_  + Info->addProjectile_;
	kunaiWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	kunaiWeaponInfo_.weaponSize_ = 100 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	kunaiWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100; ;
	kunaiWeaponInfo_.weaponSpeed_ = 1500.f * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;

	kunaiWeaponInfo_.weponConsecutiveAtkNum_ = 1;

	
	
}

void Kunai::Shoothing(float _deltaTime)
{
	timer_ += _deltaTime;
	duringtime_ += _deltaTime;
	if (timer_ > kunaiWeaponInfo_.weaponAtkSpeed_)
	{
		if (kunaiWeaponInfo_.weponConsecutiveAtkNum_ > consecutiveCounter_)
		{
			if (duringtime_ > 0.1f)
			{
				consecutiveCounter_ += 1;
				mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				playerPos_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition();
				range_.x = mouseAimPos_.x - playerPos_.x;
				range_.y = mouseAimPos_.y - playerPos_.y;
				consecutiveAngle_ = 360.f / kunaiWeaponInfo_.weaponProjectileNum_;
				for (size_t i = 0; i < kunaiWeaponInfo_.weaponProjectileNum_; i++)
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
					std::shared_ptr<KunaiProjectile> A = GetLevel()->CreateActor<KunaiProjectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y,-219.f });
					A->ProjectileSet(kunaiWeaponInfo_.weaponAtk_, kunaiWeaponInfo_.weaponSpeed_, angle_);
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

void Kunai::AimSet()
{
	if (setAim_ == false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}