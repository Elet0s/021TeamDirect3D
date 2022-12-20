#include "PreCompile.h"
#include "WorldMapRanderingActor.h"

WorldMapRanderingActor::WorldMapRanderingActor()
	: tileSize_(256.f),
	windowSize_(GameEngineWindow::GetScale()),
	tileCountXY_(8.0f ,10.f),
	tileCount_(tileCountXY_.IX()* tileCountXY_.IY()),
	worldRenderer_(nullptr)
{
}

WorldMapRanderingActor::~WorldMapRanderingActor()
{
}

void WorldMapRanderingActor::Start()
{
	
}

void WorldMapRanderingActor::Update(float _deltaTime)
{
	float4 thisWorldPosition = this->GetTransform().GetWorldPosition();
	UpdateFieldObjectInfos(thisWorldPosition);
}

void WorldMapRanderingActor::End()
{
}

void WorldMapRanderingActor::Initialize(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount
)
{
	InitializeFieldObjects(_totalFieldObjectCount, _objectInWindowCount);
	InitializeFieldRenderer(_objectInWindowCount);
}

void WorldMapRanderingActor::InitializeFieldObjects(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount
)
{
	
	worldObjectAtlasDatas_.resize(8);

	//���� .
	worldObjectAtlasDatas_[0].SetData(AtlasData(0.f, 0.f, 1.f, 0.5f, 0.f, 0.0f));

	allWorldObjectDataVector_.reserve(_totalFieldObjectCount);

	renderingFieldObjectDataVector_.reserve(_objectInWindowCount);

	
	for (size_t y = 0; y < 2; y++)
	{
		for (size_t x = 0; x < 2 * y + 1; x++)
		{
			//�ʵ������Ʈ ��ġ ����.
			float4 tilePos = this->GetTransform().GetWorldPosition();
			float Ranf = GameEngineRandom::mainRandom_.RandomFloat(10.f, 30.f);
			float RanfX = GameEngineRandom::mainRandom_.RandomFloat(10.f, 50.f);
			tilePos.x += 64.f + x * 64.f - 64.f * y + RanfX;
			tilePos.y += (0 - 64.f * y) * sinf(10.f * GameEngineMath::DegreeToRadian) + 64.f;
			tilePos.z += (0 - 64.f * y) * cosf(10.f * GameEngineMath::DegreeToRadian);


			float4 worldScale = float4(256.f, 128.f);

			allWorldObjectDataVector_.push_back(
				WorldObjectData(
					tilePos,
					worldScale,
					0
				)
			);
		}
	}
}

void WorldMapRanderingActor::InitializeFieldRenderer(size_t _objectInWindowCount)
{
	worldRenderer_ = GetLevel()->GetMainCamera()->GetInstancingRenderer("WorldRenderer");
	worldRenderer_->Initialize(
		static_cast<size_t>(tileCount_) + _objectInWindowCount,
		"Rect",
		"MultiTexturesInstancing"
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
			tilePos.y += -tileSize_ * sinf(10.f * GameEngineMath::DegreeToRadian) * y;
			tilePos.z += -tileSize_ * cosf(10.f * GameEngineMath::DegreeToRadian) * y;

			worldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.0f);
			//NewGrassTexture.png ��ü�� �� �׸���.

			worldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(2);
			//NewGrassTexture.png�� 2������ ���ԵǾ� �ִ�.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(tileSize_, tileSize_, 1.f);
			//Ÿ���� �׸��� �ν��Ͻ����ֵ鸸 ũ�� ������ ���ش�.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(tilePos);	//Ÿ�� �����ϴ� �ν��Ͻ����ֵ��� ��ġ ����.

			worldRenderer_->GetInstancingUnit(unitIndex).SetWorldRotation(float4(80.f,0.f,0.f));

			++unitIndex;
		}
	}
}


void WorldMapRanderingActor::UpdateFieldObjectInfos(const float4& _thisWorldPosition)
{
	renderingFieldObjectDataVector_.clear();
	//���� ����ֵ��� �ϴ� ���� ����. 
	//capacity�� ���ϸ� �ȵȴ�.
	float4 CameraPos = GetLevel()->GetMainCamera().get()->GetTransform().GetWorldPosition() - float4(640.f, -360.f);

	for (WorldObjectData& singleObjectData : allWorldObjectDataVector_)
	{
		if (singleObjectData.worldPosition_.x > CameraPos.x + 1280.f)
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.x < CameraPos.x)
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.y > CameraPos.y)
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.y < CameraPos.y - 2560.f)
		{
			continue;

		}
		if (singleObjectData.worldPosition_.z > CameraPos.z + 1500.f)
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
		

		worldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(3);


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