#include"PreCompile.h"
#include"WorldMapLevel.h"
#include"WorldMapActor.h"
#include "MyWorldMapRenderer.h"

WorldMapLevel::WorldMapLevel()
{

}
WorldMapLevel::~WorldMapLevel()
{

}
void WorldMapLevel::Start()
{

	std::shared_ptr<WorldMapActor> WorldMap = CreateActor<WorldMapActor>();

	WorldMap->worldmaprenderer_->CreateTileMap(50, 20, {128,128}, "grassTexture.png");
	
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