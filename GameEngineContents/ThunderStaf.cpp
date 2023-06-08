#include"PreCompile.h"
#include"ThunderStaf.h"
#include"Player.h"
#include"Monster.h"
#include "TestLevel.h"
#include "ThunderStafProjectile.h"
#include "Mouse.h"
ThunderStaf::ThunderStaf()
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
	name_ = "번개 지팡이";
	SetName(std::string_view("ThunderStaf"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}
ThunderStaf::~ThunderStaf()
{

}
void ThunderStaf::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(ThunderStafWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(ThunderStafWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(ThunderStafWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sTime = std::to_string(ThunderStafWeaponInfo_.weaponDuration_ /100).substr(0, std::to_string(ThunderStafWeaponInfo_.weaponDuration_ / 100).find(".") + 3);

	etc_ = "자신을 중심으로 공전하는\n번개 구체를 소환합니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n투사체" + std::to_string(ThunderStafWeaponInfo_.weaponProjectileNum_) + "개\n"
		+ sTime + "초 투사체 지속 시간 ";
}
void ThunderStaf::Effect()
{
	currentlevel_ += 1;
}
void ThunderStaf::Start()
{
	Off();
}

void ThunderStaf::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst().GetPlayerPassiveInfo();

	ThunderStafWeaponInfo_.weaponAtk_ = round((1.f + currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	ThunderStafWeaponInfo_.weaponAtkSpeed_ = round(500.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result));
	ThunderStafWeaponInfo_.weaponPassAtk_ = 0;
	ThunderStafWeaponInfo_.weaponRange_ = 1.f * Info->rangeSize_;
	ThunderStafWeaponInfo_.weaponProjectileNum_ = 3 + Info->addProjectile_;
	ThunderStafWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	ThunderStafWeaponInfo_.weaponSize_ = 1 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	ThunderStafWeaponInfo_.weaponDuration_ = 250 + (30.f * currentlevel_);
	ThunderStafWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result;

	if (currentlevel_ < 5)
	{
		ThunderStafWeaponInfo_.weaponProjectileNum_ = 3 + currentlevel_ + Info->addProjectile_;
	}
	else
	{
		ThunderStafWeaponInfo_.weaponProjectileNum_ = 7 + Info->addProjectile_;
	}

	if (currentlevel_ > 5)
	{
		ThunderStafWeaponInfo_.weaponSpeed_ = (100 + (20.f * (currentlevel_ - 5))) * Info->projectilespeed_ * PInfo->projectileSpeed_Result;
	}

}


void ThunderStaf::Update(float _deltaTime)
{
	StateSet();
	AimSet();
	Shoothing(_deltaTime);
}
void ThunderStaf::End()
{

}

void ThunderStaf::Shoothing(float _deltaTime)
{
	timer_ += _deltaTime;
	duringtime_ += _deltaTime;
	if (timer_ > ThunderStafWeaponInfo_.weaponAtkSpeed_)
	{
		GameEngineSound::SoundPlayOneshot("Throw_Sound.wav");
		mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst().GetTransform().GetWorldPosition();
		playerPos_ = Player::GetPlayerInst().GetTransform().GetWorldPosition();
		range_.x = mouseAimPos_.x - playerPos_.x;
		range_.y = mouseAimPos_.y - playerPos_.y;
		consecutiveAngle_ = 360.f / ThunderStafWeaponInfo_.weaponProjectileNum_;
		for (size_t i = 0; i < ThunderStafWeaponInfo_.weaponProjectileNum_; i++)
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
			ThunderStafProjectile* A = GetLevel()->CreateActor<ThunderStafProjectile>(ObjectOrder::Projectile);
			A->GetTransform().SetWorldPosition({ Player::GetPlayerInst().GetTransform().GetWorldPosition().x,	Player::GetPlayerInst().GetTransform().GetWorldPosition().y,-219.f });
			A->ProjectileSet(ThunderStafWeaponInfo_.weaponAtk_, ThunderStafWeaponInfo_.weaponSpeed_, angle_, ThunderStafWeaponInfo_.weaponPassNum_);
		}
		timer_ = 0.f;
	}
}

void ThunderStaf::AimSet()
{
	if (setAim_ == false)
	{
		GetLevel<TestLevel>()->GetMousePointer()->ChangeMousePointerRenderer(true);
		setAim_ = true;
	}

}