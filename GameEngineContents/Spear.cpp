#include"PreCompile.h"
#include"Spear.h"
#include"Player.h"

Spear::Spear()
	:
	referenceVector_(),
	resultCos_(),
	firstSort_(false)
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
		spearWeaponInfo_.weaponAtkSpeed_ = 100.f;//1초마다

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
	mouseAimPos_ = Mouse::GetMouseInfo()->IsCurPosToClient();
}
void Spear::ProjectileSort()
{
	if (firstSort_ == false) //처음이면 만들고
	{
		projectileGroupList_.reserve(30);
		for (size_t i = 0; i < spearWeaponInfo_.weaponProjectileNum_; i++)
		{
			projectileGroup_.first = CreateComponent<GameEngineTextureRenderer>();
			projectileGroup_.first->GetTransform().SetWorldScale(20, 20, 0);
			projectileGroup_.first->SetTexture("Spear.png");

			projectileGroup_.second = CreateComponent<GameEngineCollision>();
			projectileGroup_.second->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
			projectileGroup_.second->GetTransform().SetWorldScale(20, 20, 0);
			projectileGroup_.second->ChangeOrder(ObjectOrder::Projectile);


			projectileGroup_.first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -100)));
			projectileGroup_.second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());

			projectileGroupList_.push_back(projectileGroup_);

		}
		firstSort_ = true;
	}
	else if (timeer_ > 3.f)//아니면 있는걸로 돌려
	{
		timeer_ = 0.f;
		for (size_t i = 0; i < spearWeaponInfo_.weaponProjectileNum_; i++)
		{
			projectileGroupList_[i].first->On();
			projectileGroupList_[i].second->On();
			projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -100)));
			projectileGroupList_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
		}
	}
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