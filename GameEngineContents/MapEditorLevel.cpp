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
	// �׸��ϳ� ������ ���� �ϳ� ����� �� �ʹ����� ������ ���̱� ������ ����� �ý��ϴ�.
	GameEngineDebug::DrawTexture("PivotTile.png", { 0,0,0,1 }, { 0,0,0 });
}

void MapEditorLevel::End()
{
}

void MapEditorLevel::LevelStartEvent()
{
	// 2�� �ε� �ȵǵ���
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
