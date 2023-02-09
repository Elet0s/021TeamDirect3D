#include "PreCompile.h"
#include "StageClearMap.h"

StageClearMap::StageClearMap() 
	: tileSize_(256.f),
	tileCountXY_((5, 5)),
	tileCount_(tileCountXY_.IX()* tileCountXY_.IY()),
	mapRenderer_(nullptr)
{
}

StageClearMap::~StageClearMap() 
{
}

void StageClearMap::Start()
{
	{
		GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();

		TextureRenderer->Initialize("TextureAtlas");
		TextureRenderer->SetTexture("FarGround.png");
		TextureRenderer->SetPivot(PivotMode::Bot);
		TextureRenderer->GetTransform().SetWorldScale(float4{1280, 640 });
		TextureRenderer->GetTransform().SetWorldPosition(float4{ 162,-100, 512 });
	}

	mapRenderer_ = &GetLevel()->GetMainCamera()->GetInstanceRenderer("0-mapRenderer");
	mapRenderer_->Initialize(
		100,
		"Rect",
		"MultiTexturesInstancing"
	);
	mapRenderer_->SetTexture2DArray("Inst_Textures", "Field");
	mapRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");

	int unitIndex = 0;
	for (int y = 0; y < tileCountXY_.IY(); ++y)
	{
		for (int x = 0; x < tileCountXY_.IX(); ++x)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			tilePos.x += x * 128.f;
			tilePos.y += 0;
			tilePos.z += 128.f * y;

			mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.f);

			mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(2);

			mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 128.f, 1.f);

			mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
				tilePos
			);
			mapRenderer_->GetInstancingUnit(unitIndex).SetWorldRotation(float4(90.f, 0.f, 0.f));
			++unitIndex;
		}
	}
	{ 
		float4 tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 128.f;
		tilePos.y += 128.f;
		tilePos.z += -62.f;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 0.5f, 1.0f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(6);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;

		tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 116.f;
		tilePos.y += 128.f;
		tilePos.z += -32;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 0.5f, 1.0f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(6);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;

		tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 90.f;
		tilePos.y += 128.f;
		tilePos.z += 0;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 0.5f, 1.0f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(6);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;

		tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 140.f;
		tilePos.y += 128.f;
		tilePos.z += 60;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 0.5f, 1.0f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(6);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;


		tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 250.f;
		tilePos.y += 128.f;
		tilePos.z += 260;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 0.5f, 1.0f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(6);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;

		tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132 + 140.f ;
		tilePos.y += 128.f;
		tilePos.z += 150.f;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.0f, 0.5f, 0.f, 0.0f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(3);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(512.f, 256.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;
	}
	

	for (size_t i = 0; i < 4; i++)
	{
		float4 tilePos = this->GetTransform().GetWorldPosition();
		tilePos.x += 132  + 70.f +i * 64.f;
		tilePos.y += 16.f;
		tilePos.z += -64.f;

		mapRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 0.25f, 0.f, 0.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(0);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(128.f, 64.f, 1.f);

		mapRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			tilePos
		);
		++unitIndex;
	}

	{
		GameEngineTextureRenderer* playerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		playerRenderer_->GetTransform().SetLocalScale(90, 90, 1);
		playerRenderer_->GetTransform().SetWorldPosition(190, 45.f, 30.f);
		playerRenderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.2f));
		playerRenderer_->ChangeFrameAnimation("PlayerIdle");
	}
}

void StageClearMap::Update(float _deltaTime)
{

}

void StageClearMap::End()
{

}