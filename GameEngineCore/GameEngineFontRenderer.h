#pragma once
#include "GameEngineDefaultRenderer.h"

enum class LeftAndRightSort
{
	Left = 0x0,
	Center = 0x1,
	Right = 0x2,
};

enum class TopAndBotSort
{
	Top = 0x0,
	Mid = 0x4,
	Bot = 0x8
};

enum class FontPositionMode	//글자의 좌표계 설정.
{
	World = 0x4,	//글자를 배치하는 좌표가 월드좌표계 기반이다.
	Window = 0X8	//글자를 배치하는 좌표가 윈도우좌표계 기반이다.
};

class GameEngineRenderTarget;
class GameEngineFont;
class GameEngineFontRenderer : public GameEngineDefaultRenderer
{
	//이 클래스의 존재 이유:

public:
	GameEngineFontRenderer();
	~GameEngineFontRenderer();

protected:
	GameEngineFontRenderer(const GameEngineFontRenderer& _other) = delete;
	GameEngineFontRenderer(GameEngineFontRenderer&& _other) noexcept = delete;

private:
	GameEngineFontRenderer& operator=(const GameEngineFontRenderer& _other) = delete;
	GameEngineFontRenderer& operator=(const GameEngineFontRenderer&& _other) = delete;


public:
	void SetText(const std::string_view& _text, const std::string_view& _font = "돋움");

public:
	const std::string& GetText()
	{
		return text_;
	}

	void SetTextPosition(const float4& _position)	//글자의 위치 설정.
	{
		textPosition_ = _position;
	}

	float4 GetTextPostion()
	{
		return textPosition_;
	}

	void SetColor(const float4& _color)
	{
		fontColor_ = _color;
	}

	void SetSize(float _size)
	{
		fontSize_ = _size;
	}

	//글자를 지정한 지점의 왼쪽/가운데/오른쪽에 배치한다.
	void SetLeftAndRightSort(LeftAndRightSort _value)
	{
		lr_ = _value;
	}

	//글자를 지정한 지점의 위/중간/아래에 배치한다.
	void SetTopAndBotSort(TopAndBotSort _value)
	{
		tb_ = _value;
	}

	//글자의 좌표를 월드좌표계/윈도우좌표계로 설정.
	void SetPositionMode(FontPositionMode _mode)
	{
		mode_ = _mode;
	}

protected:
	virtual void Start() override;
	void Render(float _deltaTime) override;

private:
	static GameEngineRenderTarget* fontTarget_;

	std::string text_;
	GameEngineFont* font_;
	float fontSize_;
	float4 fontColor_;
	float4 textPosition_;	//글자 위치. 기본설정은 윈도우좌표계 기반

	LeftAndRightSort lr_;	//글자를 지정한 지점의 왼쪽/가운데/오른쪽에 배치한다.
	TopAndBotSort tb_;		//글자를 지정한 지점의 위/중간/아래에 배치한다.
	FontPositionMode mode_;	//글자의 좌표를 월드좌표계/윈도우좌표계 기준으로 보고 배치한다.

};

