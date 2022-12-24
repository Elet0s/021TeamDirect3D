#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;

	float4 mainLightColor_ = float4::White;     //주 조명광 색상값. 정반사광, 난반사광에 적용.
	float4 ambientLightColor_ = float4(0.25f, 0.25f, 0.25f, 1.f);  //주변광 색상값.

	float specularLightRatio_ = 1.f;  //정반사광 적용 비율. 0~1.
	float diffuseLightRatio_ = 1.f;   //난반사광 적용 비율. 0~1.
	float ambientLightRatio_ = 1.f;   //주변광 적용 비율. 0~1.

	float specularLightExponent_ = 20.f;   //정반사광 지수. 이 수치가 커지면 정반사광이 반사되는 면적이 제곱반비례로 줄어든다.
	//반대로 음수가 되면 이 조명이 비추는 모든 영역에 정반사광이 비춘다.


private:
	float4 lightingPosition_;   //조명 위치.
	float4 lightingDirection_;  //조명 방향.
	float4 lightingReverseDirection_; //조명 역방향.
	//이 세개 쓸 일이 있나?


	float4 viewLightingPosition_; //뷰공간에서의 조명 위치.
	float4 viewLightingDirection_; //뷰공간에서의 조명 방향.
	float4 viewLightingReverseDirection_; //뷰공간에서의 조명 역방향.

	float4 viewSpaceCameraPosition_;  //카메라 위치. 
	//뷰공간 카메라위치는 (0, 0, 0) 고정 아닌가?
};

struct LightingDatas
{
	//조명 데이터 모음. 상수 버퍼로 셰이더에게 전달한다.
	int lightingCount_ = 0;        //조명 개수.
	LightingData lightings_[16]; //LightingData 모음.
};

class GameEngineLighting : public GameEngineActor
{
	//이 클래스의 존재 이유: 조명.

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
	void Update(float _deltaTime) override;

public:
	LightingData& GetLightingData()
	{
		return lightingData_;
	}


private:
	void UpdataLightingData(std::weak_ptr<class GameEngineCamera> _camera);

private:
	LightingData lightingData_;

};

