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

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExistChildDirectory("GameEngineResources");
		Dir.MoveToChild("Resources");
		Dir.MoveToChild("Rogue_Genesia");
		Dir.MoveToChild("Animator"); 
		Dir.MoveToChild("IntroAnimation");
		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("IntroAnimation.FBX"));

		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNodes();

		int a = 0;

	}

	//GameEngineDebug::ConsoleOpen(); �ܼ�â�� �ʿ��ϸ� ����.

	//RTTI(Run-Time Type information): ��Ÿ�� ���� ����. 
	//���α׷� ���� �߰��� ������ Ÿ���� �޾ƿ��� ���. 

	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<TestLevel>("Test");
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
