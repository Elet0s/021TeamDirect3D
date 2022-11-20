#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineDirectory.h"

GameEngineFile::GameEngineFile() : filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(const char* _path) : GameEnginePath(_path), filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(const std::string& _path) : GameEnginePath(_path), filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(const std::string_view& _path) : GameEnginePath(_path), filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(const std::filesystem::path& _path) : GameEnginePath(_path), filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(const GameEngineFile& _other) : GameEnginePath(_other.path_), filePtr_(nullptr)
{
}

GameEngineFile::GameEngineFile(GameEngineFile&& _other) noexcept : GameEnginePath(_other.path_), filePtr_(nullptr)
{
}

GameEngineFile::~GameEngineFile()
{
	if (nullptr != filePtr_)
	{
		fclose(filePtr_);
		filePtr_ = nullptr;
	}
}

void GameEngineFile::Open(OpenMode _openMode, FileMode _fileMode)
{
	std::string mode = "";

	// "wb": ���� ���̳ʸ�.
	// "wt": ���� �ؽ�Ʈ.

	// "rb": �д´� ���̳ʸ�.
	// "rt": �д´� �ؽ�Ʈ.


	switch (_openMode)
	{
	case OpenMode::Read:
		mode += "r";
		break;

	case OpenMode::Write:
		mode += "w";
		break;

	default:
		MsgBoxAssert("�Ұ����� ����Դϴ�.");
		return;
	}

	switch (_fileMode)
	{
	case FileMode::Binary:
		mode += "b";
		break;

	case FileMode::Text:
		mode += "t";
		break;

	default:
		MsgBoxAssert("�Ұ����� ����Դϴ�.");
		return;
	}

	int openResult = fopen_s(	//������ ����� ������ ���� �����ڵ��� �޾ƿ��� �Լ�.
		&filePtr_,				//���� ���Ͽ� ���� �����ڵ��� �ּҰ�.
		path_.string().c_str(),	//��ΰ� ���Ե� ���� �̸�.
		mode.c_str()			//���� ���� ���. 
	);

	if (2 == openResult)
	{
		MsgBoxAssertString(path_.string() + "\n�������� �ʴ� ����Դϴ�.");
		return;
	}
	else if (0 != openResult)
	{
		MsgBoxAssert("������ ���������� ���µ� �����߽��ϴ�.");
		return;
	}
}

void GameEngineFile::Close()
{
	if (nullptr != filePtr_)
	{
		fclose(filePtr_);
		filePtr_ = nullptr;
	}
}

void GameEngineFile::Read(void* _readData, size_t _dataSize, size_t _readSize)
{
	size_t readResult = fread_s(
		_readData,
		_dataSize,
		_readSize,
		1,			//�д� Ƚ��.
		filePtr_
	);

	if (0 != ferror(filePtr_))
	{
		MsgBoxAssert("������ �дµ� �����߽��ϴ�.");
		return;
	}
	//if (0 != feof(filePtr_))
	//{
	//	MsgBoxAssert("���� ���� �Ѿ���ϴ�.");
	//	return;
	//}
	//�� �� ���� ������ ���̴����� ũ��� ���̴��ڵ� ���ڿ� ���̰� �ٸ��Ƿ� feof()���� ���� �� �˻� ���� �� ��.
	//->�Ƹ� �ѱ� �ּ� ���� 2����Ʈ �̻� ũ���� ���ڵ� ������ ���� ������ ���� ���� ũ�Ⱑ �� Ŀ�������� �����.
}

void GameEngineFile::Read(std::string& _text)
{
	size_t size = 0;
	Read(&size, sizeof(size_t), sizeof(size_t));
	_text.resize(size);
	Read(&_text[0], size, size);
}

void GameEngineFile::Read(float4x4& _data)
{
	Read(&_data, sizeof(float4x4), sizeof(float4x4));
}

void GameEngineFile::Read(float4& _data)
{
	Read(&_data, sizeof(float4), sizeof(float4));
}

void GameEngineFile::Read(float& _data)
{
	Read(&_data, sizeof(float), sizeof(float));
}

void GameEngineFile::Read(double& _data)
{
	Read(&_data, sizeof(double), sizeof(double));
}

void GameEngineFile::Read(unsigned int& _data)
{
	Read(&_data, sizeof(unsigned int), sizeof(unsigned int));
}

void GameEngineFile::Write(const void* _writeData, size_t _writeSize)
{
	size_t writeResult = fwrite(
		_writeData,
		_writeSize,
		1,			//���� Ƚ��.
		filePtr_
	);

	if (1 != writeResult)
	{
		MsgBoxAssert("���� ���� ����.");
		return;
	}
}

void GameEngineFile::Write(const std::string& _text)
{
	// ũ�⸦ ��������� �մϴ�.
	// string��? ũ�Ⱑ ������ �����͸� ������ �ֳ���?
	size_t size = _text.size();
	Write(&size, sizeof(size_t));
	Write(_text.data(), _text.size());
}

void GameEngineFile::Write(const float4x4& _data)
{
	Write(&_data, sizeof(float4x4));
}

void GameEngineFile::Write(const float4& _data)
{
	Write(&_data, sizeof(float4));
}

void GameEngineFile::Write(const float& _data)
{
	Write(&_data, sizeof(float));
}

void GameEngineFile::Write(const double& _data)
{
	Write(&_data, sizeof(double));
}

void GameEngineFile::Write(const unsigned int& _data)
{
	Write(&_data, sizeof(unsigned int));
}

std::string GameEngineFile::GetString()
{
	uintmax_t fileSize = GetFileSize();	//unsigned long long == uintmax_t == size_t.

	std::string allString = std::string(fileSize, '0');

	//allString.resize(fileSize);	

	Read(&allString[0], fileSize, fileSize);

	return allString;
}

uintmax_t GameEngineFile::GetFileSize() const
{
	return std::filesystem::file_size(this->path_);
	//����ũ�⸦ �дµ� �����ϸ� -1 ��ȯ.
}

uintmax_t GameEngineFile::GetFileSize(const std::filesystem::path& _path)
{
	return std::filesystem::file_size(_path);
}

GameEngineDirectory GameEngineFile::GetDirectory()
{
	return GameEngineDirectory(path_.parent_path());
}
