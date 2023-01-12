#include"PreCompile.h"
#include"WindsBlade.h"
#include "WindsBladeProjectile.h"
#include"Player.h"

WindsBlade::WindsBlade()
	:timer_(0),
	RLSwitch_(false)
{
	name_ = "�ٶ��� Į��";
	SetName(std::string_view("WindsBlade"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}

WindsBlade::~WindsBlade()
{

}

void WindsBlade::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(WindsBladeWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(WindsBladeWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(WindsBladeWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	
	etc_ = "�ڽ��� �� ������\n�ٶ��� Į���� ��ȯ�մϴ�\n" + sDamege + "�� ����\n" + sAttackSpeed + "�� ���� ����\n" + std::to_string(WindsBladeWeaponInfo_.weaponPassNum_) + "���� ";

}

void  WindsBlade::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	WindsBladeWeaponInfo_.weaponAtk_ = round((3.f + 2.f * currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	WindsBladeWeaponInfo_.weaponAtkSpeed_ = round((100.f - 0.7f *currentlevel_)/ (Info->attackSpeed_ * PInfo->attackSpeed_Result));
	WindsBladeWeaponInfo_.weaponPassAtk_ = 0;
	WindsBladeWeaponInfo_.weaponRange_ = 1.f * Info->rangeSize_;
	WindsBladeWeaponInfo_.weaponProjectileNum_ = 1 + Info->addProjectile_;
	WindsBladeWeaponInfo_.weaponPassNum_ = 4 + currentlevel_ * 2 + Info->passProjectile_;

	WindsBladeWeaponInfo_.weaponSize_ = 1 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	WindsBladeWeaponInfo_.weaponDuration_ = 250 + (30.f * currentlevel_);
	WindsBladeWeaponInfo_.weaponSpeed_ = 10 * Info->projectilespeed_ * PInfo->projectileSpeed_Result;
}
void WindsBlade::Effect()
{
	currentlevel_ += 1;
}
void WindsBlade::Start()
{
	Off();
}

void WindsBlade::Update(float _deltaTime)
{
	StateSet();
	Shoothing(_deltaTime);
}

void WindsBlade::End()
{

}

void WindsBlade::Shoothing(float _deltaTime)
{
	timer_ += _deltaTime;
	if (timer_ > WindsBladeWeaponInfo_.weaponAtkSpeed_)
	{
		GameEngineSound::SoundPlayOneshot("Throw_Sound.wav");
		std::shared_ptr<WindsBladeProjectile> A = GetLevel()->CreateActor<WindsBladeProjectile>(ObjectOrder::Projectile);
		A->GetTransform().SetWorldPosition({ Player::GetPlayerInst()->GetTransform().GetWorldPosition().x,	Player::GetPlayerInst()->GetTransform().GetWorldPosition().y,-219.f });
		A->ProjectileSet(WindsBladeWeaponInfo_.weaponAtk_, WindsBladeWeaponInfo_.weaponSpeed_, WindsBladeWeaponInfo_.weaponProjectileNum_,RLSwitch_, WindsBladeWeaponInfo_.weaponPassNum_);
		if (RLSwitch_ == false)
		{
			RLSwitch_ = true;
		}
		else if(RLSwitch_ == true)
		{
			RLSwitch_ = false;
		}
		timer_ = 0;
	}
}