#include "PreCompile.h"
#include "MetaLevel.h"
#include "MetaSpriteWindow.h"

MetaLevel::MetaLevel(): metaAnimationGUI_(nullptr)
{
}

MetaLevel::~MetaLevel()
{
}

void MetaLevel::Start()
{
	metaAnimationGUI_ = GameEngineGUI::CreateGUIWindow<MetaSpriteWindow>("Meta Sprite Window", this);
	metaAnimationGUI_->metaDir_.MoveParentToExistChildDirectory("ContentsResources");
	metaAnimationGUI_->metaDir_.MoveToChild("ContentsResources");
	metaAnimationGUI_->metaDir_.MoveToChild("Texture");
	metaAnimationGUI_->metaDir_.MoveToChild("Meta");
	metaAnimationGUI_->Off();
}

void MetaLevel::Update(float _deltaTime)
{
}

void MetaLevel::End()
{
}

void MetaLevel::LevelStartEvent()
{
	metaAnimationGUI_->On();
}

void MetaLevel::LevelEndEvent()
{
	metaAnimationGUI_->Off();
}
