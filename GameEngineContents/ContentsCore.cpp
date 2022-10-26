#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "StageLevel.h"
#include "TestLevel.h"
#include"LoginLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineFont::Load("궁서");

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	//GameEngineDebug::ConsoleOpen(); 콘솔창이 필요하면 복원.

	//RTTI(Run-Time Type information): 런타임 형식 정보. 
	//프로그램 실행 중간에 데이터 타입을 받아오는 방법. 

	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<TestLevel>("Test");
	CreateLevel<LoginLevel>("Login");
	ChangeLevel("WorldMap");


	//GameEngineTime::SetFrameLimit(60);
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _deltaTime)
{
}

void ContentsCore::End()
{
}
