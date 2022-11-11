#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayoutDesc;
class GameEngineVertexBuffer : public GameEngineRes<GameEngineVertexBuffer>
{

	//버텍스: 정점, 꼭지점. 다각형에서 두개 이상의 선이 만나는 점. 사실 점 형태로 그릴지 말지도 선택할 수 있다.
	//현재는 버텍스에 위치 정보밖에 없지만 원래 DirectX에는 위치정보 뿐만 아니라 색, 빛, 텍스처 등의 정보도 같이 포함해서, 
	//FVF(Flexible Vertex Format)이라는 개념으로 모아서 제공하고 있다.


	//그래픽 리소스들 중 버퍼(버텍스 버퍼, 인덱스 버퍼, 상수 버퍼, 스트림 출력 버퍼)는 
	// 리소스뷰 없이도 렌더링 파이프라인에 연결할 수 있다.
public:
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

private:

	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _other) = delete;


public:
	static std::shared_ptr<GameEngineVertexBuffer> Create(
		const std::string_view& _name,
		const void* _data,
		UINT _vertexSize,
		UINT _vertexCount,
		const GameEngineInputLayoutDesc& _info
	);

	static std::shared_ptr<GameEngineVertexBuffer> Create(
		const void* _data,
		UINT _vertexSize,
		UINT _vertexCount,
		const GameEngineInputLayoutDesc& _info
	);

	void Setting();

public:
	template<typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(
		const std::string_view& _name,
		const std::vector<VertexType>& _vertex
	)
	{
		return Create(
			_name,
			&_vertex[0],
			static_cast<UINT>(sizeof(VertexType)),
			static_cast<UINT>(_vertex.size()),
			VertexType::inputLayoutInfo_
		);
	}

	template<typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(
		const std::vector<VertexType>& _vertex
	)
	{
		return Create(
			&_vertex[0],
			static_cast<UINT>(sizeof(VertexType)),
			static_cast<UINT>(_vertex.size()),
			VertexType::inputLayoutInfo_
		);
	}

	const GameEngineInputLayoutDesc& GetInputLayoutDesc() const
	{
		return *inputLayoutDesc_;
	}

	inline ID3D11Buffer* GetBuffer()
	{
		return vertexBuffer_;
	}

	inline unsigned int GetVertexSize()
	{
		return vertexSize_;
	}

private:
	void CreateVertexBuffer(
		const void* _initialData,
		UINT _vertexSize,
		UINT _vertexCount
	);

private:
	ID3D11Buffer* vertexBuffer_;				//버텍스 정보를 저장할 버퍼 인터페이스.

	//버퍼 생성 관련 정보.
	D3D11_SUBRESOURCE_DATA resData_;	//버퍼의 초기값.
	D3D11_BUFFER_DESC vertexBufferDesc_;		//버퍼의 생성 명세서.

	UINT vertexSize_;		//버퍼 한개의 크기.
	UINT vertexCount_;		//버퍼 개수.
	UINT offset_;			//세팅을 시작할 버퍼의, 버퍼 시작점으로부터의 거리(byte).

	const GameEngineInputLayoutDesc* inputLayoutDesc_;


};

