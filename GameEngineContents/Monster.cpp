#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "GameItemObjectManager.h"

std::vector<std::shared_ptr<Monster>> Monster::allMonsters_;

std::shared_ptr<GameEngineInstancingRenderer> Monster::allMonstersRenderer_ = nullptr;
std::shared_ptr<GameEngineInstancingRenderer> Monster::allShadowsRenderer_ = nullptr;
std::shared_ptr<GameItemObjectManager> Monster::deadMonsterItemObject_ = std::shared_ptr<GameItemObjectManager>(new GameItemObjectManager);
int Monster::monsterCreationIndex_ = 0;

Monster::Monster()
	: mxMove_(0)
	, myMove_(0)
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
	, instancingUnitIndex_(0)
	, monsterScale_(float4::Zero)
	, isTarget_(false)
{
	monsterInfo_ = std::make_shared<MonsterInfo>();
	deadMonsterItemObject_->SetManager();
}

Monster::~Monster()
{
}

void Monster::ReserveMonsters(GameEngineLevel* _thisLevel, size_t _allMonsterCount)
{
	allMonsters_.reserve(_allMonsterCount);

	allMonstersRenderer_ = _thisLevel->GetMainCamera()->GetInstancingRenderer("1-AllMonstersRenderer");
	allMonstersRenderer_->Initialize(_allMonsterCount, "Rect", "DeferredInstanceRendering");
	allMonstersRenderer_->SetTexture2DArray("Inst_Textures", "Monster");
	allMonstersRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");

	allShadowsRenderer_ = _thisLevel->GetMainCamera()->GetInstancingRenderer("1-AllShadowsRenderer");
	allShadowsRenderer_->Initialize(_allMonsterCount, "Rect", "DeferredInstanceShadowRendering", true);
	allShadowsRenderer_->SetTexture2DArray("Inst_Textures", "Monster");
	allShadowsRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");

	for (size_t i = 0; i < GameEngineTexture2DArray::Find("Monster")->GetCount(); ++i)
	{
		GameEngineTexture2DArray::Find("Monster")->Cut(static_cast<int>(i), 10, 1);
	}

	for (size_t i = 0; i < _allMonsterCount; ++i)
	{
		allMonstersRenderer_->GetInstancingUnit(i).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.f);
		allShadowsRenderer_->GetInstancingUnit(i).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.f);
	}
}

void Monster::Unsummon()
{
	isSummoned_ = false;
	this->GetTransform().SetWorldPosition(float4::Zero);
	this->Off();

	allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldScale(float4::Zero);
	allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(float4::Zero);

	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldScale(float4::Zero);
	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(float4::Zero);
}

void Monster::Start()
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
	
	monsterAnimation_.Update(_deltaTime);
	allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
		this->GetTransform().GetWorldPosition()
	);
	allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).GetAtlasData().SetData(
		GameEngineTexture2DArray::Find("Monster")->GetCutData(monsterTextureName_, monsterAnimation_.GetCurrentIndex()),
		float4::Zero
	);

	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
		this->GetTransform().GetWorldPosition()
	);
	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).GetAtlasData().SetData(
		GameEngineTexture2DArray::Find("Monster")->GetCutData(monsterTextureName_, monsterAnimation_.GetCurrentIndex()),
		float4::Zero
	);
	//allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).Link("Inst_RenderOption", this->renderOption_);
}

void Monster::End()
{
}