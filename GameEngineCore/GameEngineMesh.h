#pragma once
#include "GameEngineRes.h"

class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineInstancingBuffer;
class GameEngineMesh : public GameEngineRes<GameEngineMesh>
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
	static GameEngineMesh* Create(const std::string_view& _meshName);

	//�޽� �̸�, ���ؽ����� �̸�, �ε������� �̸��� ���� �����ؼ� �޽� ����.
	static GameEngineMesh* Create(
		const std::string_view& _meshName,
		const std::string_view& _vertexBufferName,
		const std::string_view& _indexBufferName
	);

	static GameEngineMesh* Create(
		GameEngineVertexBuffer* _vertexBuffer,
		GameEngineIndexBuffer* _indexBuffer
	);

	//�� �޽��� ���ؽ����۸� �����ϴ� �Լ�.
	void SetVertexBuffer_InputAssembler1(const std::string_view& _vertexBufferName);

	void SetVertexBuffer_InputAssembler1(GameEngineVertexBuffer* _vertexBuffer);

	//�� �޽��� �ε������۸� �����ϴ� �Լ�.
	void SetIndexBuffer_InputAssembler2(const std::string_view& _indexBufferName);

	void SetIndexBuffer_InputAssembler2(GameEngineIndexBuffer* _indexBuffer);

	//�� �޽��� DC�� �����ϴ� �Լ�.
	void Set();	

	//�� �޽��� �ν��Ͻ̹��۸� DC�� �����ϴ� �Լ�.
	void SetInstancingBuffer(GameEngineInstancingBuffer* _instancingBuffer);	
	//�ν��Ͻ̹��۴� ���⼭ �������ۿ� �Բ� IA1 �ܰ�� ����ȴ�. 
	// �׷��� �ν��Ͻ̹��ۿ��� ���� �Լ��� ���� �������� �ʴ´�.

	//������ �Լ�.
	void Render();

	//�ν��Ͻ� ������ �Լ�.
	void RenderInstances(size_t _instancingCount);

	const class GameEngineInputLayoutDesc& GetInputLayoutDesc() const;

private:
	void InputAssembler1_VertexBufferSetting();

	void InputAssembler2_IndexBufferSetting();



private:
	GameEngineVertexBuffer* vertexBuffer_;
	GameEngineIndexBuffer* indexBuffer_;

};

