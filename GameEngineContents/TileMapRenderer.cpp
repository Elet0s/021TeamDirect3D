#include "PreCompile.h"
#include "TileMapRenderer.h" 

TileMapRenderer::TileMapRenderer(): tileTextures_(nullptr), tileX_(0), tileY_(0)
{
}

TileMapRenderer::~TileMapRenderer()
{
}

void TileMapRenderer::CreateIsometricTileMap(
	int _x, 
	int _y, 
	const float4& _tileScale,
	const std::string& _folderTexture, 
	int _defaultIndex /*= 0*/)
{
	tileTextures_ = GameEngineFolderTexture::Find(_folderTexture);

	if (nullptr == tileTextures_)
	{
		MsgBoxAssertString(_folderTexture + ": 존재하지 않는 폴더텍스처입니다.");
		return;
	}

	tileX_ = _x;
	tileY_ = _y;
	tileScale_ = _tileScale;
	tileScaleHalf_ = tileScale_.Half();

	allTiles_.resize(_y);
	for (size_t y = 0; y < allTiles_.size(); y++)
	{
		allTiles_[y].resize(_x);
		for (size_t x = 0; x < allTiles_[y].size(); x++)
		{
			allTiles_[y][x].tileIndex_ = static_cast<int>(_defaultIndex);
			allTiles_[y][x].tileImage_ = tileTextures_->GetTexture(_defaultIndex);
		}
	}
}

void TileMapRenderer::SetTileIndex(const float4& _pos, size_t _index)
{
	if (0 > _index)
	{
		return;
	}

	if (tileTextures_->GetTextureCount() <= _index)
	{
		return;
	}

	int tileIndexX = -1;
	int tileIndexY = -1;

	GetTileIndex(_pos, tileIndexX, tileIndexY);

	if (0 > tileIndexX)
	{
		return;
	}

	if (tileX_ <= tileIndexX)
	{
		return;
	}

	if (0 > tileIndexY)
	{
		return;
	}

	if (tileY_ <= tileIndexY)
	{
		return;
	}

	allTiles_[tileIndexY][tileIndexX].tileIndex_ = static_cast<int>(_index);
	allTiles_[tileIndexY][tileIndexX].tileImage_ = tileTextures_->GetTexture(_index);
}

void TileMapRenderer::GetTileIndex(const float4& _pos, int& _x, int& _y)
{
	float fX = (_pos.x / tileScaleHalf_.x + _pos.y / -tileScaleHalf_.y) / 2.f;
	float fY = (_pos.y / -tileScaleHalf_.y - _pos.x / tileScaleHalf_.x) / 2.f;

	_x = static_cast<int>(roundf(fX));
	_y = static_cast<int>(roundf(fY));
}

void TileMapRenderer::Render(float _deltaTime)
{
	static GameEngineTransform tileTransform;

	//tileTransform.SetLocalScale(this->tileScale_);
	tileTransform.SetViewMatrix(this->GetTransformData().viewMatrix_);
	tileTransform.SetProjectionMatrix(this->GetTransformData().projectionMatrix_);

	for (size_t y = 0; y < allTiles_.size(); y++)
	{
		for (size_t x = 0; x < allTiles_[y].size(); x++)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			tilePos.x = (x * tileScaleHalf_.x) + (y * -tileScaleHalf_.x);
			tilePos.y = (x * -tileScaleHalf_.y) + (y * -tileScaleHalf_.y);
			tilePos.z = tilePos.y;

			tileTransform.SetLocalScale(allTiles_[y][x].tileImage_->GetScale());
			tileTransform.SetLocalPosition(tilePos);
			tileTransform.CalculateWorldViewProjection();
			this->GetFirstShaderResourceHelper().SetConstantBuffer_Link("TransformData", tileTransform.GetTransformData());
			this->GetFirstShaderResourceHelper().SetTexture("Tex", allTiles_[y][x].tileImage_);
			GameEngineDefaultRenderer::Render(_deltaTime);
		}
	}
}

void TileMapRenderer::Start()
{
	this->SetMaterial("TextureAtlas");

	this->frameData_.posX = 0.f;
	this->frameData_.posY = 0.f;
	this->frameData_.sizeX = 1.f;
	this->frameData_.sizeY = 1.f;

	GetFirstShaderResourceHelper().SetConstantBuffer_Link("AtlasData", this->frameData_);
	GetFirstShaderResourceHelper().SetConstantBuffer_Link("PixelData", this->pixelData_);
	PushRendererToMainCamera();
}

void TileMapRenderer::Update(float _deltaTime)
{
}
