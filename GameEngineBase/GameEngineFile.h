#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write
};

enum class FileMode
{
	Binary,
	Text
};

class GameEngineFile: public GameEnginePath
{
	//������ ������ ���� ����, ������ ����/�ҷ����� �� ���� �����ϴµ� �ʿ��� ��ɵ��� ��Ƶ� Ŭ����.


public:

	GameEngineFile();
	GameEngineFile(const char* _path);
	GameEngineFile(const std::string& _path);
	GameEngineFile(const std::filesystem::path& _path);
	GameEngineFile(const GameEngineFile& _other);
	GameEngineFile(GameEngineFile&& _other) noexcept;
	~GameEngineFile();

	GameEngineFile& operator=(const GameEngineFile& _other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _other) = delete;

public:
	void Open(OpenMode _openMode, FileMode _fileMode);
	void Close();
	void Read(void* _readData, size_t _dataSize, size_t _readSize);
	void Write(void* _writeData, size_t _writeSize);
	std::string GetString();
	uintmax_t GetFileSize() const;
	static uintmax_t GetFileSize(const std::filesystem::path& _path);


public:
	void Create()
	{
		Open(OpenMode::Write, FileMode::Binary);
		Close();
	}

private:
	FILE* filePtr_;
	//������ OS�� �����ϹǷ� ������ ���� ����� ���� ����� OS�� �����ϰ� ���踦 �ΰ� �ִ�.

};

