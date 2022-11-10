#include "PreCompile.h"
#include "TileMapActor.h"
#include <string>
#include <GameEngineBase/GameEngineRandom.h>
#include "MyTileMapRenderer.h"

TileMapActor::TileMapActor(): tileRenderer_(nullptr)
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Start()
{
	tileRenderer_ = CreateComponent<MyTileMapRenderer>();

	for (size_t i = 0; i < 80; i++)
	{
		float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(0, 40));
		float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 42));
		X *= 32.0f;
		Y *= 16.0f;
		if (i < 70)
		{
			GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
			TextureRenderer->SetFolderTextureToIndex("Grass", GameEngineRandom::mainRandom_.RandomInt(0, 2));
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}
		else if (i > 75)
		{
			GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
			TextureRenderer->SetFolderTextureToIndex("Grass", 3);
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}
	}



	
	

}

void TileMapActor::Update(float _deltaTime)
{
	
}

void TileMapActor::End()
{
}
