#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineVertexShader : public GameEngineRes<GameEngineVertexShader>, public GameEngineShader
{
	//���ؽ� ���̴�: ��ǲ���̾ƿ����� �˷��� ���Ĵ�� �Ѿ�� ���ؽ�����, �ϳ��ϳ� ���� ���ϴ� ��ġ�� �����ϴ� ��.
	//�밳�� WVP ����� �����Ų��.

	friend GameEngineShader;
	//

	friend class GameEngineInputLayout;
	//��ǲ���̾ƿ��� ������ �� ���ؽ����ۿ� ���ؽ����̴��� ������ �ʿ��ϹǷ� ������.


public:
	GameEngineVertexShader();
	~GameEngineVertexShader();

private:
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete;


public:
	void Set();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

public:
	inline bool IsInstancing()
	{
		return nullptr != inst_VertexShader_->vertexShader_;
	}

	inline std::shared_ptr<GameEngineVertexShader> GetInst_VertexShader()
	{
		return inst_VertexShader_;
	}

private:
	static std::shared_ptr<GameEngineVertexShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static std::shared_ptr<GameEngineVertexShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void InstancingVertexShaderCompile(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);

private:
	void CreateVertexShader();		//�� �Լ��� ���̴� ���޼����ۿ� ���� �� ����.
	void CreateInstancingVertexShader();	//�� �Լ��� ���̴� ���޼����ۿ� ���� �� ����.

private:
	ID3D11VertexShader* vertexShader_;

	std::shared_ptr<GameEngineVertexShader> inst_VertexShader_;


};

