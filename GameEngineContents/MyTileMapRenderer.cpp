#include "PreCompile.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "MyTileMapRenderer.h"
#include "Enums.h"

MyTileMapRenderer::MyTileMapRenderer() 
	:pivotMode_(PivotMode::Center)
	, tileTextures_(nullptr)
	,tileX_(0)
	,tileY_(0)
	, KeyFree(true)
{
}

MyTileMapRenderer::~MyTileMapRenderer() 
{
}

void MyTileMapRenderer::CreateTileMap(
	int _x,
	int _y,
	const float4& _tileScale,
	const std::string& _Texture)
{
	GameEngineRandom Random;
	//GameEngineTexture* Texture = GameEngineTexture::Find(_Texture);

	/*if (nullptr == Texture)
	{
		MsgBoxAssertString(_Texture + ": 존재하지 않는 폴더텍스처입니다.");
		return;
	}*/
	

	tileTextures_ = GameEngineFolderTexture::Find("MapTile");

	if (nullptr == tileTextures_)
	{
		//MsgBoxAssert(_folderTexture + ": 존재하지 않는 폴더텍스처입니다.");
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
			if (x < 5)
			{
				allTiles_[y][x].tileImage_ = tileTextures_->GetTexture(Random.RandomInt(0,4));
			}
			else
			{
				allTiles_[y][x].tileImage_ = tileTextures_->GetTexture(Random.RandomInt(0, 4));
			}
		}
	}
}

void MyTileMapRenderer::SetTileIndex(const float4& _pos, size_t _index)
{
	if (0 > _index)
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
	//allTiles_[tileIndexY][tileIndexX].tileImage_ = tileTextures_->GetTexture(_index);
}

void MyTileMapRenderer::GetTileIndex(const float4& _pos, int& _x, int& _y)
{
	float fX = (_pos.x / tileScaleHalf_.x + _pos.y / -tileScaleHalf_.y) / 2.f;
	float fY = (_pos.y / -tileScaleHalf_.y - _pos.x / tileScaleHalf_.x) / 2.f;

	_x = static_cast<int>(roundf(fX));
	_y = static_cast<int>(roundf(fY));
}

void MyTileMapRenderer::Render(float _deltaTime)
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
			tilePos.x = x * tileScale_.x;
			tilePos.y = y * -tileScale_.y;
			tilePos.z = tilePos.y;

			tileTransform.SetLocalScale(allTiles_[y][x].tileImage_->GetScale());
			tileTransform.SetLocalPosition(tilePos);
			tileTransform.CalculateWorldViewProjection();
			this->GetShaderResourceHelper().SetConstantBuffer_Link("TransformData", tileTransform.GetTransformData());
			this->GetShaderResourceHelper().SetTexture("Tex", allTiles_[y][x].tileImage_);
			GameEngineDefaultRenderer::Render(_deltaTime);
		}
	}
}

void MyTileMapRenderer::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveMap_Right"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveMap_Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Down", VK_DOWN);
	}

	this->SetPipeLine("TextureAtlas");

	atlasDataInst_.frameData_.posX = 0.f;
	atlasDataInst_.frameData_.posY = 0.f;
	atlasDataInst_.frameData_.sizeX = 1.f;
	atlasDataInst_.frameData_.sizeY = 1.f;
	atlasDataInst_.pivotPos_ = float4::Zero;
	
	GetShaderResourceHelper().SetConstantBuffer_Link("AtlasData", this->atlasDataInst_);
	GetShaderResourceHelper().SetConstantBuffer_Link("PixelData", this->pixelData_);
	PushRendererToMainCamera();
}

void MyTileMapRenderer::Update(float _deltaTime)
{

	if (KeyFree == true)
	{
		if (GameEngineInput::GetInst()->IsPressed("MoveMap_Right"))
		{
			MoveWorld(0);
			KeyFree = false;
		}

		else if (GameEngineInput::GetInst()->IsPressed("MoveMap_Left"))
		{
			MoveWorld(1);
			KeyFree = false;
		}

		else if (GameEngineInput::GetInst()->IsPressed("MoveMap_Up"))
		{
			MoveWorld(2);
			KeyFree = false;
		}

		else if (GameEngineInput::GetInst()->IsPressed("MoveMap_Down"))
		{
			MoveWorld(3);
			KeyFree = false;
		}
	}

	if (GameEngineInput::GetInst()->IsFree("MoveMap_Right") &&
		GameEngineInput::GetInst()->IsFree("MoveMap_Left") &&
		GameEngineInput::GetInst()->IsFree("MoveMap_Up") &&
		GameEngineInput::GetInst()->IsFree("MoveMap_Down"))
	{
		KeyFree = true;
	}
}


void  MyTileMapRenderer::MoveWorld(int _Dir)
{
	std::vector<std::vector<Tile>> CopyTiles_;
	CopyTiles_.resize(tileY_);
	for (size_t y = 0; y < CopyTiles_.size(); y++)
	{
		CopyTiles_[y].resize(tileX_);
	}

	switch (_Dir)
	{
	case 0:
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CX = x + 1;
				if (CX == tileX_)
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][CX - tileX_].tileImage_;
				}
				else
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][CX].tileImage_;
				}
			}
		}
			break;
	case 1:
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CX = x - 1;
				if (CX < 0)
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][tileX_ - 1].tileImage_;
				}
				else
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][CX].tileImage_;
				}
			}
		}
		break;
	case 2:
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CY = y - 1;
				if (CY < 0)
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[tileY_ - 1][x].tileImage_;
				}
				else
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[CY][x].tileImage_;
				}
			}
		}
			break;
	case 3:
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CY = y + 1;
				if (CY == 10)
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[CY - tileY_][x].tileImage_;
				}
				else
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[CY][x].tileImage_;
				}
			}
		}
			break;
	default:
		for (int y = 0; y < CopyTiles_.size(); y++)
		{
			for (int x = 0; x < CopyTiles_[y].size(); x++)
			{
				int CX = x + 1;
				if (CX == 10)
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][x - 9].tileImage_;
				}
				else
				{
					CopyTiles_[y][x].tileImage_ = allTiles_[y][CX].tileImage_;
				}
			}
		}
			break;
		}	

		allTiles_.swap(CopyTiles_);
}


void MyTileMapRenderer::SetPivot(PivotMode _pivot)
{
	switch (_pivot)
	{
	case PivotMode::Top:
		atlasDataInst_.pivotPos_ = float4(0.f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::Center:
		atlasDataInst_.pivotPos_ = float4::Zero;
		break;
	case PivotMode::Bot:
		atlasDataInst_.pivotPos_ = float4(0.f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Left:
		atlasDataInst_.pivotPos_ = float4(0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::Right:
		atlasDataInst_.pivotPos_ = float4(-0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::LeftTop:
		atlasDataInst_.pivotPos_ = float4(0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightTop:
		atlasDataInst_.pivotPos_ = float4(-0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::LeftBot:
		atlasDataInst_.pivotPos_ = float4(0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightBot:
		atlasDataInst_.pivotPos_ = float4(-0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Custom:
		//_pivot == Custom일때는 아무것도 하지 않는다.
		break;

	default:
		MsgBoxAssert("존재할 수 없는 피봇모드입니다.");
		return;
	}

	pivotMode_ = _pivot;
}
