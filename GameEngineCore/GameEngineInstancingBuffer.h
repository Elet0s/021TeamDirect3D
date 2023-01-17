#pragma once
#include "GameEngineRes.h"


class GameEngineInstancingBuffer : public GameEngineRes<GameEngineInstancingBuffer>
{
	//�ν��Ͻ��������� �ʿ��� ����()���� GPU�� ������ ���� �ѵ� ��� �����ϴ� ����.
	//���ؽ������� ����.

	friend GameEngineRes<GameEngineInstancingBuffer>;
	//GameEngineInstancingBuffer Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineInstancingBuffer();
	~GameEngineInstancingBuffer();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineInstancingBuffer(const GameEngineInstancingBuffer& _other) = delete;
	GameEngineInstancingBuffer(GameEngineInstancingBuffer&& _other) noexcept = delete;
	GameEngineInstancingBuffer& operator=(const GameEngineInstancingBuffer& _other) = delete;
	GameEngineInstancingBuffer& operator=(const GameEngineInstancingBuffer&& _other) = delete;


public:
	static GameEngineInstancingBuffer* Create(size_t _count, size_t _size);

	void CreateInstancingBuffer(size_t _count, size_t _size);

	void ChangeData(const void* _data, size_t _byteWidth);

public:
	size_t GetBufferCount()
	{
		return bufferCount_;
	}

	ID3D11Buffer* GetBuffer() const
	{
		return instancingBuffer_;
	}

	size_t GetDataSize()
	{
		return dataSize_;
	}


private:
	void Release();

private:
	ID3D11Buffer* instancingBuffer_;
	D3D11_BUFFER_DESC instancingBufferDesc_;
	size_t bufferCount_;	//���ۿ� ����� ������ ����.
	size_t dataSize_;		//������ ���� ũ��.
};

