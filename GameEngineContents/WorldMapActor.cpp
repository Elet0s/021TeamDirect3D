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

	if (nullptr == GameEngineFolderTexture::Find("Grass"))
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistChildDirectory("ContentsResources");
			Dir.MoveToChild("ContentsResources");
			Dir.MoveToChild("Texture");
			Dir.MoveToChild("Map");
			Dir.MoveToChild("Grass");


			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
		
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistChildDirectory("ContentsResources");
			Dir.MoveToChild("ContentsResources");
			Dir.MoveToChild("Texture");
			//Dir.MoveToChild("Map");


			std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}
		
	}

	for (size_t y = 0; y < 5; y++)
	{
		for (size_t x = 0; x < 2 * y + 1; x++)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
			float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
			tilePos.x += 64.f + x * 64.f - 64.f * y + RanfX;
			tilePos.y += (-128.f * sinf(10.f * GameEngineMath::DegreeToRadian) * 18) + (-40.f * sinf(10.f * GameEngineMath::DegreeToRadian) * y) + (Ranf * sinf(10.f * GameEngineMath::DegreeToRadian));
			tilePos.z += (-128.f * cosf(10.f * GameEngineMath::DegreeToRadian) * 18) + (-40.f * cosf(10.f * GameEngineMath::DegreeToRadian) * y) + (Ranf * cosf(10.f * GameEngineMath::DegreeToRadian));
			
			if (tilePos.x <= 0.f)
			{
				continue;
			}
			std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
			TextureRenderer->SetPivot(PivotMode::Bot);
			TextureRenderer->SetTexture("tree_Group_A.png");
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(tilePos);
		}
	}

	//for (size_t y = 0; y < 20; y++)
	//{
	//	for (size_t x = 0; x < 20-y; x++)
	//	{
	//		float4 tilePos = this->GetTransform().GetWorldPosition();
	//		tilePos.x += x * 2.f * 128.f;
	//		tilePos.y += (-128.f * sinf(10.f * GameEngineMath::DegreeToRadian) * y);
	//		tilePos.z += (-128.f * cosf(10.f * GameEngineMath::DegreeToRadian) * y);
	//		
	//		std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
	//		TextureRenderer->SetPivot(PivotMode::Bot);
	//		TextureRenderer->SetTexture("tree_Group_A.png");
	//		TextureRenderer->ScaleToTexture();
	//		TextureRenderer->GetTransform().SetWorldPosition(tilePos);
	//	}
	//	for (size_t x = 0; x < 20-y; x++)
	//	{
	//		float4 tilePos = this->GetTransform().GetWorldPosition();
	//		tilePos.x += (2.f * x + 1) * 128.f;
	//		tilePos.y += (-128.f * sinf(10.f * GameEngineMath::DegreeToRadian) * y) + (64.f *sinf(10.f *GameEngineMath::DegreeToRadian));
	//		tilePos.z += (-128.f * cosf(10.f * GameEngineMath::DegreeToRadian) * y) + (64.f * cosf(10.f * GameEngineMath::DegreeToRadian));

	//		std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
	//		TextureRenderer->SetPivot(PivotMode::Bot);
	//		TextureRenderer->SetTexture("tree_Group_A.png");
	//		TextureRenderer->ScaleToTexture();
	//		TextureRenderer->GetTransform().SetWorldPosition(tilePos);
	//	}
	//}

	{
		std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
		TextureRenderer->SetPivot(PivotMode::LeftTop);
		TextureRenderer->SetTexture("TestWall.png");
		TextureRenderer->GetTransform().SetWorldScale(float4{ 300000000, 2560 });
		TextureRenderer->GetTransform().SetWorldPosition(float4{ -10000,1280 });
	}

	
}

void WorldMapActor::Update(float _deltaTime)
{

}

void WorldMapActor::End()
{
}
