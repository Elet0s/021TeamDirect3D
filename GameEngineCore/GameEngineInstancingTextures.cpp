#include "PreCompile.h"
#include "GameEngineInstancingTextures.h"
#include "GameEngineDevice.h"


GameEngineInstancingTextures::GameEngineInstancingTextures()
{
}

GameEngineInstancingTextures::~GameEngineInstancingTextures()
{
    for (ID3D11ShaderResourceView* shaderResourceView : instancingShaderResourceViews_)
    {
        shaderResourceView->Release();
        shaderResourceView = nullptr;
    }
}

std::shared_ptr<GameEngineInstancingTextures> GameEngineInstancingTextures::Load(
    const std::string_view& _path
 )
{
    return Load(_path, GameEnginePath::GetFileName(_path));
}

std::shared_ptr<GameEngineInstancingTextures> GameEngineInstancingTextures::Load(
    const std::string_view& _path,
    const std::string_view& _name
)
{
    std::shared_ptr<GameEngineInstancingTextures> newRes = CreateNamedRes(_name);
    newRes->LoadFolderTextures(_path);
    return newRes;
}

void GameEngineInstancingTextures::LoadFolderTextures(const std::string_view& _path)
{
    GameEngineDirectory folderDir = _path;
    std::vector<GameEngineFile> allFilesInFolder = folderDir.GetAllFiles();

	scratchImages_.resize(allFilesInFolder.size());
	metaDatas_.resize(allFilesInFolder.size());
	instancingShaderResourceViews_.resize(allFilesInFolder.size());

    for (size_t i = 0; i < allFilesInFolder.size(); i++)
    {
		std::wstring unicodePath = GameEngineString::AnsiToUnicodeReturn(allFilesInFolder[i].GetFullPath());

		std::string uppercaseExtension 
			= GameEngineString::ToUpperReturn(allFilesInFolder[i].GetExtension());

		if (uppercaseExtension == ".TGA")
		{
			if (S_OK != DirectX::LoadFromTGAFile(
				unicodePath.c_str(),
				DirectX::TGA_FLAGS_NONE,
				&metaDatas_[i],
				scratchImages_[i]
			))
			{
				MsgBoxAssertString(allFilesInFolder[i].GetFullPath() + ": �ؽ��� �ε� ����.");
				return;
			}
		}
		else if (uppercaseExtension == ".DDS")
		{
			MsgBoxAssert("DDS: ���� ó�� �غ���� ���� �̹��� �����Դϴ�.");
			return;
		}
		else if (uppercaseExtension == ".PNG")
		{
			if (S_OK != DirectX::LoadFromWICFile(//
				unicodePath.c_str(),				  //
				DirectX::WIC_FLAGS_NONE,			  //
				&metaDatas_[i],
				scratchImages_[i]					  //
			))
			{
				MsgBoxAssertString(allFilesInFolder[i].GetFullPath() + ": �ؽ��� �ε� ����.");
				return;
			}
		}

		if (S_OK != DirectX::CreateShaderResourceView(//
			GameEngineDevice::GetDevice(),			  //
			scratchImages_[i].GetImages(),				  //
			scratchImages_[i].GetImageCount(),			  //
			scratchImages_[i].GetMetadata(),			  //
			&instancingShaderResourceViews_[i]					  //
		))
		{
			MsgBoxAssertString(allFilesInFolder[i].GetFullPath() + ": ���̴� ���ҽ� ���� ����.");
			return;
		}
    }
}

void GameEngineInstancingTextures::VSSetting(int _bindPoint)
{
	if (true == this->instancingShaderResourceViews_.empty())
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(
		_bindPoint,
		static_cast<UINT>(instancingShaderResourceViews_.size()),
		&instancingShaderResourceViews_[0]
	);
}

void GameEngineInstancingTextures::PSSetting(int _bindPoint)
{
	if (true == this->instancingShaderResourceViews_.empty())
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(
		_bindPoint,
		static_cast<UINT>(instancingShaderResourceViews_.size()),
		&instancingShaderResourceViews_[0]
	);
}