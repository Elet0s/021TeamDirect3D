#include "PreCompile.h"
#include "FieldRenderingActor.h"

FieldRenderingActor::FieldRenderingActor()
	: tileSize_(256.f),
	windowSize_(GameEngineWindow::GetScale()),
	tileCountXY_((GameEngineWindow::GetScale().IX() / 256) + 4, (GameEngineWindow::GetScale().IY() / 256) + 4),
	tileCount_(tileCountXY_.IX() * tileCountXY_.IY()),
	fieldRenderer_(nullptr)
{
}

FieldRenderingActor::~FieldRenderingActor()
{
}

void FieldRenderingActor::Start()
{
	InitializeFieldObjects(50000, float4(60000, 60000));
	InitializeFieldRenderer();


}

void FieldRenderingActor::Update(float _deltaTime)
{
	float4 thisWorldPosition = this->GetTransform().GetWorldPosition();

	UpdateTilePosition(thisWorldPosition);

	UpdateFieldObjectInfos(thisWorldPosition);


}

void FieldRenderingActor::End()
{
}

void FieldRenderingActor::InitializeFieldObjects(
	size_t _fieldObjectCount,
	const float4& _fieldSize,
	std::function<void(const std::vector<FieldObjectData>& _fieldObjects)> _objectPlacementFunc /*= nullptr*/
)
{
	fieldObjectAtlasDatas_.resize(8);

	//긴 잡초.
	fieldObjectAtlasDatas_[0].SetData(AtlasData(0.f, 0.f, 1.f, 0.25f, 0.f, 0.f));

	//긴 돌.
	fieldObjectAtlasDatas_[1].SetData(AtlasData(0.f, 0.25f, 1.f, 0.25f, 0.f, 0.f));

	//잡초 0.
	fieldObjectAtlasDatas_[2].SetData(AtlasData(0.f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//잡초 1.
	fieldObjectAtlasDatas_[3].SetData(AtlasData(0.25f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//잡초 2.
	fieldObjectAtlasDatas_[4].SetData(AtlasData(0.5f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//돌 0.
	fieldObjectAtlasDatas_[5].SetData(AtlasData(0.75f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//돌 1.
	fieldObjectAtlasDatas_[6].SetData(AtlasData(0.f, 0.75f, 0.25f, 0.25f, 0.f, 0.f));

	//돌 2.
	fieldObjectAtlasDatas_[7].SetData(AtlasData(0.25f, 0.75f, 0.25f, 0.25f, 0.f, 0.f));



	allFieldObjectDataVector_.reserve(_fieldObjectCount);

	renderingFieldObjectDataVector_.reserve(_fieldObjectCount / 5);

	if (nullptr == _objectPlacementFunc)
	{
		for (size_t i = 0; i < _fieldObjectCount; ++i)
		{
			float4 randomWorldPosition = float4(
				GameEngineRandom::mainRandom_.RandomFloat(-_fieldSize.HX(), _fieldSize.HX()),
				GameEngineRandom::mainRandom_.RandomFloat(-_fieldSize.HY(), _fieldSize.HY()),
				-4.f
			);
			//필드 오브젝트들끼리 겹치는건 전혀 신경쓰지 않은 배치 방식.
			//나중에 고칠 것.

			int randomIndex = GameEngineRandom::mainRandom_.RandomInt(0, 7);

			float4 worldScale = float4::Zero;
			if (1 >= randomIndex)
			{
				worldScale = float4(256, 64);
			}
			else
			{
				worldScale = float4(64, 64);
			}

			allFieldObjectDataVector_.push_back(
				FieldObjectData(
					randomWorldPosition,
					worldScale,
					randomIndex
				)
			);
		}
	}
	else
	{
		_objectPlacementFunc(this->allFieldObjectDataVector_);
	}
}

void FieldRenderingActor::InitializeFieldRenderer()
{
	fieldRenderer_ = &GetLevel()->GetMainCamera()->GetInstancingRenderer("FieldRenderer");
	fieldRenderer_->Initialize(
		static_cast<size_t>(tileCountXY_.IX() * tileCountXY_.IY() + 50),
		"Rect",
		"MultiTexturesInstancing"
	);
	fieldRenderer_->SetTexture2DArray("Inst_Textures", "Field");
	fieldRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");
	//fieldRenderer_->SetAllUnitsWorldScale(256, 256, 1);
	//그려질 필요없는 렌더유닛들이 그려지는 버그 발생.

	int unitIndex = 0;
	for (int y = 0; y < tileCountXY_.IY(); ++y)
	{
		for (int x = 0; x < tileCountXY_.IX(); ++x)
		{
			fieldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.f);
			//NewGrassTexture.png 전체를 다 그린다.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(1);
			//NewGrassTexture.png는 1번으로 삽입되어 있다.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(256, 256, 1);
			//타일을 그리는 인스턴싱유닛들만 크기 설정을 해준다.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
				(tileSize_ * static_cast<float>(x)) - (tileSize_ * 7.5f),
				(tileSize_ * static_cast<float>(y)) - (tileSize_ * 5.f),
				0.f
			);	//타일 렌더하는 인스턴싱유닛들의 위치 설정.

			++unitIndex;
		}
	}
}

void FieldRenderingActor::UpdateTilePosition(const float4& _thisWorldPosition)
{
	int unitIndex = 0;
	for (int y = 0; y < tileCountXY_.IY(); ++y)
	{
		for (int x = 0; x < tileCountXY_.IX(); ++x)
		{
			if (fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x
				<= _thisWorldPosition.x - (tileSize_ * (tileCountXY_.x * 0.5f)))
			{
				fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x + (tileSize_ * tileCountXY_.x),
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y,
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			else if (fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x
				>= _thisWorldPosition.x + (tileSize_ * (tileCountXY_.x * 0.5f)))
			{
				fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x - (tileSize_ * tileCountXY_.x),
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y,
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}

			if (fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y
				<= _thisWorldPosition.y - (tileSize_ * (tileCountXY_.y * 0.5f)))
			{
				fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x,
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y + (tileSize_ * tileCountXY_.y),
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			else if (fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y
				>= _thisWorldPosition.y + (tileSize_ * (tileCountXY_.y * 0.5f)))
			{
				fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x,
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y - (tileSize_ * tileCountXY_.y),
					fieldRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			++unitIndex;
		}
	}
}

void FieldRenderingActor::UpdateFieldObjectInfos(const float4& _thisWorldPosition)
{
	renderingFieldObjectDataVector_.clear();
	//뭐가 들어있든지 일단 전부 비운다. 
	//capacity는 변하면 안된다.

	for (FieldObjectData& singleObjectData : allFieldObjectDataVector_)
	{
		if (singleObjectData.worldPosition_.x > _thisWorldPosition.x + (windowSize_.HX() * 1.5f))
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.x < _thisWorldPosition.x - (windowSize_.HX() * 1.5f))
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.y > _thisWorldPosition.y + (windowSize_.HY() * 1.5f))
		{
			continue;
		}
		else if (singleObjectData.worldPosition_.y < _thisWorldPosition.y - (windowSize_.HY() * 1.5f))
		{
			continue;
		}

		renderingFieldObjectDataVector_.push_back(&singleObjectData);
	}//윈도우크기 1.5배 안에 들어온 오브젝트들만 renderingFieldObjectDataVector_에 삽입한다.


	int objectIndex = 0;
	for (size_t unitIndex = static_cast<size_t>(tileCount_);
		unitIndex < fieldRenderer_->GetUnitCount(); ++unitIndex)
	{
		if (objectIndex >= renderingFieldObjectDataVector_.size())
		{
			//윈도우 안에 들어온 오브젝트들보다 인스턴싱유닛의 숫자가 많으면 그냥 무시하고 진행한다.
			//인스턴싱유닛도 온오프기능 만들어서 꺼야 하나?? 그게 최적화에 큰 도움이 되나??
			//fieldRenderer_->GetInstancingUnit(unitIndex).SetRenderingOff();
			//continue;
			//->렌더링오프된 인스턴싱유닛들이 이전에 그렸던 텍스처들이 윈도우에 그대로 남아서 
			// 카메라를 따라다니는것 같은 현상이 발생한다.
			break;
		}

		fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(
			renderingFieldObjectDataVector_[objectIndex]->worldScale_
		);

		fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			renderingFieldObjectDataVector_[objectIndex]->worldPosition_
		);
		//renderingFieldObjectDataVector_가 가진 트랜스폼데이터를 인스턴싱유닛들에게 입력한다.

		fieldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(
			fieldObjectAtlasDatas_[renderingFieldObjectDataVector_[objectIndex]->atlasDataIndex_]
		);
		//renderingFieldObjectDataVector_가 가진 아틀라스데이터를 인스턴싱유닛들에게 입력한다.


		fieldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(0);
		//MapObjects.png는 0번으로 삽입되어 있음.

		//fieldRenderer_->GetInstancingUnit(unitIndex).SetRenderingOn();

		++objectIndex;
	}


#ifdef _DEBUG
	if (objectIndex < renderingFieldObjectDataVector_.size())
	{
		MsgBoxAssert("인스턴싱유닛의 숫자가 모자라서 필드 오브젝트들을 다 그리지 못했습니다.");
		return;
	}
	//릴리즈모드에서 이런 일이 생기면 그냥 무시하고 진행한다.
#endif // DEBUG

}
