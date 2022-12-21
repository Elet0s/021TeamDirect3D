#include"PreCompile.h"
#include"Spear.h"
#include"Player.h"

Spear::Spear()
	:
	referenceVector_(),
	resultCos_()
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
}
void Spear::Update(float _deltaTime)
{
	SerchTarget();
}
void Spear::End()
{

}

void Spear::StateSet()
{
	if (nowLevel_ < 2)
	{
		spearWeaponInfo_.weaponAtk_ = 1.13f;
		spearWeaponInfo_.weaponAtkSpeed_ = 100.f;//1ÃÊ¸¶´Ù

		spearWeaponInfo_.weaponPassAtk_ = 0;
		spearWeaponInfo_.weaponPassNum_ = 0;

		spearWeaponInfo_.weaponSize_ = 100;
		spearWeaponInfo_.weaponDuration_ = 100;
		spearWeaponInfo_.weaponSpeed_ = 100;

		spearWeaponInfo_.weaponknockback_ = 100;

		spearWeaponInfo_.weaponProjectileNum_ = 2;
		spearWeaponInfo_.weponConsecutiveAtkNum_ = 2;

	}
	else if (nowLevel_< 3)
	{

	}
	else if (nowLevel_ < 4)
	{

	}
	else if (nowLevel_ < 5)
	{

	}
	else if (nowLevel_ < 6)
	{

	}
	else if (nowLevel_<7)
	{

	}
	else if (nowLevel_ < 8)
	{

	}
}

void Spear::SerchTarget()
{

 Mouse::GetMouseInfo()->IsCurPosToClient();
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

void Spear::ColCheak()
{

}