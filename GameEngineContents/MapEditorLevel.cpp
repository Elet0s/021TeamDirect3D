#include "PreCompile.h"
#include "MapEditorLevel.h"
#include "TileMapActor.h"
#include "LoginUI.h"
#include "Enums.h"
#include "MapEditorWindow.h"
#include "GlobalContentsValue.h"

MapEditorLevel::MapEditorLevel(): tileMap_(nullptr)
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::Start()
{
	tileMap_ = CreateActor<TileMapActor>(ObjectOrder::TileMap);
}

void MapEditorLevel::Update(float _deltaTime)
{
	// 그림하나 띄우려고 액터 하나 만드는 건 너무나도 귀찮은 일이기 때문에 만들어 봤습니다.
	GameEngineDebug::DrawTexture("PivotTile.png", { 0,0,0,1 }, { 0,0,0 });
}

void MapEditorLevel::End()
{
}

void MapEditorLevel::LevelStartEvent()
{
	// 2번 로딩 안되도록
	if (nullptr == GameEngineTexture::Find("PivotTile.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Texture");
		Dir.MoveToChild("Map");

		std::vector<GameEngineFile> res = Dir.GetAllFiles();

		for (size_t i = 0; i < res.size(); i++)
		{
			GameEngineTexture::Load(res[i].GetFullPath());
		}

		
		MapEditorWindow* TileMapEditorGUI = GameEngineGUI::CreateGUIWindow<MapEditorWindow>("MapEditorGui", this);
		TileMapEditorGUI->tileMap_ = this->tileMap_;
	}
}
