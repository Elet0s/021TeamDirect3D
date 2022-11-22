#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "Player.h"

Monster::Monster()
	: mxMove_(0)	
	, myMove_(0)
	, monRenderer_(nullptr)
	, monCollision_(nullptr)
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
void Monster::Chaseplayer(float _deltaTime)
{
	float mx = GetTransform().GetWorldPosition().x;
	float my = GetTransform().GetWorldPosition().y;
	float px	= Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
	float py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
	float RangeX = abs(mx - px) / (abs(mx - px)+ abs(my - py)); //대각선이동을 위한 보정값
	float RangeY = abs(my - py) / (abs(mx - px) + abs(my - py));
	if (mx -px < 0)
	{
		mxMove_ = mx + (monsterInfo_->speed_ * RangeX * _deltaTime);
		this->GetTransform().PixLocalPositiveX();

	}
	else if (mx - px >=0)
	{
		mxMove_ = mx - (monsterInfo_->speed_ * RangeX * _deltaTime);
		this->GetTransform().PixLocalNegativeX();
	}
	if (my -py < 0)
	{
		myMove_ = my + (monsterInfo_->speed_ * RangeY * _deltaTime);
	}
	else if (my - py >= 0)
	{
		myMove_ = my - (monsterInfo_->speed_ * RangeY * _deltaTime);
	}
	GetTransform().SetWorldPosition(mxMove_, myMove_, 0.0f);
}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}