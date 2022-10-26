#include "PreCompile.h"
#include "GameEngineFBXAnimation.h"
#include "GameEngineDevice.h"

GameEngineFBXAnimation::GameEngineFBXAnimation()
{
}

GameEngineFBXAnimation::~GameEngineFBXAnimation()
{
}

GameEngineFBXAnimation* GameEngineFBXAnimation::Create(
    const std::string& _name
 )
{
    GameEngineFBXAnimation* newRes = CreateNamedRes(_name);

    return newRes;
}

void GameEngineFBXAnimation::Setting()
{
    if (true)
    {

    }

    //GameEngineDevice::GetDC()->

}