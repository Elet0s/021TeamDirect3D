#include"PreCompile.h"
#include"GameItemObjectManager.h"
#include"GameEngineBase/GameEngineRandom.h"

GameItemObjectManager::GameItemObjectManager()
	:	isFullContainer_(false),
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
		MsgBoxAssert("지우려고 하는 오브젝트가 존재하지 않습니다.");
	}
	allObjectContainer_.erase(allObjectContainer_.begin()+ _Num);
}
	
void GameItemObjectManager::SetManager()
{
	allObjectContainer_.reserve(300);
}

std::vector< std::shared_ptr<GameItemObject>> GameItemObjectManager::GetallObjectContainer()
{
	return allObjectContainer_;
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
	if (isFullContainer_ == false)
	{
		ItemUpdateNum_ += 1;
		if (ItemUpdateNum_ == 300)
		{
			isFullContainer_ = true;
		}
		if (_itemObjectOrder == ItemObjectOrder::GreenExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
		allObjectContainer_.erase(allObjectContainer_.begin());

		if (_itemObjectOrder == ItemObjectOrder::GreenExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
	//ItemObjectOrder randomorder = ItemObjectOrder::GreenExp;
	if (isFullContainer_ == false)
	{
		ItemUpdateNum_ += 1;
		if (ItemUpdateNum_ == 300)
		{
			isFullContainer_ = true;
		}
		if (randomorder == ItemObjectOrder::GreenExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
		allObjectContainer_.erase(allObjectContainer_.begin());
		if (randomorder == ItemObjectOrder::GreenExp)
		{
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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
			std::shared_ptr<GameItemObject> newItemObject = _thisLevel->CreateActor<GameItemObject>(ObjectOrder::Item);
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