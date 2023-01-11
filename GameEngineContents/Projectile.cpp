#include"PreCompile.h"
#include"Projectile.h"
#include "GlobalContentsValue.h"
#include "Player.h"

Projectile::Projectile()
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
	posSet_(false)
{

}
Projectile::~Projectile()
{

}

void Projectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Particle.png");
	projectileRen_->GetPixelData().mulColor_ = float4::Red; //³ì»ö
	projectileRen_->GetTransform().SetWorldScale(50.f, 50.f, 1.f);
	projectileRen_->ChangeCamera(CameraOrder::MidCamera);
	projectileRen_->SetRenderingOrder(15);
	projectileRen_->Off();

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	projectileCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
	projectileCol_->Off();
}

void Projectile::TimeOff(float _deltaTime)
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

void Projectile::Update(float _deltaTime)
{
	if (posSet_ ==true)
	{
		Shoothing(_deltaTime);
		TimeOff(_deltaTime);
	}
}

void Projectile::End()
{

}

void Projectile::Shoothing(float _deltaTime)
{
	if(shoothing_ == false)
	{
		projectileRen_->On();
		projectileCol_->On();
		shoothing_ = true;
		mpx_ = GetTransform().GetWorldPosition().x;
		mpy_ = GetTransform().GetWorldPosition().y;
		px_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
		py_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
		range_.x = px_ - mpx_;
		range_.y = py_ - mpy_;

		resultVector_ = range_.Normalize3D() * 1000.f;
	}
	GetTransform().SetWorldMove(resultVector_ * _deltaTime);
}