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
	, mx_(0)
	, my_(0)
	, isSummoned_(false)
	, atkDeltaTime_(0)
	, colCheakToMonster_(false)
	, pushToMonsterVector(0)
	, range_(0)
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
	this->GetTransform().SetWorldPosition(float4::Zero);
	this->Off();
}

void Monster::Start()
{
}


void Monster::Attack()
{
}
CollisionReturn Monster::MonsterToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (colCheakToMonster_ == false)
	{
		colCheakToMonster_ = true;
	}
	std::shared_ptr<Monster> A = std::dynamic_pointer_cast<Monster>(_Other->GetActor());
	 pushToMonsterVector.x = mx_ - A->mx_;// �ݸ��� �����Ͱ� this ���Ϳ��� ���� ���⺤��
	 pushToMonsterVector.y = my_ - A->my_;

		 monsterReactionVector_ = (A->monsterResultVector_ + monsterResultVector_) / 2;//�÷��̾����װ��� ��������

		 monsterReactionVector_ += pushToMonsterVector.Normalize3D()*120;// ���ͳ��� �ε������� ���ͳ��� �о�� ��
	
	return CollisionReturn::Stop;
}

CollisionReturn Monster::MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (colCheakToPlayer_ == false)
	{
		colCheakToPlayer_ = true;
	}
	std::shared_ptr<Player> A = std::dynamic_pointer_cast<Player>(_Other->GetActor());
	if (atkDeltaTime_ >= 1.5f)
	{
		A->GetPlayerInfo().hp_ -= this->monsterInfo_->atk_;
		if (A->hitOnoff_ == false)
		{
			A->hitOnoff_ = true;
		}
		atkDeltaTime_ = 0;
	}

	pushVector_ = A->playerResultDirection_;
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

	monsterBaseVector_ = (range_.Normalize3D() * monsterInfo_->baseSpeed_); //�浹 ������ �� �⺻ ����,�� ��ġ�� �κ�
	monsterResultVector_ = monsterBaseVector_;

	if (colCheakToPlayer_ == true)//�÷��̾�� �浹�� ���� �ջ��ϴºκ�
	{
		reactionVector_ = -(monsterBaseVector_);// ���Ͱ� �÷��̾ ���������� ���� ���ۿ� 
		monsterResultVector_ = monsterBaseVector_ + (reactionVector_ *1.3f ) + pushToMonsterVector;
		monsterResultVector_ += pushVector_; // �÷��̾��� ���������� �и��� ��
		colCheakToPlayer_ = false;
	}
	else if (colCheakToMonster_ == true)//���Ϳ� �浹�� ���� �ջ��ϴºκ�
	{
		monsterResultVector_ = monsterReactionVector_;
		colCheakToMonster_ = false;
	}

	GetTransform().SetWorldMove(monsterResultVector_ * _deltaTime); //�̵�
	monsterReactionVector_ = 0;
}

void Monster::Update(float _deltaTime)
{
	atkDeltaTime_ += _deltaTime;
}

void Monster::End()
{
}