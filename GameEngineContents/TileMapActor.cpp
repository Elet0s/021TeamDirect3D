#include "PreCompile.h"
#include "GlobalContentsValue.h"
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
	col_ = CreateComponent<GameEngineCollision>();
	col_->GetTransform().SetWorldScale(float4{ 100,100,1 });
	col_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0.f,0.f,0.f,0.8f));
	col_->ChangeOrder(ObjectOrder::Sector);
	col_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());

	ResourceLoad();

	for (size_t i = 0; i < 120; i++)
	{
		float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(0, 40));
		float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 42));
		std::shared_ptr<GameEngineTextureRenderer> TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
		TextureRenderer->SetRenderingOrder(42-static_cast<int>(Y));
	

		std::shared_ptr<Texture2DShadowRenderer> shadowRenderer 
			= CreateComponent<Texture2DShadowRenderer>();

		if (i < 70)
		{
			X *= 32.0f;
			Y *= 16.0f;
			TextureRenderer->SetFolderTextureToIndex("Grass", GameEngineRandom::mainRandom_.RandomInt(0, 2));
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}
		else if (i < 80)
		{
			X *= 32.0f;
			Y *= 16.0f;
			TextureRenderer->SetFolderTextureToIndex("Grass", 3);
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -500.f });
		}

		else if (i < 117)
		{
			X *= 32.0f;
			Y *= 16.0f;
			TextureRenderer->SetFolderTextureToIndex("Rock", GameEngineRandom::mainRandom_.RandomInt(0, 2));
			TextureRenderer->ScaleToTexture();
			TextureRenderer->GetTransform().SetWorldPosition(float4{ X,-Y, -300.f });
		}
		else if (i < 120)
		{
			X *= 32.0f;
			Y *= 64.0f;
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
	if (true == col_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Mouse, CollisionType::CT_OBB2D))
	{
		Off();
	}
	if (false == col_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Mouse, CollisionType::CT_OBB2D))
	{
		On();
	}
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

CollisionReturn TileMapActor::CameraCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	_This->GetRoot()->Off();

	return CollisionReturn::Stop;
}