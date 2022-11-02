#pragma once
#include "GameEnginePath.h"
#include "GameEngineMath.h"

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
	//파일의 생성과 열고 닫음, 데이터 저장/불러오기 등 파일 관리하는데 필요한 기능들을 모아둔 클래스.


public:

	GameEngineFile();
	GameEngineFile(const char* _path);
	GameEngineFile(const std::string& _path);
	GameEngineFile(const std::string_view& _path);
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
	void Read(std::string& _text);
	void Read(float4x4& _data);
	void Read(float4& _data);
	void Read(float& _data);
	void Read(double& _data);

	void Write(const void* _writeData, size_t _writeSize);
	void Write(const std::string& _text);
	void Write(const float4x4& _data);
	void Write(const float4& _data);
	void Write(const float& _data);
	void Write(const double& _data);

	std::string GetString();
	uintmax_t GetFileSize() const;
	static uintmax_t GetFileSize(const std::filesystem::path& _path);


public:
	void Create()
	{
		Open(OpenMode::Write, FileMode::Binary);
		Close();
	}

	template<typename Struct>
	void Write(const Struct& _data)
	{
		Write(reinterpret_cast<const void*>(&_data), sizeof(Struct));
	}

	template<typename Struct>
	void Read(Struct& _data)
	{
		Read(reinterpret_cast<void*>(&_data), sizeof(Struct), sizeof(Struct));
	}

private:
	FILE* filePtr_;
	//파일은 OS가 관리하므로 웬만한 파일 입출력 관련 기능은 OS와 밀접하게 관계를 맺고 있다.

};

