#pragma once
#include "GameEngineRes.h"

class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh : public GameEngineRes<GameEngineMesh>
{
	//메쉬를 구성하는 두가지 요소인 버텍스버퍼와 인덱스버퍼를 묶어서 관리하는 클래스.

public:
	GameEngineMesh();
	~GameEngineMesh();

private:

	GameEngineMesh(const GameEngineMesh& _other) = delete;
	GameEngineMesh(GameEngineMesh&& _other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete;


public:
	//메쉬와 동일한 이름을 가진 버텍스버퍼와 인덱스버퍼로 메쉬 생성,
	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _meshName);

	//메쉬 이름, 버텍스버퍼 이름, 인덱스버퍼 이름을 각각 지정해서 메쉬 생성.
	static std::shared_ptr<GameEngineMesh> Create(
		const std::string_view& _meshName,
		const std::string_view& _vertexBufferName,
		const std::string_view& _indexBufferName
	);

	static std::shared_ptr<GameEngineMesh> Create(
		std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer,
		std::shared_ptr<GameEngineIndexBuffer> _indexBuffer
	);

	//이 메쉬에 버텍스버퍼를 세팅하는 함수.
	void SetVertexBuffer_InputAssembler1(const std::string_view& _vertexBufferName);

	void SetVertexBuffer_InputAssembler1(std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer);

	//이 메쉬에 인덱스버퍼를 세팅하는 함수.
	void SetIndexBuffer_InputAssembler2(const std::string_view& _indexBufferName);

	void SetIndexBuffer_InputAssembler2(std::shared_ptr<GameEngineIndexBuffer> _indexBuffer);

	void Setting();	//이 리소스를 렌더링 파이프라인에 연결하는 함수.

	void Render();

	const class GameEngineInputLayoutDesc& GetInputLayoutDesc() const;

private:
	void InputAssembler1_VertexBufferSetting();

	void InputAssembler2_IndexBufferSetting();



private:
	std::shared_ptr<GameEngineVertexBuffer> vertexBuffer_;
	std::shared_ptr<GameEngineIndexBuffer> indexBuffer_;

};

