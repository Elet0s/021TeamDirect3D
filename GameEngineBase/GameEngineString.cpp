#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

std::string GameEngineString::ToUpperReturn(const std::string& _text)
{
	std::string uppercaseText = _text;

	std::transform(
		uppercaseText.begin(),
		uppercaseText.end(),
		uppercaseText.begin(),
		[](char c)->char
		{
			if ('a' <= c && 'z' >= c)
			{
				return static_cast<char>(std::toupper(static_cast<int>(c)));
			}
			return c;
		}
	);

	return uppercaseText;
}

void GameEngineString::ToUpper(std::string& _text)
{
	std::transform(
		_text.begin(),
		_text.end(),
		_text.begin(),
		[](char c)->char
		{
			if ('a' <= c && 'z' >= c)
			{
				return static_cast<char>(std::toupper(static_cast<int>(c)));
			}
			return c;
		}
	);
}

void GameEngineString::AnsiToUnicode(const std::string& _inText, std::wstring& _outText)
{
	int outSize = MultiByteToWideChar(		//
		CP_ACP,								//
		0,									//
		_inText.c_str(),					//
		static_cast<int>(_inText.size()),	//
		nullptr,							//
		0									//
	);
	if (0 == outSize)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}
	else
	{
		_outText.resize(outSize);
	}

	if (0 == MultiByteToWideChar(				//
		CP_ACP,									//
		0,										//
		_inText.c_str(),						//
		static_cast<int>(_inText.size()),		//	
		&_outText[0],							//
		outSize									//
	))
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}
}

std::wstring GameEngineString::AnsiToUnicodeReturn(const std::string& _inText)
{
	std::wstring returnText = L"";

	int size = MultiByteToWideChar(
		CP_ACP,
		0,
		_inText.c_str(),
		static_cast<int>(_inText.size()),
		nullptr,
		0
	);
	if (size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return L"";
	}

	returnText.resize(size);

	size = MultiByteToWideChar(
		CP_ACP,
		0,
		_inText.c_str(),
		static_cast<int>(_inText.size()),
		&returnText[0],
		size
	);
	if (size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return L"";
	}

	return returnText;
}

void GameEngineString::AnsiToUTF8(const std::string& _inText, std::string& _outText)
{
	std::wstring wideString = L"";

	AnsiToUnicode(_inText, wideString);
	UnicodeToUTF8(wideString, _outText);
}

std::string GameEngineString::AnsiToUTF8Return(const std::string& _inText)
{
	std::wstring wideString = L"";
	std::string result = "";

	AnsiToUnicode(_inText, wideString);
	UnicodeToUTF8(wideString, result);

	return result;
}

void GameEngineString::UnicodeToUTF8(const std::wstring& _inText, std::string& _outText)
{
	int outSize = WideCharToMultiByte(
		CP_UTF8, 0, _inText.c_str(), static_cast<int>(_inText.size()), nullptr, 0, nullptr, nullptr);

	if (outSize == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}

	_outText.resize(outSize);

	outSize = WideCharToMultiByte(				//
		CP_UTF8,							//
		0,									//
		_inText.c_str(),					//
		static_cast<int>(_inText.size()),	//
		&_outText[0],						//
		static_cast<int>(_outText.size()),	//
		nullptr,							//
		nullptr								//
	);

	if (outSize == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}
}