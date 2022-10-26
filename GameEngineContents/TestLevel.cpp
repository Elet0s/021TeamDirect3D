#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"
#include "TimeActor.h"

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

	

	tileMap_ = CreateActor<TileMapActor>();
	tileMap_->tileRenderer_->CreateTileMap(20, 20, { 128,128 }, "grassTexture.png");
	tileMap_->tileRenderer_->SetPivot(PivotMode::LeftTop);
	
	CreateActor<TimeActor>();

	//GetMainCameraActor()->GetTransform().SetWorldMove({ 640.f, -360.f });
}

void TestLevel::Update(float _DeltaTime)
{

}


