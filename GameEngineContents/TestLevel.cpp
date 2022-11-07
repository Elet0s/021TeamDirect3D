#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"
#include "TimeActor.h"
#include "StageUI.h"
#include "GlobalContentsValue.h"

TestLevel::TestLevel() //: tileCameraActor_(nullptr)
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



	if (true)
	{
		/*{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistChildDirectory("ContentsResources");
			Dir.MoveToChild("ContentsResources");
			Dir.MoveToChild("Texture");
			Dir.MoveToChild("Map");

			std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();

			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}*/

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistChildDirectory("ContentsResources");
			Dir.MoveToChild("ContentsResources");
			Dir.MoveToChild("Texture");
			Dir.MoveToChild("UI");
			std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();

			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}

		
	}

	tilemaps_.resize(3);

	for (size_t i = 0; i < 3; i++)
	{
		tilemaps_[i].resize(3);
		for (size_t j = 0; j < 3; j++)
		{
			tilemaps_[i][j] = CreateActor<TileMapActor>();
			tilemaps_[i][j]->GetTransform().SetWorldPosition(float4(640.f * static_cast<float>(j), -(640.f * static_cast<float>(i))));
			tilemaps_[i][j]->tileRenderer_->CreateTileMap(5, 5, { 128, 128 }, "grassTexture.png");
			tilemaps_[i][j]->tileRenderer_->SetPivot(PivotMode::LeftTop);
		}
	}


	if (nullptr == Player::GetMainPlayer())
	{

		Player* NewPlayer = CreateActor<Player>(ObjectOrder::Player);
		NewPlayer->SetLevelOverOn();
		NewPlayer->SetLevel(this);
		NewPlayer->GetTransform().SetWorldPosition({ 640.f, -360.f });
	}

	{
		for (size_t i = 0; i < 10; i++)
		{
			BlackEyes* NewMonster = CreateActor<BlackEyes>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
		for (size_t i = 0; i < 10; i++)
		{
			Brown* NewMonster = CreateActor<Brown>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
		for (size_t i = 0; i < 10; i++)
		{
			Green* NewMonster = CreateActor<Green>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
		for (size_t i = 0; i < 10; i++)
		{
			NormalGoblin* NewMonster = CreateActor<NormalGoblin>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
		for (size_t i = 0; i < 10; i++)
		{
			RedFlyingEyes* NewMonster = CreateActor<RedFlyingEyes>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
		for (size_t i = 0; i < 10; i++)
		{
			FlyingEyes* NewMonster = CreateActor<FlyingEyes>(ObjectOrder::Monster);
			Monster_.push_back(NewMonster);
		}
	}

	CreateActor<TimeActor>();
	CreateActor<StageUI>()->SoulCoinRenderersOff();
}

void TestLevel::Update(float _DeltaTime)
{						
	//tileCameraActor_->GetTransform().SetWorldPosition(GetMainCameraActorTransform().GetWorldPosition());
	//GameEngineCore::engineThreadPool_.Work(std::bind(&TestLevel::UpdateWorld, this));
	UpdateWorld();
}

void TestLevel::CreateMapAndCamraMove()
{																		

}

void TestLevel::UpdateWorld()
{
	float4 CenterPos = tilemaps_[1][1]->GetTransform().GetWorldPosition() + float4(320.f, -320.f);
	int Dir = -1;

	if (CenterPos.x + 320.f < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		Dir = 0;
	}
	else if (CenterPos.x - 320.f > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		Dir = 1;
	}
	else if (CenterPos.y + 320.f < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
	{
		Dir = 2;
	}
	else if (CenterPos.y - 320.f > GetMainCameraActor()->GetTransform().GetWorldPosition().y)
	{
		Dir = 3;
	}

	MoveWorld(Dir);
}

void TestLevel::MoveWorld(int _Dir)
{
	std::vector<std::vector<TileMapActor*>> CopyTiles_;
	CopyTiles_.resize(3);
	for (size_t y = 0; y < CopyTiles_.size(); y++)
	{
		CopyTiles_[y].resize(3);
	}


	switch (_Dir)
	{
	case 0:   // ¿À¸¥ÂÊÀ¸·Î °¬À»¶§
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			tilemaps_[y][0]->GetTransform().SetWorldPosition(float4(tilemaps_[y][2]->GetTransform().GetWorldPosition().x + 640, tilemaps_[y][2]->GetTransform().GetWorldPosition().y));
		}
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CX = x + 1;
				if (CX == 3)
				{
					CopyTiles_[y][x] = tilemaps_[y][CX - 3];
				}
				else
				{
					CopyTiles_[y][x] = tilemaps_[y][CX];
				}
			}
		}
		
		break;
	case 1:
		// ¿ÞÂÊÀ¸·Î °¬À»¶§
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			tilemaps_[y][2]->GetTransform().SetWorldPosition(float4(tilemaps_[y][0]->GetTransform().GetWorldPosition().x - 640, tilemaps_[y][2]->GetTransform().GetWorldPosition().y));
		}
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CX = x - 1;
				if (CX < 0)
				{
					CopyTiles_[y][x] = tilemaps_[y][2];
				}
				else
				{
					CopyTiles_[y][x] = tilemaps_[y][CX];
				}
			}
		}
		break;
	case 2: // À§·Î °¬À» ¶§
		for (int x = 0; x < CopyTiles_.size(); x++)
		{
			tilemaps_[2][x]->GetTransform().SetWorldPosition(float4(tilemaps_[0][x]->GetTransform().GetWorldPosition().x, tilemaps_[0][x]->GetTransform().GetWorldPosition().y + 640));
		}
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CY = y - 1;
				if (CY < 0)
				{
					CopyTiles_[y][x] = tilemaps_[2][x];
				}
				else
				{
					CopyTiles_[y][x] = tilemaps_[CY][x];
				}
			}
		}
		
		break;
	case 3: // ¾Æ·¡·Î °¬À» ¶§
		for (int x = 0; x < CopyTiles_.size(); x++)
		{
			tilemaps_[0][x]->GetTransform().SetWorldPosition(float4(tilemaps_[2][x]->GetTransform().GetWorldPosition().x, tilemaps_[2][x]->GetTransform().GetWorldPosition().y - 640));
		}
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CY = y + 1;
				if (CY == 3)
				{
					CopyTiles_[y][x] = tilemaps_[CY - 3][x];
				}
				else
				{
					CopyTiles_[y][x] = tilemaps_[CY][x];
				}
			}
		}
		break;
	default:
		return;
	}

	tilemaps_.swap(CopyTiles_);
}


