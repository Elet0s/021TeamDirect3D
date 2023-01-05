#pragma once
#include "GlobalContentsValue.h"
//exp, hpmeet, voidbead
class GameItemObjectManager;
class GameItemObject : public GameEngineActor
{
	friend   GameItemObjectManager;
public:
	GameItemObject();
	~GameItemObject();


	GameItemObject(const GameItemObject& _Other) = delete;
	GameItemObject(GameItemObject&& _Other) noexcept = delete;
	GameItemObject& operator=(const GameItemObject& _Other) = delete;
	GameItemObject& operator=(GameItemObject&& _Other) noexcept = delete;

public:

protected:
	CollisionReturn ItemToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void ColCheak();

private:
	ItemObjectOrder itemObjectOrder_;
	std::shared_ptr<GameEngineTextureRenderer> itemObjectRenderer_;
	std::shared_ptr<GameEngineCollision>itemObjectCol_;//닿으면 효과발생
	bool chasePlayer_;


};