#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineGeometryShader: public GameEngineRes<GameEngineGeometryShader>, public GameEngineShader
{
	//지오메트리 셰이더.
	//버텍스셰이더에서 넣어준 도형 외의 점, 선, 삼각형 등의 자체적인 기본 도형을 생성해서 래스터라이저로 넘기는 셰이더.
	//버텍스셰이더 후, 래스터라이저 이전에 실행된다.

	friend GameEngineShader;

public:
	GameEngineGeometryShader();
	~GameEngineGeometryShader();

private:
	GameEngineGeometryShader(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&& _other) noexcept = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader&& _other) = delete;


public:
	void Set();

private:
	static std::shared_ptr<GameEngineGeometryShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static std::shared_ptr<GameEngineGeometryShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void CreateGeometryShader();

private:
	ID3D11GeometryShader* geometryShader_;

};

