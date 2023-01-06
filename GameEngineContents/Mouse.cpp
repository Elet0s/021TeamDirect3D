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


	float y_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().y + (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y * sinf(60.f * GameEngineMath::DegreeToRadian));
	float z_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z + 240.f+ (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y * cosf(30.f * GameEngineMath::DegreeToRadian));//+(y_* cosf(30.f * GameEngineMath::DegreeToRadian));
	float b = y_ / z_;


	float x_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().x + (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x)+ (GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y);
	
	mouseCollision_->GetTransform().SetLocalPosition(
		x_,
		y_,
		z_
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