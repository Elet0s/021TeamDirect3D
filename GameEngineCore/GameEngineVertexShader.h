#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineVertexShader: public GameEngineRes<GameEngineVertexShader>, public GameEngineShader
{
	//버텍스 셰이더: 인풋레이아웃에서 알려준 형식대로 넘어온 버텍스들을, 하나하나 내가 원하는 위치로 조작하는 것.
	//대개는 WVP 행렬을 적용시킨다.

	friend GameEngineRes<GameEngineVertexShader>;
	//GameEngineVertexShader 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend GameEngineShader;
	//

	friend class GameEngineInputLayout;
	//


private:
	GameEngineVertexShader();
	~GameEngineVertexShader();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

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

	inline GameEngineVertexShader* GetInstancingShader()
	{
		return instancingVertexShader_;
	}

private:	
	static GameEngineVertexShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEngineVertexShader* Load(
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


	GameEngineVertexShader* instancingVertexShader_;
};

