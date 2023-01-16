#include"PreCompile.h"
#include"KunaiProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"
#include "Monster.h"

KunaiProjectile::KunaiProjectile()
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
KunaiProjectile::~KunaiProjectile()
{

}

void KunaiProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Kunai.png");
	projectileRen_->GetTransform().SetWorldScale(20.f, 40.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	projectileCol_->GetTransform().SetLocalScale({ 25.0f, 25.0f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Single);
	projectileCol_->Off();
}

void KunaiProjectile::TimeOff(float _deltaTime)
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

void KunaiProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		TimeOff(_deltaTime);
		Shoothing(_deltaTime);
		projectileCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&KunaiProjectile::ProjectileToMonster, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void KunaiProjectile::End()
{

}

void KunaiProjectile::ProjectileSet(float _atk, float _speed, float _angle, size_t _passNum)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	angle_ = _angle;
	posSet_ = true;
	passNum_ = _passNum;
}

void KunaiProjectile::Shoothing(float _deltaTime)
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

void KunaiProjectile::Rotate()
{
	GetTransform().SetWorldRotation(0, 0, GetLevel<TestLevel>()->GetMousePointer()->GetAimLineAngle() + angle_);
}

CollisionReturn KunaiProjectile::ProjectileToMonster(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	dynamic_cast<Monster*>(_Other->GetActor())->flash_ = true;
	dynamic_cast<Monster*>(_Other->GetActor())->GetMonsterInfo().hp_ -= projectileatk_; //µ¥¹ÌÁöÁÜ
	if (passNum_ == 0)
	{
		projectileRen_->Off();
		projectileCol_->Off();
		Death();
	}
	else if (passNum_ > 0)
	{
		passNum_ -= 1;
	}
	return CollisionReturn::Continue;
}

void KunaiProjectile::LevelEndEvent()
{
	Death();
}