#pragma once

class GameEnginePath
{
	//std::fileSystem을 기반으로 특정 파일의 경로와 파일명, 확장자를 관리하는 클래스. 
	//https://en.cppreference.com/w/cpp/filesystem/path

protected:
	std::filesystem::path path_;


public:
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _path);
	GameEnginePath(const std::string& _path);
	GameEnginePath(const std::string_view& _path);
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
	std::string GetExtension() const;
	std::string GetFolderPath() const;
	std::string ReplaceFileName(const std::filesystem::path& _newFileName);
	std::string ReplaceExtension(const std::filesystem::path& _newExtention);

	static bool IsExist(const std::filesystem::path& _path);
	static std::string GetFileName(const std::filesystem::path& _path);
	static std::string GetStem(const std::filesystem::path& _path);
	static std::string GetExtension(const std::filesystem::path& _path);
	static std::string GetFolderPath(const std::filesystem::path& _path);


};

