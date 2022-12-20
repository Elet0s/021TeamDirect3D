#include"PreCompile.h"
#include"WorldMapLevel.h"
#include"WorldMapActor.h"
#include"WorldMapRanderingActor.h"

WorldMapLevel::WorldMapLevel()
{

}
WorldMapLevel::~WorldMapLevel()
{

}
void WorldMapLevel::Start()
{

	worldMapRanderingActor_ = CreateActor<WorldMapRanderingActor>();
	worldMapRanderingActor_->Initialize(
		1000,
		50
	);
	//fieldRenderingActor_->Initialize(
	//	750,
	//	700,
	//	float4(6000, 6000)
	//);
	worldMapRanderingActor_->GetTransform().SetLocalScale(float4::White);
	worldMapRanderingActor_->GetTransform().SetWorldScale(float4::White);
	worldMapRanderingActor_->GetTransform().SetWorldPosition(float4::Zero);
	
	GetMainCameraActorTransform().SetWorldPosition(float4(640.f, -2560.f * sinf(10.f * GameEngineMath::DegreeToRadian) + 70.f, -2560.f * cosf(10.f * GameEngineMath::DegreeToRadian)));
	GetMainCamera()->SetProjectionMode(CameraProjectionMode::Perspective);
}
void WorldMapLevel::Update(float _deltaTime)
{
	float cameraSpeed = 500.f;

	float4 Pos = GetMainCameraActorTransform().GetWorldPosition();

	if (true == GameEngineInput::GetInst()->IsPressed("CamBoost"))
	{
		cameraSpeed *= 3.f;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("CamLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetLeftVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetRightVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsDown("CamUp"))
	{
		if (GetMainCameraActorTransform().GetWorldRotation().IX() != 45)
		{
			GetMainCameraActorTransform().SetWorldRotation(float4(45.f, 0.f, 0.f));
			GetMainCameraActorTransform().SetWorldPosition(GetMainCameraActorTransform().GetWorldPosition().x, GetMainCameraActorTransform().GetWorldPosition().y + 300.f, GetMainCameraActorTransform().GetWorldPosition().z);
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("CamDown"))
	{
		if (GetMainCameraActorTransform().GetWorldRotation().IX() != 0)
		{
			GetMainCameraActorTransform().SetWorldRotation(float4(0.f, 0.f, 0.f));
			GetMainCameraActorTransform().SetWorldPosition(GetMainCameraActorTransform().GetWorldPosition().x, GetMainCameraActorTransform().GetWorldPosition().y - 300.f, GetMainCameraActorTransform().GetWorldPosition().z);
		}
	}

	if (true == GameEngineInput::GetInst()->IsPressed("CamForward"))
	{
		GetMainCameraActorTransform().SetLocalMove(
		float4(0.f, sinf(10.f * GameEngineMath::DegreeToRadian), cosf(10.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamBack"))
	{
		GetMainCameraActorTransform().SetLocalMove(
			float4(0.f, -sinf(10.f * GameEngineMath::DegreeToRadian), -cosf(10.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime);
	}

}
void WorldMapLevel::End()
{

}
void WorldMapLevel::LevelStartEvent()
{

}