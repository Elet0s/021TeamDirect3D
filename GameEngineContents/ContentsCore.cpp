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
	GameEngineFont::Load("�ü�");

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	//GameEngineDebug::ConsoleOpen(); �ܼ�â�� �ʿ��ϸ� ����.

	//RTTI(Run-Time Type information): ��Ÿ�� ���� ����. 
	//���α׷� ���� �߰��� ������ Ÿ���� �޾ƿ��� ���. 

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
