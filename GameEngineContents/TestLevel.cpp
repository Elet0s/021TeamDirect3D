#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"

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
		GameEngineDirectory dir;
		dir.MoveParentToExistChildDirectory("ContentsResources");
		dir.MoveToChild("ContentsResources");
		dir.MoveToChild("Texture");
		dir.MoveToChild("Map");
		dir.MoveToChild("MapTile");

		GameEngineFolderTexture::Load(dir.GetFullPath());
	}

	tileMap_ = CreateActor<TileMapActor>();
	tileMap_->tileRenderer_->CreateTileMap(10, 10, { 128,128 }, "grassTexture.png");
	tileMap_->tileRenderer_->SetPivot(PivotMode::LeftTop);
	

	GetMainCameraActor()->GetTransform().SetWorldMove({ 640.f, -360.f });
}

void TestLevel::Update(float _DeltaTime)
{

}


