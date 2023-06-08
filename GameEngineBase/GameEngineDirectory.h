#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
	//솔루션 파일이 있는 지점을 원점으로, 프로젝트 내 원하는 디렉토리로 이동하는 기능들을 모아 둔 클래스. 
public:

	GameEngineDirectory();
	GameEngineDirectory(const char* _path);
	GameEngineDirectory(const std::string& _path);
	GameEngineDirectory(const std::string_view& _path);
	GameEngineDirectory(const std::filesystem::path& _path);
	GameEngineDirectory(const GameEngineDirectory& _other);
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept;
	~GameEngineDirectory();

	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _other) = delete;

public:
	void MoveToParent();
	void MoveToParent(const std::string_view& _parentName);
	bool MoveParentToExistChildDirectory(const std::string_view& _childName);
	bool IsRoot() const;
	bool IsFileExist(const std::string_view& _fileName);
	void MoveToChild(const std::string_view& _childName);
	std::string PlusFilePath(const std::string_view& _fileName);

public:
	std::vector<GameEngineFile> GetAllFiles(const std::string_view& _ext = "");
	std::vector<GameEngineDirectory> GetAllDirectories();
	std::vector<GameEngineDirectory> GetRecursiveAllDirectories();
};

