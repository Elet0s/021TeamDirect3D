#include "Precompile.h"
#include"GameItemObject.h"
#include"GlobalContentsValue.h"
#include"Player.h"

GameItemObject::GameItemObject()
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
	ColCheak();
}
void GameItemObject::End()
{

}

CollisionReturn GameItemObject::ItemToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	
	return CollisionReturn::Stop;
}
CollisionReturn GameItemObject::GainRangeToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{

	return CollisionReturn::Stop;
}

void GameItemObject::ColCheak()
{
	gainRangeCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&GameItemObject::GainRangeToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	itemObjectCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Player, CollisionType::CT_Sphere2D, std::bind(&GameItemObject::GainRangeToPlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
}