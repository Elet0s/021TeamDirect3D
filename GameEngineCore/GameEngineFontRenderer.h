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

enum class FontPositionMode	//������ ��ǥ�� ����.
{
	World = 0x4,	//���ڸ� ��ġ�ϴ� ��ǥ�� ������ǥ�� ����̴�.
	Window = 0X8	//���ڸ� ��ġ�ϴ� ��ǥ�� ��������ǥ�� ����̴�.
};

class GameEngineRenderTarget;
class GameEngineFont;
class GameEngineFontRenderer : public GameEngineDefaultRenderer
{
	//�� Ŭ������ ���� ����:

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
	void SetText(const std::string_view& _text, const std::string_view& _font = "����");

public:
	const std::string& GetText()
	{
		return text_;
	}

	void SetTextPosition(const float4& _position)	//������ ��ġ ����.
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

	//���ڸ� ������ ������ ����/���/�����ʿ� ��ġ�Ѵ�.
	void SetLeftAndRightSort(LeftAndRightSort _value)
	{
		lr_ = _value;
	}

	//���ڸ� ������ ������ ��/�߰�/�Ʒ��� ��ġ�Ѵ�.
	void SetTopAndBotSort(TopAndBotSort _value)
	{
		tb_ = _value;
	}

	//������ ��ǥ�� ������ǥ��/��������ǥ��� ����.
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
	float4 textPosition_;	//���� ��ġ. �⺻������ ��������ǥ�� ���

	LeftAndRightSort lr_;	//���ڸ� ������ ������ ����/���/�����ʿ� ��ġ�Ѵ�.
	TopAndBotSort tb_;		//���ڸ� ������ ������ ��/�߰�/�Ʒ��� ��ġ�Ѵ�.
	FontPositionMode mode_;	//������ ��ǥ�� ������ǥ��/��������ǥ�� �������� ���� ��ġ�Ѵ�.

};

