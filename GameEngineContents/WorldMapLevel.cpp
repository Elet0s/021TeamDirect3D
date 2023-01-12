#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "Player.h"
#include "Mouse.h"
#include "SoundPlayer.h"
#include "StageCreater.h"
#include "StageUI.h"
#include "StageObject.h"
#include "WorldMapRenderingActor.h"
#include "GlobalContentsValue.h"

WorldMapLevel::WorldMapLevel()
	: WorldMapRenderingActor_(nullptr),
	WorldLevelLighting_(nullptr),
	//TestActor_(nullptr),
	stageCreater_(nullptr),
	mousePointer_(nullptr),
	stageUI_(nullptr),
	soundCheck_(false)
{
}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{
	//TestActor_ = CreateActor<TestActor>();

	WorldMapRenderingActor_ = CreateActor<WorldMapRenderingActor>();
	WorldMapRenderingActor_->Initialize(
		1000,
		300
	);

	stageCreater_ = CreateActor<StageCreater>();

	WorldMapRenderingActor_->GetTransform().SetLocalScale(float4::White);
	WorldMapRenderingActor_->GetTransform().SetWorldScale(float4::White);
	WorldMapRenderingActor_->GetTransform().SetWorldPosition(float4::Zero);

	WorldLevelLighting_ = CreateActor<GameEngineLighting>(0, "WorldMapLighting");
	//����ʿ� ���� �߰�.

	WorldLevelLighting_->GetTransform().SetWorldRotation(-30.f, 45.f, 0.f);
	//���� ���� ����.

	WorldLevelLighting_->GetLightingData().mainLightColor_ = float4(0.7f, 0.7f, 0.7f);
	//���ݻ籤, ���ݻ籤 ��, ��� ����.

	WorldLevelLighting_->GetLightingData().ambientLightColor_ = float4(0.1f, 0.1f, 0.1f);
	//ȯ�汤 ��, ��� ����.

	WorldLevelLighting_->GetLightingData().specularLightRatio_ = 0.f;
	//���ݻ籤 ��� ����.

	WorldLevelLighting_->GetLightingData().diffuseLightRatio_ = 2.f;
	//���ݻ籤�� �ι�� ����.

	this->GetMainCamera()->PushLighting(WorldLevelLighting_);
	//����ī�޶� ���� ���.
	
	GetMainCameraActorTransform().SetWorldPosition(float4(872.f, -1088.f, -2300.f));
	GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);
	//GetUICamera()->GetTransform().SetWorldPosition(float4(896.f, -1145.f, -2226.f));

	if (false == GameEngineInput::GetInst()->IsKey("WorldCameraLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("WorldCameraLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("WorldCameraRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("WorldCameraFoward", VK_UP);
		GameEngineInput::GetInst()->CreateKey("WorldCameraBack", VK_DOWN);
	}

	if (nullptr == mousePointer_)
	{
		mousePointer_ = CreateActor<Mouse>(ObjectOrder::Mouse, "WorldMapMousePointer");
	}

    stageUI_ = CreateActor<StageUI>();
	stageUI_->SetUI(UIType::World);
}

void WorldMapLevel::Update(float _deltaTime)
{
	UpdateCameraMovement(_deltaTime);

	CheckNextStageSelection();

	SoundCheck();
}

void WorldMapLevel::End()
{
}

void WorldMapLevel::LevelStartEvent()
{
	this->GetMainCamera()->SetFarZ(10000.f);
	stageUI_->SetUI(UIType::World);
	Player::GetPlayerInst()->Off();
	
	SoundPlayer::BGMPlay_->ChangeBgm("MapSelectionForest.wav");
}

void WorldMapLevel::UpdateCameraMovement(float _deltaTime)
{
	static const float cameraSpeed = 500.f;
	//�������� �ѹ� �����ؼ� ��� ����ϴٰ� ���� �������� �Ҹ��ų ���̹Ƿ� ���ý���ƽ���� ����.

	float4 Pos = GetMainCameraActorTransform().GetWorldPosition();

	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraLeft"))
	{
		Pos += GetMainCameraActorTransform().GetLeftVector() * cameraSpeed * _deltaTime;

		if (Pos.x <= 500.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetLeftVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraRight"))
	{
		Pos += GetMainCameraActorTransform().GetRightVector() * cameraSpeed * _deltaTime;

		if (Pos.x >= 1250.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
			GetMainCameraActorTransform().GetRightVector() * cameraSpeed * _deltaTime);
	}


	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraFoward"))
	{

		Pos += float4(
			0.f,
			sinf(30.f * GameEngineMath::DegreeToRadian),
			cosf(30.f * GameEngineMath::DegreeToRadian)
		) * cameraSpeed * _deltaTime;

		if (Pos.z >= -810.f)
		{
			return;
		}

		GetMainCameraActorTransform().SetLocalMove(
			float4(
				0.f,
				sinf(30.f * GameEngineMath::DegreeToRadian),
				cosf(30.f * GameEngineMath::DegreeToRadian)
			) * cameraSpeed * _deltaTime
		);
	}

	if (true == GameEngineInput::GetInst()->IsPressed("WorldCameraBack"))
	{
		Pos += float4(
			0.f,
			-sinf(30.f * GameEngineMath::DegreeToRadian),
			-cosf(30.f * GameEngineMath::DegreeToRadian)
		) * cameraSpeed * _deltaTime;

		if (Pos.z <= -2300.f)
		{
			return;
		}


		GetMainCameraActorTransform().SetLocalMove(
			float4(0.f,
				-sinf(30.f * GameEngineMath::DegreeToRadian),
				-cosf(30.f * GameEngineMath::DegreeToRadian)
			) * cameraSpeed * _deltaTime
		);
	}
}

void WorldMapLevel::CheckNextStageSelection()
{
	static const float4 renderPivot = float4(0.f, 0.5f, 0.f, 0.f);
	//�������� �ѹ� �����ؼ� ��� ����ϴٰ� ���� �������� �Ҹ��ų ���̹Ƿ� ���ý���ƽ���� ����.
	//�ٸ� �����Ǻ��� �ʿ��ϴٸ� ������ ��.

	std::list<std::shared_ptr<StageObject>> nextLevelList = stageCreater_->GetCurLevel()->GetNextLevelList();

	for (std::list<std::shared_ptr<StageObject>>::iterator iter = nextLevelList.begin();
		iter != nextLevelList.end(); ++iter)
	{
		if (false == mousePointer_->IsPointing((*iter)->GetWorldWorldMatrix(), renderPivot))
		{
			continue;
		}

		if (true == GameEngineInput::GetInst()->IsDown("Click"))
		{
			stageCreater_->SendPlayerToNextStage(*iter);
		}
	}
}

void WorldMapLevel::SoundCheck()
{
	float4 renderPivot = float4(0.f, 0.5f, 0.f, 0.f);
	std::list<std::shared_ptr<StageObject>> nextLevelList = stageCreater_->GetCurLevel()->GetNextLevelList();

	for (std::list<std::shared_ptr<StageObject>>::iterator iter = nextLevelList.begin();
		iter != nextLevelList.end(); ++iter)
	{
		if (true == mousePointer_->IsPointing((*iter)->GetWorldWorldMatrix(), renderPivot))
		{
			if (soundCheck_ == false)
			{
				GameEngineSound::SoundPlayOneshot("Menu_Cycle.wav");
			}
			soundCheck_ = true;
			return;
		}
	
	}

	soundCheck_ = false;
}
