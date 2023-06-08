#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "GameItemObjectManager.h"

#include "Brown.h"
#include "FlyingEyes.h"
#include "NormalGoblin.h"
#include "NormalKobold.h"
#include "NormalSkeleton.h"
#include "Red.h"
#include "RedFlyingEyes.h"

#include "BlackEyes.h"
#include "GoblinLivesey.h"
#include "Green.h"
#include "KoboldLivesey.h"

#include "Boss01.h"

std::vector<Monster*> Monster::allMonsters_;

GameEngineInstanceRenderer* Monster::allMonstersRenderer_ = nullptr;
GameEngineInstanceRenderer* Monster::allShadowsRenderer_ = nullptr;
GameItemObjectManager* Monster::dropMonsterItemObject_ = new GameItemObjectManager();
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
	, flash_(false)
	, flashLoop_(false)
	, flashTimer_(0)
	, isToRight_(true)
{
	monsterInfo_ = new MonsterInfo();
	dropMonsterItemObject_->SetManager();
}

Monster::~Monster()
{
	if (nullptr != monsterInfo_)
	{
		delete monsterInfo_;
		monsterInfo_ = nullptr;
	}

	if (nullptr != dropMonsterItemObject_)
	{
		delete dropMonsterItemObject_;
		dropMonsterItemObject_ = nullptr;
	}
}

void Monster::ReserveMonsters(GameEngineLevel* _thisLevel, size_t _allMonsterCount)
{
	allMonsters_.reserve(_allMonsterCount);

	allMonstersRenderer_ = &_thisLevel->GetCamera(CameraOrder::MidCamera)->GetInstanceRenderer("1-AllMonstersRenderer");
	allMonstersRenderer_->Initialize(_allMonsterCount, "Rect", "MonsterInstanceRendering");
	allMonstersRenderer_->SetTexture2DArray("Inst_Textures", "Monster");
	allMonstersRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");

	//allShadowsRenderer_ = _thisLevel->GetCamera(CameraOrder::MidCamera)->GetInstancingRenderer("1-AllShadowsRenderer");
	//미드카메라에서 그림자가 그려지지 않는 원인 찾아낼 것.
	allShadowsRenderer_ = &_thisLevel->GetMainCamera()->GetInstanceRenderer("1-AllShadowsRenderer");
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

void Monster::UnsummonAllMonsters()
{
	for (Monster* const singleMonster : allMonsters_)
	{
		if (true == singleMonster->isSummoned_)
		{
			singleMonster->Unsummon();
		}
	}
}

void Monster::CreateMonsterWithEnum(GameEngineLevel* _thisLevel, MonsterType _monsterType, size_t _monsterCount)
{
	switch (_monsterType)
	{
		case MonsterType::Brown:
			Monster::CreateMonster<Brown>(_thisLevel, _monsterCount);
			break;
		case MonsterType::FlyingEyes:
			Monster::CreateMonster<FlyingEyes>(_thisLevel, _monsterCount);
			break;
		case MonsterType::NormalGoblin:
			Monster::CreateMonster<NormalGoblin>(_thisLevel, _monsterCount);
			break;
		case MonsterType::NormalKobold:
			Monster::CreateMonster<NormalKobold>(_thisLevel, _monsterCount);
			break;
		case MonsterType::NormalSkeleton:
			Monster::CreateMonster<NormalSkeleton>(_thisLevel, _monsterCount);
			break;
		case MonsterType::Red:
			Monster::CreateMonster<Red>(_thisLevel, _monsterCount);
			break;
		case MonsterType::RedFlyingEyes:
			Monster::CreateMonster<RedFlyingEyes>(_thisLevel, _monsterCount);
			break;
		case MonsterType::BlackEyes:
			Monster::CreateMonster<BlackEyes>(_thisLevel, _monsterCount);
			break;
		case MonsterType::GoblinLivesey:
			Monster::CreateMonster<GoblinLivesey>(_thisLevel, _monsterCount);
			break;
		case MonsterType::Green:
			Monster::CreateMonster<Green>(_thisLevel, _monsterCount);
			break;
		case MonsterType::KoboldLivesey:
			Monster::CreateMonster<KoboldLivesey>(_thisLevel, _monsterCount);
			break;
		case MonsterType::Boss:
			Monster::CreateMonster<Boss01>(_thisLevel, _monsterCount);
			break;

		default:
			MsgBoxAssert("아직 준비되지 않은 형태의 몬스터입니다.");
			break;
	}
}

void Monster::Start()
{
}

CollisionReturn Monster::MonsterToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (colCheakToMonster_ == false)
	{
		colCheakToMonster_ = true;
	}
	Monster* A = dynamic_cast<Monster*>(_Other->GetActor());
	pushToMonsterVector.x = mx_ - A->mx_;// 콜리전 대상몬스터가 this 몬스터에게 오는 방향벡터
	pushToMonsterVector.y = my_ - A->my_;

	monsterReactionVector_ = (A->monsterResultVector_ + monsterResultVector_) / 2;//플레이어한테가는 최종벡터

	monsterReactionVector_ += pushToMonsterVector.Normalize3D() * 120;// 몬스터끼리 부딪혔을때 몬스터끼리 밀어내는 힘

	return CollisionReturn::Continue;
}

CollisionReturn Monster::MonsterToPlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (colCheakToPlayer_ == false)
	{
		colCheakToPlayer_ = true;
	}
	Player* A = dynamic_cast<Player*>(_Other->GetActor());
	if (atkDeltaTime_ >= 1.5f)
	{
		A->GetPlayerInfo().hp_ -= this->monsterInfo_->atk_;
		if (A->hitOnoff_ == false)
		{
			A->hitOnoff_ = true;
			A->flash_ =true;
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

	return CollisionReturn::Continue;
}

void Monster::Chaseplayer(float _deltaTime)
{ 
	mx_ = GetTransform().GetWorldPosition().x;//몬스터 좌표
	my_ = GetTransform().GetWorldPosition().y;
	px_ = Player::GetPlayerInst().GetTransform().GetWorldPosition().x; //플레이어 좌표
	py_ = Player::GetPlayerInst().GetTransform().GetWorldPosition().y;
	range_.x = px_ - mx_;//플레이어와 몬스터 x거리차이
	range_.y = py_ - my_;

	if (range_.x < 0 && true == isToRight_)
	{
		isToRight_ = false;
		allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SwitchLeftToRight();
		allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SwitchLeftToRight();
		renderOption_.vertexInversion_ = -1;
	}
	else if (range_.x > 0 && false == isToRight_)
	{
		isToRight_ = true;
		allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SwitchLeftToRight();
		allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SwitchLeftToRight();
		renderOption_.vertexInversion_ = 1;
	}


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

	if (monsterInfo_->monsterType_ == MonsterType::Boss)
	{
		if (playerRange_ < 400.f)
		{
			monsterInfo_->bossPattern_ = BossPattern::Idle;
		}
	}
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
	allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).Link("Inst_PixelData", this->pixelData_);

	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
		this->GetTransform().GetWorldPosition().x,
		this->GetTransform().GetWorldPosition().y, 
		this->GetTransform().GetWorldPosition().z + 2.f
	);
	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).GetAtlasData().SetData(
		GameEngineTexture2DArray::Find("Monster")->GetCutData(monsterTextureName_, monsterAnimation_.GetCurrentIndex()),
		float4::Zero
	);
	allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).Link("Inst_RenderOption", this->renderOption_);
	FlashMonster(_deltaTime);
}

void Monster::End()
{

}

void Monster::FlashMonster(float _deltaTime)
{
	if (flash_ == true)
	{
		if (flashTimer_ < 0.2f)
		{
			flashTimer_ += _deltaTime;
			pixelData_.mulColor_ = float4{ 1.0f, 0.7f, 0.7f, 0.7f };
		}
		else
		{
			flashLoop_ = true;
		}

		if (flashLoop_ == true)
		{
			pixelData_.mulColor_ = float4{ 1.f,1.f ,1.f ,1.f };
			flashTimer_ = 0;
			flashLoop_ = false;
			flash_ = false;
		}
	}

}

void Monster::HpCheak()
{
	if (monsterInfo_->hp_ > 0)
	{
		return;
	}
	if (monsterInfo_->hp_ <= 0)
	{
		int random_ = GameEngineRandom::mainRandom_.RandomInt(1, 3);

		switch (monsterInfo_->monsterType_)
		{
			case MonsterType::Brown:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_C.wav");
				}
				break;
			case MonsterType::FlyingEyes:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_C.wav");
				}
				break;
			case MonsterType::NormalGoblin:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_C.wav");
				}
				break;
			case MonsterType::NormalKobold:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit.wav");
				}
				else 
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit_old.wav");
				}
				break;
			case MonsterType::NormalSkeleton:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Skeleton_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Skeleton_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Skeleton_Hit_C.wav");
				}
				break;
			case MonsterType::Red:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_C.wav");
				}
				break;
			case MonsterType::RedFlyingEyes:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_C.wav");
				}
				break;
			case MonsterType::BlackEyes:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Bat_Hit_C.wav");
				}
				break;
			case MonsterType::GoblinLivesey:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Goblin_Hit_C.wav");
				}
				break;
			case MonsterType::Green:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_A.wav");
				}
				else if (random_ == 2)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_B.wav");
				}
				else if (random_ == 3)
				{
					GameEngineSound::SoundPlayOneshot("Mushroom_Hit_C.wav");
				}
				break;
			case MonsterType::KoboldLivesey:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit.wav");
				}
				else
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit_old.wav");
				}
				break;
			case MonsterType::Boss:
				if (random_ == 1)
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit.wav");
				}
				else
				{
					GameEngineSound::SoundPlayOneshot("Generic_Hit_old.wav");
				}
		}
		dropMonsterItemObject_->CreateItemObject(GetLevel(), this->GetTransform().GetWorldPosition());

		switch (monsterInfo_->monsterType_)
		{
			case MonsterType::BlackEyes:
				Player::GetPlayerInst().GetPlayerInfo().eliteTargetScore_ += 1;
				break;
			case MonsterType::GoblinLivesey:
				Player::GetPlayerInst().GetPlayerInfo().eliteTargetScore_ += 1;
				break;
			case MonsterType::Green:
				Player::GetPlayerInst().GetPlayerInfo().eliteTargetScore_ += 1;
				break;
			case MonsterType::KoboldLivesey:
				Player::GetPlayerInst().GetPlayerInfo().eliteTargetScore_ += 1;
				break;
			default:
				Player::GetPlayerInst().GetPlayerInfo().targetScore_ += 1;
				break;
		}


		RelocationMonster();
		monsterInfo_->hp_ = monsterInfo_->maxHp_;
	}
}

void Monster::ReduceHP()
{
	if (monsterInfo_->maxHp_ >= monsterInfo_->hp_)
	{
		monsterHp_->GetPixelData().slice_ = float4(1 - (monsterInfo_->hp_ / monsterInfo_->maxHp_), 0.0f, 0.0f, 0.0f);
	}

}

void Monster::RelocationMonster()
{
	float4 CameraPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();


	while (true)
	{
		float4 monsterPosition_ = GameEngineRandom::mainRandom_.RandomFloat4(
			float4(CameraPos.x - 1280, CameraPos.y - 720),
			float4(CameraPos.x + 1280, CameraPos.y + 720));
		monsterPosition_.z = -199.f;
		if (monsterPosition_.x > CameraPos.x + 640 || monsterPosition_.x < CameraPos.x - 640)
		{
			GetTransform().SetWorldPosition(monsterPosition_);

			allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_
			);

			allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_.x,
				monsterPosition_.y,
				monsterPosition_.z + 2.f
			);
			break;
		}
		else if (monsterPosition_.y > CameraPos.y + 360 || monsterPosition_.y < CameraPos.y - 360)
		{
			GetTransform().SetWorldPosition(monsterPosition_);

			allMonstersRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_
			);

			allShadowsRenderer_->GetInstancingUnit(this->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_.x,
				monsterPosition_.y,
				monsterPosition_.z + 2.f
			);
			break;
		}
	}

}