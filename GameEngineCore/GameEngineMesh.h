#pragma once
#include "GameEngineRes.h"

class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh: public GameEngineRes<GameEngineMesh>
{
	//메쉬를 구성하는 두가지 요소인 버텍스버퍼와 인덱스버퍼를 묶어서 관리하는 클래스.

	friend GameEngineRes<GameEngineMesh>;
	//GameEngineMesh 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineMesh();
	~GameEngineMesh();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineMesh(const GameEngineMesh& _other) = delete;
	GameEngineMesh(GameEngineMesh&& _other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete;


public:	
	//메쉬와 동일한 이름을 가진 버텍스버퍼와 인덱스버퍼로 메쉬 생성,
	static GameEngineMesh* Create(const std::string& _meshName);

	//메쉬 이름, 버텍스버퍼 이름, 인덱스버퍼 이름을 각각 지정해서 메쉬 생성.
	static GameEngineMesh* Create(
		const std::string& _meshName,
		const std::string& _vertexBufferName,
		const std::string& _indexBufferName
	);

	static GameEngineMesh* Create(
		GameEngineVertexBuffer* _vertexBuffer,
		GameEngineIndexBuffer* _indexBuffer
	);

	//이 메쉬에 버텍스버퍼를 세팅하는 함수.
	void SetVertexBuffer_InputAssembler1(const std::string& _vertexBufferName);

	void SetVertexBuffer_InputAssembler1(GameEngineVertexBuffer* _vertexBuffer);

	//이 메쉬에 인덱스버퍼를 세팅하는 함수.
	void SetIndexBuffer_InputAssembler2(const std::string& _indexBufferName);

	void SetIndexBuffer_InputAssembler2(GameEngineIndexBuffer* _indexBuffer);

	void Setting();	//이 리소스를 렌더링 파이프라인에 연결하는 함수.

	void Render();

	const class GameEngineInputLayoutDesc& GetInputLayoutDesc() const;

private:
	void InputAssembler1_VertexBufferSetting();

	void InputAssembler2_IndexBufferSetting();

private:
	GameEngineVertexBuffer* vertexBuffer_;
	GameEngineIndexBuffer* indexBuffer_;

};

