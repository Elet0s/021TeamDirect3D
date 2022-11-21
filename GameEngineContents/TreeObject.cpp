#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "TreeObject.h"

TreeObject::TreeObject() 
	: renderer_(nullptr)
	, col_(nullptr)
{
}

TreeObject::~TreeObject() 
{
}


void TreeObject::Start()
{
	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->SetTexture("tree_A.png");
	renderer_->ScaleToTexture();
	col_ = CreateComponent<GameEngineCollision>();
	col_->GetTransform().SetLocalPosition(float4(0.f, -104.f));
	col_->GetTransform().SetWorldScale(float4(64.f, 64.f, 1.f));
	col_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Green);
	col_->ChangeOrder(ObjectOrder::MapObject);
	col_->DebugOff();
}

void TreeObject::Update(float _deltaTime)
{

}

void TreeObject::End()
{

}

