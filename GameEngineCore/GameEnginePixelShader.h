#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineRes<GameEnginePixelShader>, public GameEngineShader
{
	//픽셀셰이더: 각 픽셀의 색깔을 결정한다.

	friend GameEngineShader;

public:
	GameEnginePixelShader();
	~GameEnginePixelShader();

private:

	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete;


public:
	void Setting();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

private:
	static std::shared_ptr<GameEnginePixelShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0);
	static std::shared_ptr<GameEnginePixelShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0);
	void CreatePixelShader();

private:
	ID3D11PixelShader* pixelShader_;

};

