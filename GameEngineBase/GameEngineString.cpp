#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

void GameEngineString::ToUpper(std::string& _text)
{
	std::transform(
		_text.begin(),
		_text.end(),
		_text.begin(),
		[](int c)->int
		{
			if ('a' <= c && 'z' >= c)
			{
				return std::toupper(c);
			}
			return c;
		}
	);
}

std::string GameEngineString::ToUpperReturn(const std::string_view& _text)
{
	std::string returnText = _text.data();

	std::transform(
		returnText.begin(),
		returnText.end(),
		returnText.begin(),
		[](int c)->int
		{
			if ('a' <= c && 'z' >= c)
			{
				return std::toupper(c);
			}
			return c;
		}
	);

	return returnText;
}

std::string GameEngineString::Replace(
	const std::string_view& _text,
	const std::string_view& _prevText,
	const std::string_view& _newText
)
{
	size_t findIndex = _text.find(_prevText);

	if (std::string::npos == findIndex)
	{
		return _text.data();
	}

	std::string resultString = _text.data();
	resultString.replace(findIndex, _prevText.size(), _newText);
	return resultString;
}

void GameEngineString::Replace(
	std::string& _text,
	const std::string_view& _prevText,
	const std::string_view& _newText
)
{
	size_t findIndex = _text.find(_prevText);

	if (std::string::npos == findIndex)
	{
		return;
	}

	_text.replace(findIndex, _prevText.size(), _newText);
}

bool GameEngineString::AnsiToUnicode(const std::string_view& _inText, std::wstring& _outText)
{
	int outSize = MultiByteToWideChar(		//
		CP_ACP,								//
		0,									//
		_inText.data(),					//
		static_cast<int>(_inText.size()),	//
		nullptr,							//
		0									//
	);
	if (0 == outSize)
	{
		MsgBoxAssert("Ansi->Unicode 변환에 실패했습니다.");
		return false;
	}
	else
	{
		_outText.resize(outSize);
	}

	if (0 == MultiByteToWideChar(				//
		CP_ACP,									//
		0,										//
		_inText.data(),						//
		static_cast<int>(_inText.size()),		//	
		&_outText[0],							//
		outSize									//
	))
	{
		MsgBoxAssert("Ansi->Unicode 변환에 실패했습니다.");
		return false;
	}

	return true;
}

std::wstring GameEngineString::AnsiToUnicodeReturn(const std::string_view& _inText)
{
	std::wstring returnText = L"";

	int size = MultiByteToWideChar(
		CP_ACP,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		nullptr,
		0
	);
	if (0 == size)
	{
		MsgBoxAssert("Ansi->Unicode 변환에 실패했습니다.");
		return L"";
	}

	returnText.resize(size);

	if (0 >= MultiByteToWideChar(
		CP_ACP,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		&returnText[0],
		size
	))
	{
		MsgBoxAssert("Ansi->Unicode 변환에 실패했습니다.");
		return L"";
	}

	return returnText;
}

bool GameEngineString::UnicodeToUTF8(const std::wstring_view& _inText, std::string& _outText)
{
	int outSize = WideCharToMultiByte(
		CP_UTF8, 0, _inText.data(), static_cast<int>(_inText.size()), nullptr, 0, nullptr, nullptr);

	if (0 >= outSize)
	{
		MsgBoxAssert("Unicode->UTF8 변환에 실패했습니다.");
		return false;
	}

	_outText.resize(outSize);

	if (0 == WideCharToMultiByte(			//
		CP_UTF8,							//
		0,									//
		_inText.data(),						//
		static_cast<int>(_inText.size()),	//
		&_outText[0],						//
		static_cast<int>(_outText.size()),	//
		nullptr,							//
		nullptr								//
	))
	{
		MsgBoxAssert("Unicode->UTF8 변환에 실패했습니다.");
		return false;
	}

	return true;
}

std::string GameEngineString::UnicodeToUTF8Return(const std::wstring_view& _inText)
{
	std::string result = "";
	UnicodeToUTF8(_inText, result);
	return result;
}

bool GameEngineString::AnsiToUTF8(const std::string_view& _inText, std::string& _outText)
{
	std::wstring wideString = L"";
	AnsiToUnicode(_inText, wideString);
	UnicodeToUTF8(wideString, _outText);
	return true;
}

std::string GameEngineString::AnsiToUTF8Return(const std::string_view& _inText)
{
	std::wstring wideString = L"";
	std::string result = "";

	AnsiToUnicode(_inText, wideString);
	UnicodeToUTF8(wideString, result);

	return result;
}

bool GameEngineString::UTF8ToUnicode(const std::string_view& _inText, std::wstring& _outText)
{
	_outText.clear();
	int outSize = MultiByteToWideChar(
		CP_UTF8,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		nullptr,
		0
	);

	if (0 >= outSize)
	{
		MsgBoxAssert("UTF8->Unicode 변환에 실패했습니다.");
		return false;
	}

	_outText.resize(outSize);

	if (0 >= MultiByteToWideChar(
		CP_UTF8,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		&_outText[0],
		outSize
	))
	{
		MsgBoxAssert("UTF8->Unicode 변환에 실패했습니다.");
		return false;
	}

	return true;
}

std::wstring GameEngineString::UTF8ToUnicodeReturn(const std::string_view& _inText)
{
	std::wstring returnText = L"";
	UTF8ToUnicode(_inText, returnText);
	return returnText;
}

bool GameEngineString::UnicodeToAnsi(const std::wstring_view& _inText, std::string& _outText)
{
	int outSize = WideCharToMultiByte(
		CP_ACP,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		nullptr,
		0,
		nullptr,
		nullptr
	);

	if (0 >= outSize)
	{
		MsgBoxAssert("Unicode->Ansi 변환에 실패했습니다.");
		return false;
	}

	_outText.resize(outSize);

	if (0 >= WideCharToMultiByte(
		CP_UTF8,
		0,
		_inText.data(),
		static_cast<int>(_inText.size()),
		&_outText[0],
		static_cast<int>(_outText.size()),
		nullptr,
		nullptr
	))
	{
		MsgBoxAssert("Unicode->Ansi 변환에 실패했습니다.");
		return false;
	}

	return true;
}

std::string GameEngineString::UnicodeToAnsiReturn(const std::wstring_view& _inText)
{
	std::string returnText = "";
	UnicodeToAnsi(_inText, returnText);
	return returnText;
}

bool GameEngineString::UTF8ToAnsi(const std::string_view& _inText, std::string& _outText)
{
	return UnicodeToAnsi(UTF8ToUnicodeReturn(_inText), _outText);
}

std::string GameEngineString::UTF8ToAnsiReturn(const std::string_view& _inText)
{
	std::string returnText = "";
	std::wstring wideString = L"";
	UTF8ToUnicode(_inText, wideString);
	UnicodeToAnsi(wideString, returnText);
	return returnText;
}
