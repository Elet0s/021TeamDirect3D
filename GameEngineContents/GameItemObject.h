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
	bool chasePlayer_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void ChasePlayer(float _deltaTime);

private:
	ItemObjectOrder itemObjectOrder_;
	ObjectOrder objectOrder_;
	std::shared_ptr<GameEngineTextureRenderer> itemObjectRenderer_;
	std::shared_ptr<GameEngineCollision>itemObjectCol_;//닿으면 효과발생

};