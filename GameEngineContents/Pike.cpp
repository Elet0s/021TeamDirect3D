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
	name_ = "창";
	SetName(std::string_view("Pike"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}
Pike::~Pike()
{

}
void Pike::Init()
{
	StateSet();
	std::string sDamege = std::to_string(pikeWeaponInfo_.weaponAtk_).substr(0, std::to_string(pikeWeaponInfo_.weaponAtk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(pikeWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(pikeWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sSize = std::to_string(static_cast<int>(pikeWeaponInfo_.weaponSize_));

	etc_ = "조준된 방향으로\n빠르게 찌릅니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n투사체 " + std::to_string(pikeWeaponInfo_.weaponProjectileNum_) + " 개\n" 
		+ sSize + "% 투사체 크기 ";
}
void Pike::Effect()
{
	currentlevel_ += 1;
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
	PlayerInfo* Info = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	pikeWeaponInfo_.weaponAtk_ = round((5.f + (1.2f * currentlevel_)) * (Info->atk_ * PInfo->atkMultiple_Result / 100.f));
	pikeWeaponInfo_.weaponAtkSpeed_ = (100.f + 2.f * currentlevel_) / (Info->attackSpeed_ * PInfo->attackSpeed_Result);

	pikeWeaponInfo_.weaponPassAtk_ = 0;
	pikeWeaponInfo_.weaponPassNum_ = 1 + Info->passProjectile_;

	pikeWeaponInfo_.weaponSize_ = 1.f + (0.2f * currentlevel_) * (Info->projectileSize_ * PInfo->projectileSize_Result  / 100);
	pikeWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100; ;
	pikeWeaponInfo_.weaponSpeed_ = 1000.f * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100; // 속도 10배 조정함
	pikeWeaponInfo_.weaponProjectileNum_ = 1;
	pikeWeaponInfo_.weponConsecutiveAtkNum_ = 2;

	if (currentlevel_ >= 3)
	{
		pikeWeaponInfo_.weaponProjectileNum_ = 2 + Info->addProjectile_;
	}

	if (currentlevel_ < 4)
	{
		pikeWeaponInfo_.weaponProjectileNum_ = 2 + currentlevel_ +Info->addProjectile_;
	}
	else
	{
		pikeWeaponInfo_.weaponProjectileNum_ = 5 + currentlevel_ + Info->addProjectile_;
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