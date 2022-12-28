#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;
	friend struct LightingDatas;

	float4 mainLightColor_ = float4::White;     //주 조명광 색상값. 정반사광, 난반사광에 적용.
	float4 ambientLightColor_ = float4(0.1f, 0.1f, 0.1f, 1.f);  //주변광 색상값.

	float specularLightRatio_ = 1.f;  //정반사광 적용 비율. 0~1.
	float diffuseLightRatio_ = 1.f;   //난반사광 적용 비율. 0~1.
	float ambientLightRatio_ = 1.f;   //주변광 적용 비율. 0~1.

	float specularLightExponent_ = 20.f;   //정반사광 지수. 이 수치가 커지면 정반사광이 반사되는 면적이 제곱반비례로 줄어든다.
	//반대로 음수가 되면 이 조명이 비추는 모든 영역에 정반사광이 비춘다.


private:
	LightingData()
		: lightingViewFrustumNearZ_(0.f),
		lightingViewFrustumFarZ_(1.f),
		shadowDepthRenderTargetWidth_(0.f),
		shadowDepthRenderTargetHeight_(0.f)
	{
	}

private:
	float4x4 lightingViewMatrix_;			//조명의 뷰행렬.
	float4x4 inverseLightingViewMatrix_;	//조명의 뷰행렬의 역행렬.

	float4x4 lightingProjectionMatrix_;			//조명의 투영행렬.
	float4x4 inverseLightingProjectionMatrix_;	//조명의 투영행렬의 역행렬.

	//float4x4 lightingViewProjectionMatrix_;	//조명의 뷰, 투영 통합행렬.

	float4x4 cameraViewMatrix_;			//카메라의 뷰행렬.
	float4x4 inverseCameraViewMatrix_;	//카메라의 뷰행렬의 역행렬.

	float shadowDepthRenderTargetWidth_;		//그림자 렌더타겟 가로길이.
	float shadowDepthRenderTargetHeight_;	//그림자 렌더타겟 세로길이.
	float lightingViewFrustumNearZ_;	//조명의 뷰프러스텀 근평면 z값.
	float lightingViewFrustumFarZ_;		//조명의 뷰프러스텀 원평면 z값.

	float4 lightingPosition_;   //월드공간 조명 위치.
	float4 lightingDirection_;  //월드공간 조명 방향.
	float4 inverseLightingDirection_; //월드공간 조명 역방향.
	//셰이더가 이 값을 직접 쓸 일은 없을 것 같지만 그래도 보낸다.

	float4 viewLightingPosition_; //뷰공간에서의 조명 위치.
	float4 viewLightingDirection_; //뷰공간에서의 조명 방향.
	float4 inverseViewLightingDirection_; //뷰공간에서의 조명 역방향.

	//float4 viewSpaceCameraPosition_;  //카메라 위치. 
	//뷰공간 카메라위치는 (0, 0, 0) 고정 아닌가?
};

struct LightingDatas
{
	//조명 데이터 모음. 상수 버퍼 형태로 셰이더에게 전달한다.
	int lightingCount_ = 0;        //조명 개수.
	LightingData lightings_[16]; //LightingData 모음.
};

class GameEngineLighting : public GameEngineActor
{
	//이 클래스의 존재 이유: 조명과 그림자.

	friend class GameEngineCamera;

public:
	GameEngineLighting();
	~GameEngineLighting();

protected:
	GameEngineLighting(const GameEngineLighting& _other) = delete;
	GameEngineLighting(GameEngineLighting&& _other) noexcept = delete;

private:
	GameEngineLighting& operator=(const GameEngineLighting& _other) = delete;
	GameEngineLighting& operator=(const GameEngineLighting&& _other) = delete;


public:
	void Start() override;
	void Update(float _deltaTime) override;

public:
	LightingData& GetLightingData()
	{
		return lightingData_;
	}

	D3D11_VIEWPORT& GetLightViewport()
	{
		return lightingViewport_;
	}


private:
	void UpdataLightingData(std::weak_ptr<class GameEngineCamera> _camera);
	void SetShadowDepthRenderTarget();

private:
	LightingData lightingData_;		//이 조명의 각종 정보.
	std::shared_ptr<class GameEngineRenderTarget> shadowDepthRenderTarget_;	//그림자 깊이정보를 저장할 렌더타겟.
	D3D11_VIEWPORT lightingViewport_;	//이 조명의 뷰포트.
};

