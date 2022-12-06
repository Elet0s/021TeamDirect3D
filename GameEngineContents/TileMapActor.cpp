#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "TileMapActor.h"
#include "TreeObject.h"
#include <string>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "MyTileMapRenderer.h"
#include "Texture2DShadowRenderer.h"

TileMapActor::TileMapActor(): tileRenderer_(nullptr), renderOn(true)
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Start()
{
	int Count = 0;
	renderers_.resize(120);
	trees_.resize(3);
	shadowRenderers_.resize(120);
	tileRenderer_ = CreateComponent<MyTileMapRenderer>();
	tileRenderer_->SetLevel(GetLevel());
	col_ = CreateComponent<GameEngineCollision>();
	col_->GetTransform().SetWorldScale(float4{ 1280,640,1 });
	col_->GetTransform().SetWorldMove(float4{ 640,-320,1 });
	col_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0.f,0.f,0.f,0.0f));
	col_->ChangeOrder(ObjectOrder::Sector);
	//col_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());

	ResourceLoad();

	{
		for (size_t i = 0; i < 120; i++)
		{
			float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 40));
			float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 40));
			renderers_[i] = CreateComponent<GameEngineTextureRenderer>();
			renderers_[i]->SetRenderingOrder(42 - static_cast<int>(Y));
			renderers_[i]->SetScaleRatio(0.8f);

			shadowRenderers_[i] = CreateComponent<Texture2DShadowRenderer>();

			if (i < 70)
			{
				X *= 32.0f;
				Y *= 16.0f;
				renderers_[i]->SetFolderTextureToIndex("Grass", GameEngineRandom::mainRandom_.RandomInt(0, 2));
				renderers_[i]->ScaleToTexture();
				renderers_[i]->GetTransform().SetLocalPosition(float4{ X,-Y, -10.f });
			}
			else if (i < 80)
			{
				X *= 32.0f;
				Y *= 16.0f;
				renderers_[i]->SetFolderTextureToIndex("Grass", 3);
				renderers_[i]->ScaleToTexture();
				renderers_[i]->GetTransform().SetLocalPosition(float4{ X,-Y, -10.f });
			}

			else if (i < 117)
			{
				X *= 32.0f;
				Y *= 16.0f;
				renderers_[i]->SetFolderTextureToIndex("Rock", GameEngineRandom::mainRandom_.RandomInt(0, 2));
				renderers_[i]->ScaleToTexture();
				renderers_[i]->GetTransform().SetLocalPosition(float4{ X,-Y, -10.f });
			}
			else if (i < 120)
			{
				Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 10));
				X *= 32.0f;
				Y *= 64.0f;
				renderers_[i]->SetFolderTextureToIndex("Rock", 3);
				renderers_[i]->ScaleToTexture();
				renderers_[i]->GetTransform().SetLocalPosition(float4{ X,-Y, -10.f });
				Count++;
			}

			shadowRenderers_[i]->SetTextureRenderer(renderers_[i]);
		}
	}
	
	{
		for (size_t i = 0; i < trees_.size();i++)
		{
			trees_[i] = GetLevel()->CreateActor<TreeObject>();
			trees_[i]->SetParent(shared_from_this());
			while (true == trees_[i]->GetCheckCol()->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::TreeObject, CollisionType::CT_OBB2D))
			{
				float X = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 20));
				float Y = static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 10));
				X *= 64;
				Y *= 64;
				trees_[i]->GetRenderer()->SetRenderingOrder(42 - static_cast<int>(Y));
				trees_[i]->GetTransform().SetLocalPosition(float4{ X,-Y, -300.f });
			}
		}
	}
}

void TileMapActor::Update(float _deltaTime)
{
	if (true == renderOn)
	{
		float4 CameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition() - float4(750.f, -400.f);
		for (size_t i = 0; i < 120; ++i)
		{
			float4 Pos = renderers_[i]->GetTransform().GetWorldPosition();

			if ((Pos.IX() >= CameraPos.IX() && Pos.IX() <= CameraPos.IX() + 1500.f)
				&& (Pos.IY() <= CameraPos.IY() + 200.f && Pos.IY() >= CameraPos.IY() -800.f))
			
			{
				renderers_[i]->On();
				shadowRenderers_[i]->On();
			}
		}
	}

	{
		float4 CameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition() - float4(750.f, -400.f);
		for (size_t i = 0; i < 120; ++i)
		{
			float4 Pos = renderers_[i]->GetTransform().GetWorldPosition();

			if ((Pos.IX() < CameraPos.IX() || Pos.IX() > CameraPos.IX() + 1500.f)
				|| (Pos.IY() > CameraPos.IY() || Pos.IY() < CameraPos.IY() - 800.f))

			{
				renderers_[i]->Off();
				shadowRenderers_[i]->Off();
			}
		}

	}

	if (true == renderOn &&
		false == col_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Camera, CollisionType::CT_OBB2D))
	{
		renderOn = false;
		for (size_t i = 0; i < 120; ++i)
		{
			renderers_[i]->Off();
			shadowRenderers_[i]->Off();
		}

		tileRenderer_->Off();
	}
	else if (false == renderOn 
		&&true == col_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Camera, CollisionType::CT_OBB2D))
	{
		renderOn = true;
		tileRenderer_->On();
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