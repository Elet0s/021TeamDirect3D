#pragma once
#include "GameEngineRes.h"


class GameEngineInstancingBuffer : public GameEngineRes<GameEngineInstancingBuffer>
{
	//인스턴스렌더링에 필요한 정보()들을 GPU로 보내기 전에 한데 모아 저장하는 버퍼.
	//버텍스버퍼의 일종.

	friend GameEngineRes<GameEngineInstancingBuffer>;
	//GameEngineInstancingBuffer 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineInstancingBuffer();
	~GameEngineInstancingBuffer();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

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
	size_t bufferCount_;	//버퍼에 저장된 데이터 갯수.
	size_t dataSize_;		//데이터 단위 크기.
};

