#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "ClearLevel.h"
#include "SoulCardSelectBox.h"
#include "ClearUIBox.h"

ClearUIBox::ClearUIBox() 
	:mainrenderer_(nullptr)
	, button1renderer_(nullptr)
	, button2renderer_(nullptr)
	, button3renderer_(nullptr)
	, button1FontRenderer_(nullptr)
	, button2FontRenderer_(nullptr)
	, button3FontRenderer_(nullptr)
	, button1Col_(nullptr)
	, button2Col_(nullptr)
	, button3Col_(nullptr)
	, button1On_(true)
	, button2On_(true)
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

	{
		button1FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button1FontRenderer_->SetTextPosition(float4(90.f, 125.f, -1000.f));
		button1FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button1FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		button1FontRenderer_->SetSize(28.f);
		button1FontRenderer_->SetText("300 ���");

		button2FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button2FontRenderer_->SetTextPosition(float4(90.f, 185.f, -2000.f));
		button2FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button2FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Left);
		button2FontRenderer_->SetSize(28.f);
		button2FontRenderer_->SetText("ī�� ����");

		button3FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
		button3FontRenderer_->SetTextPosition(float4(1080.f, 630.f, -2000.f));
		button3FontRenderer_->ChangeCamera(CameraOrder::UICamera);
		button3FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::Center);
		button3FontRenderer_->SetSize(30.f);
		button3FontRenderer_->SetText("���� ��������");
	}

	{
		button3renderer_ = CreateComponent<GameEngineTextureRenderer>();
		button3renderer_->SetTexture("Button_Default_State_Stage.png");
		button3renderer_->ScaleToTexture();
		button3renderer_->GetTransform().SetWorldPosition(430.f, -291.f, -10.f);
		button3renderer_->ChangeCamera(CameraOrder::UICamera);


		button3Col_ = CreateComponent<GameEngineCollision>();
		button3Col_->ChangeOrder(ObjectOrder::MapObject);
		button3Col_->GetTransform().SetWorldScale(float4(400.f, 80.f, 1.f));
		button3Col_->GetTransform().SetWorldPosition(430.f, -291.f, -10.f);
		button3Col_->SetDebugSetting(CollisionType::CT_OBB2D, float4::White);
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
			button1FontRenderer_->Off();
			button1On_ = false;
			if (button2renderer_->IsUpdate())
			{
				button2FontRenderer_->SetTextPosition(float4(90.f, 125.f, -1000.f));
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
			RendererOff();
			button2On_ = false;
			soulCardSelectBox_ = GetLevel()->CreateActor<SoulCardSelectBox>();
		}
	}
	else
	{
		button2renderer_->SetTexture("Button_Default_State.png");
	}

	if (button3Col_->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::Mouse, CollisionType::CT_AABB2D))
	{
		button3renderer_->SetTexture("Button_Selected_Stage.png");
		if (GameEngineInput::GetInst()->IsUp("Click"))
		{
			GEngine::ChangeLevel("WorldMap");
		}
	}
	else
	{
		button3renderer_->SetTexture("Button_Default_State_Stage.png");
	}

	if (soulCardSelectBox_ != nullptr && soulCardSelectBox_->IsDead())
	{
		soulCardSelectBox_ = nullptr;
		RendererOn();
	}

}


void ClearUIBox::RendererOn()
{
	mainrenderer_->On();
	button3FontRenderer_->On();
	button3renderer_->On();
	button3Col_->On();
	if (button1On_ == true)
	{
		button1FontRenderer_->On();
		button1renderer_->On();
		button1Col_->On();
	}

	if (button2On_ == true)
	{
		button2FontRenderer_->On();
		button2renderer_->On();
		button2Col_->On();
	}
}

void ClearUIBox::RendererOff()
{
	mainrenderer_->Off();
	button1FontRenderer_->Off();
	button1renderer_->Off();
	button1Col_->Off();
	
	button2FontRenderer_->Off();
	button2renderer_->Off();
	button2Col_->Off();

	button3FontRenderer_->Off();
	button3renderer_->Off();
	button3Col_->Off();
	
}