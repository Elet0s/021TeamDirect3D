#pragma once
#include "GameEngineRes.h"

class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh: public GameEngineRes<GameEngineMesh>
{
	//�޽��� �����ϴ� �ΰ��� ����� ���ؽ����ۿ� �ε������۸� ��� �����ϴ� Ŭ����.

	friend GameEngineRes<GameEngineMesh>;
	//GameEngineMesh Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineMesh();
	~GameEngineMesh();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineMesh(const GameEngineMesh& _other) = delete;
	GameEngineMesh(GameEngineMesh&& _other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete;


public:	
	//�޽��� ������ �̸��� ���� ���ؽ����ۿ� �ε������۷� �޽� ����,
	static GameEngineMesh* Create(const std::string& _meshName);

	//�޽� �̸�, ���ؽ����� �̸�, �ε������� �̸��� ���� �����ؼ� �޽� ����.
	static GameEngineMesh* Create(
		const std::string& _meshName,
		const std::string& _vertexBufferName,
		const std::string& _indexBufferName
	);

	static GameEngineMesh* Create(
		GameEngineVertexBuffer* _vertexBuffer,
		GameEngineIndexBuffer* _indexBuffer
	);

	//�� �޽��� ���ؽ����۸� �����ϴ� �Լ�.
	void SetVertexBuffer_InputAssembler1(const std::string& _vertexBufferName);

	void SetVertexBuffer_InputAssembler1(GameEngineVertexBuffer* _vertexBuffer);

	//�� �޽��� �ε������۸� �����ϴ� �Լ�.
	void SetIndexBuffer_InputAssembler2(const std::string& _indexBufferName);

	void SetIndexBuffer_InputAssembler2(GameEngineIndexBuffer* _indexBuffer);

	void Setting();	//�� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

	void Render();

	const class GameEngineInputLayoutDesc& GetInputLayoutDesc() const;

private:
	void InputAssembler1_VertexBufferSetting();

	void InputAssembler2_IndexBufferSetting();

private:
	GameEngineVertexBuffer* vertexBuffer_;
	GameEngineIndexBuffer* indexBuffer_;

};

