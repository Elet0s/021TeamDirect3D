#include "PreCompile.h"
#include "MyWorldMapRenderer.h"
#include <GameEngineBase/GameEngineRandom.h>

MyWorldMapRenderer::MyWorldMapRenderer()
	:pivotmode_(PivotMode::Center)
	, tileTextures_(nullptr)
	, tileX_(0)
	, tileY_(0)
	, KeyFree(true)
{
}

MyWorldMapRenderer::~MyWorldMapRenderer()
{
}

void MyWorldMapRenderer::CreateTileMap(
	int _x,
	int _y,
	const float4& _tileScale,
	const std::string& _Texture)
{
	GameEngineRandom Random;
	//GameEngineTexture* Texture = GameEngineTexture::Find(_Texture);

	/*if (nullptr == Texture)
	{
		MsgBoxAssertString(_Texture + ": �������� �ʴ� �����ؽ�ó�Դϴ�.");
		return;
	}*/


	tileTextures_ = GameEngineTexture::Find(_Texture);

	if (nullptr == tileTextures_)
	{
		MsgBoxAssertString(_Texture + ": �������� �ʴ� �����ؽ�ó�Դϴ�.");
		return;
	}


	tileX_ = _x;
	tileY_ = _y;
	tilescale_ = _tileScale;
	tilescalehalf_ = tilescale_.Half();

	alltiles_.resize(_y);
	for (size_t y = 0; y < alltiles_.size(); y++)
	{
		alltiles_[y].resize(_x);
		for (size_t x = 0; x < alltiles_[y].size(); x++)
		{
			if (x < 5)
			{
				alltiles_[y][x].tileImage_ = tileTextures_;
			}
			else
			{
				alltiles_[y][x].tileImage_ = tileTextures_;
			}
		}
	}
}

void MyWorldMapRenderer::SetTileIndex(const float4& _pos, size_t _index)
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

	alltiles_[tileIndexY][tileIndexX].tileIndex_ = static_cast<int>(_index);
	//allTiles_[tileIndexY][tileIndexX].tileImage_ = tileTextures_->GetTexture(_index);
}

void MyWorldMapRenderer::GetTileIndex(const float4& _pos, int& _x, int& _y)
{
	float fX = (_pos.x / tilescalehalf_.x + _pos.y / -tilescalehalf_.y) / 2.f;
	float fY = (_pos.y / -tilescalehalf_.y - _pos.x / tilescalehalf_.x) / 2.f;

	_x = static_cast<int>(roundf(fX));
	_y = static_cast<int>(roundf(fY));
}

void MyWorldMapRenderer::Render(float _deltaTime)
{
	

	static GameEngineTransform tileTransform;

	//tileTransform.SetLocalScale(this->tileScale_);
	tileTransform.SetViewMatrix(this->GetTransformData().viewMatrix_);
	tileTransform.SetProjectionMatrix(this->GetTransformData().projectionMatrix_);

	for (size_t y = 0; y < alltiles_.size(); y++)
	{
		for (size_t x = 0; x < alltiles_[y].size(); x++)
		{
			float4 tilePos = this->GetTransform().GetWorldPosition();
			tilePos.x += x * tilescale_.x;
			tilePos.y += -tilescale_.y * sinf(10.f * GameEngineMath::DegreeToRadian) * y;
			tilePos.z += -tilescale_.y * cosf(10.f * GameEngineMath::DegreeToRadian) * y;

			tileTransform.SetLocalScale(alltiles_[y][x].tileImage_->GetScale());
			tileTransform.SetLocalPosition(tilePos);
			tileTransform.SetLocalRotation( float4(80.f,0.f,0.f));
			tileTransform.CalculateWorldViewProjection();
			this->GetFirstShaderResourceHelper().SetConstantBuffer_Link("TransformData", tileTransform.GetTransformData());
			this->GetFirstShaderResourceHelper().SetTexture("Tex", alltiles_[y][x].tileImage_);
			GameEngineDefaultRenderer::Render(_deltaTime);
		}
	}
}

void MyWorldMapRenderer::Start()
{
	/*if (false == GameEngineInput::GetInst()->IsKey("MoveMap_Right"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveMap_Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveMap_Down", VK_DOWN);
	}*/

	PushRendererToMainCamera();

	this->SetMaterial("TextureAtlas");

	atlasdatainst_.frameData_.posX = 0.f;
	atlasdatainst_.frameData_.posY = 0.f;
	atlasdatainst_.frameData_.sizeX = 1.f;
	atlasdatainst_.frameData_.sizeY = 1.f;
	atlasdatainst_.pivotPos_ = float4::Zero;

	GetFirstShaderResourceHelper().SetConstantBuffer_Link("AtlasData", this->atlasdatainst_);
	GetFirstShaderResourceHelper().SetConstantBuffer_Link("PixelData", this->pixeldata_);
}

void MyWorldMapRenderer::Update(float _deltaTime)
{

}


void  MyWorldMapRenderer::MoveWorld(int _Dir)
{

}


void MyWorldMapRenderer::SetPivot(PivotMode _pivot)
{
	switch (_pivot)
	{
	case PivotMode::Top:
		atlasdatainst_.pivotPos_ = float4(0.f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::Center:
		atlasdatainst_.pivotPos_ = float4::Zero;
		break;
	case PivotMode::Bot:
		atlasdatainst_.pivotPos_ = float4(0.f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Left:
		atlasdatainst_.pivotPos_ = float4(0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::Right:
		atlasdatainst_.pivotPos_ = float4(-0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::LeftTop:
		atlasdatainst_.pivotPos_ = float4(0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightTop:
		atlasdatainst_.pivotPos_ = float4(-0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::LeftBot:
		atlasdatainst_.pivotPos_ = float4(0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightBot:
		atlasdatainst_.pivotPos_ = float4(-0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Custom:
		//_pivot == Custom�϶��� �ƹ��͵� ���� �ʴ´�.
		break;

	default:
		MsgBoxAssert("������ �� ���� �Ǻ�����Դϴ�.");
		return;
	}

	pivotmode_ = _pivot;
}