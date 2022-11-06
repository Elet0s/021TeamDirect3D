#pragma once
#include "GameEngineRes.h"

class GameEngineConstantBuffer : public GameEngineRes<GameEngineConstantBuffer>
{
	//상수 버퍼 생성 및 관리 클래스.

	//상수 버퍼(Constant buffer): 버텍스셰이더 및 픽셀셰이더에서 사용될 상수들을 모아 놓은 버퍼. 
	// 여기서 상수는 게임엔진디바이스 클래스에 있는 RenderStart()함수를 호출한 이후, 
	// RenderEnd()함수가 호출될때까지, 그러니까 렌더링파이프라인이 진행되는 동안 변하지 않는 값들을 가리키는 말이다.
	// 한마디로, 램에서 GPU로 넘겨주고자 하는 데이터 모음.
	//상수 버퍼를 사용하는 이유는 셰이더에서 매번 사용되는 상수들을 cpp 파일에서 전달해주어야 한다고 가정할 때,
	// 개별적으로 하나하나 값을 전달해 주는 것보다 한꺼번에 모아두었다가 복사해서 옮기는 것이 캐시의 지역성 때문에 효율이 더 좋다.
	// 따라서 하나의 구조체로 묶어 보내도록 하기 위해 상수 버퍼라는 개념을 사용한다.
	//상수 버퍼의 메모리 구조상, 크기가 반드시 최소 하드웨어 할당 크기(16 바이트)의 배수여야 한다.

	//상수버퍼 자체와 상수버퍼 세팅 구조를 헷갈리지 말 것.
	//상수버퍼는 셰이더가 컴파일되고 생성되는 시점에 같이 생성된다.
	//렌더러마다 각각의 상수버퍼를 전부 다 만들 수는 없으므로 돌려 쓴다.
	
	
public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

protected:
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) noexcept = delete;

private:
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete;


public:	
	static GameEngineConstantBuffer* Create(
		const std::string_view& _name,	//상수버퍼는 이름이 반드시 있어야 한다. 그래서 다른 리소스 생성함수와는 다르게 이름 기본값이 없다.
		const D3D11_SHADER_BUFFER_DESC& _desc
	);
	static GameEngineConstantBuffer* Find(const std::string_view& _name, int _byteWidth);
	static GameEngineConstantBuffer* CreateAndFind(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc
	);



	//매 루프마다 바뀌는 트랜스폼 데이터 등의 상수버퍼가 가진 정보를 그래픽카드의 메모리로 전달하는 함수.
	void ChangeData(const void* _data, size_t _dataSize) const;
	//실질적인 상수버퍼의 데이터세팅은 여기에서 한다.
	//맵, 언맵 함수를 호출하므로 최소한으로 사용할 것.

	//상수버퍼를 렌더링 파이프라인의 정점셰이더에 연결하는 함수.
	void VSSetting(int _bindPoint);

	//상수버퍼를 렌더링 파이프라인의 픽셀셰이더에 연결하는 함수.
	void PSSetting(int _bindPoint);

	static void ResourceDestroy();

public:
	D3D11_BUFFER_DESC& GetBufferDesc()
	{
		return constantBufferDesc_;
	}

private:
	static GameEngineConstantBuffer* CreateNamedRes(const std::string_view& _name, int _byteWidth);
	void CreateConstantBuffer(const D3D11_SHADER_BUFFER_DESC& _desc);

private:
	static std::map<std::string, std::map<int, GameEngineConstantBuffer*>> allConstantBuffers_;
	//상수버퍼를 이름과 바이트 크기로까지 구분하기 위해 이중 맵 구조 사용.
	//그래서 여러 셰이더들이 똑같은 상수버퍼를 쓰는 경우에도 문제가 생기지 않는다.

	//typedef struct _D3D11_SHADER_BUFFER_DESC
	//{
	//	LPCSTR                  Name;		상수버퍼 이름.
	//	D3D_CBUFFER_TYPE        Type;		상수버퍼의 종류.
	//	UINT                    Variables;	상수버퍼의 멤버변수 개수.
	//	UINT                    Size;		상수버퍼 크기.
	//	UINT                    uFlags;		상수버퍼가 연결될 슬롯을 지정하는 플래그. 
	//} D3D11_SHADER_BUFFER_DESC;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_BUFFER_DESC constantBufferDesc_;


	ID3D11Buffer* constantBuffer_;


};