#include"PreCompile.h"
#include"CleaverProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"
#include "Monster.h"

CleaverProjectile::CleaverProjectile()
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
CleaverProjectile::~CleaverProjectile()
{

}

void CleaverProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Cleave_Attack.png");
	projectileRen_->GetTransform().SetWorldScale(640.f, 160.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Blue);
	projectileCol_->GetTransform().SetLocalScale({ 640.f, 100.f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Multiple);
	projectileCol_->Off();
}

void CleaverProjectile::TimeOff(float _deltaTime)
{
	if (timer_ < 1.f)
	{
		timer_ += _deltaTime;
	}
	else
	{
		Death();
	}
}

void CleaverProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		TimeOff(_deltaTime);
		Shoothing(_deltaTime);
		projectileCol_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&CleaverProjectile::ProjectileToMonster, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void CleaverProjectile::End()
{

}

void CleaverProjectile::ProjectileSet(float _atk, float _speed, float _angle, size_t _passNum)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	angle_ = _angle;
	posSet_ = true;
	passNum_ = _passNum;
}

void CleaverProjectile::Shoothing(float _deltaTime)
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

void CleaverProjectile::Rotate()
{
	GetTransform().SetWorldRotation(0, 0, GetLevel<TestLevel>()->GetMousePointer()->GetAimLineAngle() + angle_);
}

CollisionReturn CleaverProjectile::ProjectileToMonster(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	dynamic_cast<Monster*>(_Other->GetActor())->flash_ = true;
	dynamic_cast<Monster*>(_Other->GetActor())->GetMonsterInfo().hp_ -= projectileatk_; //��������
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
	return CollisionReturn::Stop;
}

void CleaverProjectile::LevelEndEvent()
{
	Death();
}