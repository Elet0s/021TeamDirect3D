#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "StageLevel.h"
#include "TestLevel.h"
#include "ShaderTestLevel.h"
#include "GameEngineStatusWindow.h"
#include "SoundPlayer.h"


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

	GameEngineFont::Load("궁서");
	GameEngineFont::Load("Free Pixel");

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	PrepareContentsShader("ContentsResources");

	//GameEngineDebug::ConsoleOpen(); 콘솔창이 필요하면 복원.

	//RTTI(Run-Time Type information): 런타임 형식 정보. 
	//프로그램 실행 중간에 데이터 타입을 받아오는 방법. 

	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<TestLevel>("Test");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<ShaderTestLevel>("ShaderTestLevel");
	//ChangeLevel("Test");
	ChangeLevel("ShaderTestLevel");
	//ChangeLevel("WorldMap");


	//GameEngineTime::SetFrameLimit(60);
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _deltaTime)
{
}

void ContentsCore::End()
{
	if (SoundPlayer::BGMPlay_ != nullptr)
	{
		SoundPlayer::BGMPlay_->Destory();
	}

	
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
		MsgBoxAssertString(std::string(_dirName) + "그런 이름의 디렉토리가 없습니다. 디렉토리명을 확인하세요.");
		return;
	}


	std::shared_ptr<GameEngineMaterial> newContentsMaterial0
		= GameEngineMaterial::Create("Test");
	newContentsMaterial0->SetVertexShader("Test.hlsl");
	newContentsMaterial0->SetPixelShader("Test.hlsl");
	newContentsMaterial0->SetRasterizer("EngineRasterizer");
	newContentsMaterial0->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial0->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newContentsMaterial1
		= GameEngineMaterial::Create("Texture2DShadow");
	newContentsMaterial1->SetVertexShader("Texture2DShadow.hlsl");
	newContentsMaterial1->SetPixelShader("Texture2DShadow.hlsl");
	newContentsMaterial1->SetRasterizer("EngineRasterizer");
	newContentsMaterial1->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial1->SetDepthStencil_OutputMerger("EngineBaseDepth");

}
