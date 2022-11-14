#pragma once
#include "GameEnginePath.h"
#include "GameEngineMath.h"

class GameEngineFile;
class Serializer
{
	//����ȭ(Serialization): ���μ��� �ۿ����� ������ �� ���� ������ ��ü ���� ������ 
	// ���Ϸ� �а� ���ų� ��Ʈ��ũ�� ���� �ۼ��� �ϱ� ���� ���·� �ٲٴ� �۾�. 
public:
	virtual void Write(GameEngineFile& _File) = 0;
	virtual void Read(GameEngineFile& _File) = 0;
};

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
	void Write(const std::string_view& _text);
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

	template<typename Value>
	void Write(std::vector<Value>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		Write(&Size, sizeof(int));

		if (Size <= 0)
		{
			return;
		}

		Value* Check = &_Data[0];

		Serializer* Ser = dynamic_cast<Serializer*>(Check);

		for (size_t i = 0; i < _Data.size(); i++)
		{
			if (nullptr == Ser)
			{
				Write(&_Data[i], sizeof(Value));
			}
			else
			{
				_Data[i].Write(*this);
			}

		}
	}

	template<typename Struct>
	void Read(Struct& _data)
	{
		Read(reinterpret_cast<void*>(&_data), sizeof(Struct), sizeof(Struct));
	}

private:
	FILE* filePtr_;
	//������ OS�� �����ϹǷ� ������ ���� ����� ���� ����� OS�� �����ϰ� ���踦 �ΰ� �ִ�.

};

