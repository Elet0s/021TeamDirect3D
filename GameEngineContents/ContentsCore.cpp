#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "StageLevel.h"
#include "ClearLevel.h"
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
	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	if (false == GameEngineInput::GetInst()->IsKey("Click"))
	{
		GameEngineInput::GetInst()->CreateKey("Click", VK_LBUTTON);
	}

	LoadContentsResource();
	LoadContentsShader();

	//GameEngineDebug::ConsoleOpen(); 콘솔창이 필요하면 복원.

	//RTTI(Run-Time Type information): 런타임 형식 정보. 
	//프로그램 실행 중간에 데이터 타입을 받아오는 방법. 

	CreateLevel<TitleLevel>("Title");
	CreateLevel<TestLevel>("Test");
	CreateLevel<StageLevel>("Stage");
	CreateLevel<ShaderTestLevel>("ShaderTestLevel");
	CreateLevel<ClearLevel>("Clear");
	CreateLevel<WorldMapLevel>("WorldMap");
	ChangeLevel("WorldMap");
	//ChangeLevel("ShaderTestLevel");
	//ChangeLevel("Clear");


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
		SoundPlayer::BGMPlay_->Destroy();
	}	
}

void ContentsCore::LoadContentsShader()
{
	GameEngineDirectory contentsShaderDir;
	if (true == contentsShaderDir.MoveParentToExistChildDirectory("ContentsResources"))
	{
		contentsShaderDir.MoveToChild("ContentsResources");
		contentsShaderDir.MoveToChild("Shader");
		std::vector<GameEngineFile> contentsShaderPath = contentsShaderDir.GetAllFiles(".hlsl");

		for (GameEngineFile& path : contentsShaderPath)
		{
			GameEngineShader::AutoCompile(path.GetFullPath());
		}
	}
	else
	{
		MsgBoxAssertString(std::string("ContentsResources") + "그런 이름의 디렉토리가 없습니다. 디렉토리명을 확인하세요.");
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

	std::shared_ptr<GameEngineMaterial> newContentsMaterial2
		= GameEngineMaterial::Create("SingleTextureInstancing");
	newContentsMaterial2->SetVertexShader("SingleTextureInstancing.hlsl");
	newContentsMaterial2->SetPixelShader("SingleTextureInstancing.hlsl");
	newContentsMaterial2->SetRasterizer("EngineRasterizer");
	newContentsMaterial2->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial2->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newContentsMaterial3
		= GameEngineMaterial::Create("MultiTexturesInstancing");
	newContentsMaterial3->SetVertexShader("MultiTexturesInstancing.hlsl");
	newContentsMaterial3->SetPixelShader("MultiTexturesInstancing.hlsl");
	newContentsMaterial3->SetRasterizer("EngineRasterizer");
	newContentsMaterial3->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial3->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial4
		= GameEngineMaterial::Create("MultiTexturesInstShadow");
	newContentsMaterial4->SetVertexShader("MultiTexturesInstShadow.hlsl");
	newContentsMaterial4->SetPixelShader("MultiTexturesInstShadow.hlsl");
	newContentsMaterial4->SetRasterizer("EngineRasterizer");
	newContentsMaterial4->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial4->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial5
		= GameEngineMaterial::Create("DeferredInstanceRendering");
	newContentsMaterial5->SetVertexShader("DeferredInstanceRendering.hlsl");
	newContentsMaterial5->SetPixelShader("DeferredInstanceRendering.hlsl");
	newContentsMaterial5->SetRasterizer("EngineRasterizer");
	newContentsMaterial5->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial5->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial6
		= GameEngineMaterial::Create("DeferredInstanceShadowRendering");
	newContentsMaterial6->SetVertexShader("DeferredInstanceShadowRendering.hlsl");
	newContentsMaterial6->SetPixelShader("DeferredInstanceShadowRendering.hlsl");
	newContentsMaterial6->SetRasterizer("EngineRasterizer");
	newContentsMaterial6->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial6->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial7
		= GameEngineMaterial::Create("DeferredShadowRendering");
	newContentsMaterial7->SetVertexShader("DeferredShadowRendering.hlsl");
	newContentsMaterial7->SetPixelShader("DeferredShadowRendering.hlsl");
	newContentsMaterial7->SetRasterizer("EngineRasterizer");
	newContentsMaterial7->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial7->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial8
		= GameEngineMaterial::Create("DeferredRendering");
	newContentsMaterial8->SetVertexShader("DeferredRendering.hlsl");
	newContentsMaterial8->SetPixelShader("DeferredRendering.hlsl");
	newContentsMaterial8->SetRasterizer("EngineRasterizer");
	newContentsMaterial8->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial8->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newContentsMaterial9
		= GameEngineMaterial::Create("MonsterInstanceRendering");
	newContentsMaterial9->SetVertexShader("MonsterInstanceRendering.hlsl");
	newContentsMaterial9->SetPixelShader("MonsterInstanceRendering.hlsl");
	newContentsMaterial9->SetRasterizer("EngineRasterizer");
	newContentsMaterial9->SetBlend_OutputMerger("AlphaBlend");
	newContentsMaterial9->SetDepthStencil_OutputMerger("EngineBaseDepth");

}

void ContentsCore::LoadContentsResource()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Actor");
		Dir.MoveToChild("BossMonster");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Actor");
		Dir.MoveToChild("Player");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("InstancingTest");
		Dir.MoveToChild("Field");
		GameEngineTexture2DArray::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("InstancingTest");
		Dir.MoveToChild("Monster");
		GameEngineTexture2DArray::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("Map");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("GameObjectUI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("MouseUI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("PlayerUI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("SoulCardUI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFiles();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	GameEngineDirectory soundDir;
	soundDir.MoveParentToExistChildDirectory("ContentsResources");
	soundDir.MoveToChild("ContentsResources");
	soundDir.MoveToChild("Sound");

	std::vector<GameEngineFile> sound = soundDir.GetAllFiles();
	for (GameEngineFile& SoundPlay : sound)
	{
		GameEngineSound::LoadResource(SoundPlay);
	}

	GameEngineTexture::Cut("PlayerIdle.png", 11, 1);
	GameEngineTexture::Cut("PlayerRun.png", 10, 1);

	GameEngineFont::Load("궁서");
	GameEngineFont::Load("맑음");
	GameEngineFont::Load("Free Pixel");
}
