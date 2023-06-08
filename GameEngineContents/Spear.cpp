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
	name_ = "단창";
	SetName(std::string_view("Spear"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 7;
}
Spear::~Spear()
{

}
void Spear::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(spearWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(spearWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(spearWeaponInfo_.weaponAtkSpeed_).find(".") + 3);


	etc_ = "투사체를 조준된 방향으로\n발사합니다\n"+ sDamege + "의 피해\n" + sAttackSpeed +"초 마다 공격\n투사체" + std::to_string(spearWeaponInfo_.weaponProjectileNum_)+ " 개\n" + std::to_string(spearWeaponInfo_.weponConsecutiveAtkNum_) + "연속 공격 ";
}
void Spear::Effect()
{
	currentlevel_ += 1;
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
	PlayerInfo* Info = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst().GetPlayerPassiveInfo();

	spearWeaponInfo_.weaponAtk_ = round((3.f + 2.f * currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	spearWeaponInfo_.weaponAtkSpeed_ = (100.f - 7.f * currentlevel_)/ (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	spearWeaponInfo_.weaponPassAtk_ = 0;
	spearWeaponInfo_.weaponRange_ = 1.f * Info->projectileSize_;
	spearWeaponInfo_.weaponProjectileNum_ = 1 + Info->addProjectile_;
	spearWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	spearWeaponInfo_.weaponSize_ = 100 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	spearWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100; ;
	spearWeaponInfo_.weaponSpeed_ = 1500.f * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;

	spearWeaponInfo_.weponConsecutiveAtkNum_ = 2;

	if (currentlevel_ >= 2)
	{
		spearWeaponInfo_.weponConsecutiveAtkNum_ = 3;
	}

	if (currentlevel_ >= 4)
	{
		spearWeaponInfo_.weaponProjectileNum_ = 2  + Info->addProjectile_;
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
			GameEngineSound::SoundPlayOneshot("Throw_Sound.wav");
			if (duringtime_ > 0.1f)
			{
				consecutiveCounter_ += 1;
				mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst().GetTransform().GetWorldPosition();
				playerPos_ = Player::GetPlayerInst().GetTransform().GetWorldPosition();
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
					SpearProjectile* A = GetLevel()->CreateActor<SpearProjectile>(ObjectOrder::Projectile);
					A->GetTransform().SetWorldPosition({ Player::GetPlayerInst().GetTransform().GetWorldPosition().x,	Player::GetPlayerInst().GetTransform().GetWorldPosition().y,-219.f });
					A->ProjectileSet(spearWeaponInfo_.weaponAtk_, spearWeaponInfo_.weaponSpeed_, angle_,spearWeaponInfo_.weaponPassNum_);
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


void Spear::AimSet()
{
	if (setAim_ ==false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}