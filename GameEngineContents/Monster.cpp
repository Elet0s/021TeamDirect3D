#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "Player.h"

Monster::Monster()
	: mxMove_(0)
	, myMove_(0)
	, monRenderer_(nullptr)
	, monCollision_(nullptr)
	, colCheak_(false)
	, playerRange_(0)
	,mx_(0)
	,my_(0)
{
	monsterInfo_ = std::make_shared<MonsterInfo>();
}

Monster::~Monster()
{
}

void Monster::Start()
{

		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Actor");
		Dir.MoveToChild("Monster");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());

		}


}
void Monster::SummonMon()
{


	for (size_t i = 0; i < 1; i++)
	{
		int px = static_cast<int>(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x);
		int py = static_cast<int>(Player::GetPlayerInst()->GetTransform().GetWorldPosition().y);
		float srangeX = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(px - 1280, px + 1280));
		float srangeY = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(py - 720, py + 720));

		if (srangeX > px + 640 || srangeX < px - 640)
		{
			GetTransform().SetWorldPosition(srangeX, srangeY, 0.0f);
		}
		else if (srangeX< px + 640 && srangeX>px -640)
		{
			if (srangeY > py + 360 || srangeY < py - 360)
			{
				GetTransform().SetWorldPosition(srangeX, srangeY, 0.0f);
			}
			else
			{
				i--;
			}
		}
		else
		{
			i--;
		}
	}
}

CollisionReturn Monster::MonsterToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	std::shared_ptr<Monster> A = std::dynamic_pointer_cast<Monster>(_Other->GetActor());
	if (colCheak_ == false)
	{
		colCheak_ = true;
	}
	
	if (A->playerRange_ > playerRange_)
	{
		A->GetMonsterInfo().colSpeed_ = -((monsterInfo_->baseSpeed_ + A->monsterInfo_->baseSpeed_) / 2);
		GetMonsterInfo().colSpeed_ = ((monsterInfo_->baseSpeed_ + A->monsterInfo_->baseSpeed_) / 4);
	}
	if (A->playerRange_ <= playerRange_)
	{
		GetMonsterInfo().colSpeed_ = -((monsterInfo_->baseSpeed_ + A->monsterInfo_->baseSpeed_) / 2);
		A->GetMonsterInfo().colSpeed_ = ((monsterInfo_->baseSpeed_ + A->monsterInfo_->baseSpeed_) / 4);
	}
	return CollisionReturn::Continue;
}
CollisionReturn Monster::MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	std::shared_ptr<Player> A = std::dynamic_pointer_cast<Player>(_Other->GetActor());


		A->GetPlayerInfo().pushSpeed_ = ((monsterInfo_->baseSpeed_ + A->GetPlayerInfo().speed_) / 5);
		GetMonsterInfo().colSpeed_ = -((monsterInfo_->baseSpeed_ + A->GetPlayerInfo().speed_) / 2);
	
	return CollisionReturn::Continue;
}
void Monster::Chaseplayer(float _deltaTime)
{
	 mx_ = GetTransform().GetWorldPosition().x;
	 my_ = GetTransform().GetWorldPosition().y;
	float px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
	float py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
	range_.x = px -mx_;
	range_.y = py -my_;
	playerRange_ = abs(range_.x) + abs(range_.y);
	if (false == monCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
	{
		monsterInfo_->ResultSpeed_ = monsterInfo_->baseSpeed_;
		colCheak_ = false;
		monsterInfo_->colSpeed_ = 0;
		GetTransform().SetWorldMove(range_.Normalize3D() * monsterInfo_->ResultSpeed_ * _deltaTime);
	}
	if (colCheak_ == true)
	{
			monsterInfo_->ResultSpeed_ = monsterInfo_->colSpeed_;
			GetTransform().SetWorldMove(range_.Normalize3D() * monsterInfo_->ResultSpeed_ * _deltaTime);
	}

}


void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}