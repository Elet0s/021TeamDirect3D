#pragma once
#include "GameEngineShaderResourceHelper.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancing
{
	//�� Ŭ������ ���� ����:

	friend class GameEngineCamera;
	//�ν��Ͻ��� ���̴����ҽ��̹Ƿ� ���ӿ���ī�޶� �ʿ�� �ϴ� ������ �ſ� ���Ƽ� ������� �Ѵ�.

	friend class GameEngineRenderer;
	//���ӿ��������� Ŭ������ �ν��Ͻ��� ���̴����ҽ����ۿ� ī��Ʈ�� �ʿ�� �ϴ� ������??


public:
	static unsigned int minInstancingCount_;
	static unsigned int startInstancingCount_;

public:
	GameEngineInstancing();
	~GameEngineInstancing();

protected:
	GameEngineInstancing(const GameEngineInstancing& _other) = delete;
	GameEngineInstancing(GameEngineInstancing&& _other) noexcept = delete;

private:
	GameEngineInstancing& operator=(const GameEngineInstancing& _other) = delete;
	GameEngineInstancing& operator=(const GameEngineInstancing&& _other) = delete;


public:
	void InstancingBufferChangeData();

public:



private:
	// ���������� Ű�� ���ҵ� �ؾ� �մϴ�.
	// ������ �����ϴٴ°�
	// �Ȱ��� ���̴�
	// �Ȱ��� �Ž�
	// �Ȱ��� �������
	// �Ȱ��� �ؽ�ó�� ���ٴ� ��.

	std::shared_ptr<class GameEngineRenderUnit> renderUnit_;

	GameEngineInstancingBuffer* instancingBuffer_;

	std::vector<char> dataBuffer_;
	GameEngineShaderResourceHelper shaderResourceHelper_;

	int dataInsert_;
	size_t size_;
	unsigned int count_;
	int maxDataCount_;


};

