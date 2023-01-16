#include "PreCompile.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineDevice.h"
#include "GameEngineTexture.h"


GameEngineFolderTexture::GameEngineFolderTexture()
{
}

GameEngineFolderTexture::~GameEngineFolderTexture()
{
	textures_.clear();
}

GameEngineFolderTexture* GameEngineFolderTexture::Load(const std::string_view& _path)
{
	return Load(_path, GameEnginePath::GetFileName(_path));
}

GameEngineFolderTexture* GameEngineFolderTexture::Load(const std::string_view& _path, const std::string_view& _name)
{
	GameEngineFolderTexture* newFolderTexture = CreateNamedRes(_name);
	newFolderTexture->LoadFolder(_path);
	return newFolderTexture;
}

void GameEngineFolderTexture::LoadFolder(const std::string_view& _path)
{
	GameEngineDirectory folderTextureDir = _path;
	std::vector<GameEngineFile> allFolderFiles = folderTextureDir.GetAllFiles();

	for (size_t i = 0; i < allFolderFiles.size(); i++)
	{
		GameEngineTexture* newTexture = new GameEngineTexture();
		newTexture->LoadTexture(allFolderFiles[i].GetFullPath());
		textures_.push_back(newTexture);
	}
}
