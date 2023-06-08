#pragma once
#include "GameEnginePath.h"
#include "GameEngineMath.h"

class GameEngineFile;
class GameEngineSerializer
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
	void Read(unsigned int& _data);

	void Write(const void* _writeData, size_t _writeSize);
	void Write(const std::string& _text);
	void Write(const float4x4& _data);
	void Write(const float4& _data);
	void Write(const float& _data);
	void Write(const double& _data);
	void Write(const unsigned int& _data);

	std::string GetString();
	uintmax_t GetFileSize() const;
	static uintmax_t GetFileSize(const std::filesystem::path& _path);
	class GameEngineDirectory GetDirectory();


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
	void Write(std::vector<Value>& _data)
	{
		size_t dataSize = _data.size();
		Write(dataSize);

		if (dataSize <= 0)
		{
			return;
		}
		std::size_t temp = 0;
		for (size_t i = 0; i < _data.size(); i++)
		{
			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
				//template< class Base, class Derived > struct std::is_base_of;
				//Derived Ŭ������ Base Ŭ������ ��ӹ޾Ҵ��� �ƴ��� �����ϴ� ����ü.
			{
				Write(_data[i]);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&_data[i]);
				serializer->Write(*this);
			}
		}
	}

	template<typename Key, typename  Value>
	void Write(std::map<Key, Value>& _Data)
	{
		size_t dataSize = _Data.size();
		Write(dataSize);

		if (dataSize <= 0)
		{
			return;
		}

		for (std::pair<Key, Value> writePair : _Data)
		{
			if (false == std::is_base_of<GameEngineSerializer, Key>::value)
				//template< class Base, class Derived > struct std::is_base_of;
				//Derived Ŭ������ Base Ŭ������ ��ӹ޾Ҵ��� �ƴ��� �����ϴ� ����ü.
			{
				Write(writePair.first);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&writePair.first);
				serializer->Write(*this);
			}

			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
			{
				Write(writePair.second);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&writePair.second);
				serializer->Write(*this);
			}
		}
	}

	template<typename Struct>
	void Read(Struct& _data)
	{
		Read(reinterpret_cast<void*>(&_data), sizeof(Struct), sizeof(Struct));
	}

	template<typename Value>
	void Read(std::vector<Value>& _data)
	{
		size_t dataSize = 0;
		Read(dataSize);

		if (dataSize <= 0)
		{
			return;
		}

		_data.resize(dataSize);

		for (size_t i = 0; i < dataSize; i++)
		{
			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
				//template< class Base, class Derived > struct std::is_base_of;
				//Derived Ŭ������ Base Ŭ������ ��ӹ޾Ҵ��� �ƴ��� �����ϴ� ����ü.
			{
				Read(_data[i]);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&_data[i]);
				serializer->Read(*this);
			}
		}
	}

	template<typename Key, typename  Value>
	void Read(std::map<Key, Value>& _data)
	{
		size_t dataSize = 0;
		Read(dataSize);

		if (dataSize <= 0)
		{
			return;
		}

		for (size_t i = 0; i < dataSize; ++i)
		{
			std::pair<Key, Value> readPair;

			if (false == std::is_base_of<GameEngineSerializer, Key>::value)
				//template< class Base, class Derived > struct std::is_base_of;
				//Derived Ŭ������ Base Ŭ������ ��ӹ޾Ҵ��� �ƴ��� �����ϴ� ����ü.
			{
				Read(readPair.first);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&readPair.first);
				serializer->Read(*this);
			}


			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
				//template< class Base, class Derived > struct std::is_base_of;
				//Derived Ŭ������ Base Ŭ������ ��ӹ޾Ҵ��� �ƴ��� �����ϴ� ����ü.
			{
				Read(readPair.second);
			}
			else
			{
				GameEngineSerializer* serializer = reinterpret_cast<GameEngineSerializer*>(&readPair.second);
				serializer->Read(*this);
			}

			_data.insert(readPair);
		}
	}

private:
	FILE* filePtr_;
	//������ OS�� �����ϹǷ� ������ ���� ����� ���� ����� OS�� �����ϰ� ���踦 �ΰ� �ִ�.

};

