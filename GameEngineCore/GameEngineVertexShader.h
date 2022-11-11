#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineVertexShader : public GameEngineRes<GameEngineVertexShader>, public GameEngineShader
{
	//버텍스 셰이더: 인풋레이아웃에서 알려준 형식대로 넘어온 버텍스들을, 하나하나 내가 원하는 위치로 조작하는 것.
	//대개는 WVP 행렬을 적용시킨다.

	friend GameEngineShader;
	//

	friend class GameEngineInputLayout;
	//


public:
	GameEngineVertexShader();
	~GameEngineVertexShader();

private:
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete;


public:
	void Setting();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

public:
	inline bool IsInstancing()
	{
		return nullptr != instancingVertexShader_->vertexShader_;
	}

	inline std::shared_ptr<GameEngineVertexShader> GetInstancingShader()
	{
		return instancingVertexShader_;
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
	void InstancingShaderCompile(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);

private:
	void CreateVertexShader();		//두 함수간 차이는 경고메세지밖에 없는 점 주의.
	void CreateInstancingShader();	//두 함수간 차이는 경고메세지밖에 없는 점 주의.

private:
	ID3D11VertexShader* vertexShader_;


	std::shared_ptr<GameEngineVertexShader> instancingVertexShader_;
};

