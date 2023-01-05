#include"PreCompile.h"
#include"GameItemObjectManager.h"
#include"GameEngineBase/GameEngineRandom.h"

GameItemObjectManager::GameItemObjectManager()
{
}
GameItemObjectManager::~GameItemObjectManager()
{

}
	
void GameItemObjectManager::SetManager()
{
	allObjectContainer_.reserve(300);
}

ItemObjectOrder GameItemObjectManager::RandomObjectOrder()
{
	int randomint = GameEngineRandom::mainRandom_.RandomInt(1,100);
	ItemObjectOrder randomObjectOrder = ItemObjectOrder::None;
	if (randomint > 90)
	{
		randomObjectOrder = ItemObjectOrder::Meet;
	}
	else if (randomint >80)
	{
		randomObjectOrder = ItemObjectOrder::Gold;
	}
	else if (randomint >70)
	{
		randomObjectOrder = ItemObjectOrder::Voidbead;
	}
	else if (randomint >50)
	{
		randomObjectOrder = ItemObjectOrder::RedExp;
	}
	else if (randomint >30)
	{
		randomObjectOrder = ItemObjectOrder::YellowExp;
	}
	else if (randomint >0)
	{
		randomObjectOrder = ItemObjectOrder::GreenExp;
	}
	return randomObjectOrder;
}

void GameItemObjectManager::CreateItemObject(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder, float4 _itemObjectPos)
{


	if (_itemObjectOrder == ItemObjectOrder::GreenExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (_itemObjectOrder == ItemObjectOrder::YellowExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (_itemObjectOrder == ItemObjectOrder::RedExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (_itemObjectOrder == ItemObjectOrder::Gold)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (_itemObjectOrder == ItemObjectOrder::Meet)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (_itemObjectOrder == ItemObjectOrder::Voidbead)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = _itemObjectOrder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("Void.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
}

void GameItemObjectManager::CreateItemObject(GameEngineLevel* _thisLevel, float4 _itemObjectPos)
{

	ItemObjectOrder randomorder = RandomObjectOrder();
	if (randomorder == ItemObjectOrder::GreenExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (randomorder == ItemObjectOrder::YellowExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (randomorder == ItemObjectOrder::RedExp)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
		newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
		newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (randomorder == ItemObjectOrder::Gold)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (randomorder == ItemObjectOrder::Meet)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
	else if (randomorder == ItemObjectOrder::Voidbead)
	{
		std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
		newItemObject->itemObjectOrder_ = randomorder;
		newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
		newItemObject->itemObjectRenderer_->SetTexture("Void.png");
		newItemObject->itemObjectRenderer_->GetTransform().SetWorldPosition(_itemObjectPos);
		newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
		newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
		newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
		newItemObject->itemObjectCol_->GetTransform().SetWorldPosition(_itemObjectPos);
		allObjectContainer_.push_back(newItemObject);
	}
}