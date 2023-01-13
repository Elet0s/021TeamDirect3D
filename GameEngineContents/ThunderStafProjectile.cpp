#include"PreCompile.h"
#include"ThunderStafProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"
#include "Monster.h"

ThunderStafProjectile::ThunderStafProjectile()
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
	angle_(0.f),
	passNum_(0)
{
}
ThunderStafProjectile::~ThunderStafProjectile()
{

}

void ThunderStafProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Particle.png");
	projectileRen_->GetPixelData().mulColor_=float4::Blue;
	projectileRen_->GetTransform().SetWorldScale(40.f, 40.f, 1.f);
	projectileRen_->GetTransform().SetWorldPosition(0.f, 100.f, 0.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	projectileCol_->SetParent(projectileRen_);
	projectileCol_->GetTransform().SetWorldScale({ 25.0f, 25.0f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Multiple);

	projectileCol_->Off();
}

void ThunderStafProjectile::TimeOff(float _deltaTime)
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

void ThunderStafProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		TimeOff(_deltaTime);
		Shoothing(_deltaTime);
		projectileCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&ThunderStafProjectile::ProjectileToMonster, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void ThunderStafProjectile::End()
{

}

void ThunderStafProjectile::ProjectileSet(float _atk, float _speed, float _angle, size_t _passNum)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	angle_ = _angle;
	posSet_ = true;
	passNum_ = _passNum;
}

void ThunderStafProjectile::Shoothing(float _deltaTime)
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
	GetTransform().SetWorldPosition({Player::GetPlayerInst()->GetTransform().GetWorldPosition()});
	GetTransform().SetAddWorldRotation({0.f,0.f,80.f *_deltaTime });


}

void ThunderStafProjectile::Rotate()
{
	GetTransform().SetWorldRotation(60, 0, GetLevel<TestLevel>()->GetMousePointer()->GetAimLineAngle() + angle_);
}

CollisionReturn ThunderStafProjectile::ProjectileToMonster(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= projectileatk_; //µ•πÃ¡ˆ¡‹

	return CollisionReturn::Stop;
}

void ThunderStafProjectile::LevelEndEvent()
{
	Death();
}