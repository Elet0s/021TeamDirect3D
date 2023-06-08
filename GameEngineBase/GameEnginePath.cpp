#include "PreCompile.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath() : path_(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _path) : path_(_path)
{
}

GameEnginePath::GameEnginePath(const std::string& _path) : path_(_path)
{
}

GameEnginePath::GameEnginePath(const std::string_view& _path) : path_(_path)
{
}

GameEnginePath::GameEnginePath(const char* _path) : path_(_path)
{
}

GameEnginePath::~GameEnginePath()
{
}

void GameEnginePath::SetCurrentPath()
{
	path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExist() const
{
	return std::filesystem::exists(this->path_);
}

std::string GameEnginePath::GetFullPath() const
{
	return path_.string();
}

std::string GameEnginePath::GetFileName() const
{
	return path_.filename().string();
}

std::string GameEnginePath::GetStem() const
{
	return path_.stem().string();
}

std::string GameEnginePath::GetExtension() const
{
	return path_.extension().string();
}

std::string GameEnginePath::GetFolderPath() const
{
	return path_.parent_path().string();
}

std::string GameEnginePath::ReplaceFileName(const std::filesystem::path& _newFileName)
{
	return path_.replace_filename(_newFileName).string();
}

std::string GameEnginePath::ReplaceExtension(const std::filesystem::path& _newExtention)
{
	return path_.replace_extension(_newExtention).string();
}

bool GameEnginePath::IsExist(const std::filesystem::path& _path)
{
	return std::filesystem::exists(_path);
}

std::string GameEnginePath::GetFileName(const std::filesystem::path& _path)
{
	//std::filesystem::path returnFileName = _path;
	//return returnFileName.filename().string();
	return _path.filename().string();
}

std::string GameEnginePath::GetStem(const std::filesystem::path& _path)
{
	//std::filesystem::path returnStem = _path;
	//return returnStem.stem().string();
	return _path.stem().string();
}

std::string GameEnginePath::GetExtension(const std::filesystem::path& _path)
{
	//std::filesystem::path returnExtention = _path;
	//return returnExtention.extension().string();
	return _path.extension().string();
}

std::string GameEnginePath::GetFolderPath(const std::filesystem::path& _path)
{
	//std::filesystem::path returnFolderPath = _path;
	//return returnFolderPath.parent_path().string();
	return _path.parent_path().string();
}
