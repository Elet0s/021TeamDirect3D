#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory: public GameEnginePath
{
	//�ַ�� ������ �ִ� ������ ��������, ������Ʈ �� ���ϴ� ���丮�� �̵��ϴ� ��ɵ��� ��� �� Ŭ����. 
public:

	GameEngineDirectory();
	GameEngineDirectory(const char* _path);
	GameEngineDirectory(const std::string& _path);
	GameEngineDirectory(const std::filesystem::path& _path);
	GameEngineDirectory(const GameEngineDirectory& _other);
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept;
	~GameEngineDirectory();

	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _other) = delete;

public:
	void MoveToParent();
	void MoveToParent(const std::string& _parentName);
	bool MoveParentToExistChildDirectory(const std::string& _childName);
	bool IsRoot() const;
	void MoveToChild(const std::string& _childName);
	std::string PlusFilePath(const std::string& _fileName);

public:
	std::vector<GameEngineFile> GetAllFiles(const std::string& _ext = "");
	std::vector<GameEngineDirectory> GetAllDirectories();
	std::vector<GameEngineDirectory> GetRecursiveAllDirectories();
};

