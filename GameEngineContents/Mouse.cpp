#include "PreCompile.h"
#include"Mouse.h"
#include "GlobalContentsValue.h"

Mouse::Mouse()
	: mouseDefaultRenderer_(nullptr),
	mouseCrossHairRenderer_(nullptr),
	mouseAimLineRenderer_(nullptr),
	mouseCollision_(nullptr),
	mousePositionInWindow_(float4::Zero),
	mousePositionInWorldSpace_(float4::Zero),
	playerWorldPosition_(float4::Zero),
	isAimLine_(true)
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

	mouseDefaultRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mouseDefaultRenderer_->GetTransform().SetWorldScale(40, 56, 1);
	mouseDefaultRenderer_->GetTransform().SetLocalPosition( 20, -28, 0 );
	mouseDefaultRenderer_->SetTexture("CursorSprite.png");
	mouseDefaultRenderer_->Off();

	mouseCrossHairRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mouseCrossHairRenderer_->GetTransform().SetWorldScale(32, 32, 1);
	mouseCrossHairRenderer_->SetTexture("CrossHair.png");
	mouseCrossHairRenderer_->Off();


	mouseAimLineRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	mouseAimLineRenderer_->GetTransform().SetWorldScale(256, 256, 1);
	mouseAimLineRenderer_->SetTexture("AimLine.png");
	//mouseAimLineRenderer_->Off();


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
		//전투맵에서의 동작.

		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x,
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y,
			this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().z 
		);



		if (true == isAimLine_)
		{
			mouseAimLineRenderer_->GetTransform().SetWorldPosition(this->GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition());


			float4 thisPosition = this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();

			float temp = float4::VectorXYToDegree(float4::Green, thisPosition);

			this->GetTransform().SetWorldRotation(
				temp
			);


			
		}
	}
	else /*if (CameraProjectionMode::Perspective == this->GetLevel()->GetMainCamera()->GetProjectionMode())*/
	{
		//월드맵에서의 동작. 미완성.
		//this->GetTransform().SetWorldPosition(
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().x,
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().y,
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition().z * 500.f
		//);

		//this->GetTransform().SetWorldPosition(
		//	this->GetLevel()->GetMainCamera()->GetMouseWorldPosition()	// 실제로는 뷰공간좌표.
		//);
		////(1.0264, 0.5773, 1.0000)

		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetUICamera()->GetMouseWorldPosition().x,	// 실제로는 뷰공간좌표.
			this->GetLevel()->GetUICamera()->GetMouseWorldPosition().y,	// 실제로는 뷰공간좌표.
			this->GetLevel()->GetUICamera()->GetMouseWorldPosition().z + 100000.f	// 실제로는 뷰공간좌표.
		);


	}
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