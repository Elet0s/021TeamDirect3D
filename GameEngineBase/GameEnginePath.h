#pragma once

class GameEnginePath
{
	//std::fileSystem�� ������� Ư�� ������ ��ο� ���ϸ�, Ȯ���ڸ� �����ϴ� Ŭ����. 
	//https://en.cppreference.com/w/cpp/filesystem/path

protected:
	std::filesystem::path path_;


public:
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _path);
	GameEnginePath(const std::string& _path);
	GameEnginePath(const char* _path);
	~GameEnginePath();

	GameEnginePath(const GameEnginePath& _other) = delete;
	GameEnginePath(GameEnginePath&& _other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _other) = delete;

public:
	void SetCurrentPath();
	bool IsExist() const;

	std::string GetFullPath() const;
	std::string GetFileName() const;
	std::string GetStem() const;
	std::string GetExtention() const;

	static std::string GetFileName(const std::string& _path);
	static std::string GetStem(const std::string& _path);
	static std::string GetExtension(const std::string& _path);
	

};

