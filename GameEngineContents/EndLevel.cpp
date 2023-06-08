#include"PreCompile.h"
#include"EndLevel.h"
#include "EndActor.h"

EndLevel::EndLevel()
{

}
EndLevel::~EndLevel()
{

}

void EndLevel::Start()
{
	CreateActor<EndActor>();
}
void EndLevel::Update(float _deltaTime)
{

}
void EndLevel::End()
{

}
