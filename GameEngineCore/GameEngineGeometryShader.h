#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineGeometryShader: public GameEngineRes<GameEngineGeometryShader>, public GameEngineShader
{
	//지오메트리 셰이더.
	//버텍스셰이더에서 넣어준 도형 외의 점, 선, 삼각형 등의 자체적인 기본 도형을 생성해서 래스터라이저로 넘기는 셰이더.
	//버텍스셰이더 후, 래스터라이저 이전에 실행된다.

	friend GameEngineRes<GameEngineGeometryShader>;
	//GameEngineGeometryShader 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend GameEngineShader;
	//GameEngineGeometryShader의 Load() 함수를 GameEngineShader클래스에서 호출하기 위해 프렌드.

private:
	GameEngineGeometryShader();
	~GameEngineGeometryShader();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineGeometryShader(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&& _other) noexcept = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader&& _other) = delete;


public:
	void Set();

private:
	static GameEngineGeometryShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEngineGeometryShader* Load(
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

