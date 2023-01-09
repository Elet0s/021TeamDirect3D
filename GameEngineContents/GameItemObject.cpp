#include "Precompile.h"
#include"GameItemObject.h"
#include"GlobalContentsValue.h"
#include"Player.h"

GameItemObject::GameItemObject()
	:itemObjectOrder_(ItemObjectOrder::None),
	chasePlayer_(false),
	ox_(0),
	oy_(0),
	px_(0),
	py_(0)
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
	ChasePlayer(_deltaTime);
}

void GameItemObject::End()
{

}

 
void GameItemObject::ChasePlayer(float _deltaTime)
{ 
	if (chasePlayer_ == true)
	{
		ox_ = GetTransform().GetWorldPosition().x;
		oy_ = GetTransform().GetWorldPosition().y;
		px_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x; 
		py_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
		range_.x = px_ - ox_;
		range_.y = py_ - oy_;

		resultVector_ = range_.Normalize3D() * 500.f;
		GetTransform().SetWorldMove(resultVector_ * _deltaTime);
	}
}

ItemObjectOrder GameItemObject::GetObjectOrder()
{
	return itemObjectOrder_;
}