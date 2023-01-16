#include "PreCompile.h"
#include "ShopLevel.h"
#include "SoulCardSelectBox.h"
#include "ShopUIBox.h"
#include "StageUI.h"
#include "Player.h"
#include "StageClearMap.h"
#include "Mouse.h"

ShopLevel::ShopLevel() 
{
}

ShopLevel::~ShopLevel() 
{
}

void ShopLevel::Start()
{
	CreateActor<StageClearMap>();
	stageui_ = CreateActor<StageUI>();
	if (shopUIBox_ == nullptr)
	{
		shopUIBox_ = CreateActor<ShopUIBox>();
	}
	GetMainCameraActorTransform().SetWorldPosition(float4(192.f, 48.f, -135.f));
	GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);

	mousePointer_ = CreateActor<Mouse>(0, "ClearLevelMousePointer");

}
void ShopLevel::Update(float _deltaTime)
{

}
void ShopLevel::End()
{

}
void ShopLevel::LevelStartEvent()
{
	
	//if (Player::GetPlayerInst() != nullptr)
	//{
		Player::GetPlayerInst().Off();
	//}
	stageui_->SetUI(UIType::Shop);
}

void ShopLevel::LevelEndEvent()
{

}