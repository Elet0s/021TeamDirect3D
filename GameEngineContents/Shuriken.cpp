#include"PreCompile.h"
#include"Shuriken.h"
#include"Player.h"
#include"Monster.h"

Shuriken::Shuriken()
	: referenceVector_(),
	shuriKenRenderer_(),
	shuriKenCol_(),
	shuriKenWeaponInfo_(),
	shuriKenSerchCol_(),
	TargetMonsters_(),
	minHpPair_()
{

}
Shuriken::~Shuriken()
{


}
void Shuriken::Start()
{
	valueSoulCard_ = SoulCard::Shuriken;
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
	shuriKenRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	shuriKenRenderer_->GetTransform().SetWorldScale(50, 80, 0);
	shuriKenRenderer_->SetTexture("Spear.png");
	//spearRenderer_->GetTransform().SetWorldRotation({30});

	//referenceVector_ = GetTransform().GetUpVector();

	shuriKenCol_ = CreateComponent<GameEngineCollision>();
	shuriKenCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	shuriKenCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	shuriKenCol_->ChangeOrder(ObjectOrder::Projectile);

	shuriKenCol_ = CreateComponent<GameEngineCollision>();
	shuriKenCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::White);
	shuriKenCol_->GetTransform().SetLocalScale({ 350.0f, 350.0f, 1.0f });
	shuriKenCol_->ChangeOrder(ObjectOrder::SkillSerchBoad);

	Off();

	shuriKenWeaponInfo_.weaponAtkSpeed_ = 100.f;
	shuriKenWeaponInfo_.weaponAtk_ = 1;
	shuriKenWeaponInfo_.weaponDuration_ = 100;
	shuriKenWeaponInfo_.weaponknockback_ = 100;
	shuriKenWeaponInfo_.weaponPassAtk_ = 1;
	shuriKenWeaponInfo_.weaponSize_ = 100;
	shuriKenWeaponInfo_.weaponSpeed_ = 100;
}

void Shuriken::RangeCheak(float _deltaTime)
{
	shuriKenCol_->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
}
void Shuriken::Update(float _deltaTime)
{
	RangeCheak(_deltaTime);
	shuriKenCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	renderRotate(_deltaTime);
}
void Shuriken::End()
{

}
void Shuriken::renderRotate(float _deltaTime)
{
	referenceVector_ = Player::GetPlayerInst()->GetTransform().GetUpVector();

	for (size_t i = 0; i < TargetMonsters_.size(); i++)//범위안에 들어와있는 친구들 중에
	{
		if (TargetMonsters_[i]->GetMonsterInfo().hp_ > 0)
		{

			if (i == 0)//첫번째
			{
				minHpPair_ = std::make_pair(i, TargetMonsters_[i]->GetMonsterInfo().hp_);
			}
			else if (minHpPair_.second > TargetMonsters_[i]->GetMonsterInfo().hp_)//이전보다 현제검사중인 친구의 체력이 더 낮으면
			{
				minHpPair_ = std::make_pair(i, TargetMonsters_[i]->GetMonsterInfo().hp_);
			}
		}
	}
	if (minHpPair_.second > 0)
	{
		float Mx = TargetMonsters_[minHpPair_.first]->GetTransform().GetWorldPosition().x;
		float My = TargetMonsters_[minHpPair_.first]->GetTransform().GetWorldPosition().y;
		float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
		float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
		float4 RangeVector = (Px - Mx, Py - My);
		RangeVector = RangeVector.Normalize3D();

		float Cos = (referenceVector_.x * RangeVector.x) + (referenceVector_.y * RangeVector.y);
		float A = acos(Cos);
	}
}

CollisionReturn Shuriken::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	
	TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));
	return CollisionReturn::Stop;
}