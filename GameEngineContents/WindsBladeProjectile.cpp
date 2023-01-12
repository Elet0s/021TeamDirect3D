#include"PreCompile.h"
#include"WindsBladeProjectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"
#include"TestLevel.h"
#include "Mouse.h"
#include "Monster.h"

WindsBladeProjectile::WindsBladeProjectile()
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
	passNum_(0)
{
}
WindsBladeProjectile::~WindsBladeProjectile()
{

}

void WindsBladeProjectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("WindBlade.png");
	projectileRen_->CreateFrameAnimation_CutTexture("WindBlade", FrameAnimation_Desc("WindBlade.png", 0, 3, 0.1f));
	projectileRen_->ChangeFrameAnimation("WindBlade");
	projectileRen_->GetTransform().SetWorldScale(96.f, 96.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	projectileCol_->GetTransform().SetLocalScale({ 60.f, 60.f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->SetCollisionMode(CollisionMode::Single);
	projectileCol_->Off();
}

void WindsBladeProjectile::TimeOff(float _deltaTime)
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

void WindsBladeProjectile::Update(float _deltaTime)
{
	if (posSet_ == true)
	{
		TimeOff(_deltaTime);
		Shoothing(_deltaTime);
		projectileCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&WindsBladeProjectile::ProjectileToMonster, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void WindsBladeProjectile::End()
{

}

void WindsBladeProjectile::ProjectileSet(float _atk, float _speed, size_t _projectileNum, bool _RLSwitch ,size_t _passNum)
{
	projectileatk_ = _atk;
	projectilespeed_ = _speed;
	posSet_ = true;
	projectileNum_ = _projectileNum;
	RLSwitch_ = _RLSwitch;
	passNum_ = _passNum;
}

void WindsBladeProjectile::Shoothing(float _deltaTime)
{
	if (shoothing_ == false)
	{
		if (projectileRen_->IsUpdate() == false)
		{
			projectileRen_->On();
			projectileCol_->On();
		}
		if (RLSwitch_ == true)
		{
			projectileRen_->GetTransform().PixLocalNegativeX();
		}
		shoothing_ = true;
	}
	if (RLSwitch_ == true)
	{
		GetTransform().SetWorldLeftMove(projectilespeed_, _deltaTime);
	}
	else if (RLSwitch_ == false)
	{
		GetTransform().SetWorldRightMove(projectilespeed_, _deltaTime);
	}

}

CollisionReturn WindsBladeProjectile::ProjectileToMonster(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= projectileatk_; //µ¥¹ÌÁöÁÜ
	projectileRen_->Off();
	projectileCol_->Off();
	Death();
	return CollisionReturn::Continue;
}

void WindsBladeProjectile::LevelEndEvent()
{
	Death();
}