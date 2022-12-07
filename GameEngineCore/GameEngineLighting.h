#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;

	float4 lightColor_ = float4::White;//�� ��.

private:
	float4 lightingPos_;               //���� ��ġ.
	float4 lightingDirection_;         //���� ����.
	float4 lightingInversedDirection_; //���� ������.

	float4 viewLightingPos_;               //������� ����� ���� ��ġ.
	float4 viewLightingDirection_;         //������� ����� ���� ����.
	float4 viewLightingInversedDirection_; //������� ����� ���� ������.
};

struct LightingDatas
{
	//���� ������ ����. ��� ���۷� ���̴����� �����Ѵ�.
	int lightingCount_;        //���� ����.
	LightingData lightings_[128]; //LightingData ����. �ִ� 128�� ����.
};

class GameEngineLighting : public GameEngineActor
{
	//�� Ŭ������ ���� ����: ����.

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

