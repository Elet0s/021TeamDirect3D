#include "PreCompile.h"
#include "ClearLevel.h"
#include "SoulCardSelectBox.h"
#include "ClearUIBox.h"
#include "StageClearMap.h"

ClearLevel::ClearLevel() 
	:clearbox_(nullptr),
	SoulSelectbox_(nullptr),
	issoulselect_(false)
{	
}

ClearLevel::~ClearLevel() 
{
}

void ClearLevel::Start()
{
	CreateActor<StageClearMap>();
	clearbox_ = CreateActor<ClearUIBox>();
	GetMainCameraActorTransform().SetWorldPosition(float4(192.f, 48.f, -135.f));
	GetMainCamera()->SetProjectionMode(CameraProjectionMode::Perspective);

	if (false == GameEngineInput::GetInst()->IsKey("click"))
	{
		GameEngineInput::GetInst()->CreateKey("Click", VK_LBUTTON);
	}
}
void ClearLevel::Update(float _deltaTime)
{
	if (true == issoulselect_ && SoulSelectbox_ == nullptr)
	{
		SoulSelectbox_ = CreateActor<SoulCardSelectBox>();
	}
	else if (issoulselect_ == false && false == clearbox_->IsUpdate())
	{
		SoulSelectbox_ = nullptr;
		clearbox_->On();
	}
	int a = 0;
}
void ClearLevel::End()
{

}
void ClearLevel::LevelStartEvent()
{

}