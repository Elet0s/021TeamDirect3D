#include "PreCompile.h"
#include"Mouse.h"
#include "GlobalContentsValue.h"

std::shared_ptr<Mouse> Mouse::mainMouse_ = nullptr;

Mouse::Mouse()
	: mouseRenderer_(nullptr),
	mouseCollision_(nullptr),
	mousePositionInWindow_(float4::Zero),
	mousePositionInWorldSpace_(float4::Zero)
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	mouseCollision_ = CreateComponent<GameEngineCollision>();
	mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision_->GetTransform().SetWorldScale( 100, 100, 100 );
	mouseCollision_->ChangeOrder(ObjectOrder::Mouse);

	mouseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mouseRenderer_->GetTransform().SetWorldScale(64, 64, 100);
	mouseRenderer_->ChangeCamera(CameraOrder::UICamera);
	mouseRenderer_->SetTexture("CursorSprite.png");
}
void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	mouseRenderer_->GetTransform().SetLocalPosition(
		GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x+10.0f,
		GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y,
		-100.0f
	);
	float b = (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x);
	float x_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().x + (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x* 0.3125f);
	float y_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().y + (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y* 0.3125f);

	mouseCollision_->GetTransform().SetLocalPosition(
		x_,
		y_,
		GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z+ 240.f
	);

}
void Mouse::End()
{
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
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