#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineComputeShader: public GameEngineRes<GameEngineComputeShader>, public GameEngineShader
{


	friend GameEngineRes<GameEngineComputeShader>;
	//GameEngineComputeShader 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend GameEngineShader;
	//GameEngineComputeShader의 Load() 함수를 GameEngineShader클래스에서 호출하기 위해 프렌드.


private:
	GameEngineComputeShader();
	~GameEngineComputeShader();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineComputeShader(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader(GameEngineComputeShader&& _other) noexcept = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader&& _other) = delete;


public:	
	void Set();	

private:
	static GameEngineComputeShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEngineComputeShader* Load(
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

