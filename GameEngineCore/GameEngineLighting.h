#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;

	float4 mainLightColor_ = float4::White;     //�� ���� ����. ���ݻ籤, ���ݻ籤�� ����.
	float4 ambientLightColor_ = float4(0.25f, 0.25f, 0.25f, 1.f);  //�ֺ��� ����.

	float specularLightRatio_ = 1.f;  //���ݻ籤 ���� ����. 0~1.
	float diffuseLightRatio_ = 1.f;   //���ݻ籤 ���� ����. 0~1.
	float ambientLightRatio_ = 1.f;   //�ֺ��� ���� ����. 0~1.

	float specularLightExponent_ = 20.f;   //���ݻ籤 ����. �� ��ġ�� Ŀ���� ���ݻ籤�� �ݻ�Ǵ� ������ �����ݺ�ʷ� �پ���.
	//�ݴ�� ������ �Ǹ� �� ������ ���ߴ� ��� ������ ���ݻ籤�� �����.


private:
	float4 lightingPosition_;   //���� ��ġ.
	float4 lightingDirection_;  //���� ����.
	float4 lightingReverseDirection_; //���� ������.
	//�� ���� �� ���� �ֳ�?


	float4 viewLightingPosition_; //����������� ���� ��ġ.
	float4 viewLightingDirection_; //����������� ���� ����.
	float4 viewLightingReverseDirection_; //����������� ���� ������.

	float4 viewSpaceCameraPosition_;  //ī�޶� ��ġ. 
	//����� ī�޶���ġ�� (0, 0, 0) ���� �ƴѰ�?
};

struct LightingDatas
{
	//���� ������ ����. ��� ���۷� ���̴����� �����Ѵ�.
	int lightingCount_ = 0;        //���� ����.
	LightingData lightings_[16]; //LightingData ����.
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

