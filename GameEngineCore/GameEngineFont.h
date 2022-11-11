#pragma once
#include "GameEngineRes.h"
#include <FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

class GameEngineFont : public GameEngineRes<GameEngineFont>
{

	friend class GameEngineFontInit;

	static IFW1Factory* fontFactory_;

public:
	GameEngineFont();
	~GameEngineFont();

private:

	GameEngineFont(const GameEngineFont& _other) = delete;
	GameEngineFont(GameEngineFont&& _other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _other) = delete;
	GameEngineFont& operator=(const GameEngineFont&& _other) = delete;


public:
	static std::shared_ptr<GameEngineFont> Load(const std::string_view& _path, const std::string_view& _name);
	void FontDraw(
		const std::string_view& _text,
		float _fontSize,
		const float4& _screenPos,
		const float4& _color,
		UINT _flag = FW1_LEFT
	);

public:
	static std::shared_ptr<GameEngineFont> Load(const std::string_view& _path)
	{
		return Load(_path, GameEnginePath::GetFileName(_path));
	}



private:
	void LoadFont(const std::string_view& _path);

private:
	IFW1FontWrapper* fontWrapper_;


};

