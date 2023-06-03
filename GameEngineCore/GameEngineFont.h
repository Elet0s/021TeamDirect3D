#pragma once
#include "GameEngineRes.h"
#include <FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

class GameEngineFont : public GameEngineRes<GameEngineFont>
{
	friend GameEngineRes<GameEngineFont>;
	//GameEngineFont 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineFontInit;

	static IFW1Factory* fontFactory_;

private:
	GameEngineFont();
	~GameEngineFont();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineFont(const GameEngineFont& _other) = delete;
	GameEngineFont(GameEngineFont&& _other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _other) = delete;
	GameEngineFont& operator=(const GameEngineFont&& _other) = delete;


public:
	static GameEngineFont* Load(const std::string_view& _path, const std::string_view& _name);
	void FontDraw(
		const std::string_view& _text,
		float _fontSize,
		const float4& _screenPos,
		const float4& _color,
		UINT _flag = FW1_LEFT
	);

public:
	static GameEngineFont* Load(const std::string_view& _path)
	{
		return Load(_path, GameEnginePath::GetFileName(_path));
	}



private:
	void LoadFont(const std::string_view& _path);

private:
	IFW1FontWrapper* fontWrapper_;


};

