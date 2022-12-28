#pragma once
#include "GameEngineActor.h"

struct LightingData
{
	friend class GameEngineLighting;
	friend struct LightingDatas;

	float4 mainLightColor_ = float4::White;     //�� ���� ����. ���ݻ籤, ���ݻ籤�� ����.
	float4 ambientLightColor_ = float4(0.1f, 0.1f, 0.1f, 1.f);  //�ֺ��� ����.

	float specularLightRatio_ = 1.f;  //���ݻ籤 ���� ����. 0~1.
	float diffuseLightRatio_ = 1.f;   //���ݻ籤 ���� ����. 0~1.
	float ambientLightRatio_ = 1.f;   //�ֺ��� ���� ����. 0~1.

	float specularLightExponent_ = 20.f;   //���ݻ籤 ����. �� ��ġ�� Ŀ���� ���ݻ籤�� �ݻ�Ǵ� ������ �����ݺ�ʷ� �پ���.
	//�ݴ�� ������ �Ǹ� �� ������ ���ߴ� ��� ������ ���ݻ籤�� �����.


private:
	LightingData()
		: lightingViewFrustumNearZ_(0.f),
		lightingViewFrustumFarZ_(1.f),
		shadowDepthRenderTargetWidth_(0.f),
		shadowDepthRenderTargetHeight_(0.f)
	{
	}

private:
	float4x4 lightingViewMatrix_;			//������ �����.
	float4x4 inverseLightingViewMatrix_;	//������ ������� �����.

	float4x4 lightingProjectionMatrix_;			//������ �������.
	float4x4 inverseLightingProjectionMatrix_;	//������ ��������� �����.

	//float4x4 lightingViewProjectionMatrix_;	//������ ��, ���� �������.

	float4x4 cameraViewMatrix_;			//ī�޶��� �����.
	float4x4 inverseCameraViewMatrix_;	//ī�޶��� ������� �����.

	float shadowDepthRenderTargetWidth_;		//�׸��� ����Ÿ�� ���α���.
	float shadowDepthRenderTargetHeight_;	//�׸��� ����Ÿ�� ���α���.
	float lightingViewFrustumNearZ_;	//������ ���������� ����� z��.
	float lightingViewFrustumFarZ_;		//������ ���������� ����� z��.

	float4 lightingPosition_;   //������� ���� ��ġ.
	float4 lightingDirection_;  //������� ���� ����.
	float4 inverseLightingDirection_; //������� ���� ������.
	//���̴��� �� ���� ���� �� ���� ���� �� ������ �׷��� ������.

	float4 viewLightingPosition_; //����������� ���� ��ġ.
	float4 viewLightingDirection_; //����������� ���� ����.
	float4 inverseViewLightingDirection_; //����������� ���� ������.

	//float4 viewSpaceCameraPosition_;  //ī�޶� ��ġ. 
	//����� ī�޶���ġ�� (0, 0, 0) ���� �ƴѰ�?
};

struct LightingDatas
{
	//���� ������ ����. ��� ���� ���·� ���̴����� �����Ѵ�.
	int lightingCount_ = 0;        //���� ����.
	LightingData lightings_[16]; //LightingData ����.
};

class GameEngineLighting : public GameEngineActor
{
	//�� Ŭ������ ���� ����: ����� �׸���.

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
	LightingData lightingData_;		//�� ������ ���� ����.
	std::shared_ptr<class GameEngineRenderTarget> shadowDepthRenderTarget_;	//�׸��� ���������� ������ ����Ÿ��.
	D3D11_VIEWPORT lightingViewport_;	//�� ������ ����Ʈ.
};

