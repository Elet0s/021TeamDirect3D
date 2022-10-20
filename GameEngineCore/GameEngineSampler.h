#pragma once
#include "GameEngineRes.h"

class GameEngineSampler: public GameEngineRes<GameEngineSampler>
{
	//샘플러 관리 클래스.
	//샘플링: 텍스쳐 확대/축소, 밉매핑 등의 연산 과정 중간에 픽셀 색상 선택의 기준이 되어줄 텍셀이 없는 상황에서
	// 특정 픽셀의 색을 임의로 정해야 할 때, 해당 픽셀의 색을 어떻게 결정할 지에 대한 옵션을 정하는 것.
	
	friend GameEngineRes<GameEngineSampler>;
	//GameEngineSampler 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineSampler();
	~GameEngineSampler();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineSampler(const GameEngineSampler& _other) = delete;
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete;
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete;


public:	
	static GameEngineSampler* Create(const std::string& _name, const D3D11_SAMPLER_DESC& _desc);

	void VSSetting(int _bindPoint);	
	void PSSetting(int _bindPoint);	


private:
	void Create(const D3D11_SAMPLER_DESC& _desc);

private:
	ID3D11SamplerState* samplerState_;	//


	//typedef struct D3D11_SAMPLER_DESC
	//	D3D11_FILTER Filter;					텍스쳐를 샘플링할때 적용할 필터.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressU;	UV좌표 0~1범위를 가로로 벗어난 메쉬에 대한 처리 방법.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressV;	UV좌표 0~1범위를 세로로 벗어난 메쉬에 대한 처리 방법.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressW;	??
	//	FLOAT MipLODBias;						밉맵 시작 오프셋??
	// 
	//	UINT MaxAnisotropy;						비등방성 필터링 최대값. 1~16 범위로 가능. 1은 비등방성 필터링 사용 안함.
	//최대값인 16으로 하면 1/16로 축소된 밉맵 이미지까지 만들어서 사용한다는 건가??
	//Filter가 D3D11_FILTER_ANISOTROPIC, D3D11_FILTER_COMPARISON_ANISOTROPIC일때만 적용.
	// 
	//	D3D11_COMPARISON_FUNC ComparisonFunc;	샘플링 데이터를 기존 샘플링 데이터와 비교할 때 적용되는 옵션??
	//Filter가 D3D11_FILTER_COMPARISON_~ 으로 시작할 때만 적용.
	// 
	//	FLOAT BorderColor[4];					rgba 0~1 범위내에서 경계선 색상을 정한다.
	//AddressU, AddressV, AddressW 중 D3D11_TEXTURE_ADDRESS_BORDER를 선택한 곳에만 적용된다.
	// 
	//	FLOAT MinLOD;							밉맵 레벨 범위 최저 제한. 0이면 가장 크고 상세한 밉맵 레벨.
	//	FLOAT MaxLOD;							밉맵 레벨 범위 최고 제한. 0이면 가장 크고 상세한 밉맵 레벨. 반드시 MinLOD보다 크거나 같은 값이어야 한다.
	//											
	//} 	D3D11_SAMPLER_DESC;

	D3D11_SAMPLER_DESC samplerDesc_;

};

