#include"PreCompile.h"
#include"PikeProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"
#include "Monster.h"

PikeProjectile::PikeProjectile()
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
PikeProjectile::~PikeProjectile()
{

}

void PikeProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Spike.png");
	projectileRen_->GetTransform().SetWorldScale(50.f, 120.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_AABB2D, float4::Blue);
	projectileCol_->GetTransform().SetLocalScale({ 50.f, 120.f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Single);
	projectileCol_->Off();
}

void PikeProjectile::TimeOff(float _deltaTime)
{
	if (timer_ < 0.05f)
	{
		timer_ += _deltaTime;
	}
	else
	{
		Death();
	}
}

void PikeProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		TimeOff(_deltaTime);
		Shoothing(_deltaTime);
		projectileCol_->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&PikeProjectile::ProjectileToMonster, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void PikeProjectile::End()
{

}

void PikeProjectile::ProjectileSet(float _atk, float _speed, float _angle)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	angle_ = _angle;
	posSet_ = true;
}

void PikeProjectile::Shoothing(float _deltaTime)
{
	if (shoothing_ == false)
	{
		if (projectileRen_->IsUpdate() == false)
		{
			projectileRen_->On();
			projectileCol_->On();
		}
		Rotate();
		shoothing_ = true;
	}
	GetTransform().SetWorldUpMove(projectilespeed_, _deltaTime);
}

void PikeProjectile::Rotate()
{
	GetTransform().SetWorldRotation(0, 0, GetLevel<TestLevel>()->GetMousePointer()->GetAimLineAngle() + angle_);
}

CollisionReturn PikeProjectile::ProjectileToMonster(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= projectileatk_; //µ•πÃ¡ˆ¡‹
	return CollisionReturn::Continue;
}