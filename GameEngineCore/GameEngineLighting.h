#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;

	float4 lightColor_ = float4::White;//빛 색.

private:
	float4 lightingPos_;               //조명 위치.
	float4 lightingDirection_;         //조명 방향.
	float4 lightingInversedDirection_; //조명 역방향.

	float4 viewLightingPos_;               //뷰행렬이 적용된 조명 위치.
	float4 viewLightingDirection_;         //뷰행렬이 적용된 조명 방향.
	float4 viewLightingInversedDirection_; //뷰행렬이 적용된 조명 역방향.
};

struct LightingDatas
{
	//조명 데이터 모음. 상수 버퍼로 셰이더에게 전달한다.
	int lightingCount_;        //조명 개수.
	LightingData lightings_[128]; //LightingData 모음. 최대 128개 제한.
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

