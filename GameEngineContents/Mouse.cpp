#include "PreCompile.h"
#include"Mouse.h"
#include "GlobalContentsValue.h"

//std::shared_ptr<Mouse> Mouse::mainMouse_ = nullptr;

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
	//mouseCollision_ = CreateComponent<GameEngineCollision>();
	//mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	//mouseCollision_->GetTransform().SetWorldScale( 10, 10, 10 );
	//mouseCollision_->ChangeOrder(ObjectOrder::Mouse);

	//mouseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//mouseRenderer_->GetTransform().SetWorldScale(64, 64, 100);
	//mouseRenderer_->ChangeCamera(CameraOrder::UICamera);
	//mouseRenderer_->SetTexture("CursorSprite.png");

	this->GetTransform().SetLocalScale(float4::One);
	this->GetTransform().SetWorldScale(float4::One);

	mouseCollision_ = CreateComponent<GameEngineCollision>();
	mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision_->GetTransform().SetWorldScale( 10, 10, 10 );
	mouseCollision_->GetTransform().SetLocalPosition( 20, -28, 0 );
	mouseCollision_->ChangeOrder(ObjectOrder::Mouse);

	mouseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mouseRenderer_->GetTransform().SetWorldScale(40, 56, 1);
	mouseRenderer_->GetTransform().SetLocalPosition( 20, -28, 0 );
	mouseRenderer_->SetTexture("CursorSprite.png");
}

void Mouse::Update(float _DeltaTime)
{
	//GetCurPos();
	//mouseRenderer_->GetTransform().SetLocalPosition(
	//	GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x+10.0f,
	//	GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y,
	//	-100.0f
	//);
	//mouseCollision_->GetTransform().SetLocalPosition(
	//	GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x + 10.0f,
	//	GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y, 
	//	-100.0f
	//);


	///////////////////////////////////////////////////////////////////

	if (CameraProjectionMode::Orthographic == this->GetLevel()->GetMainCamera()->GetProjectionMode())
	{
		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x,
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y,
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().z + 200.f
		);
	}
	else /*if (CameraProjectionMode::Perspective == this->GetLevel()->GetMainCamera()->GetProjectionMode())*/
	{
		//this->GetTransform().SetWorldPosition(
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().x,
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().y,
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().z * 500.f
		//);

		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetMainCamera()->GetMouseWorldPosition()	// 실제로는 뷰공간좌표.
		);
		//(1.0264, 0.5773, 1.0000)
	}



	//float4 temp = this->GetTransform().GetWorldPosition();
}

void Mouse::End()
{
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}

//void Mouse::CreateMouse(GameEngineLevel* _thisLevel)
//{
//	 if (nullptr != mainMouse_)
//	 {
//		 MsgBoxAssert("마우스가 이미 존재합니다.");
//		 return;
//	 }
//	 mainMouse_ = _thisLevel->CreateActor<Mouse>(ObjectOrder::Mouse);
//	 mainMouse_->SetLevelOverOn();
//}