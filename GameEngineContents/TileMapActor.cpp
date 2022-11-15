#include "PreCompile.h"
#include "TileMapActor.h"
#include <string>
#include <GameEngineBase/GameEngineRandom.h>
#include "MyTileMapRenderer.h"
#include "Texture2DShadowRenderer.h"

TileMapActor::TileMapActor(): tileRenderer_(nullptr)
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Start()
{
	int Count = 0;
	tileRenderer_ = CreateComponent<MyTileMapRenderer>();

	ResourceLoad();

	for (size_t i = 0; i < 120; i++)
	{
		float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(0, 40));
		float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 42));
		std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
		TextureRenderer->SetRenderingOrder(42-static_cast<int>(Y));
		X *= 32.0f;
		Y *= 16.0f;

		std::shared_ptr<Texture2DShadowRenderer> shadowRenderer 
			= CreateComponent<Texture2DShadowRenderer>();

		if (i < 70)
		{
			TextureRenderer->SetFolderTextureToIndex("Grass", GameEngineRandom::mainRandom_.RandomInt(0, 2));
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}
		else if (i < 80)
		{
			TextureRenderer->SetFolderTextureToIndex("Grass", 3);
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}

		else if (i < 117)
		{
			TextureRenderer->SetFolderTextureToIndex("Rock", GameEngineRandom::mainRandom_.RandomInt(0, 2));
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -300.f });
		}
		else if (i < 120)
		{
			TextureRenderer->SetFolderTextureToIndex("Rock", 3);
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -300.f });
			Count++;
		}

		shadowRenderer->SetTextureRenderer(TextureRenderer);
	}
	Count;
}

void TileMapActor::Update(float _deltaTime)
{
	
}

void TileMapActor::End()
{
}


void TileMapActor::ResourceLoad()
{
	if (nullptr == GameEngineFolderTexture::Find("Rock"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Texture");
		Dir.MoveToChild("Map");
		Dir.MoveToChild("Rock");


		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
}