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
	void Set();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

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

	bool isDeferredRendering_;	//true: gBuffer ����Ÿ���� �ؽ�ó�� �������ϴ� ���۵巻������ �ȼ����̴�.
};

