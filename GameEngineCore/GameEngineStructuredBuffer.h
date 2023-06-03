#pragma once
#include "GameEngineRes.h"

class GameEngineStructuredBuffer : public GameEngineRes<GameEngineStructuredBuffer>
{
	//

	friend GameEngineRes<GameEngineStructuredBuffer>;
	//GameEngineStructuredBuffer 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineStructuredBufferSetter;
	//GameEngineStructuredBufferSetter 클래스에서 리소스세팅 함수를 호출하기 위해 프렌드.

private:
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer&& _other) = delete;

public:
	//이름규칙: 인스턴싱용 구조화버퍼는 Inst_로 시작.

	static GameEngineStructuredBuffer* Create(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);
	static GameEngineStructuredBuffer* Find(const std::string_view& _name, size_t _byteWidth);
	static GameEngineStructuredBuffer* FindOrCreate(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);

private:
	void ChangeData(const void* _data, size_t _byteWidth);

	//구조화 버퍼를 정점셰이더에 연결하는 함수.
	void VSSetShaderResource(int _bindPoint);

	//구조화 버퍼를 컴퓨트셰이더에 연결하는 함수.
	void CSSetShaderResource(int _bindPoint);

	//구조화 버퍼를 픽셀셰이더에 연결하는 함수.
	void PSSetShaderResource(int _bindPoint);


	void VSResetShaderResource(int _bindPoint);
	void PSResetShaderResource(int _bindPoint);

public:
	static void ResourceDestroy();
	//GameEngineRes의 리소스저장 컨테이너를 쓸 수 없으므로 전용 컨테이너를 따로 만들고 리소스 생성과 삭제 절차도 다시 만들어야 한다.


public:
	inline size_t GetDataSize() const
	{
		return dataSize_;
	}

protected:
	static GameEngineStructuredBuffer* CreateNamedRes(const std::string_view& _name, size_t _byteWidth);
	//GameEngineRes의 리소스저장 컨테이너를 쓸 수 없으므로 전용 컨테이너를 따로 만들고 리소스 생성과 삭제 절차도 다시 만들어야 한다.


private:
	void CreateOrResize(
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count,
		void* _initialData = nullptr
	);
	void CreateStructuredBuffer(size_t _dataSize, size_t _count, void* _initialData = nullptr);

	void CreateOrResize(size_t _count, void* _initialData = nullptr);

	void Release();


private:
	static std::map<std::string, std::map<size_t, GameEngineStructuredBuffer*>> allStructuredBuffers_;
	//일반적인 GameEngineRes<ResType> 리소스들과는 다르게 이름과 크기를 둘 다 저장하고 대조해봐야 하므로 
	// 이중맵 구조의 전용 컨테이너에 저장하고 삭제할때도 따로 삭제한다.

	ID3D11Buffer* structuredBuffer_;
	D3D11_BUFFER_DESC structuredBufferDesc_;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_MAPPED_SUBRESOURCE mappedPtrInCPU_;	//구조화버퍼에 해당하는 GPU 내 메모리영역에 매핑시킬 CPU 메모리의 주소값.

	ID3D11ShaderResourceView* shaderResourceView_;	//셰이더 리소스뷰.
	//구조화버퍼는 버퍼지만 셰이더 리소스로 분류되므로 셰이더 리소스 뷰가 필요하다.

	size_t count_;	//데이터 개수.
	size_t dataSize_;		//데이터 단위 크기.
	bool isInitialized_;	//초기화 여부.
};

