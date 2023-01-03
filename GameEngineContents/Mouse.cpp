#include "PreCompile.h"
#include"Mouse.h"
#include "GlobalContentsValue.h"

std::shared_ptr<Mouse> Mouse::mainMouse_ = nullptr;

Mouse::Mouse()
	:mouseRenderer(0)
	, mouseCollision_(0)
	, mousePositionToWindow_(0)
	,mousePositionToClient_(0)
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	{
		mouseCollision_ = CreateComponent<GameEngineCollision>();
		mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
		mouseCollision_->GetTransform().SetLocalScale({ 64.0f, 64.0f, 1.0f });
		mouseCollision_->ChangeOrder(ObjectOrder::Mouse);
	}

	mouseRenderer = CreateComponent<GameEngineTextureRenderer>();
	mouseRenderer->GetTransform().SetLocalScale(64, 64, 100);
	mouseRenderer->ChangeCamera(CameraOrder::UICamera);
	mouseRenderer->SetTexture("CursorSprite.png");
}
void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	//GetTransform().SetWorldPosition(GetLevel()->GetMainCamera()->GetMouseScreenPosition().x, GetLevel()->GetMainCamera()->GetMouseScreenPosition().y, GetLevel()->GetMainCamera()->GetMouseScreenPosition().z + 100);
	mouseRenderer->GetTransform().SetLocalPosition(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x+10.0f, GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y,-100.0f);
	mouseCollision_->GetTransform().SetLocalPosition(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x + 10.0f, GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y, -100.0f);

}
void Mouse::End()
{

}

 void Mouse::CreateMouse(GameEngineLevel* _thisLevel)
{
	 if (nullptr != mainMouse_)
	 {
		 MsgBoxAssert("마우스가 이미 존재합니다.");
		 return;
	 }
	 mainMouse_ = _thisLevel->CreateActor<Mouse>(ObjectOrder::Mouse);
	 mainMouse_->SetLevelOverOn();
}