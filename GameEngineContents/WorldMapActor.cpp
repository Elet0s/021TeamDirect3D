#include "PreCompile.h"
#include "WorldMapActor.h"
#include <string>
#include <GameEngineBase/GameEngineRandom.h>
#include "MyWorldMapRenderer.h"

WorldMapActor::WorldMapActor() : worldmaprenderer_(nullptr)
{
}

WorldMapActor::~WorldMapActor()
{
}

void WorldMapActor::Start()
{
	worldmaprenderer_ = CreateComponent<MyWorldMapRenderer>();

	/*for (size_t i = 0; i < 100; i++)
	{
		float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(0, 80));
		float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(0, 80));
		X *= 32.0f;
		Y *= 32.0f;
		GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
		TextureRenderer->SetFolderTextureToIndex("Grass", GameEngineRandom::mainRandom_.RandomInt(0,2));
		TextureRenderer->ScaleToTexture();
		TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f});
	}*/
	if(nullptr == GameEngineFolderTexture::Find("Grass"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Texture");
		Dir.MoveToChild("Map");
		Dir.MoveToChild("Grass");


		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 20; x++)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			tilePos.x += x * 128.f;
			tilePos.y += -128.f * sinf(30.f * GameEngineMath::DegreeToRadian) * y;
			tilePos.z += -128.f * cosf(30.f * GameEngineMath::DegreeToRadian) * y;
			
			GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
			TextureRenderer->SetPivot(PivotMode::Bot);
			TextureRenderer->SetFolderTextureToIndex("Grass", 0);
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(tilePos);


		
		}
	}


}

void WorldMapActor::Update(float _deltaTime)
{

}

void WorldMapActor::End()
{
}
