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

	if (2 == openResult)
	{
		MsgBoxAssertString(path_.string() + "\n존재하지 않는 경로입니다.");
		return;
	}
	else if (0 != openResult)
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
	size_t readResult = fread_s(
		_readData,
		_dataSize,
		_readSize,
		1,			//읽는 횟수.
		filePtr_
	);

	if (0 != ferror(filePtr_))
	{
		MsgBoxAssert("파일을 읽는데 실패했습니다.");
		return;
	}
	//if (0 != feof(filePtr_))
	//{
	//	MsgBoxAssert("파일 끝을 넘어섰습니다.");
	//	return;
	//}
	//알 수 없는 이유로 셰이더파일 크기와 셰이더코드 문자열 길이가 다르므로 feof()같은 파일 끝 검사 하지 말 것.
	//->아마 한글 주석 등의 2바이트 이상 크기의 글자들 때문에 글자 수보다 실제 파일 크기가 더 커진것으로 예상됨.
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
		1,			//쓰는 횟수.
		filePtr_
	);

	if (1 != writeResult)
	{
		MsgBoxAssert("파일 쓰기 실패.");
		return;
	}
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
	uintmax_t fileSize = GetFileSize();	//unsigned long long == uintmax_t == size_t.

	std::string allString = std::string(fileSize, '0');

	//allString.resize(fileSize);	

	Read(&allString[0], fileSize, fileSize);

	return allString;
}

uintmax_t GameEngineFile::GetFileSize() const
{
	return std::filesystem::file_size(this->path_);
	//파일크기를 읽는데 실패하면 -1 == 0xffffffff 반환.
}

uintmax_t GameEngineFile::GetFileSize(const std::filesystem::path& _path)
{
	return std::filesystem::file_size(_path);
}

GameEngineDirectory GameEngineFile::GetDirectory()
{
	return GameEngineDirectory(path_.parent_path());
}
