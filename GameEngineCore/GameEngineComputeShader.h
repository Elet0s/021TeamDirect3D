#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineComputeShader: public GameEngineRes<GameEngineComputeShader>, public GameEngineShader
{
	friend GameEngineShader;


public:
	GameEngineComputeShader();
	~GameEngineComputeShader();

	GameEngineComputeShader(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader(GameEngineComputeShader&& _other) noexcept = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader&& _other) = delete;


public:	
	void Set();	

private:
	static std::shared_ptr<GameEngineComputeShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static std::shared_ptr<GameEngineComputeShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void CreateComputeShader();

private:
	ID3D11ComputeShader* computeShader_;

};

