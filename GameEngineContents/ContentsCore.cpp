#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "StageLevel.h"
#include "TestLevel.h"
#include "ShaderTestLevel.h"


ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
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

	GameEngineFont::Load("�ü�");

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	PrepareContentsShader("ContentsResources");

	//GameEngineDebug::ConsoleOpen(); �ܼ�â�� �ʿ��ϸ� ����.

	//RTTI(Run-Time Type information): ��Ÿ�� ���� ����. 
	//���α׷� ���� �߰��� ������ Ÿ���� �޾ƿ��� ���. 

	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<TestLevel>("Test");
	CreateLevel<ShaderTestLevel>("ShaderTest");
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

void ContentsCore::PrepareContentsShader(const std::string_view& _dirName)
{
	GameEngineDirectory contentsShaderDir;
	if (true == contentsShaderDir.MoveParentToExistChildDirectory(_dirName))
	{
		contentsShaderDir.MoveToChild(_dirName);
		contentsShaderDir.MoveToChild("Shader");
		std::vector<GameEngineFile> contentsShaderPath = contentsShaderDir.GetAllFiles(".hlsl");

		for (GameEngineFile& path : contentsShaderPath)
		{
			GameEngineShader::AutoCompile(path.GetFullPath());
		}
	}
	else
	{
		MsgBoxAssertString(std::string(_dirName) + "�׷� �̸��� ���丮�� �����ϴ�. ���丮���� Ȯ���ϼ���.");
		return;
	}


	std::shared_ptr<GameEngineMaterial> newContentsMaterial0
		= GameEngineMaterial::Create("Test");
	newContentsMaterial0->SetVertexShader("Test.hlsl");
	newContentsMaterial0->SetPixelShader("Test.hlsl");
	newContentsMaterial0->SetRasterizer("EngineRasterizer");
	newContentsMaterial0->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial0->SetDepthStencil_OutputMerger("EngineBaseDepth");


}
