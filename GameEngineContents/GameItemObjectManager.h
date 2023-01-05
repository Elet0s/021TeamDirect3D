#pragma once
#include "GlobalContentsValue.h"
#include"GameItemObject.h"

class GameItemObjectManager :GameEngineUpdateObject
{
public:
	GameItemObjectManager();
	~GameItemObjectManager();


	GameItemObjectManager(const GameItemObjectManager& _Other) = delete;
	GameItemObjectManager(GameItemObjectManager&& _Other) noexcept = delete;
	GameItemObjectManager& operator=(const GameItemObjectManager& _Other) = delete;
	GameItemObjectManager& operator=(GameItemObjectManager&& _Other) noexcept = delete;
protected:

	void Start() override;

	void CreateItemObject(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder, float4 _itemObjectPos)
	{
		if (_itemObjectOrder == ItemObjectOrder::GreenExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ == float4(0.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			expContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::YellowExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ == float4(1.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			expContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::RedExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ == float4(1.0f, 0.0f, 0.0f, 1.0f);
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			expContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Gold)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			goldContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Meet)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			meetContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Voidbead)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetLocalScale(64, 64, 0);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::UICamera);
			newItemObject->itemObjectRenderer_->SetTexture("Void.png");
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 30,30 });
			voidbeadContainer_.push_back(newItemObject);
		}
	}
private:
	std::vector< std::shared_ptr<GameItemObject>> expContainer_;
	std::vector< std::shared_ptr<GameItemObject>> meetContainer_;
	std::vector< std::shared_ptr<GameItemObject>> voidbeadContainer_;
	std::vector< std::shared_ptr<GameItemObject>> goldContainer_;
};