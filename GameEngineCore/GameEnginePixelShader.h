#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineRes<GameEnginePixelShader>, public GameEngineShader
{
	//�ȼ����̴�: �� �ȼ��� ������ �����Ѵ�.

	friend GameEngineRes<GameEnginePixelShader>;
	//GameEnginePixelShader Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend GameEngineShader;
	//GameEnginePixelShader�� Load() �Լ��� GameEngineShaderŬ�������� ȣ���ϱ� ���� ������.

private:
	GameEnginePixelShader();
	~GameEnginePixelShader();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

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

	inline GameEnginePixelShader* GetInst_PixelShader()
	{
		return inst_PixelShader_;
	}

private:
	static GameEnginePixelShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEnginePixelShader* Load(
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

	GameEnginePixelShader* inst_PixelShader_;

	bool isDeferredRendering_;	//true: gBuffer ����Ÿ���� �ؽ�ó�� �������ϴ� ���۵巻������ �ȼ����̴�.
};

