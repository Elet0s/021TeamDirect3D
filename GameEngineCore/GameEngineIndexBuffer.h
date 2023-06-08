#pragma once
#include "GameEngineRes.h"


class GameEngineIndexBuffer : public GameEngineRes<GameEngineIndexBuffer>
{
	//인덱스버퍼: 버텍스셰이더를 거쳐 넘어온 점들을 어떻게 연결시킬지에 대한 정보를 가진 버퍼.

	//인덱스: 버텍스와 1:1 대응되는 정수형 번호. 
	// 여러 정보를 가진 버텍스를 매번 생성하고 불러내는 것보다,
	// 인덱스를 통해 버텍스를 필요한 만큼만 불러내는것이 연산량을 아낄 수 있다고 한다.

	//그래픽 리소스들 중 버퍼(버텍스 버퍼, 인덱스 버퍼, 상수 버퍼, 스트림 출력 버퍼)는 
	// 리소스뷰 없이도 렌더링 파이프라인에 연결할 수 있다.

	friend GameEngineRes<GameEngineIndexBuffer>;
	//GameEngineIndexBuffer클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _other) = delete;


public:
	static GameEngineIndexBuffer* Create(
		const std::string_view& _name,
		const void* _data,
		UINT _indexSize,
		UINT _indexCount
	);

	static GameEngineIndexBuffer* Create(
		const void* _data,
		UINT _indexSize,
		UINT _indexCount
	);

	void Set();

public:
	template<typename IndexType>
	static GameEngineIndexBuffer* Create(
		const std::string_view& _name,
		const std::vector<IndexType>& _indexes
	)
	{
		return Create(
			_name,
			&_indexes[0],
			static_cast<UINT>(sizeof(IndexType)),
			static_cast<UINT>(_indexes.size())
		);
	}

	template<typename IndexType>
	static GameEngineIndexBuffer* Create(
		const std::vector<IndexType>& _indexes
	)
	{
		return Create(
			&_indexes[0],
			static_cast<UINT>(sizeof(IndexType)),
			static_cast<UINT>(_indexes.size())
		);
	}

	inline UINT GetIndexCount() const
	{
		return indexCount_;
	}

private:
	void CreateIndexBuffer(const void* _initialData, UINT _indexSize, UINT _indexCount);

private:
	ID3D11Buffer* indexBuffer_;				//인덱스를 저장할 버퍼.

	//버퍼 생성 관련 정보.
	D3D11_SUBRESOURCE_DATA resData_;	//버퍼의 초기값.
	D3D11_BUFFER_DESC indexBufferDesc_;		//버퍼의 생성 명세서.

	//버퍼 세팅 관련 정보.
	UINT indexSize_;					//인덱스 한개 크기.
	UINT indexCount_;					//인덱스 개수.
	UINT offset_;						//세팅을 시작할 버퍼의, 버퍼 시작점으로부터의 거리(byte).

};

