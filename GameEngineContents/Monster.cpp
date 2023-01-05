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
	pushToMonsterVector.x = mx_ - A->mx_;// 콜리전 대상몬스터가 this 몬스터에게 오는 방향벡터
	pushToMonsterVector.y = my_ - A->my_;

	monsterReactionVector_ = (A->monsterResultVector_ + monsterResultVector_) / 2;//플레이어한테가는 최종벡터

	monsterReactionVector_ += pushToMonsterVector.Normalize3D()*120;// 몬스터끼리 부딪혔을때 몬스터끼리 밀어내는 힘
	
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

	monsterBaseVector_ = (range_.Normalize3D() * monsterInfo_->baseSpeed_); //충돌 안했을 때 기본 방향,힘 합치는 부분
	monsterResultVector_ = monsterBaseVector_;

	if (colCheakToPlayer_ == true)//플레이어와 충돌시 벡터 합산하는부분
	{
		reactionVector_ = -(monsterBaseVector_);// 몬스터가 플레이어에 접촉했으니 힘의 반작용 
		monsterResultVector_ = monsterBaseVector_ + (reactionVector_ *1.3f ) + pushToMonsterVector;
		monsterResultVector_ += pushVector_; // 플레이어의 움직임으로 밀리는 힘
		colCheakToPlayer_ = false;
	}
	else if (colCheakToMonster_ == true)//몬스터와 충돌시 벡터 합산하는부분
	{
		monsterResultVector_ = monsterReactionVector_;
		colCheakToMonster_ = false;
	}

	GetTransform().SetWorldMove(monsterResultVector_ * _deltaTime); //이동
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