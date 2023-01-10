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
	void Set();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

public:
	bool IsInstancing() const
	{
		return nullptr != inst_PixelShader_->pixelShader_;
	}

	bool IsDeferredRendering() const
	{
		return this->isDeferredRendering_;
	}

	inline std::shared_ptr<GameEnginePixelShader> GetInst_PixelShader()
	{
		return inst_PixelShader_;
	}

private:
	static std::shared_ptr<GameEnginePixelShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static std::shared_ptr<GameEnginePixelShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void InstancingPixelShaderCompile(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);

	void CreatePixelShader();
	void CreateInstancingPixelShader();

private:
	ID3D11PixelShader* pixelShader_;

	std::shared_ptr<GameEnginePixelShader> inst_PixelShader_;

	bool isDeferredRendering_;	//true: gBuffer 렌더타겟의 텍스처에 렌더링하는 디퍼드렌더링용 픽셀셰이더.
};

