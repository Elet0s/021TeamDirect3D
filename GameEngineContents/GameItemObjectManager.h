#pragma once
#include "GlobalContentsValue.h"
#include"GameItemObject.h"

class GameEngineRandom;
class GameItemObjectManager
{
public:
	GameItemObjectManager();
	~GameItemObjectManager();


	GameItemObjectManager(const GameItemObjectManager& _Other) = delete;
	GameItemObjectManager(GameItemObjectManager&& _Other) noexcept = delete;
	GameItemObjectManager& operator=(const GameItemObjectManager& _Other) = delete;
	GameItemObjectManager& operator=(GameItemObjectManager&& _Other) noexcept = delete;
public:
	void CreateItemObject(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder, float4 _itemObjectPos);
	void CreateItemObject(GameEngineLevel* _thisLevel, float4 _itemObjectPos);
	void SetManager();
protected:
	ItemObjectOrder RandomObjectOrder();
private:
	std::vector< std::shared_ptr<GameItemObject>> allObjectContainer_;
};