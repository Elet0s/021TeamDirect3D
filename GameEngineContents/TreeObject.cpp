#include "PreCompile.h"
#include "Player.h"
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

	checkCol_ = CreateComponent<GameEngineCollision>();
	checkCol_->GetTransform().SetWorldScale(renderer_->GetTransform().GetWorldScale());
	checkCol_->SetDebugSetting(CollisionType::CT_AABB2D, float4::Red);
	checkCol_->ChangeOrder(ObjectOrder::TreeObject);
	//checkCol_->DebugOff();
}

void TreeObject::Update(float _deltaTime)
{


	if (true == checkCol_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Player, CollisionType::CT_OBB2D))
	{
		if (GetTransform().GetWorldPosition().IY() - 50 > Player::GetPlayerInst().GetTransform().GetWorldPosition().IY())
		{
			renderer_->SetRenderingOrder(static_cast<int>(ObjectOrder::TreeObject));
		}
		else
		{
			renderer_->SetRenderingOrder(-1);
		}
	}



	if (true == checkCol_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Camera, CollisionType::CT_OBB2D))
	{
		renderer_->On();
	}
	else
	{
		renderer_->Off();
	}
}

void TreeObject::End()
{

}

