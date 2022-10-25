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
	std::vector<char> dataBuffer_;
	GameEngineShaderResourceHelper shaderResourceHelper_;
	GameEngineMaterial* instancingPipeLine_;
	GameEngineInstancingBuffer* instancingBuffer_;

	int dataInsert_;
	size_t size_;
	unsigned int count_;
	int maxDataCount_;


};

