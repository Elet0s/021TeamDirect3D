#include "PreCompile.h"
#include "GEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCameraActor.h"

bool GEngine::isCollisionDebug_ = false;

GEngine::GEngine()
{
}

GEngine::~GEngine()
{
}

void GEngine::ChangeLevel(const std::string& _levelName)
{
	GameEngineCore::ChangeLevel(_levelName);
}

void GEngine::CollisionDebugOn()
{
	isCollisionDebug_ = true;
}

void GEngine::CollisionDebugOff()
{
	isCollisionDebug_ = false;
}

void GEngine::CollisionDebugSwitch()
{
	isCollisionDebug_ = !isCollisionDebug_;
}

bool GEngine::IsCollisionDebug()
{
	return isCollisionDebug_;
}

GameEngineLevel* GEngine::GetCurrentLevel()
{
	return GameEngineCore::GetCurrentLevel();
}
