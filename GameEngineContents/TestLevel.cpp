#include "PreCompile.h"
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
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"
#include "SoundPlayer.h"
#include "FieldRenderingActor.h"

TestLevel::TestLevel()
	: fieldRenderingActor_(nullptr),
	testLevelLighting_(nullptr), 
	mousePointer_(nullptr)
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
		Player::CreatePlayer(this, { 0, 0 });
	}

	{
		std::shared_ptr<PlayerUI> NewPlayerUI = CreateActor<PlayerUI>(ObjectOrder::UI);
	}

	Monster::ReserveMonsters(this, 10);

	//Monster::CreateMonster<Brown>(this, 50);
	//Monster::CreateMonster<Green>(this, 50);
	//Monster::CreateMonster<NormalGoblin>(this, 50);
	Monster::CreateMonster<RedFlyingEyes>(this, 10);
	//Monster::CreateMonster<FlyingEyes>(this, 50);

	//Monster::SummonMonster<Brown>(this, 50);
	//Monster::SummonMonster<Green>(this, 50);
	//Monster::SummonMonster<NormalGoblin>(this, 50);
	Monster::SummonMonster<RedFlyingEyes>(this, 10);
	//Monster::SummonMonster<FlyingEyes>(this, 50);

	//for (size_t i = 0; i < Monster::GetMonsterList().size(); i++)
	//{
	//		Monster::GetMonsterList()[i]->Unsummon();
	//}
	//Monster::SummonMonster<RedFlyingEyes>(this, 10);



	
	//ShowCursor(false); 마우스 감추기
	CreateActor<TimeActor>();
	CreateActor<StageUI>()->SoulCoinRenderersOff();

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
}

void TestLevel::Update(float _DeltaTime)
{						
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
	SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1); 
	this->GetMainCamera()->SetFarZ(500.f);
	this->GetCamera(CameraOrder::MidCamera)->SetFarZ(500.f);
}

void TestLevel::LevelEndEvent()
{
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


