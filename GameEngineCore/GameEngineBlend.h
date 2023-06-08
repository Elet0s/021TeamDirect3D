#pragma once
#include "GameEngineRes.h"


class GameEngineBlend : public GameEngineRes<GameEngineBlend>
{
	//블렌드스테이트 생성, 관리 삭제 담당 클래스.
	//블렌드: 색상 혼합 및 반투명을 제어하는 기술.

	friend GameEngineRes<GameEngineBlend>;
	//GameEngineBlend 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineBlend();
	~GameEngineBlend();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineBlend(const GameEngineBlend& _other) = delete;
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete;


public:
	static GameEngineBlend* Create(
		const std::string_view& _name,
		const D3D11_BLEND_DESC& _desc
	);
	void Set();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

private:
	void CreateBlendState(const D3D11_BLEND_DESC& _desc);

private:
	ID3D11BlendState* blendState_;	//렌더링 파이프라인 아웃풋머져 단계에 연결할 블렌드스테이트.

	//typedef struct D3D11_BLEND_DESC
	//{
	//	BOOL AlphaToCoverageEnable;							알파블렌딩에도 안티앨리어싱을 하는 기술인 알파 투 커버리지를 적용할 지 여부.
	//	BOOL IndependentBlendEnable;						여러 가지의 독립적인 블렌딩 설정값을 가지게 할 지 여부. 
	//														 true: 8가지 블렌딩 설정값을 가짐.
	//														 false: 0번 설정값만 블렌딩에 사용함.
	// 
	//	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];		렌더타겟에 적용될 알파블렌딩 설정값 정보를 저장할 D3D11_RENDER_TARGET_BLEND_DESC구조체 배열.
	//														 최대 8개 렌더타겟에 각각 다른 알파블렌딩 방식을 저장할 수 있다.

	//	typedef struct D3D11_RENDER_TARGET_BLEND_DESC
	//	{
	//		BOOL BlendEnable;						알파블렌딩을 할 지 여부.
	//		D3D11_BLEND SrcBlend;					알파블렌딩 공식의 srcFactor의 4개 원소를 어떻게 채울지 선택하는 옵션.
	//		D3D11_BLEND DestBlend;					알파블렌딩 공식의 destFactor의 4개 원소를 어떻게 채울지 선택하는 옵션.
	//		D3D11_BLEND_OP BlendOp;					알파블렌딩 공식의 옵션 부분에 어떤 연산을 적용할지 선택하는 옵션.
	//		D3D11_BLEND SrcBlendAlpha;				srcColor의 알파값 설정.
	//		D3D11_BLEND DestBlendAlpha;				destColor의 알파값 설정.
	//		D3D11_BLEND_OP BlendOpAlpha;			알파블렌딩 공식의 옵션 항목에 더하기 적용. 알파값 계산에만 적용된다.
	//		UINT8 RenderTargetWriteMask;			블렌딩을 적용할 색상. RGBA중 몇가지만 선택해서 알파블렌딩을 적용할 수도 있다.
	//	} 	D3D11_RENDER_TARGET_BLEND_DESC;
	//
	//} 	D3D11_BLEND_DESC;

	// 
	//알파블렌딩 공식.
	//output: 최종 결과물.
	//dest: 백버퍼의 현재 색상.
	//src: 백버퍼의 색상과 블렌드할 원본의 색상.
	//옵션: BlendOp으로 지정하는 블렌드 연산 방식.
	//outputColor = (srcColor * srcFactor) 옵션 (destColor * destFactor)


	D3D11_BLEND_DESC blendDesc_;		//블렌드스테이트를 만들때 사용할 세부정보.
	float4 factor_;				//srcFactor나 destFactor를 직접 입력할때 사용할 값. 현재는 사용하지 않음.
	unsigned int mask_;			//블렌딩을 적용할 색상값. 웬만하면 기본값인 모든 색상에서 손대지 말 것.

};

