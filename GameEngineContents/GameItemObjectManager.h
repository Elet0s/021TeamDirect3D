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
	void CreateItemObject(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder, float4 _itemObjectPos);//아이템 종류 직접설정한것으로 생성
	void CreateItemObject(GameEngineLevel* _thisLevel, float4 _itemObjectPos); // 아이템 종류 랜덤으로 생성
	void SetManager();

protected:
	ItemObjectOrder RandomObjectOrder();
private:
	std::vector< std::shared_ptr<GameItemObject>> allObjectContainer_;
	size_t ItemUpdateNum_; // 현재 활성화 되어있는 아이템 총 갯수
	bool isFullContainer_; 
};