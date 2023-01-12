#include"PreCompile.h"
#include"SpearProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"

SpearProjectile::SpearProjectile()
	:projectileRen_(),
	projectileCol_(),
	timer_(0.f),
	px_(0.f),
	py_(0.f),
	mpx_(0.f),
	mpy_(0.f),
	shoothing_(false),
	range_(),
	resultVector_(),
	posSet_(false),
	projectileatk_(0.f),
	projectilespeed_(0.f),
	angle_(0.f)
{

}
SpearProjectile::~SpearProjectile()
{

}

void SpearProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Spear.png");
	projectileRen_->GetTransform().SetWorldScale(40.f, 40.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	projectileCol_->GetTransform().SetLocalScale({ 25.0f, 25.0f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Single);
	projectileCol_->Off();
}

void SpearProjectile::TimeOff(float _deltaTime)
{
	if (timer_ < 3.f)
	{
		timer_ += _deltaTime;
	}
	else
	{
		Death();
	}
}

void SpearProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		Shoothing(_deltaTime);
		TimeOff(_deltaTime);
		projectileCol_->IsCollision(
			CollisionType::CT_Sphere2D,
			ObjectOrder::Monster,
			CollisionType::CT_Sphere2D,
			std::bind(
				&SpearProjectile::ProjectileToPlayer,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		);
	}
}

void SpearProjectile::End()
{

}

void SpearProjectile::ProjectileSet(float _atk, float _speed)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	posSet_ = true;
}

void SpearProjectile::Shoothing(float _deltaTime)
{
	if (shoothing_ == false)
	{
		if (projectileRen_->IsUpdate() == false)
		{
			projectileRen_->On();
			projectileCol_->On();
		}
			mouseAimPos_ = GetLevel<TestLevel>()->GetMousePointer()->GetTransform().GetWorldPosition() + Player::GetPlayerInst()->GetTransform().GetWorldPosition();
			playerPos_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition();

			range_.x =   mouseAimPos_.x - playerPos_.x;
			range_.y =  mouseAimPos_.y- playerPos_.y;
			referenceVector_ = range_.Normalize3D() * _deltaTime * projectilespeed_;
			Rotate();
			shoothing_ = true;
	}
	GetTransform().SetWorldMove(referenceVector_);
}

void SpearProjectile::ProjectileAngleSet(float _angle)
{
	angle_ = _angle;
}

void SpearProjectile::Rotate()
{
	GetTransform().SetWorldRotation(0, 0, GetLevel<TestLevel>()->GetMousePointer()->GetAimLineAngle() + angle_);

}

CollisionReturn SpearProjectile::ProjectileToPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	Player::GetPlayerInst()->GetPlayerInfo().hp_ -= projectileatk_;
	projectileRen_->Off();
	projectileCol_->Off();
	Death();
	return CollisionReturn::Continue;
}