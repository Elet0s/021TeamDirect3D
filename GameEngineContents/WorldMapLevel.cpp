#include"PreCompile.h"
#include"WorldMapLevel.h"
#include"WorldMapActor.h"
#include"Mouse.h"
#include "StageCreater.h"
#include"WorldMapRenderingActor.h"

WorldMapLevel::WorldMapLevel()
{

}
WorldMapLevel::~WorldMapLevel()
{

}
void WorldMapLevel::Start()
{
	WorldMapRenderingActor_ = CreateActor<WorldMapRenderingActor>();
	CreateActor<StageCreater>();
	WorldMapRenderingActor_->Initialize(
		1000,
		300
	);

	WorldMapRenderingActor_->GetTransform().SetLocalScale(float4::White);
	WorldMapRenderingActor_->GetTransform().SetWorldScale(float4::White);
	WorldMapRenderingActor_->GetTransform().SetWorldPosition(float4::Zero);

	WorldLevelLighting_ = CreateActor<GameEngineLighting>(0, "TestLevelLighting");
	//테스트레벨에 조명 추가.

	WorldLevelLighting_->GetTransform().SetWorldRotation(100.f, 0.f, 0.f);
	//조명 각도 설정.

	WorldLevelLighting_->GetLightingData().mainLightColor_ = float4(0.7f, 0.7f, 0.7f);
	//정반사광, 난반사광 색, 밝기 설정.

	WorldLevelLighting_->GetLightingData().ambientLightColor_ = float4(0.1f, 0.1f, 0.1f);
	//환경광 색, 밝기 설정.

	WorldLevelLighting_->GetLightingData().specularLightRatio_ = 0.f;
	//정반사광 사용 안함.

	WorldLevelLighting_->GetLightingData().diffuseLightRatio_ = 2.f;
	//난반사광을 두배로 적용.

	this->GetMainCamera()->PushLighting(WorldLevelLighting_);
	//카메라에 조명 등록.
	
	GetMainCameraActorTransform().SetWorldPosition(float4(896.f, -1145.f, -2226.f));
	GetMainCamera()->SetProjectionMode(CameraProjectionMode::Perspective);


	if (false == GameEngineInput::GetInst()->IsKey("WorldCameraLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("WorldCameraLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("WorldCameraRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("WorldCameraFoward", VK_UP);
		GameEngineInput::GetInst()->CreateKey("WorldCameraBack", VK_DOWN);

	}
}
void WorldMapLevel::Update(float _deltaTime)
{
	float cameraSpeed = 500.f;

	float4 Pos = GetMainCameraActorTransform().GetWorldPosition();

	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraLeft"))
	{
		Pos += GetMainCameraActorTransform().GetLeftVector() * cameraSpeed * _deltaTime;

		if (Pos.x <= 200.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetLeftVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraRight"))
	{
		Pos += GetMainCameraActorTransform().GetRightVector() * cameraSpeed * _deltaTime;

		if (Pos.x >= 1500.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetRightVector() * cameraSpeed * _deltaTime);
	}


	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraFoward"))
	{

		Pos += float4(0.f, sinf(30.f * GameEngineMath::DegreeToRadian), cosf(30.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime;

		if (Pos.z >= -810.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
		float4(0.f, sinf(30.f * GameEngineMath::DegreeToRadian), cosf(30.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraBack"))
	{
		Pos += float4(0.f, -sinf(30.f * GameEngineMath::DegreeToRadian), -cosf(30.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime;

		if (Pos.z <= -2226.f)
		{
			return;
		}


		GetMainCameraActorTransform().SetLocalMove(
			float4(0.f, -sinf(30.f * GameEngineMath::DegreeToRadian), -cosf(30.f * GameEngineMath::DegreeToRadian)) * cameraSpeed * _deltaTime);
	}

}
void WorldMapLevel::End()
{

}
void WorldMapLevel::LevelStartEvent()
{
	this->GetMainCamera()->SetFarZ(10000.f);
}