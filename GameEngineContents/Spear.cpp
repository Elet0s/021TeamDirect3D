#include"PreCompile.h"
#include"Spear.h"
#include"Player.h"

Spear::Spear()
	:
	referenceVector_(),
	spearRenderer_(),
	spearCol_(),
	spearWeaponInfo_()
{

}
Spear::~Spear()
{

}

void Spear::Init()
{
;
}
void Spear::Effect()
{

}

void Spear::Start()
{
	valueSoulCard_ = SoulCard::Spear;
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
	spearRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	spearRenderer_->GetTransform().SetWorldScale(50, 80, 0);
	spearRenderer_->SetTexture("Spear.png");
	//spearRenderer_->GetTransform().SetWorldRotation({30});

	//referenceVector_ = GetTransform().GetUpVector();

	spearCol_ = CreateComponent<GameEngineCollision>();
	spearCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	spearCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	spearCol_->ChangeOrder(ObjectOrder::Projectile);

	Off();

	spearWeaponInfo_.weaponAtkSpeed_= 100.f;
	spearWeaponInfo_.weaponAtk_= 1;
	spearWeaponInfo_.weaponDuration_= 100;
	spearWeaponInfo_.weaponknockback_= 100;
	spearWeaponInfo_.weaponPassAtk_=1;
	spearWeaponInfo_.weaponSize_=100;
	spearWeaponInfo_.weaponSpeed_=100;
}
void Spear::Update(float _deltaTime)
{

}
void Spear::End()
{

}