#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineRes<GameEnginePixelShader>, public GameEngineShader
{
	//�ȼ����̴�: �� �ȼ��� ������ �����Ѵ�.

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
	void Setting();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

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

