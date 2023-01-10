#include"PreCompile.h"
#include"Projectile.h"
#include "GlobalContentsValue.h"

Projectile::Projectile()
	:projectileRen_(),
	projectileCol_()
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

	projectileCol_ = CreateComponent<GameEngineCollision>();
	projectileCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
	projectileCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	projectileCol_->ChangeOrder(ObjectOrder::Projectile);
}
void Projectile::Update(float _deltaTime)
{

}
void Projectile::End()
{

}