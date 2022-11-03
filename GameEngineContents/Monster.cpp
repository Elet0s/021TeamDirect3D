#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "Player.h"

Monster::Monster()
	:speed_(100.0f)
	, MXmove_(0)	
	, MYmove_(0)
{
}

Monster::~Monster()
{
}

void Monster::Start()
{

}
void Monster::SummonMon()
{
	for (size_t i = 0; i < 1; i++)
	{
		int px = static_cast<int>(Player::GetMainPlayer()->GetTransform().GetWorldPosition().x);
		int py = static_cast<int>(Player::GetMainPlayer()->GetTransform().GetWorldPosition().y);
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
	float px	= Player::GetMainPlayer()->GetTransform().GetWorldPosition().x;
	float py = Player::GetMainPlayer()->GetTransform().GetWorldPosition().y;
	float RangeX = abs(mx - px) / (abs(mx - px)+ abs(my - py)); //대각선이동을 위한 보정값
	float RangeY = abs(my - py) / (abs(mx - px) + abs(my - py));
	if (mx -px < 0)
	{
		MXmove_ = mx + (speed_ * RangeX * _deltaTime);
		this->GetTransform().PixLocalPositiveX();

	}
	else if (mx - px >=0)
	{
		MXmove_ = mx - (speed_ * RangeX * _deltaTime);
		this->GetTransform().PixLocalNegativeX();
	}
	if (my -py < 0)
	{
		MYmove_ = my + (speed_ * RangeY * _deltaTime);
	}
	else if (my - py >= 0)
	{
		MYmove_ = my - (speed_ * RangeY * _deltaTime);
	}
	GetTransform().SetWorldPosition(MXmove_, MYmove_, 0.0f);
}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}