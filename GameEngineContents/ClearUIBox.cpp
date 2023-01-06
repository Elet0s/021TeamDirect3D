#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "ClearLevel.h"
#include "SoulCardSelectBox.h"
#include "ClearUIBox.h"

ClearUIBox::ClearUIBox() 
	:mainrenderer_(nullptr)
{
}

ClearUIBox::~ClearUIBox() 
{
}

void ClearUIBox::Start()
{
	mainrenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mainrenderer_->SetTexture("ClearUIBox.png");
	mainrenderer_->ScaleToTexture();
	mainrenderer_->ChangeCamera(CameraOrder::UICamera);
	mainrenderer_->GetTransform().SetWorldPosition(-350, 0, 0);

	mainrenderer_->GetPixelData().mulColor_.a = 0.85f;


	{
		button1renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button1renderer_->SetTexture("Button_Default_State.png");
		button1renderer_->GetTransform().SetWorldPosition(-350, 220.f, -10.f);
		button1renderer_->ScaleToTexture();
		button1renderer_->ChangeCamera(CameraOrder::UICamera);


		button1Col_ = CreateComponent<GameEngineCollision>();
		button1Col_->ChangeOrder(ObjectOrder::MapObject);
		button1Col_->GetTransform().SetWorldScale(float4(480.f, 50.f, 1.f));
		button1Col_->GetTransform().SetWorldPosition(-350, 220.f, -10.f);
		button1Col_->SetDebugSetting(CollisionType::CT_OBB2D, float4::White);
	}
	


	{
		button2renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button2renderer_->SetTexture("Button_Default_State.png");
		button2renderer_->GetTransform().SetWorldPosition(-350, 160.f, -10.f);
		button2renderer_->ScaleToTexture();
		button2renderer_->ChangeCamera(CameraOrder::UICamera);


		button2Col_ = CreateComponent<GameEngineCollision>();
		button2Col_->ChangeOrder(ObjectOrder::MapObject);
		button2Col_->GetTransform().SetWorldScale(float4(480.f, 50.f, 1.f));
		button2Col_->GetTransform().SetWorldPosition(-350, 160.f, -10.f);
		button2Col_->SetDebugSetting(CollisionType::CT_OBB2D, float4::White);
	}
}

void ClearUIBox::Update(float _deltaTime)
{
	if (button1Col_->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::Mouse, CollisionType::CT_AABB2D))
	{
		button1renderer_->SetTexture("Button_Selected.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			button1renderer_->Off();
			button1Col_->Off();
			if (button2renderer_->IsUpdate())
			{
				button2renderer_->GetTransform().SetWorldMove(float4(0, 60, 0));
				button2Col_->GetTransform().SetWorldMove(float4(0, 60, 0));
				
			}
			return;
		}
	}
	else
	{
		button1renderer_->SetTexture("Button_Default_State.png");
	}


	if (button2Col_->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::Mouse, CollisionType::CT_AABB2D))
	{
		button2renderer_->SetTexture("Button_Selected.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			Off();
			GetLevel<ClearLevel>()->isSoulselectOn();
		}
	}
	else
	{
		button2renderer_->SetTexture("Button_Default_State.png");
	}
}