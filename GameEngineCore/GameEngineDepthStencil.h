#pragma once
#include "GameEngineRes.h"


class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
	//깊이스텐실 스테이트 생성 및 관리 클래스.

	friend GameEngineRes<GameEngineDepthStencil>;
	//GameEngineDepthStencil 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineDepthStencil();
	~GameEngineDepthStencil();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineDepthStencil(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil&& _other) = delete;


public:
	static GameEngineDepthStencil* Create(
		const std::string_view& _name,
		const D3D11_DEPTH_STENCIL_DESC& _desc
	);
	void Set();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

private:
	void CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& _desc);

private:
	ID3D11DepthStencilState* depthStencilState_;	//렌더링 파이프라인에 연결할 깊이스텐실 스테이트

	//typedef struct D3D11_DEPTH_STENCIL_DESC
	//{
	//	BOOL DepthEnable;						깊이테스트를 활성화 여부.
	//	D3D11_DEPTH_WRITE_MASK DepthWriteMask;	깊이테스트 결과를 기존 깊이 데이터와 비교할 지 여부??

	//		typedef 
	//		enum D3D11_DEPTH_WRITE_MASK
	//		{
	//			D3D11_DEPTH_WRITE_MASK_ZERO = 0,	기존 깊이 데이터와 비교 안 함.
	//			D3D11_DEPTH_WRITE_MASK_ALL = 1		기존 깊이 데이터와 비교 함.
	//		} 	D3D11_DEPTH_WRITE_MASK;
	// 
	// 
	//	D3D11_COMPARISON_FUNC DepthFunc;		깊이테스트 방식.
	//	
	//		typedef 
	//		enum D3D11_COMPARISON_FUNC
	//		{
	//			D3D11_COMPARISON_NEVER = 1,			아무것도 통과시키지 않음.
	//			D3D11_COMPARISON_LESS = 2,			값이 작은 것만 통과.
	//			D3D11_COMPARISON_EQUAL = 3,			값이 같은 것만 통과.
	//			D3D11_COMPARISON_LESS_EQUAL = 4,	값이 작거나 같은 것만 통과.
	//			D3D11_COMPARISON_GREATER = 5,		값이 큰 것만 통과.
	//			D3D11_COMPARISON_NOT_EQUAL = 6,		값이 같지 않은 것만 통과.
	//			D3D11_COMPARISON_GREATER_EQUAL = 7,	값이 크거나 같은 것만 통과.
	//			D3D11_COMPARISON_ALWAYS = 8			언제나 통과.
	//		} 	D3D11_COMPARISON_FUNC;			
	// 
	// 
	//	BOOL StencilEnable;						스텐실테스트를 활성화 여부.
	//	UINT8 StencilReadMask;					??
	//	UINT8 StencilWriteMask;					??
	//	D3D11_DEPTH_STENCILOP_DESC FrontFace;	??
	//	D3D11_DEPTH_STENCILOP_DESC BackFace;	??
	//} 	D3D11_DEPTH_STENCIL_DESC;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc_;		//깊이스텐실 스테이트를 만들때 필요한 상세 정보.

};

