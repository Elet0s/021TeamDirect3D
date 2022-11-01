#pragma once

class GameEngineString
{
	//인코딩: 

	//아스키코드(American Standard Code for Information Interchange, 미국 정보 교환 표준 부호): 
	//1963년 ANSI에서 표준화한 1바이트 문자 인코딩 체계. 
	//1바이트 == 8비트 중 패리티 비트(Parity Bit: 전송 오류 감지용 비트)로 사용하는 1비트를 제외한 
	// 나머지 7비트로 문자를 표현하므로 2^7=128개의 문자들로 구성되어 있다. 
	//대소문자 알파벳 26*2=52글자 + 숫자 10글자 + 33개의 공백 포함한 특수문자 + 33개의 
	// 출력 불가능한 제어문자들로 이루어져 있다.


	//ANSI: 미국 국립 표준 협회(American National Standards Institute) 혹은 
	// 그곳에서 지정한 1바이트 '이상'의 크기(멀티바이트(Multibyte))를 가진 문자체계.
	//언어마다 한 글자당 용량이 제각각이라서 문자열 길이 파악이 어렵고, 
	// 같은 값이라도, 각 언어의 코드페이지마다 다른 글자를 표현하므로, 지정한 언어가 달라지면 코드페이지가 달라져서 
	// 한 언어에서는 아무 문제없는 문자열이 다른 언어에서는 의미없는 기호 나열이 되는, 글자 깨짐 현상이 발생한다.
	
	//유니코드(Unicode): 유니코드 콘소시엄(Unicode Consortium)에서 만든, 전세계 모든 문자를 표현하기 위해 만든 문자체계.
	//각각의 문자마다 2바이트 이상(와이드바이트(Widebyte))의 고정된 크기와, 대응되는 코드값을 가지고 있다. 
	//그래서 언어가 달라지면 코드값 범위 자체가 달라져서 글자깨짐 현상이 발생하지 않는다.
	
	//UTF-8(Unicode Transformation Format - 8bit): 한 글자당 8비트(2바이트)의 크기를 배정한 유니코드 체계.
	//유니코드 포맷중 가장 글자당 크기가 작으면서도 세계 여러 문자를 표현할 수 있으므로 가장 널리 쓰이는 문자체계이다.

private:

	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _other) = delete;
	GameEngineString(GameEngineString&& _other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _other) = delete;
	GameEngineString& operator=(GameEngineString&& _other) = delete;

public:
	//주어진 문자들을 전부 대문자로 변경하는 함수. 입력받은 텍스트를 바꾼다.
	static void ToUpper(std::string& _text);

	//주어진 문자들을 전부 대문자로 변경하는 함수. 바꿔진 텍스트를 반환한다.
	static std::string ToUpperReturn(const std::string& _text);


	static bool AnsiToUnicode(const std::string& _inText, std::wstring& _outText);
	static std::wstring AnsiToUnicodeReturn(const std::string& _inText);

	static bool UnicodeToUTF8(const std::wstring& _inText, std::string& _outText);
	static std::string UnicodeToUTF8Return(const std::wstring& _inText);

	static bool AnsiToUTF8(const std::string& _inText, std::string& _outText);
	static std::string AnsiToUTF8Return(const std::string& _inText);

	static bool UTF8ToUnicode(const std::string& _inText, std::wstring& _outText);
	static std::wstring UTF8ToUnicodeReturn(const std::string& _inText);

	static bool UnicodeToAnsi(const std::wstring& _inText, std::string& _outText);
	static std::string UnicodeToAnsiReturn(const std::wstring& _inText);

	static bool UTF8ToAnsi(const std::string& _inText, std::string& _outText);
	static std::string UTF8ToAnsiReturn(const std::string& _inText);
};

