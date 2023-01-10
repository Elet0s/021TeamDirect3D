#include "PreCompile.h"
#include "GameEngineTexture2DArray.h"
#include "GameEngineDevice.h"

GameEngineTexture2DArray::GameEngineTexture2DArray():shaderResourceView_(nullptr)
{
}

GameEngineTexture2DArray::~GameEngineTexture2DArray()
{
	shaderResourceView_->Release();
}

std::shared_ptr<GameEngineTexture2DArray> GameEngineTexture2DArray::Load(
    const std::string_view& _path
 )
{
    return Load(_path, GameEnginePath::GetFileName(_path));
}

std::shared_ptr<GameEngineTexture2DArray> GameEngineTexture2DArray::Load(
    const std::string_view& _path,
    const std::string_view& _name
)
{
    std::shared_ptr<GameEngineTexture2DArray> newRes = CreateNamedRes(_name);
    newRes->LoadTextures(_path);
    return newRes;
}

void GameEngineTexture2DArray::Cut(const std::string_view& _textureName, int _x, int _y)
{
	Cut(this->GetIndex(_textureName), _x, _y);
}

void GameEngineTexture2DArray::Cut(int _textureIndex, int _x, int _y)
{
	cutData_[_textureIndex].reserve(static_cast<size_t>(_x) * static_cast<size_t>(_y));

	float sizeX = 1.f / _x;
	float sizeY = 1.f / _y;

	float4 cuttingStart = float4::Zero;

	for (int y = 0; y < _y; ++y)
	{
		for (int x = 0; x < _x; ++x)
		{
			float4 frameData;
			frameData.posX = cuttingStart.x;
			frameData.posY = cuttingStart.y;
			frameData.sizeX = sizeX;
			frameData.sizeY = sizeY;
			cutData_[_textureIndex].push_back(frameData);

			cuttingStart.x += sizeX;
		}

		cuttingStart.x = 0.f;
		cuttingStart.y += sizeY;
	}
}

void GameEngineTexture2DArray::LoadTextures(const std::string_view& _folderPath)
{
    GameEngineDirectory folderPath = _folderPath;
    std::vector<GameEngineFile> allFilesInFolder = folderPath.GetAllFiles();

	metaDatas_.resize(allFilesInFolder.size());
	images_.resize(allFilesInFolder.size());
	loadedScratchImages_.resize(allFilesInFolder.size());
	cutData_.resize(allFilesInFolder.size());

    for (size_t i = 0; i < allFilesInFolder.size(); i++)
    {
		std::wstring unicodePath = GameEngineString::AnsiToUnicodeReturn(allFilesInFolder[i].GetFullPath());

		std::string uppercaseExtension 
			= GameEngineString::ToUpperReturn(allFilesInFolder[i].GetExtension());

		std::string uppercaseFileName
			= GameEngineString::ToUpperReturn(allFilesInFolder[i].GetFileName());

		nameIndexPairs_.insert(std::make_pair(uppercaseFileName, static_cast<UINT>(i)));

		if (uppercaseExtension == ".TGA")
		{
			if (S_OK != DirectX::LoadFromTGAFile(
				unicodePath.c_str(),
				DirectX::TGA_FLAGS_NONE,
				&metaDatas_[i],
				loadedScratchImages_[i]
			))
			{
				MsgBoxAssertString(allFilesInFolder[i].GetFullPath() + ": 텍스쳐 로드 실패.");
				return;
			}
		}
		else if (uppercaseExtension == ".DDS")
		{
			MsgBoxAssert("DDS: 아직 처리 준비되지 않은 이미지 포맷입니다.");
			return;
		}
		else if (uppercaseExtension == ".PNG")
		{
			if (S_OK != DirectX::LoadFromWICFile(//
				unicodePath.c_str(),				  //
				DirectX::WIC_FLAGS_NONE,			  //
				&metaDatas_[i],
				loadedScratchImages_[i]					  //
			))
			{
				MsgBoxAssertString(allFilesInFolder[i].GetFullPath() + ": 텍스쳐 로드 실패.");
				return;
			}
		}

		if (0 < i 
			&& (metaDatas_[i].width != metaDatas_[0].width 
				|| metaDatas_[i].height != metaDatas_[0].height
				|| metaDatas_[i].format != metaDatas_[0].format))
		{
			MsgBoxAssert("0번 텍스처와 같은 크기와 포맷을 가진 텍스처만 삽입할 수 있습니다.");
			return;
		}

		images_[i] = *loadedScratchImages_[i].GetImages();
    }

	if (S_OK != scratchImage_.InitializeArrayFromImages(
		&images_[0],
		images_.size()
	))
	{
		MsgBoxAssert("텍스처 배열 생성 실패.");
		return;
	}

	if (S_OK != DirectX::CreateShaderResourceView(
		GameEngineDevice::GetDevice(),
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		scratchImage_.GetMetadata(),
		&shaderResourceView_
	))
	{
		MsgBoxAssert("셰이더 리소스뷰 배열 생성 실패.");
		return;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	shaderResourceView_->GetDesc(&desc);

}

void GameEngineTexture2DArray::VSSetShaderResource(int _bindPoint)
{
	if (nullptr == this->shaderResourceView_)
	{
		MsgBoxAssert("셰이더리소스뷰가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->VSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineTexture2DArray::CSSetShaderResource(int _bindPoint)
{
	if (nullptr == this->shaderResourceView_)
	{
		MsgBoxAssert("셰이더리소스뷰가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->CSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineTexture2DArray::PSSetShaderResource(int _bindPoint)
{
	if (nullptr == this->shaderResourceView_)
	{
		MsgBoxAssert("셰이더리소스뷰가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->PSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineTexture2DArray::VSResetShaderResource(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetDC()->VSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineTexture2DArray::PSResetShaderResource(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetDC()->PSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}
