#pragma once
#include "GameEngineRes.h"

class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh : public GameEngineRes<GameEngineMesh>
{
	//�޽��� �����ϴ� �ΰ��� ����� ���ؽ����ۿ� �ε������۸� ��� �����ϴ� Ŭ����.

public:
	GameEngineMesh();
	~GameEngineMesh();

private:

	GameEngineMesh(const GameEngineMesh& _other) = delete;
	GameEngineMesh(GameEngineMesh&& _other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete;


public:
	//�޽��� ������ �̸��� ���� ���ؽ����ۿ� �ε������۷� �޽� ����,
	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _meshName);

	//�޽� �̸�, ���ؽ����� �̸�, �ε������� �̸��� ���� �����ؼ� �޽� ����.
	static std::shared_ptr<GameEngineMesh> Create(
		const std::string_view& _meshName,
		const std::string_view& _vertexBufferName,
		const std::string_view& _indexBufferName
	);

	static std::shared_ptr<GameEngineMesh> Create(
		std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer,
		std::shared_ptr<GameEngineIndexBuffer> _indexBuffer
	);

	//�� �޽��� ���ؽ����۸� �����ϴ� �Լ�.
	void SetVertexBuffer_InputAssembler1(const std::string_view& _vertexBufferName);

	void SetVertexBuffer_InputAssembler1(std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer);

	//�� �޽��� �ε������۸� �����ϴ� �Լ�.
	void SetIndexBuffer_InputAssembler2(const std::string_view& _indexBufferName);

	void SetIndexBuffer_InputAssembler2(std::shared_ptr<GameEngineIndexBuffer> _indexBuffer);

	void Setting();	//�� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

	void Render();

	const class GameEngineInputLayoutDesc& GetInputLayoutDesc() const;

private:
	void InputAssembler1_VertexBufferSetting();

	void InputAssembler2_IndexBufferSetting();



private:
	std::shared_ptr<GameEngineVertexBuffer> vertexBuffer_;
	std::shared_ptr<GameEngineIndexBuffer> indexBuffer_;

};

