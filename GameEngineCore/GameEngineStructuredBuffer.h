#pragma once
#include "GameEngineRes.h"

class GameEngineStructuredBuffer : public GameEngineRes<GameEngineStructuredBuffer>
{

	friend class GameEngineStructuredBufferSetter;

	friend class GameEngineFBXMesh;

public:
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();

private:

	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer&& _other) = delete;

public:
	//이름규칙: 인스턴싱용 구조화버퍼는 Inst_로 시작.

	static std::shared_ptr<GameEngineStructuredBuffer> Create(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);
	static std::shared_ptr<GameEngineStructuredBuffer> Find(const std::string_view& _name, int _byteWidth);
	static std::shared_ptr<GameEngineStructuredBuffer> CreateAndFind(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);

	void ChangeData(const void* _data, size_t _byteWidth);

	//구조화 버퍼를 렌더링 파이프라인의 정점셰이더에 연결하는 함수.
	void VSSetting(int _bindPoint);

	//구조화 버퍼를 렌더링 파이프라인의 픽셀셰이더에 연결하는 함수.
	void PSSetting(int _bindPoint);


	void VSReset(int _bindPoint);
	void PSReset(int _bindPoint);


	static void ResourceDestroy();
	//GameEngineRes의 리소스저장 컨테이너를 쓸 수 없으므로 전용 컨테이너를 따로 만들고 리소스 생성과 삭제 절차도 다시 만들어야 한다.


public:
	inline size_t GetDataSize()
	{
		return dataUnitSize_;
	}

protected:
	static std::shared_ptr<GameEngineStructuredBuffer> CreateNamedRes(const std::string_view& _name, int _byteWidth);
	//GameEngineRes의 리소스저장 컨테이너를 쓸 수 없으므로 전용 컨테이너를 따로 만들고 리소스 생성과 삭제 절차도 다시 만들어야 한다.


private:
	void CreateOrResize(
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count,
		void* _initialData = nullptr
	);
	void CreateStructuredBuffer(size_t _dataUnitSize, size_t _count, void* _initialData = nullptr);

	void CreateOrResize(size_t _count, void* _initialData = nullptr);

	void Release();


private:
	static std::map<std::string, std::map<int, std::shared_ptr<GameEngineStructuredBuffer>>> allStructuredBuffers_;
	//일반적인 GameEngineRes<ResType> 리소스들과는 다르게 이름과 크기를 둘 다 저장하고 대조해봐야 하므로 
	// 이중맵 구조의 전용 컨테이너에 저장하고 삭제할때도 따로 삭제한다.

	ID3D11Buffer* structuredBuffer_;
	D3D11_BUFFER_DESC structuredBufferDesc_;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU_;	//구조화버퍼의 데이터를 받을 그래픽카드 내 메모리의 주소값.

	ID3D11ShaderResourceView* shaderResourceView_;	//셰이더 리소스뷰.
	//구조화버퍼는 버퍼지만 셰이더 리소스로 분류되므로 셰이더 리소스 뷰가 필요하다.

	size_t count_;	//데이터 개수.
	size_t dataUnitSize_;		//데이터 단위 크기.
	bool isInitialized_;	//초기화 여부.
};

