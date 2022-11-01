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
	//������ ���ڸ��� 2����Ʈ �̻�(���̵����Ʈ(Widebyte))�� ������ ũ���, �����Ǵ� �ڵ尪�� ������ �ִ�. 
	//�׷��� �� �޶����� �ڵ尪 ���� ��ü�� �޶����� ���ڱ��� ������ �߻����� �ʴ´�.
	
	//UTF-8(Unicode Transformation Format - 8bit): �� ���ڴ� 8��Ʈ(2����Ʈ)�� ũ�⸦ ������ �����ڵ� ü��.
	//�����ڵ� ������ ���� ���ڴ� ũ�Ⱑ �����鼭�� ���� ���� ���ڸ� ǥ���� �� �����Ƿ� ���� �θ� ���̴� ����ü���̴�.

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

