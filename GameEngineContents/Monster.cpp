#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

std::vector<std::shared_ptr<Monster>> Monster::allMonsters_;

Monster::Monster()
	: mxMove_(0)
	, myMove_(0)
	, monRenderer_(nullptr)
	, monCollision_(nullptr)
	, colCheak_(false)
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
	if (colCheak_ == false)
	{
		colCheak_ = true;
	}

	std::shared_ptr<Player> A = std::dynamic_pointer_cast<Player>(_Other->GetActor());
	pushVector_ = A->resultDirection_;
	float PX = abs(pushVector_.x);
	float PY = abs(pushVector_.y);
	if (mx_ < px_)
	{
		if (my_ < py_) // ���Ͱ� 3��и�
		{
			if ( PX > PY)// �÷��̾ x���̵�
			{
				pushVector_.y -= 100.f;
			}
			else if (PX < PY)//�÷��̾ y���̵�
			{
				pushVector_.x -= 100.f;
			}
			else if (PX == PY && PX != 0)//�÷��̾ �밢�� �̵�
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
		else if (my_ > py_)// ���Ͱ� 1��и� 
		{
			if (PX > PY)// �÷��̾ x���̵�
			{
				pushVector_.y += 100.f;
			}
			else if (PX < PY)//�÷��̾ y���̵�
			{
				pushVector_.x -= 100.f;
			}
			else if (PX == PY && PX !=0)//�÷��̾ �밢�� �̵�
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
		if (my_ > py_)// ���Ͱ� 2��и� 
		{
			if (PX > PY)// �÷��̾ x���̵�
			{
				pushVector_.y += 100.f;
			}
			else if (PX < PY)//�÷��̾ y���̵�
			{
				pushVector_.x += 100.f;
			}
			else if (PX == PY && PX != 0)//�÷��̾ �밢�� �̵�
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
		else if (my_ < py_)// ���Ͱ� 4��и� 
		{
			if (PX > PY)// �÷��̾ x���̵�
			{
				pushVector_.y -= 100.f;
			}
			else if (PX < PY)//�÷��̾ y���̵�
			{
				pushVector_.x += 100.f;
			}
			else if (PX == PY && PX != 0)//�÷��̾ �밢�� �̵�
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

 // ���ʹ� �ڷ�
	
	return CollisionReturn::Stop;
}

void Monster::Chaseplayer(float _deltaTime)
{
	 mx_ = GetTransform().GetWorldPosition().x;//���� ��ǥ
	 my_ = GetTransform().GetWorldPosition().y;
	 px_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x; //�÷��̾� ��ǥ
	 py_ = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;
	range_.x = px_ - mx_;//�÷��̾�� ���� x�Ÿ�����
	range_.y = py_ - my_;
	playerRange_ = static_cast<float>(sqrt(pow(range_.x,2) + pow(range_.y,2))); // ���Ϳ� �÷��̾� ������ �Ÿ��� ���밪


	resultRange_ = (range_.Normalize3D() * monsterInfo_->baseSpeed_); //�浹 ������ �� �⺻ ����,�� ��ġ�� �κ�

	if (colCheak_ == true)//�浹�� ���� �ջ��ϴºκ�
	{
		monsterInfo_->colSpeed_ = -(resultRange_);// �̴� �� ���ۿ� 
		resultRange_ += monsterInfo_->colSpeed_; 

		resultRange_ += pushVector_; // �÷��̾�� �и��� ��
		colCheak_ = false;
	}

	GetTransform().SetWorldMove(resultRange_ * _deltaTime); //�̵�
}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}