#pragma once
#include "GameEngineShaderResourceHelper.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancing
{
	//�� Ŭ������ ���� ����: �ν��Ͻ̿� �������ְ� �ν��Ͻ̼��̴��� ���� ������ ������ Ŭ����.

	friend class GameEngineCamera;
	//�ν��Ͻ��� ���̴����ҽ��̹Ƿ� ���ӿ���ī�޶� �ʿ�� �ϴ� ������ �ſ� ���Ƽ� ������� �Ѵ�.

	friend class GameEngineRenderer;
	//���ӿ��������� Ŭ������ �ν��Ͻ��� ���̴����ҽ����ۿ� ī��Ʈ�� �ʿ�� �ϴ� ������??


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
	//�� �ν��Ͻ̿� ���������� ����ϴ� �Լ�.
	void PushUnit(std::shared_ptr<class GameEngineRenderUnit> _renderUnit);

private:
	//??
	void InstancingBufferChangeData();


private:
	// ���������� Ű�� ���ҵ� �ؾ� �մϴ�.
	// ������ �����ϴٴ°�
	// �Ȱ��� ���̴�
	// �Ȱ��� �Ž�
	// �Ȱ��� �������
	// �Ȱ��� �ؽ�ó�� ���ٴ� ��.

	std::shared_ptr<class GameEngineRenderUnit> initRenderUnit_;

	std::vector<std::vector<std::shared_ptr<class GameEngineRenderUnit>>> renderUnits_;

	GameEngineInstancingBuffer* instancingBuffer_;

	std::vector<char> dataBuffer_;
	GameEngineShaderResourceHelper shaderResourceHelper_;

	int dataInsert_;
	size_t size_;
	unsigned int count_;
	int maxDataCount_;


};

