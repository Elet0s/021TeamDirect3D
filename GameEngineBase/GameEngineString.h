#pragma once

class GameEngineString
{
	//���ڵ�: 

	//�ƽ�Ű�ڵ�(American Standard Code for Information Interchange, �̱� ���� ��ȯ ǥ�� ��ȣ): 
	//1963�� ANSI���� ǥ��ȭ�� 1����Ʈ ���� ���ڵ� ü��. 
	//1����Ʈ == 8��Ʈ �� �и�Ƽ ��Ʈ(Parity Bit: ���� ���� ������ ��Ʈ)�� ����ϴ� 1��Ʈ�� ������ 
	// ������ 7��Ʈ�� ���ڸ� ǥ���ϹǷ� 2^7=128���� ���ڵ�� �����Ǿ� �ִ�. 
	//��ҹ��� ���ĺ� 26*2=52���� + ���� 10���� + 33���� ���� ������ Ư������ + 33���� 
	// ��� �Ұ����� ����ڵ�� �̷���� �ִ�.


	//ANSI: �̱� ���� ǥ�� ��ȸ(American National Standards Institute) Ȥ�� 
	// �װ����� ������ 1����Ʈ '�̻�'�� ũ��(��Ƽ����Ʈ(Multibyte))�� ���� ����ü��.
	//���� �� ���ڴ� �뷮�� �������̶� ���ڿ� ���� �ľ��� ��ư�, 
	// ���� ���̶�, �� ����� �ڵ����������� �ٸ� ���ڸ� ǥ���ϹǷ�, ������ �� �޶����� �ڵ��������� �޶����� 
	// �� ������ �ƹ� �������� ���ڿ��� �ٸ� ������ �ǹ̾��� ��ȣ ������ �Ǵ�, ���� ���� ������ �߻��Ѵ�.
	
	//�����ڵ�(Unicode): �����ڵ� �ܼҽþ�(Unicode Consortium)���� ����, ������ ��� ���ڸ� ǥ���ϱ� ���� ���� ����ü��.


private:

	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _other) = delete;
	GameEngineString(GameEngineString&& _other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _other) = delete;
	GameEngineString& operator=(GameEngineString&& _other) = delete;

public:
	//�־��� ���ڵ��� ���� �빮�ڷ� �����ϴ� �Լ�. �Է¹��� �ؽ�Ʈ�� �ٲ۴�.
	static void ToUpper(std::string& _text);

	//�־��� ���ڵ��� ���� �빮�ڷ� �����ϴ� �Լ�. �ٲ��� �ؽ�Ʈ�� ��ȯ�Ѵ�.
	static std::string ToUpperReturn(const std::string_view& _text);

	//���ڿ� �κ� ��ü. ��Ʈ�� ��ȯ.
	static std::string Replace(
		const std::string_view& _text,
		const std::string_view& _prevText,
		const std::string_view& _newText
	);

	//���ڿ� �κ� ��ü.
	static void Replace(
		std::string& _text,
		const std::string_view& _prevText,
		const std::string_view& _newText
	);

	static bool AnsiToUnicode(const std::string_view& _inText, std::wstring& _outText);
	static std::wstring AnsiToUnicodeReturn(const std::string_view& _inText);

	static bool UnicodeToUTF8(const std::wstring_view& _inText, std::string& _outText);
	static std::string UnicodeToUTF8Return(const std::wstring_view& _inText);

	static bool AnsiToUTF8(const std::string_view& _inText, std::string& _outText);
	static std::string AnsiToUTF8Return(const std::string_view& _inText);

	static bool UTF8ToUnicode(const std::string_view& _inText, std::wstring& _outText);
	static std::wstring UTF8ToUnicodeReturn(const std::string_view& _inText);

	static bool UnicodeToAnsi(const std::wstring_view& _inText, std::string& _outText);
	static std::string UnicodeToAnsiReturn(const std::wstring_view& _inText);

	static bool UTF8ToAnsi(const std::string_view& _inText, std::string& _outText);
	static std::string UTF8ToAnsiReturn(const std::string_view& _inText);
};

