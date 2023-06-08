#include"PreCompile.h"
#include"GameItemObjectManager.h"
#include"GameEngineBase/GameEngineRandom.h"

GameItemObjectManager::GameItemObjectManager()
	: isFullContainer_(false),
	ItemUpdateNum_(0)

{
}
GameItemObjectManager::~GameItemObjectManager()
{

}

void GameItemObjectManager::DelteObject(size_t _Num)
{
	if (allObjectContainer_[_Num] == nullptr)
	{
		MsgBoxAssert("������� �ϴ� ������Ʈ�� �������� �ʽ��ϴ�.");
	}
	allObjectContainer_[_Num]->Death();
	allObjectContainer_.erase(allObjectContainer_.begin()+ _Num);
	ItemUpdateNum_ -= 1;

	if (isFullContainer_==true)
	{
		isFullContainer_ = false;
	}
}
	
void GameItemObjectManager::SetManager()
{
	allObjectContainer_.reserve(300);
}

std::vector< GameItemObject*> GameItemObjectManager::GetallObjectContainer()
{
	return allObjectContainer_;
}

ItemObjectOrder GameItemObjectManager::RandomObjectOrder()
{
	int randomint = GameEngineRandom::mainRandom_.RandomInt(1,100);
	ItemObjectOrder randomObjectOrder = ItemObjectOrder::None;
	if (randomint > 99)
	{
		randomObjectOrder = ItemObjectOrder::Voidbead;
	}
	else if (randomint >96)
	{
		randomObjectOrder = ItemObjectOrder::Meet;
	}
	else if (randomint >90)
	{
		randomObjectOrder = ItemObjectOrder::Gold;
	}
	else if (randomint >60)
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
void GameItemObjectManager::ObjectAllClear()
{
	allObjectContainer_.clear();
	ItemUpdateNum_ = 0;
	if (isFullContainer_ == true)
	{
		isFullContainer_ = false;
	}
}
void GameItemObjectManager::CreateItemObject(GameEngineLevel* _thisLevel, ItemObjectOrder _itemObjectOrder, float4 _itemObjectPos)
{
	if (isFullContainer_ == false)
	{
		ItemUpdateNum_ += 1;
		if (ItemUpdateNum_ == 300)
		{
			isFullContainer_ = true;
		}
		if (_itemObjectOrder == ItemObjectOrder::GreenExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);

			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::YellowExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::RedExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Gold)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Meet)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Voidbead)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("Void.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
	}
	else if (isFullContainer_ == true)
	{
		allObjectContainer_[0]->itemObjectRenderer_->Off();
		allObjectContainer_[0]->itemObjectCol_->Off();
		allObjectContainer_[0]->Death();
		allObjectContainer_.erase(allObjectContainer_.begin());

		if (_itemObjectOrder == ItemObjectOrder::GreenExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);

			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::YellowExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::RedExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Gold)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Meet)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (_itemObjectOrder == ItemObjectOrder::Voidbead)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = _itemObjectOrder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("Void.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
	}
}

void GameItemObjectManager::CreateItemObject(GameEngineLevel* _thisLevel, float4 _itemObjectPos)
{
	ItemObjectOrder randomorder = RandomObjectOrder();
	if (isFullContainer_ == false)
	{
		ItemUpdateNum_ += 1;
		if (ItemUpdateNum_ == 299)
		{
			isFullContainer_ = true;
		}
		if (randomorder == ItemObjectOrder::GreenExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::YellowExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::RedExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Gold)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Meet)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Voidbead)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("Void.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
	}
	else if (isFullContainer_ == true)
	{
		allObjectContainer_[0]->itemObjectRenderer_->Off();
		allObjectContainer_[0]->itemObjectCol_->Off();
		allObjectContainer_[0]->Death();
		allObjectContainer_.erase(allObjectContainer_.begin());
		if (randomorder == ItemObjectOrder::GreenExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::YellowExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 1.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::RedExp)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(16, 16, 0);
			newItemObject->itemObjectRenderer_->SetTexture("XP_Sprite.png");
			newItemObject->itemObjectRenderer_->GetPixelData().mulColor_ = float4(1.0f, 0.0f, 0.0f, 1.0f);
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Gold)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("SmallCoin.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Meet)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("ChickenLeg.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
		else if (randomorder == ItemObjectOrder::Voidbead)
		{
			GameItemObject* newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
			newItemObject->itemObjectOrder_ = randomorder;
			newItemObject->itemObjectRenderer_ = newItemObject->CreateComponent<GameEngineTextureRenderer>();
			newItemObject->itemObjectRenderer_->GetTransform().SetWorldScale(32, 32, 0);
			newItemObject->itemObjectRenderer_->SetTexture("Void.png");
			newItemObject->itemObjectCol_ = newItemObject->CreateComponent<GameEngineCollision>();
			newItemObject->itemObjectCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Yellow);
			newItemObject->itemObjectRenderer_->ChangeCamera(CameraOrder::MidCamera);
			newItemObject->itemObjectCol_->ChangeOrder(ObjectOrder::Item);
			newItemObject->itemObjectCol_->GetTransform().SetWorldScale({ 16,16 });
			newItemObject->GetTransform().SetWorldPosition(_itemObjectPos);
			allObjectContainer_.push_back(newItemObject);
		}
	}
}