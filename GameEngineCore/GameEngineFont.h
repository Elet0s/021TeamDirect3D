#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore\ThirdParty\FW1FontWrapper\Include\FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

class GameEngineFont: public GameEngineRes<GameEngineFont>
{
	friend GameEngineRes<GameEngineFont>;
	//GameEngineFont Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend class GameEngineFontInit;

	static IFW1Factory* fontFactory_;

private:
	GameEngineFont();
	~GameEngineFont();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineFont(const GameEngineFont& _other) = delete;
	GameEngineFont(GameEngineFont&& _other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _other) = delete;
	GameEngineFont& operator=(const GameEngineFont&& _other) = delete;


public:
	static GameEngineFont* Load(const std::string& _path, const std::string& _name);
	void FontDraw(
		const std::string& _text,
		float _fontSize,
		const float4& _screenPos,
		const float4& _color,
		UINT _flag = FW1_LEFT
	);

public:	
	static GameEngineFont* Load(const std::string& _path)
	{
		return Load(_path, GameEnginePath::GetFileName(_path));
	}



private:
	void LoadFont(const std::string& _path);

private:
	IFW1FontWrapper* fontWrapper_;


};

