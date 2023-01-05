#include "PreCompile.h"
#include "ClearLevel.h"
#include "StageClearMap.h"

ClearLevel::ClearLevel() 
{
}

ClearLevel::~ClearLevel() 
{
}

void ClearLevel::Start()
{
	CreateActor<StageClearMap>();
	
	GetMainCameraActorTransform().SetWorldPosition(float4(360.f, 48.f, -135.f));
	GetMainCamera()->SetProjectionMode(CameraProjectionMode::Perspective);
}
void ClearLevel::Update(float _deltaTime)
{
	
}
void ClearLevel::End()
{

}
void ClearLevel::LevelStartEvent()
{

}