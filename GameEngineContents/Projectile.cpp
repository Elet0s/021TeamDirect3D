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
	posSet_(false),
	projectileatk_(0.f)
{

}
Projectile::~Projectile()
{

}

void Projectile::Start()
{
	projectileRen_ = CreateComponent<GameEngineTextureRenderer>();
	projectileRen_->SetTexture("Particle.png");
	projectileRen_->GetPixelData().mulColor_ = float4::Red; //���
	projectileRen_->GetTransform().SetWorldScale(50.f, 50.f, 1.f);
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
		projectileCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&Projectile::ProjectileToPlayer, this, std::placeholders::_1, std::placeholders::_2));

	}
}

void Projectile::End()
{

}

void Projectile::ProjectileSet(float _atk)
{
	projectileatk_ = _atk;
	posSet_ = true;
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

		resultVector_ = range_.Normalize3D() * 1000.f * _deltaTime;
	}
	GetTransform().SetWorldMove(resultVector_);
}

CollisionReturn Projectile::ProjectileToPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	Player::GetPlayerInst()->GetPlayerInfo().hp_ -= projectileatk_;
	projectileRen_->Off();
	projectileCol_->Off();
	Death();
	return CollisionReturn::Continue;
}