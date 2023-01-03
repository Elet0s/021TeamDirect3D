#include"PreCompile.h"
#include"Firering.h"
#include"Player.h"

Firering::Firering()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
{

}
Firering::~Firering()
{

}
void Firering::Init()
{

}
void Firering::Effect()
{

}
void Firering::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Cast_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(315, 315, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Cast_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(315, 315, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Cast_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(100, 100, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Cast_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(100, 100, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Cast_Circle_E.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(100, 100, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);

	Off();

}
void Firering::Update(float _deltaTime)
{
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);
}
void Firering::End()
{

}

void Firering::RotateRenderer(float _deltaTime)
{
	if (addRadian_ < 360)
	{
		addRadian_ += 5* _deltaTime;
	}
	else
	{
		addRadian_ = 0;
	}

	circleRendererA_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererB_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleRendererC_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererD_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleCenterRenderer_->GetTransform().SetWorldRotation(60, 0, addRadian_);
}

CollisionReturn Firering::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // 발사체 부딪히면
{

	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//여기서 데미지 갱신해줘야함
	_Other->GetActor()->Off();
	//off한 몬스터 부활 시켜주는 자료구조에 넣어주는 부분 필요함 자료구조는 계속 업데이트 돌면서 죽은 애들 위치갱신해줌
	return CollisionReturn::Stop;
}