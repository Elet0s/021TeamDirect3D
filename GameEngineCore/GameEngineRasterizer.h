#pragma once
#include "GameEngineRes.h"


class GameEngineRasterizer: public GameEngineRes<GameEngineRasterizer>
{
	//래스터라이저가 하는 일
	//1. 잘라내기(clipping):
	// 투영공간(view frustum) 밖에 있는 것들은 렌더링에서 제외하고, 투영 공간에 일부만 제외되어 잘린 것들은 
	// 잘린 곳에 투영공간에 맞는 새 버텍스를 만드는 작업.
	// 다른 메쉬에 가려지는 메쉬를 잘라내는 깊이 클리핑(depth clipping), 
	// 특정한 사각 영역을 지정해 잘라내는 가위 클리핑(scissor clipping) 등이 있다.
	// 
	//2. 원근 나누기(perspective division):
	// 멀리있는 오브젝트들의 버텍스 간격은 가깝게, 가까운 오브젝트들의 버텍스들은 멀리 배치해서 원근감을 구현하는 것.
	// 
	//3. 뒷면 솎아내기(backface culling): 
	// 다른것에 가려져서 보이지 않는 부분/투명해서 비쳐보이는 부분 등을 판정해서 렌더링할 부분과 그렇지 않은 부분을 가려내는 작업.
	// 
	//4. 뷰포트 변환(viewport transform):
	// 투영공간에 맞게 -1~1 사이로(z값은 0~1사이로) 축소된 버텍스들의 위치를 출력할 윈도우 크기에 맞춰서 확대시키는 작업.
	// 
	//5. 스캔 변환(scan transform):
	// 최종적으로 남은 버텍스들의 사이를, 
	// 버텍스들의 색상정보를 받아 선형보간해서 뽑아낸 각 픽셀별 색상값의 프래그먼트(예비 픽셀)로 채우는 작업.
	//
	//이상의 과정들을 통해 색상값을 바꿔야 하는 픽셀들 골라내서(속칭 픽셀 건지기) 픽셀셰이더로 넘긴다.
	// 
	//->데카르트좌표계를 윈도우 좌표계로 변환한다.


	friend GameEngineRes<GameEngineRasterizer>;
	//GameEngineRasterizer 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineRasterizer();
	~GameEngineRasterizer();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete;


public:	

	static GameEngineRasterizer* Create(
		const std::string& _name,
		const D3D11_RASTERIZER_DESC& _desc
	);
	void Setting();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

private:
	void Create(const D3D11_RASTERIZER_DESC& _desc);

private:
	ID3D11RasterizerState* rasterizerState_;		//래스터라이저의 동작 방식을 여기에 저장해서 파이프라인에 연결한다.
	//ID3D11RasterizerState* wireState_;	//필모드가 와이어인 래스터라이저 스테이트.

	//typedef struct D3D11_RASTERIZER_DESC
	//{
	//	D3D11_FILL_MODE FillMode;		정점들을 잇는 선 사이를 채울지 말지 결정하는 옵션.
	//	D3D11_CULL_MODE CullMode;		앞뒷면 중 어느 면을 컬링할지 결정하는 옵션.
	//	BOOL FrontCounterClockwise;		반시계방향으로 배치된 정점들을 정면으로 판정할지, 그 반대로 할지 결정하는 옵션.
	//	INT DepthBias;					깊이 바이아스??
	//	FLOAT DepthBiasClamp;			깊이 바이아스 클램프??
	//	FLOAT SlopeScaledDepthBias;		??
	//	BOOL DepthClipEnable;			깊이 클리핑 적용 여부.
	//	BOOL ScissorEnable;				시저렉탱글 컬링(지정한 사각형 밖의 모든 요소를 그리지 않음) 적용 여부.
	//	BOOL MultisampleEnable;			멀티샘플링 적용 여부.
	//	BOOL AntialiasedLineEnable;		선 안티앨리어싱 적용 여부.
	//} 	D3D11_RASTERIZER_DESC;

	D3D11_RASTERIZER_DESC rasterizerDesc_;		//래스터라이저 생성 명세서.

};

