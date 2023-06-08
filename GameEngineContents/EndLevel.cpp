#include"PreCompile.h"
#include"EndLevel.h"
#include "EndActor.h"

EndLevel::EndLevel()
{

}
EndLevel::~EndLevel()
{
	int i = 0;
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
