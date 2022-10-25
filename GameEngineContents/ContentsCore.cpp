#include "PreCompile.h"
#include "ContentsCore.h"
#include "LoginLevel.h"
#include "PlayLevel.h"
#include "TestLevel.h"
#include "MapEditorLevel.h"
#include "MetaLevel.h"

//#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{


	GameEngineDirectory contentsResourceDir;
	contentsResourceDir.MoveParentToExistChildDirectory("ContentsResources");
	contentsResourceDir.MoveToChild("ContentsResources");
	contentsResourceDir.MoveToChild("Texture");

	std::vector<GameEngineFile> contentsTextures = contentsResourceDir.GetAllFiles();

	for (size_t i = 0; i < contentsTextures.size(); i++)
	{
		GameEngineTexture::Load(contentsTextures[i].GetFullPath());
	}

	GameEngineFont::Load("궁서");



	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}


	//GameEngineDebug::ConsoleOpen(); 콘솔창이 필요하면 복원.

	//RTTI(Run-Time Type information): 런타임 형식 정보. 
	//프로그램 실행 중간에 데이터 타입을 받아오는 방법. 



	CreateLevel<LoginLevel>("Login");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<TestLevel>("TestLevel");
	CreateLevel<MapEditorLevel>("MapEditor");
	CreateLevel<MetaLevel>("MetaEditor");

	ChangeLevel("Login");


	GameEngineTime::SetFrameLimit(60);


	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _deltaTime)
{
}

void ContentsCore::End()
{
}
