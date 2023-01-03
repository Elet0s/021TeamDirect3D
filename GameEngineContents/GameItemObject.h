#pragma once
#include "GlobalContentsValue.h"
//exp, hpmeet, voidbead
class GameItemObject : public GameEngineActor
{
public:
	GameItemObject();
	~GameItemObject();


	GameItemObject(const GameItemObject& _Other) = delete;
	GameItemObject(GameItemObject&& _Other) noexcept = delete;
	GameItemObject& operator=(const GameItemObject& _Other) = delete;
	GameItemObject& operator=(GameItemObject&& _Other) noexcept = delete;

public:
	ItemObjectOrder itemObjectOrder_;
	std::shared_ptr<GameEngineTextureRenderer> itemObjectRenderer_;
	std::shared_ptr<GameEngineCollision>itemObjectCol_;//닿으면 효과발생
	std::shared_ptr<GameEngineCollision> gainRangeCol_;//획득 범위 플레이어 들어오면 쫒아감
protected:
	CollisionReturn ItemToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GainRangeToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void ColCheak();

	static void CreateItem(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder)
	{
		if (_itemObjectOrder == ItemObjectOrder::Exp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 100);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		}
		else if (_itemObjectOrder == ItemObjectOrder::Gold)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 100);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
		}
		else if (_itemObjectOrder == ItemObjectOrder::Meet)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 100);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		}
		else if (_itemObjectOrder == ItemObjectOrder::Voidbead)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 100);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		}
	}



private:

};