#include "PreCompile.h"
#include "StageObject.h"
#include "TestLevel.h"
#include "TimeActor.h"
#include "StageUI.h"
#include "GlobalContentsValue.h"
#include "Mouse.h"
#include "Player.h"
#include "PlayerUI.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "DashUI.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"
#include "SoundPlayer.h"
#include "FieldRenderingActor.h"
#include "StageObject.h"
#include "NormalSkeleton.h"
#include "NormalKobold.h"
#include "Red.h"
#include "KoboldLivesey.h"
#include "GoblinLivesey.h"
#include "Boss01.h"
#include "MagicCircle.h"
#include "SoulCardSelectBox.h"
#include"GameItemObjectManager.h"

TestLevel::TestLevel()
	: fieldRenderingActor_(nullptr),
	testLevelLighting_(nullptr), 
	mousePointer_(nullptr),
	stageUI_(nullptr),
	stageType_(StageType::Max),
	combatType_(CombatType::Max),
	killCount_(0),
	timeLimit_(0.f),
	summonCounter_(0)
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	//mainCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	//mainCameraActor->GetCameraComponent()->SetProjectionMode(CameraProjectionMode::Orthographic);
	//mainCameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::MousePointerCamera);


	fieldRenderingActor_ = CreateActor<FieldRenderingActor>();
	fieldRenderingActor_->Initialize(
		550,
		100,
		float4(100, 100),
		60.f
	);
	fieldRenderingActor_->GetTransform().SetLocalScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldPosition(float4::Zero);

	if (true == Player::GetPlayerWeakPtr().expired())
	{
		Player::CreatePlayer(this, { 0, 0,-219 });
	}

	std::shared_ptr<PlayerUI> NewPlayerUI = CreateActor<PlayerUI>(ObjectOrder::UI);
	
	Monster::ReserveMonsters(this, 722);

	Monster::CreateMonster<RedFlyingEyes>(this, 100);
	Monster::CreateMonster<NormalSkeleton>(this, 100);
	Monster::CreateMonster<NormalKobold>(this, 100);
	Monster::CreateMonster<NormalGoblin>(this, 100);
	Monster::CreateMonster<Red>(this, 100);
	Monster::CreateMonster<FlyingEyes>(this, 100);
	Monster::CreateMonster<Brown>(this, 100);

	Monster::CreateMonster<Green>(this, 5);
	Monster::CreateMonster<KoboldLivesey>(this, 5);
	Monster::CreateMonster<GoblinLivesey>(this, 5);
	Monster::CreateMonster<BlackEyes>(this, 5);

	Monster::CreateMonster<Boss01>(this, 1);


	
	//ShowCursor(false); 마우스 감추기
	CreateActor<TimeActor>();
	stageUI_ = CreateActor<StageUI>();

	testLevelLighting_ = CreateActor<GameEngineLighting>(0, "TestLevelLighting");
	//테스트레벨에 조명 추가.

	testLevelLighting_->GetTransform().SetWorldRotation(45.f, 45.f, 0.f);
	//조명 각도 설정.

	testLevelLighting_->GetLightingData().mainLightColor_ = float4(0.7f, 0.7f, 0.7f);
	//정반사광, 난반사광 색, 밝기 설정.

	testLevelLighting_->GetLightingData().ambientLightColor_ = float4(0.1f, 0.1f, 0.1f);
	//환경광 색, 밝기 설정.

	testLevelLighting_->GetLightingData().specularLightRatio_ = 0.f;
	//정반사광 사용 안함.

	testLevelLighting_->GetLightingData().diffuseLightRatio_ = 2.f;
	//난반사광을 두배로 적용.

	this->GetMainCamera()->PushLighting(testLevelLighting_);
	//메인카메라에 조명 등록.

	this->GetCamera(CameraOrder::MidCamera)->PushLighting(testLevelLighting_);
	//미드카메라에도 조명 등록.

	if (nullptr == mousePointer_)
	{
		mousePointer_ = CreateActor<Mouse>(ObjectOrder::Mouse, "TestLevelMousePointer");
	}

	CreateActor<DashUI>();
}

void TestLevel::Update(float _DeltaTime)
{						
	stageManagerTimer_ += _DeltaTime;
	StageMonsterManager();

	PlayerMoveCamera();

	this->GetCameraActor(CameraOrder::MidCamera)->GetTransform().SetWorldPosition(
		GetMainCameraActor()->GetTransform().GetWorldPosition()
	);

	fieldRenderingActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());

	mousePointer_->UpdatePivotPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());

	//mousePointer_->ChangeMousePointerRenderer(true);

}

void TestLevel::LevelStartEvent()
{
	summonCounter_ = 0;
		stageManagerTimer_ = 0.f;

	Player::GetPlayerInst()->On();
	stageUI_->SetUI(UIType::Stage);
	if (Player::GetPlayerInst()->GetPlayerInfo().level_ == 0)
	{
	CreateActor<SoulCardSelectBox>()->DrawWeapon();

	}
	this->GetMainCamera()->SetFarZ(500.f);
	this->GetCamera(CameraOrder::MidCamera)->SetFarZ(500.f);

	//PrepareNewStage();
}

void TestLevel::LevelEndEvent()
{
	Monster::UnsummonAllMonsters();
	Monster::GetItemObjectManager()->ObjectAllClear();
	SoundPlayer::BGMPlay_->Stop();
}

void TestLevel::PlayerMoveCamera()
{
	float Time = GameEngineTime::GetDeltaTime();
	float4 MoveVector = Player::GetPlayerInst()->GetTransform().GetWorldPosition() - GetMainCameraActorTransform().GetWorldPosition();

	if (abs(MoveVector.x) < 1.0f)
	{
		MoveVector.x = 0.f;
	}

	if (abs(MoveVector.y) < 1.0f)
	{
		MoveVector.y = 0.f;
	}

	GetMainCameraActor()->GetTransform().SetWorldMove(float4((MoveVector.x) * Time, (MoveVector.y) *1.5f * Time));

}

//void TestLevel::PrepareNewStage()
//{
//	this->stageType_ = StageObject::GetNextStageInfo().stageType_;
//	this->combatType_ = StageObject::GetNextStageInfo().combatType_;
//
//	if (CombatType::Max == this->combatType_)
//	{
//		MsgBoxAssert("비 전투맵 오브젝트인데 전투맵으로 넘어왔습니다.");
//		return;
//	}
//
//	this->killCount_ = StageObject::GetNextStageInfo().killCount_;
//	this->timeLimit_ = StageObject::GetNextStageInfo().timeLimit_;
//
//	Monster::ReserveMonsters(this, StageObject::GetNextStageInfo().totalMonsterCount_);
//
//	for (std::pair<MonsterType, size_t> countPerType : StageObject::GetNextStageInfo().summoningMonsterCountMap_)
//	{
//		Monster::CreateMonsterWithEnum(this, countPerType.first, countPerType.second);
//	}
//}

void TestLevel::MouseMoveCamera()
{
	float Time = GameEngineTime::GetDeltaTime();

	float4 MouseDir = float4::Zero;
	float4 CheckPos = GetMainCamera()->GetMousePositionInWorldSpace() - Player::GetPlayerInst()->GetTransform().GetWorldPosition();

	if (CheckPos.x > 360.f)
	{
		MouseDir.x = 100.f;
	}
	else if (CheckPos.x < -360.f)
	{
		MouseDir.x = -100.f;
	}

	if (CheckPos.y > 180.f)
	{
		MouseDir.y = 100.f;
	}
	else if (CheckPos.y < -180.f)
	{
		MouseDir.y = -100.f;
	}
	
	GetMainCameraActor()->GetTransform().SetWorldMove(float4((MouseDir.x) * Time, (MouseDir.y) * Time));
}

void TestLevel::StageMonsterManager()
{
		switch (StageObject::GetNextStageInfo().combatType_)
		{
		case CombatType::TimeAttack:
			if (summonCounter_ == 0 && stageManagerTimer_ < 1.f)
			{
				SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1);
				Monster::SummonMonster<Brown>(this, 100);
				summonCounter_ += 1;
			}

			else if (summonCounter_ == 1 && stageManagerTimer_ > 20.f)
			{
				Monster::SummonMonster<FlyingEyes>(this, 100);
				summonCounter_ += 1;
			}
			else if (summonCounter_ == 2 && stageManagerTimer_ > 50.f)
			{
				Monster::SummonMonster<NormalGoblin>(this, 50);
				Monster::SummonMonster<NormalKobold>(this, 50);

				summonCounter_ += 1;
			}
			else if (summonCounter_ == 3 && stageManagerTimer_ > 100.f)
			{

				for (size_t i = 0; i < Monster::GetMonsterList().size(); i++)
				{
					if (Monster::GetMonsterList()[i]->GetMonsterInfo().monsterType_ == MonsterType::FlyingEyes)
					{
						Monster::GetMonsterList()[i]->Unsummon();
					}
					if (Monster::GetMonsterList()[i]->GetMonsterInfo().monsterType_ == MonsterType::Brown)
					{
						Monster::GetMonsterList()[i]->Unsummon();
					}
				}
				summonCounter_ += 1;
			}
			else if (summonCounter_ == 4 && stageManagerTimer_ > 105.f)
			{
				Monster::SummonMonster<NormalSkeleton>(this, 100);
				Monster::SummonMonster<Red>(this, 100);
				Monster::SummonMonster<RedFlyingEyes>(this, 100);
				Monster::SummonMonster<KoboldLivesey>(this, 5);
				Monster::SummonMonster<GoblinLivesey>(this, 5);
				summonCounter_ += 1;
			}
			break;
		case CombatType::Kill:
			if (summonCounter_ == 0 && stageManagerTimer_ < 1.f)
			{
				SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1);
				Monster::SummonMonster<RedFlyingEyes>(this, 20);
				summonCounter_ += 1;
			}

			else if (summonCounter_ == 1 && stageManagerTimer_ > 20.f)
			{
				Monster::SummonMonster<FlyingEyes>(this, 10);
				Monster::SummonMonster<Brown>(this, 10);
				Monster::SummonMonster<NormalGoblin>(this, 10);
				summonCounter_ += 1;
			}
			else if (summonCounter_ == 2 && stageManagerTimer_ > 50.f)
			{
				Monster::SummonMonster<FlyingEyes>(this, 10);
				Monster::SummonMonster<Brown>(this, 10);
				Monster::SummonMonster<NormalGoblin>(this, 10);

				summonCounter_ += 1;
			}
			else if (summonCounter_ == 3 && stageManagerTimer_ > 100.f)
			{
				Monster::SummonMonster<FlyingEyes>(this, 10);
				Monster::SummonMonster<Brown>(this, 10);
				Monster::SummonMonster<NormalGoblin>(this, 10);
				Monster::SummonMonster<NormalKobold>(this, 10);
				Monster::SummonMonster<Red>(this, 10);
				summonCounter_ += 1;
			}
			
			break;
		case CombatType::EilteKill:
			if (summonCounter_ == 0 && stageManagerTimer_ < 1.f)
			{
				SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1);
				Monster::SummonMonster<NormalGoblin>(this, 20);
				Monster::SummonMonster<NormalKobold>(this, 20);
				Monster::SummonMonster<KoboldLivesey>(this, 2);
				Monster::SummonMonster<GoblinLivesey>(this, 2);
				summonCounter_ += 1;
			}

			else if (summonCounter_ == 1 && stageManagerTimer_ > 20.f)
			{
				Monster::SummonMonster<NormalGoblin>(this, 50);
				summonCounter_ += 1;
			}
			else if (summonCounter_ == 2 && stageManagerTimer_ > 50.f)
			{
				Monster::SummonMonster<NormalKobold>(this, 50);
				summonCounter_ += 1;
			}
			break;
		case CombatType::BossKill:
			SoundPlayer::BGMPlay_->ChangeBgm("BossFight.wav");

			if (summonCounter_ == 0 && stageManagerTimer_ < 1.f)
			{
				Monster::SummonMonster<RedFlyingEyes>(this, 30);
				Monster::SummonMonster<Boss01>(this, 1);
				summonCounter_ += 1;
			}

			else if (summonCounter_ == 1 && stageManagerTimer_ > 20.f)
			{
				Monster::SummonMonster<RedFlyingEyes>(this, 20);
				Monster::SummonMonster<BlackEyes>(this, 2);
				summonCounter_ += 1;
			}
			else if (summonCounter_ == 2 && stageManagerTimer_ > 50.f)
			{
				Monster::SummonMonster<Red>(this, 50);
				Monster::SummonMonster<Green>(this, 2);

				summonCounter_ += 1;
			}
			else if (summonCounter_ == 3 && stageManagerTimer_ > 100.f)
			{
				for (size_t i = 0; i < Monster::GetMonsterList().size(); i++)
				{
					if (Monster::GetMonsterList()[i]->GetMonsterInfo().monsterType_ == MonsterType::RedFlyingEyes)
					{
						Monster::GetMonsterList()[i]->Unsummon();
					}
					if (Monster::GetMonsterList()[i]->GetMonsterInfo().monsterType_ == MonsterType::Red)
					{
						Monster::GetMonsterList()[i]->Unsummon();
					}
				}
				Monster::SummonMonster<NormalSkeleton>(this, 100);
				summonCounter_ += 1;
			}

			break;
		case CombatType::Max:

			break;
		default:
			break;
		}
}