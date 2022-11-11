#pragma once
#include "GameEngineRes.h"


class GameEngineInstancingBuffer : public GameEngineRes<GameEngineInstancingBuffer>
{
	//인스턴스렌더링에 필요한 정보들을 GPU로 보내기 전에 한데 모아 저장하는 버퍼.
	//버텍스버퍼의 일종.


public:
	GameEngineInstancingBuffer();
	~GameEngineInstancingBuffer();

private:

	GameEngineInstancingBuffer(const GameEngineInstancingBuffer& _other) = delete;
	GameEngineInstancingBuffer(GameEngineInstancingBuffer&& _other) noexcept = delete;
	GameEngineInstancingBuffer& operator=(const GameEngineInstancingBuffer& _other) = delete;
	GameEngineInstancingBuffer& operator=(const GameEngineInstancingBuffer&& _other) = delete;


public:
	static std::shared_ptr<GameEngineInstancingBuffer> Create(unsigned int _count, unsigned int _size);

	void CreateInstancingBuffer(unsigned int _count, unsigned int _size);

	void ChangeData(const void* _data, size_t _dataSize);

public:
	unsigned int GetBufferCount()
	{
		return bufferCount_;
	}

	ID3D11Buffer* GetBuffer()
	{
		return instancingBuffer_;
	}

	unsigned int GetDataSize()
	{
		return dataSize_;
	}


private:
	void Release();

private:
	ID3D11Buffer* instancingBuffer_;
	D3D11_BUFFER_DESC instancingBufferDesc_;
	unsigned int bufferCount_;	//버퍼에 저장된 데이터 갯수.
	unsigned int dataSize_;		//데이터 한개 크기.
};

