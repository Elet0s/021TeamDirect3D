#include "PreCompile.h"
#include "WorldMapRenderingActor.h"

WorldMapRenderingActor::WorldMapRenderingActor()
	: tileSize_(256.f),
	windowSize_(GameEngineWindow::GetInst().GetScale()),
	tileCountXY_(8.0f ,10.f),
	tileCount_(tileCountXY_.IX()* tileCountXY_.IY()),
	worldRenderer_(nullptr)
{
}

WorldMapRenderingActor::~WorldMapRenderingActor()
{
}

void WorldMapRenderingActor::Start()
{
	{
		GameEngineTextureRenderer* TextureRenderer = CreateComponent<GameEngineTextureRenderer>();
		
		TextureRenderer->Initialize("TextureAtlas");
		TextureRenderer->SetTexture("FarGround.png");
		TextureRenderer->GetTransform().SetWorldScale(float4{ 10000, 2560 });
		TextureRenderer->GetTransform().SetWorldPosition(float4{ 1032,1000, 100 });
	}
}

void WorldMapRenderingActor::Update(float _deltaTime)
{
	float4 thisWorldPosition = this->GetTransform().GetWorldPosition();
	UpdateFieldObjectInfos(thisWorldPosition);
}

void WorldMapRenderingActor::End()
{
}

void WorldMapRenderingActor::Initialize(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount
)
{
	InitializeFieldObjects(_totalFieldObjectCount, _objectInWindowCount);
	InitializeFieldRenderer(_objectInWindowCount);
}

void WorldMapRenderingActor::InitializeFieldObjects(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount
)
{
	
	worldObjectAtlasDatas_.resize(8);

	//���� .
	worldObjectAtlasDatas_[0].SetData(AtlasData(0.f, 0.f, 1.f, 0.5f, 0.f, 0.0f));
	// ���� ����
	worldObjectAtlasDatas_[1].SetData(AtlasData(0.f, 0.5f, 1.f, 0.5f, 0.f, 0.0f));

	allWorldObjectDataVector_.reserve(_totalFieldObjectCount);

	renderingFieldObjectDataVector_.reserve(_objectInWindowCount);

	
	treeObejctSetting();
}

void WorldMapRenderingActor::InitializeFieldRenderer(size_t _objectInWindowCount)
{
	worldRenderer_ = &GetLevel()->GetMainCamera()->GetInstanceRenderer("0-WorldRenderer");
	worldRenderer_->Initialize(
		static_cast<size_t>(tileCount_) + _objectInWindowCount,
		"Rect",
		"DeferredInstanceRendering"
	);
	worldRenderer_->SetTexture2DArray("Inst_Textures", "Field");
	worldRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");
	//fieldRenderer_->SetAllUnitsWorldScale(256, 256, 1);
	//�׷��� �ʿ���� �������ֵ��� 256, 256 ũ��� �׷����� ���� �߻�.

	int unitIndex = 0;
	for (int y = 0; y < tileCountXY_.IY(); ++y)
	{
		for (int x = 0; x < tileCountXY_.IX(); ++x)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			tilePos.x += x * tileSize_;
			tilePos.y += -tileSize_ * sinf(30.f * GameEngineMath::DegreeToRadian) * y;
			tilePos.z += -tileSize_ * cosf(30.f * GameEngineMath::DegreeToRadian) * y;

			worldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.0f);
			//NewGrassTexture.png ��ü�� �� �׸���.

			worldRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(2);

			worldRenderer_->GetInstancingUnit(unitIndex).SetNormalMapTextureIndex(1);

			//NewGrassTexture.png�� 2������ ���ԵǾ� �ִ�.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(tileSize_, tileSize_, 1.f);
			//Ÿ���� �׸��� �ν��Ͻ����ֵ鸸 ũ�� ������ ���ش�.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(tilePos);	//Ÿ�� �����ϴ� �ν��Ͻ����ֵ��� ��ġ ����.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldRotation(float4(60.f,0.f,0.f));

			++unitIndex;
		}
	}
}


void WorldMapRenderingActor::UpdateFieldObjectInfos(const float4& _thisWorldPosition)
{
	renderingFieldObjectDataVector_.clear();
	//���� ����ֵ��� �ϴ� ���� ����. 
	//capacity�� ���ϸ� �ȵȴ�.
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition() - float4(640.f, -360.f);

	for (WorldObjectData& singleObjectData : allWorldObjectDataVector_)
	{
		float4 ObjectWorldPosition = singleObjectData.worldPosition_;

		ObjectWorldPosition *= GetLevel()->GetMainCamera()->GetViewMatrix();
		ObjectWorldPosition *= GetLevel()->GetMainCamera()->GetProjectionMatrix();

		ObjectWorldPosition /= ObjectWorldPosition.w;

		ObjectWorldPosition;


		if (ObjectWorldPosition.x > 1.5f)
		{
			continue;
		}
		else if (ObjectWorldPosition.x < -1.5f)
		{
			continue;
		}

		if (ObjectWorldPosition.y > 1.2f)
		{
			continue;
		}
		else if (ObjectWorldPosition.y < -1.2f)
		{
			continue;
		}
	
	
		else if (singleObjectData.worldPosition_.z < CameraPos.z)
		{
			continue;
		}
		
		renderingFieldObjectDataVector_.push_back(&singleObjectData);
	}

	for (size_t i = static_cast<size_t>(tileCount_); i < worldRenderer_->GetUnitCount(); i++)
	{
		worldRenderer_->GetInstancingUnit(i).SetWorldScale(
			float4::Zero
		);
	}

	int objectIndex = 0;

	for (size_t unitIndex = static_cast<size_t>(tileCount_);
		unitIndex < worldRenderer_->GetUnitCount(); ++unitIndex)
	{
		if (objectIndex >= renderingFieldObjectDataVector_.size())
		{
			break;
		}
		worldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(
			renderingFieldObjectDataVector_[objectIndex]->worldScale_
		);

		worldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			renderingFieldObjectDataVector_[objectIndex]->worldPosition_
		);
		
		worldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(
			worldObjectAtlasDatas_[renderingFieldObjectDataVector_[objectIndex]->atlasDataIndex_]
		);
		

		worldRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(3);


		++objectIndex;
	}




#ifdef _DEBUG
	if (objectIndex < renderingFieldObjectDataVector_.size())
	{
		MsgBoxAssert("�ν��Ͻ������� ���ڰ� ���ڶ� �ʵ� ������Ʈ���� �� �׸��� ���߽��ϴ�.");
		return;
	}
	//�������忡�� �̷� ���� ����� �׳� �����ϰ� �����Ѵ�.
#endif // DEBUG

}

void WorldMapRenderingActor::treeObejctSetting()
{
	float py = -512.f;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t y = 0; y < 5; y++)
		{
			for (size_t x = 0; x < (5 - y); x++)
			{
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += 0.f + x * 128.f - 64.f * (5 - y) + RanfX;
				tilePos.y += (py - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (py - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);;


				float4 worldScale = float4(256.f, 128.f);

				if (tilePos.x < -100.f || tilePos.y < -2132.f * sinf(30.f * GameEngineMath::DegreeToRadian))
				{
					continue;
				}
				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						0
					)
				);
			}
		}
		py -= 256.f;
		for (size_t y = 0; y < 5; y++)
		{
			for (size_t x = 0; x < y + 1; x++)
			{
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += 0.f + x * 128.f - 64.f * y + 1 + RanfX;
				tilePos.y += (py - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (py - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);;


				float4 worldScale = float4(256.f, 128.f);
				
				if (tilePos.x < -100.f || tilePos.z < -2432.0f * cosf(30.f * GameEngineMath::DegreeToRadian))
				{
					continue;
				}
				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						0
					)
				);
			}
		}
		py -= 256.f;
	}
	
	
	 py = -512.f;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t y = 0; y < 5; y++)
		{
			for (size_t x = 0; x < (5 - y); x++)
			{
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += 1800.f - x * 128.f + 64.f * (5 - y) - RanfX;
				tilePos.y += (py - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (py - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);;


				float4 worldScale = float4(256.f, 128.f);



				if (tilePos.x > 1900.f || tilePos.z < -2432.0f * cosf(30.f * GameEngineMath::DegreeToRadian))
				{
					continue;
				}
				
				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						0
					)
				);
			}
		}
		py -= 256.f;
		for (size_t y = 0; y < 5; y++)
		{
			for (size_t x = 0; x < y + 1; x++)
			{
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += 1800.f - x * 128.f + 64.f * y + 1 - RanfX;
				tilePos.y += (py - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (py - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);;


				float4 worldScale = float4(256.f, 128.f);

				if (tilePos.x > 1900.f || tilePos.z < -2432.0f * cosf(30.f * GameEngineMath::DegreeToRadian))
				{
					continue;
				}

				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						0
					)
				);
			}
		}
		py -= 256.f;
	}


	for (size_t y = 0; y < 7; y++)
	{
		for (size_t x = 0; x < 16; x++)
		{

			if (y % 2 != 0)
			{
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += -128.f + x * 128.f - RanfX;
				tilePos.y += (0 - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (0 - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);



				float4 worldScale = float4(256.f, 128.f);

				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						1
					)
				);
			}

			else
			{
				if (x > 14)
				{
					break;
				}
				float4 tilePos = this->GetTransform().GetWorldPosition();
				float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
				float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
				tilePos.x += 0 + x * 128.f + RanfX;
				tilePos.y += (0 - 64.f * y) * sinf(30.f * GameEngineMath::DegreeToRadian) + 64.f + Ranf * sinf(30.f * GameEngineMath::DegreeToRadian);
				tilePos.z += (0 - 64.f * y) * cosf(30.f * GameEngineMath::DegreeToRadian) + Ranf * cosf(30.f * GameEngineMath::DegreeToRadian);

				float4 worldScale = float4(256.f, 128.f);

				allWorldObjectDataVector_.push_back(
					WorldObjectData(
						tilePos,
						worldScale,
						1
					)
				);

			}		
		}
	}

}