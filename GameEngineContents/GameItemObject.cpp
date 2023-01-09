#include "Precompile.h"
#include"GameItemObject.h"
#include"GlobalContentsValue.h"
#include"Player.h"

GameItemObject::GameItemObject()
	:itemObjectOrder_(ItemObjectOrder::None),
	chasePlayer_(false)
{
	
}

GameItemObject::~GameItemObject()
{

}

void GameItemObject::Start()
{

}

void GameItemObject::Update(float _deltaTime)
{
}

void GameItemObject::End()
{

}


void GameItemObject::ChasePlayer(float _deltaTime)
{
	if (chasePlayer_ == true)
	{

	}
}

ItemObjectOrder GameItemObject::GetObjectOrder()
{
	return itemObjectOrder_;
}