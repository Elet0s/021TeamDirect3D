#include "PreCompile.h"
#include "FieldRenderingActor.h"

FieldRenderingActor::FieldRenderingActor()
	: tileSize_(128.f),
	tileCount_((GameEngineWindow::GetScale().IX() / 128) + 4, (GameEngineWindow::GetScale().IY() / 128) + 4),
	tileRenderer_(nullptr)
{
}

FieldRenderingActor::~FieldRenderingActor()
{
}

void FieldRenderingActor::Start()
{
	tileRenderer_ = &GetLevel()->GetMainCamera()->GetInstancingRenderer("TileRenderer");
	tileRenderer_->Initialize(
		static_cast<size_t>(tileCount_.IX() * tileCount_.IY()),
		"Rect",
		"TileTextureInstancing"
	);
	tileRenderer_->SetTexture("Tex", "grassTexture.png");
	tileRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");
	tileRenderer_->SetAllUnitsWorldScale( 128, 128, 1 );


	int unitIndex = 0;
	for (int y = 0; y < tileCount_.IY(); ++y)
	{
		for (int x = 0; x < tileCount_.IX(); ++x)
		{
			tileRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().frameData_.posX = 0.f;
			tileRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().frameData_.posY = 0.f;
			tileRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().frameData_.sizeX = 1.f;
			tileRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().frameData_.sizeY = 1.f;
			tileRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().pivotPos_ = float4::Zero;
			tileRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
				(tileSize_ * static_cast<float>(x)) - (tileSize_ * 7.5f),
				(tileSize_ * static_cast<float>(y)) - (tileSize_ * 5.f),
				0.f
			);
			++unitIndex;
		}
	}



}

void FieldRenderingActor::Update(float _deltaTime)
{
	float4 actorWorldPosition = this->GetTransform().GetWorldPosition();

	int unitIndex = 0;
	for (int y = 0; y < tileCount_.IY(); ++y)
	{
		for (int x = 0; x < tileCount_.IX(); ++x)
		{
			if (tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x
				<= actorWorldPosition.x - (tileSize_ * (tileCount_.x * 0.5f)))
			{
				tileRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x + (tileSize_ * tileCount_.x),
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y,
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			else if (tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x
				>= actorWorldPosition.x + (tileSize_ * (tileCount_.x * 0.5f)))
			{
				tileRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x - (tileSize_ * tileCount_.x),
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y,
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}

			if (tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y
				<= actorWorldPosition.y - (tileSize_ * (tileCount_.y * 0.5f)))
			{
				tileRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x,
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y + (tileSize_ * tileCount_.y),
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			else if (tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y
				>= actorWorldPosition.y + (tileSize_ * (tileCount_.y * 0.5f)))
			{
				tileRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().x,
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().y - (tileSize_ * tileCount_.y),
					tileRenderer_->GetInstancingUnit(unitIndex).GetWorldPosition().z
				);
			}
			++unitIndex;
		}
	}
}

void FieldRenderingActor::End()
{
}
