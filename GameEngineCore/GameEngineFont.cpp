#include "PreCompile.h"
#include "GameEngineFont.h"
#include "GameEngineDevice.h"

IFW1Factory* GameEngineFont::fontFactory_ = nullptr;

class GameEngineFontInit
{
public:
	GameEngineFontInit()
	{
		if (S_OK != FW1CreateFactory(FW1_VERSION, &GameEngineFont::fontFactory_))
		{
			MsgBoxAssert("폰트팩토리 생성 실패.");
			return;
		}
	}

	~GameEngineFontInit()
	{
		if (nullptr != GameEngineFont::fontFactory_)
		{
			GameEngineFont::fontFactory_->Release();
			GameEngineFont::fontFactory_ = nullptr;
		}
	}

private:

};

GameEngineFontInit inst_;


GameEngineFont::GameEngineFont() : fontWrapper_(nullptr)
{
}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != fontWrapper_)
	{
		fontWrapper_->Release();
		fontWrapper_ = nullptr;
	}
}

std::shared_ptr<GameEngineFont> GameEngineFont::Load(const std::string_view& _path, const std::string_view& _name)
{
	std::shared_ptr<GameEngineFont> newRes = CreateNamedRes(_name);
	newRes->LoadFont(_path);
	return newRes;
}

void GameEngineFont::FontDraw(
	const std::string_view& _text,
	float _fontSize,
	const float4& _screenPos,
	const float4& _color,
	UINT _flag /*= FW1_LEFT*/
)
{
	std::wstring wText = GameEngineString::AnsiToUnicodeReturn(_text);


	fontWrapper_->DrawString(
		GameEngineDevice::GetContext(),
		wText.c_str(),
		_fontSize,
		_screenPos.x,
		_screenPos.y,
		_color.GetUINTColor(),
		_flag
	);
}

void GameEngineFont::LoadFont(const std::string_view& _path)
{
	std::wstring wPath = GameEngineString::AnsiToUnicodeReturn(_path);

	if (S_OK != fontFactory_->CreateFontWrapper(
		GameEngineDevice::GetDevice(),
		wPath.c_str(),
		&fontWrapper_
	))
	{
		MsgBoxAssert("폰트 생성 실패.");
		return;
	}
}

