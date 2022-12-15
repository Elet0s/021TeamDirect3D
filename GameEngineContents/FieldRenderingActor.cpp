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
	//Initialize() �Լ����� ��¥ �ʱ�ȭ�� �ϹǷ� ���⼭ �� �� ����.
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

void FieldRenderingActor::Initialize(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount,
	const float4& _totalFieldSize,
	float _diffusionDegree /*= 1.f*/
)
{
	InitializeFieldObjects(_totalFieldObjectCount, _objectInWindowCount, _totalFieldSize, _diffusionDegree);
	InitializeFieldRenderer(_objectInWindowCount);
}

void FieldRenderingActor::InitializeFieldObjects(
	size_t _totalFieldObjectCount,
	size_t _objectInWindowCount,
	const float4& _totalFieldSize,
	float _diffusionDegree /*= 1.f*/
)
{
	fieldObjectAtlasDatas_.resize(8);

	//�� ����.
	fieldObjectAtlasDatas_[0].SetData(AtlasData(0.f, 0.f, 1.f, 0.25f, 0.f, 0.f));

	//�� ��.
	fieldObjectAtlasDatas_[1].SetData(AtlasData(0.f, 0.25f, 1.f, 0.25f, 0.f, 0.f));

	//���� 0.
	fieldObjectAtlasDatas_[2].SetData(AtlasData(0.f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//���� 1.
	fieldObjectAtlasDatas_[3].SetData(AtlasData(0.25f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//���� 2.
	fieldObjectAtlasDatas_[4].SetData(AtlasData(0.5f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//�� 0.
	fieldObjectAtlasDatas_[5].SetData(AtlasData(0.75f, 0.5f, 0.25f, 0.25f, 0.f, 0.f));

	//�� 1.
	fieldObjectAtlasDatas_[6].SetData(AtlasData(0.f, 0.75f, 0.25f, 0.25f, 0.f, 0.f));

	//�� 2.
	fieldObjectAtlasDatas_[7].SetData(AtlasData(0.25f, 0.75f, 0.25f, 0.25f, 0.f, 0.f));

	allFieldObjectDataVector_.reserve(_totalFieldObjectCount);

	renderingFieldObjectDataVector_.reserve(_objectInWindowCount);

	for (size_t i = 0; i < _totalFieldObjectCount; ++i)
	{
		//�ʵ������Ʈ ��ġ ����.
		float4 randomWorldPosition = float4(
			GameEngineRandom::mainRandom_.RandomFloat(-_totalFieldSize.HX(), _totalFieldSize.HX()) * _diffusionDegree,
			GameEngineRandom::mainRandom_.RandomFloat(-_totalFieldSize.HY(), _totalFieldSize.HY()) * _diffusionDegree,
			-4.f
		);
		//�ʵ� ������Ʈ�鳢�� ��ġ�°� ���� �Ű澲�� ���� ��ġ ���.
		//���߿� ��ĥ ��.

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

void FieldRenderingActor::InitializeFieldRenderer(size_t _objectInWindowCount)
{
	fieldRenderer_ = GetLevel()->GetMainCamera()->GetInstancingRenderer("FieldRenderer");
	fieldRenderer_->Initialize(
		static_cast<size_t>(tileCount_) + _objectInWindowCount,
		"Rect",
		"MultiTexturesInstancing"
	);
	fieldRenderer_->SetTexture2DArray("Inst_Textures", "Field");
	fieldRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");
	//fieldRenderer_->SetAllUnitsWorldScale(256, 256, 1);
	//�׷��� �ʿ���� �������ֵ��� 256, 256 ũ��� �׷����� ���� �߻�.

	int unitIndex = 0;
	for (int y = 0; y < tileCountXY_.IY(); ++y)
	{
		for (int x = 0; x < tileCountXY_.IX(); ++x)
		{
			fieldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.f);
			//NewGrassTexture.png ��ü�� �� �׸���.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(1);
			//NewGrassTexture.png�� 1������ ���ԵǾ� �ִ�.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(tileSize_, tileSize_, 1.f);
			//Ÿ���� �׸��� �ν��Ͻ����ֵ鸸 ũ�� ������ ���ش�.

			fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
				(tileSize_ * static_cast<float>(x)) - (tileSize_ * 7.5f),
				(tileSize_ * static_cast<float>(y)) - (tileSize_ * 5.f),
				0.f
			);	//Ÿ�� �����ϴ� �ν��Ͻ����ֵ��� ��ġ ����.

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
				> _thisWorldPosition.x + (tileSize_ * (tileCountXY_.x * 0.5f)))
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
				> _thisWorldPosition.y + (tileSize_ * (tileCountXY_.y * 0.5f)))
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
	//���� ����ֵ��� �ϴ� ���� ����. 
	//capacity�� ���ϸ� �ȵȴ�.

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
	}//������ũ�� 1.5�� �ȿ� ���� ������Ʈ�鸸 renderingFieldObjectDataVector_�� �����Ѵ�.


	int objectIndex = 0;
	for (size_t unitIndex = static_cast<size_t>(tileCount_);
		unitIndex < fieldRenderer_->GetUnitCount(); ++unitIndex)
	{
		if (objectIndex >= renderingFieldObjectDataVector_.size())
		{
			//������ �ȿ� ���� ������Ʈ�麸�� �ν��Ͻ������� ���ڰ� ������ �׳� �����ϰ� �����Ѵ�.
			//�ν��Ͻ����ֵ� �¿������ ���� ���� �ϳ�?? �װ� ����ȭ�� ū ������ �ǳ�??
			//fieldRenderer_->GetInstancingUnit(unitIndex).SetRenderingOff();
			//continue;
			//->������������ �ν��Ͻ����ֵ��� ������ �׷ȴ� �ؽ�ó���� �����쿡 �״�� ���Ƽ� 
			// ī�޶� ����ٴϴ°� ���� ������ �߻��Ѵ�.
			break;
		}

		fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(
			renderingFieldObjectDataVector_[objectIndex]->worldScale_
		);

		fieldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
			renderingFieldObjectDataVector_[objectIndex]->worldPosition_
		);
		//renderingFieldObjectDataVector_�� ���� Ʈ�����������͸� �ν��Ͻ����ֵ鿡�� �Է��Ѵ�.

		fieldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(
			fieldObjectAtlasDatas_[renderingFieldObjectDataVector_[objectIndex]->atlasDataIndex_]
		);
		//renderingFieldObjectDataVector_�� ���� ��Ʋ�󽺵����͸� �ν��Ͻ����ֵ鿡�� �Է��Ѵ�.

		fieldRenderer_->GetInstancingUnit(unitIndex).SetTextureIndex(0);
		//MapObjects.png�� 0������ ���ԵǾ� ����.

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
