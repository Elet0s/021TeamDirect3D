#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"
#include "TimeActor.h"
#include "StageUI.h"
#include "Player.h"
#include "GlobalContentsValue.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{


	if (nullptr == GameEngineTexture::Find("grassTexture.png"))
	{
		{
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
		}

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

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistChildDirectory("ContentsResources");
			Dir.MoveToChild("ContentsResources");
			Dir.MoveToChild("Texture");
			Dir.MoveToChild("Map");
			Dir.MoveToChild("Grass");

		
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}
	
	
	tilemap = CreateActor<TileMapActor>();
	tilemap->tileRenderer_->CreateTileMap(20, 20, { 128,128 }, "grassTexture.png");
	tilemap->tileRenderer_->SetPivot(PivotMode::LeftTop);
	
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
			Monster* BlackEyes = CreateActor<Monster>(ObjectOrder::Monster);
			Monster_.push_back(BlackEyes);
		}
	}

	CreateActor<TimeActor>();
	CreateActor<StageUI>()->SoulCoinRenderersOff();
}

void TestLevel::Update(float _DeltaTime)
{

}


