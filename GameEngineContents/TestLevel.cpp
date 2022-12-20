#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"
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

TestLevel::TestLevel(): fieldRenderingActor_(nullptr)
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	//tileCameraActor_ = CreateActor<GameEngineCameraActor>(11, "TileCamera");
	//tileCameraActor_->GetCameraComponent()->SetCameraOrder(CameraOrder::TileCamera);
	//tileCameraActor_->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	//this->PushCamera(tileCameraActor_->GetCameraComponent(), CameraOrder::TileCamera);


	GameEngineDirectory monsterDir;
	monsterDir.MoveParentToExistChildDirectory("ContentsResources");
	monsterDir.MoveToChild("ContentsResources");
	monsterDir.MoveToChild("Actor");
	monsterDir.MoveToChild("Monster");

	std::vector<GameEngineFile> monsterTexture = monsterDir.GetAllFiles();
	for (size_t i = 0; i < monsterTexture.size(); i++)
	{
		GameEngineTexture::Load(monsterTexture[i].GetFullPath());
	}


	GameEngineDirectory skillDir;
	skillDir.MoveParentToExistChildDirectory("ContentsResources");
	skillDir.MoveToChild("ContentsResources");
	skillDir.MoveToChild("Actor");
	skillDir.MoveToChild("Skill");

	std::vector<GameEngineFile> skillTexture = skillDir.GetAllFiles();
	for (size_t i = 0; i < skillTexture.size(); i++)
	{
		GameEngineTexture::Load(skillTexture[i].GetFullPath());
	}

	GameEngineDirectory WeaponDir;
	WeaponDir.MoveParentToExistChildDirectory("ContentsResources");
	WeaponDir.MoveToChild("ContentsResources");
	WeaponDir.MoveToChild("Actor");
	WeaponDir.MoveToChild("Skill");
	WeaponDir.MoveToChild("Weapon");

	std::vector<GameEngineFile> WeaponTexture = WeaponDir.GetAllFiles();
	for (size_t i = 0; i < WeaponTexture.size(); i++)
	{
		GameEngineTexture::Load(WeaponTexture[i].GetFullPath());
	}
		
	GameEngineDirectory uiTextureDir;
	uiTextureDir.MoveParentToExistChildDirectory("ContentsResources");
	uiTextureDir.MoveToChild("ContentsResources");
	uiTextureDir.MoveToChild("Texture");
	uiTextureDir.MoveToChild("UI");
	std::vector<GameEngineFile> uiTexture = uiTextureDir.GetAllFiles();

	for (size_t i = 0; i < uiTexture.size(); i++)
	{
		GameEngineTexture::Load(uiTexture[i].GetFullPath());
	}
		
	GameEngineDirectory soundDir;
	soundDir.MoveParentToExistChildDirectory("ContentsResources");
	soundDir.MoveToChild("ContentsResources");
	soundDir.MoveToChild("Sound");

	std::vector<GameEngineFile> sound = soundDir.GetAllFiles();
	for (GameEngineFile& soundPlay : sound)
	{
		GameEngineSound::LoadResource(soundPlay);
	}

	//tilemaps_.resize(3);

	//for (size_t i = 0; i < 3; i++)
	//{
	//	tilemaps_[i].resize(3);
	//	for (size_t j = 0; j < 3; j++)
	//	{
	//		tilemaps_[i][j] = CreateActor<TileMapActor>();
	//		tilemaps_[i][j]->GetTransform().SetWorldPosition(float4(1280.f * static_cast<float>(j), -(640.f * static_cast<float>(i))));
	//		tilemaps_[i][j]->tileRenderer_->CreateTileMap(10, 5, { 128, 128 }, "GrassTexture.png");
	//		tilemaps_[i][j]->tileRenderer_->SetPivot(PivotMode::LeftTop);
	//	}
	//}

	fieldRenderingActor_ = CreateActor<FieldRenderingActor>();
	fieldRenderingActor_->Initialize(
		550,
		50,
		float4(100, 100),
		60.f
	);
	//fieldRenderingActor_->Initialize(
	//	750,
	//	700,
	//	float4(6000, 6000)
	//);
	fieldRenderingActor_->GetTransform().SetLocalScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldPosition(float4::Zero);


	std::shared_ptr< GameEngineCollision> col = GetMainCameraActor()->CreateComponent<GameEngineCollision>();
	col->GetTransform().SetWorldScale(float4{ 1280,720 });
	col->ChangeOrder(ObjectOrder::Camera);
	col->SetDebugSetting(CollisionType::CT_OBB2D, float4::Zero);

	if (true == Player::GetPlayerWeakPtr().expired())
	{
		Player::CreatePlayer(this, { 0, 0 });
	}

	{
		std::shared_ptr<PlayerUI> NewPlayerUI = CreateActor<PlayerUI>(ObjectOrder::UI);
	}

	Monster::ReserveMonsters(this, 10);

	//Monster::CreateMonster<Brown>(this, 10);
	//Monster::CreateMonster<Green>(this, 10);
	//Monster::CreateMonster<NormalGoblin>(this, 10);
	Monster::CreateMonster<RedFlyingEyes>(this, 10);
	//Monster::CreateMonster<FlyingEyes>(this, 10);

	//Monster::SummonMonster<Brown>(this, 10);
	//Monster::SummonMonster<Green>(this, 10);
	//Monster::SummonMonster<NormalGoblin>(this, 10);
	Monster::SummonMonster<RedFlyingEyes>(this, 10);
	//Monster::SummonMonster<FlyingEyes>(this, 10);

	
	std::shared_ptr<Mouse> NewMouse = CreateActor<Mouse>(ObjectOrder::Mouse);

	
	//ShowCursor(false); 마우스 감추기
	CreateActor<TimeActor>();
	CreateActor<StageUI>()->SoulCoinRenderersOff();

}

void TestLevel::Update(float _DeltaTime)
{						
	//tileCameraActor_->GetTransform().SetWorldPosition(GetMainCameraActorTransform().GetWorldPosition());
	//GameEngineCore::engineThreadPool_.Work(std::bind(&TestLevel::UpdateWorld, this));
	//UpdateWorld();

	PlayerMoveCamera();

	fieldRenderingActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
}

void TestLevel::LevelStartEvent()
{
	SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1);
}
void TestLevel::LevelEndEvent()
{
	SoundPlayer::BGMPlay_->Stop();
}

void TestLevel::CreateMapAndCamraMove()
{																		

}

//void TestLevel::UpdateWorld()
//{
//	float4 CenterPos = tilemaps_[1][1]->GetTransform().GetWorldPosition() + float4(640.f, -320.f);
//	float4 PlayerPos = Player::GetPlayerInst()->GetTransform().GetWorldPosition();
//
//	int Dir = -1;
//
//	if (CenterPos.x + 640.f < PlayerPos.x)
//	{
//		Dir = 0;
//	}
//	else if (CenterPos.x - 640.f > PlayerPos.x)
//	{
//		Dir = 1;
//	}
//	else if (CenterPos.y + 320.f < PlayerPos.y)
//	{
//		Dir = 2;
//	}
//	else if (CenterPos.y - 320.f > PlayerPos.y)
//	{
//		Dir = 3;
//	}
//
//	MoveWorld(Dir);
//}
//
//
//void TestLevel::MoveWorld(int _Dir)
//{
//	PlayerMoveCamera();
//	MouseMoveCamera();
//	std::vector<std::vector<std::shared_ptr<TileMapActor>>> CopyTiles_;
//	CopyTiles_.resize(3);
//	for (size_t y = 0; y < CopyTiles_.size(); y++)
//	{
//		CopyTiles_[y].resize(3);
//	}
//
//
//	switch (_Dir)
//	{
//	case 0:   // 오른쪽으로 갔을때
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			tilemaps_[y][0]->GetTransform().SetWorldPosition(float4(tilemaps_[y][2]->GetTransform().GetWorldPosition().x + 1280, tilemaps_[y][2]->GetTransform().GetWorldPosition().y));
//		}
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			for (int x = 0; x < CopyTiles_[y].size(); x++)
//			{
//				int CX = x + 1;
//				if (CX == 3)
//				{
//					CopyTiles_[y][x] = tilemaps_[y][CX - 3];
//				}
//				else
//				{
//					CopyTiles_[y][x] = tilemaps_[y][CX];
//				}
//			}
//		}
//		break;
//	case 1:
//		// 왼쪽으로 갔을때
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			tilemaps_[y][2]->GetTransform().SetWorldPosition(float4(tilemaps_[y][0]->GetTransform().GetWorldPosition().x - 1280, tilemaps_[y][2]->GetTransform().GetWorldPosition().y));
//		}
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			for (int x = 0; x < CopyTiles_[y].size(); x++)
//			{
//				int CX = x - 1;
//				if (CX < 0)
//				{
//					CopyTiles_[y][x] = tilemaps_[y][2];
//				}
//				else
//				{
//					CopyTiles_[y][x] = tilemaps_[y][CX];
//				}
//			}
//		}
//		break;
//	case 2: // 위로 갔을 때
//		for (int x = 0; x < CopyTiles_.size(); x++)
//		{
//			tilemaps_[2][x]->GetTransform().SetWorldPosition(float4(tilemaps_[0][x]->GetTransform().GetWorldPosition().x, tilemaps_[0][x]->GetTransform().GetWorldPosition().y + 640));
//		}
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			for (int x = 0; x < CopyTiles_[y].size(); x++)
//			{
//				int CY = y - 1;
//				if (CY < 0)
//				{
//					CopyTiles_[y][x] = tilemaps_[2][x];
//				}
//				else
//				{
//					CopyTiles_[y][x] = tilemaps_[CY][x];
//				}
//			}
//		}
//		
//		break;
//	case 3: // 아래로 갔을 때
//		for (int x = 0; x < CopyTiles_.size(); x++)
//		{
//			tilemaps_[0][x]->GetTransform().SetWorldPosition(float4(tilemaps_[2][x]->GetTransform().GetWorldPosition().x, tilemaps_[2][x]->GetTransform().GetWorldPosition().y - 640));
//		}
//		for (int y = 0; y < CopyTiles_.size(); y++)
//		{
//			for (int x = 0; x < CopyTiles_[y].size(); x++)
//			{
//				int CY = y + 1;
//				if (CY == 3)
//				{
//					CopyTiles_[y][x] = tilemaps_[CY - 3][x];
//				}
//				else
//				{
//					CopyTiles_[y][x] = tilemaps_[CY][x];
//				}
//			}
//		}
//		break;
//	default:
//		return;
//	}
//
//	tilemaps_.swap(CopyTiles_);
//
//	
//}

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
	float4 CheckPos = GetMainCamera()->GetMouseWorldPositionToActor() - Player::GetPlayerInst()->GetTransform().GetWorldPosition();


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
		else if (CheckPos.x < -180.f)
		{
			MouseDir.y = -100.f;
		}
	

	GetMainCameraActor()->GetTransform().SetWorldMove(float4((MouseDir.x) * Time, (MouseDir.y) * Time));

}


