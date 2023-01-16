#include "PreCompile.h"
#include "ClearLevel.h"
#include "SoulCardSelectBox.h"
#include "ClearUIBox.h"
#include "StageUI.h"
#include "Player.h"
#include "StageClearMap.h"
#include "Mouse.h"

ClearLevel::ClearLevel() 
	:clearbox_(nullptr)
	, stageui_(nullptr)
{	
}

ClearLevel::~ClearLevel() 
{
}

void ClearLevel::Start()
{
	CreateActor<StageClearMap>();
	stageui_ = CreateActor<StageUI>();
	GetMainCameraActorTransform().SetWorldPosition(float4(192.f, 48.f, -135.f));
	GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);
	
	mousePointer_ = CreateActor<Mouse>(0, "ClearLevelMousePointer");

}
void ClearLevel::Update(float _deltaTime)
{
	
}
void ClearLevel::End()
{

}
void ClearLevel::LevelStartEvent()
{
	if (clearbox_ == nullptr)
	{
		clearbox_ = CreateActor<ClearUIBox>();
	}
	//if (Player::GetPlayerInst() != nullptr)
	//{
		Player::GetPlayerInst().Off();
	//}
	stageui_->SetUI(UIType::Claer);
}

void ClearLevel::LevelEndEvent()
{
	clearbox_->Death();
	clearbox_ = nullptr;
}