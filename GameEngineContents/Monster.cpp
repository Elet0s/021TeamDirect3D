#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

std::vector<std::shared_ptr<Monster>> Monster::allMonsters_;

Monster::Monster()
	: mxMove_(0)
	, myMove_(0)
	, monRenderer_(nullptr)
	, monCollision_(nullptr)
	, colCheakToPlayer_(false)
	, playerRange_(0)
	,mx_(0)
	,my_(0)
	, isSummoned_(false)
{
	monsterInfo_ = std::make_shared<MonsterInfo>();
}

Monster::~Monster()
{
}

void Monster::ReserveMonsters(size_t _allMonsterCount)
{
	allMonsters_.reserve(_allMonsterCount);
}

void Monster::Unsummon()
{
	isSummoned_ = false;
	this->monCollision_->Off();
	this->monRenderer_->Off();
	this->shadowRenderer_->Off();
	this->GetTransform().SetWorldPosition(float4::Zero);
}

void Monster::Start()
{
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


	return CollisionReturn::Stop;
}

CollisionReturn Monster::MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (colCheakToPlayer_ == false)
	{
		colCheakToPlayer_ = true;
	}

	std::shared_ptr<Player> A = std::dynamic_pointer_cast<Player>(_Other->GetActor());
	pushVector_ = A->playerResultDirection_;
	float PX = abs(pushVector_.x);
	float PY = abs(pushVector_.y);
	if (mx_ < px_)
	{
		if (my_ < py_) // 몬스터가 3사분면
		{
			if ( PX > PY)// 플레이어가 x축이동
			{
				pushVector_.y -= 100.f;
			}
			else if (PX < PY)//플레이어가 y축이동
			{
				pushVector_.x -= 100.f;
			}
			else if (PX == PY && PX != 0)//플레이어가 대각선 이동
			{
				float PC = abs(range_.x) / abs(range_.y);
				if (PC > 1)
				{
				
					pushVector_.x -= 200.f;
				}
				else if (PC < 1)
				
				{
					pushVector_.y -= 200.f;
				}
			}
		}
		else if (my_ > py_)// 몬스터가 1사분면 
		{
			if (PX > PY)// 플레이어가 x축이동
			{
				pushVector_.y += 100.f;
			}
			else if (PX < PY)//플레이어가 y축이동
			{
				pushVector_.x -= 100.f;
			}
			else if (PX == PY && PX !=0)//플레이어가 대각선 이동
			{
				float PC = abs(range_.x) / abs(range_.y);
				if (PC > 1)
				{
					pushVector_.x -= 200.f;
				}
				else if (PC < 1)
				
				{
					pushVector_.y += 200.f;
				}
			}
		}
	}
	else if (mx_ > px_)
	{
		if (my_ > py_)// 몬스터가 2사분면 
		{
			if (PX > PY)// 플레이어가 x축이동
			{
				pushVector_.y += 100.f;
			}
			else if (PX < PY)//플레이어가 y축이동
			{
				pushVector_.x += 100.f;
			}
			else if (PX == PY && PX != 0)//플레이어가 대각선 이동
			{
				float PC = abs(range_.x) / abs(range_.y);
				if (PC > 1)
				{
					pushVector_.x += 200.f;
				}
				else if (PC < 1)
				
				{
					pushVector_.y += 200.f;
				}
			}
		}
		else if (my_ < py_)// 몬스터가 4사분면 
		{
			if (PX > PY)// 플레이어가 x축이동
			{
				pushVector_.y -= 100.f;
			}
			else if (PX < PY)//플레이어가 y축이동
			{
				pushVector_.x += 100.f;
			}
			else if (PX == PY && PX != 0)//플레이어가 대각선 이동
			{
				float PC = abs(range_.x) / abs(range_.y);
				if (PC > 1)
				{
					pushVector_.x += 200.f;
				}
				else if (PC < 1)
			
				{
					pushVector_.y -= 200.f;
				}
			}
		}
	}

 // 몬스터는 뒤로
	
	return CollisionReturn::Stop;
}

void Monster::Chaseplayer(float _deltaTime)
{
	 mx_ = GetTransform().GetWorldPosition().x;//몬스터 좌표
	 my_ = GetTransform().GetWorldPosition().y;
	 px_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x; //플레이어 좌표
	 py_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
	range_.x = px_ - mx_;//플레이어와 몬스터 x거리차이
	range_.y = py_ - my_;
	playerRange_ = static_cast<float>(sqrt(pow(range_.x,2) + pow(range_.y,2))); // 몬스터와 플레이어 사이의 거리의 절대값

	monsterResultVector_ = (range_.Normalize3D() * monsterInfo_->baseSpeed_); //충돌 안했을 때 기본 방향,힘 합치는 부분

	if (colCheakToPlayer_ == true)//플레이어와 충돌시 벡터 합산하는부분
	{
		reactionVector_ = -(monsterResultVector_);// 몬스터가 플레이어에 접촉했으니 힘의 반작용 
		monsterResultVector_ +=  reactionVector_;

		monsterResultVector_ += pushVector_; // 플레이어의 움직임으로 밀리는 힘
		colCheakToPlayer_ = false;
	}

	GetTransform().SetWorldMove(monsterResultVector_ * _deltaTime); //이동
}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}