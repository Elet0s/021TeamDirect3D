#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

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

	// "wb": 쓴다 바이너리.
	// "wt": 쓴다 텍스트.

	// "rb": 읽는다 바이너리.
	// "rt": 읽는다 텍스트.


	switch (_openMode)
	{
	case OpenMode::Read:
		mode += "r";
		break;

	case OpenMode::Write:
		mode += "w";
		break;

	default:
		MsgBoxAssert("불가능한 방식입니다.");
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
		MsgBoxAssert("불가능한 방식입니다.");
		return;
	}

	int openResult = fopen_s(	//지정한 경로의 파일을 열고 파일핸들을 받아오는 함수.
		&filePtr_,				//열린 파일에 대한 파일핸들의 주소값.
		path_.string().c_str(),	//경로가 포함된 파일 이름.
		mode.c_str()			//파일 오픈 모드. 
	);

	if (0 != openResult)
	{
		MsgBoxAssert("파일을 정상적으로 여는데 실패했습니다.");
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
	fread_s(
		_readData,
		_dataSize,
		_readSize,
		1,			//읽는 횟수.
		filePtr_
	);
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
	fwrite(
		_writeData,
		_writeSize,
		1,			//쓰는 횟수.
		filePtr_
	);
}

void GameEngineFile::Write(const std::string& _text)
{
	// 크기를 저장해줘야 합니다.
	// string은? 크기가 일정한 데이터를 가지고 있나요?
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
	std::string allString;

	uintmax_t fileSize = GetFileSize();

	allString.resize(fileSize);	//unsigned long long == uintmax_t == size_t.

	Read(&allString[0], fileSize, fileSize);

	return allString;
}

uintmax_t GameEngineFile::GetFileSize() const
{
	return std::filesystem::file_size(this->path_);
}

uintmax_t GameEngineFile::GetFileSize(const std::filesystem::path& _path)
{
	return std::filesystem::file_size(_path);
}
