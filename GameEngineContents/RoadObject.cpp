#include "PreCompile.h"
#include "RoadObject.h"
#include "GlobalContentsValue.h"

RoadObject::RoadObject()
	:renderer_(nullptr)
	, col_(nullptr)
{
}

RoadObject::~RoadObject() 
{
}

void RoadObject::Start()
{
	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->SetTexture("Path_alt_travel.png");
	renderer_->ScaleToTexture();
	col_ = CreateComponent<GameEngineCollision>();
	col_->GetTransform().SetWorldScale(float4(0.f, 0.f, 1.f));
	col_->SetDebugSetting(CollisionType::CT_OBB, float4::Green);
	col_->ChangeOrder(ObjectOrder::Road);
	col_->SetCollisionMode(CollisionMode::Multiple);
	//col_->DebugOff();
}

void RoadObject::Update(float _deltaTime)
{
	if (true == col_->IsCollision(CollisionType::CT_AABB, ObjectOrder::Road, CollisionType::CT_AABB))
	{
		Death();
	}
}

void RoadObject::End()
{

}

