#pragma once
#include "GameEngineCamera.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShaderResourcesHelper.h"

struct RenderOption 
{
    float DeltaTime = 0.0f;
    float SumDeltaTime = 0.0f;
	int Temp0;
	int Temp1;
};

// ����Ÿ���� ���õǾ� �ִٸ� �̳༮���� �׸����� �ִ�.

class GameEngineRenderUnit 
{
public:
	GameEngineShaderResourcesHelper ShaderResources;

	void SetPipeLine(const std::string& _Name);

	// �츮 ���������� �̷� �̸��� ����x�� ������ �̷��� �����ϱ�� �߾�.
	void EngineShaderResourcesSetting(GameEngineRenderer* _Renderer);

	GameEngineRenderUnit();

	void Render(float _DeltaTime);

	void SetRenderer(GameEngineRenderer* _Renderer);

	GameEngineRenderingPipeLine* GetPipeLine();

	GameEngineRenderingPipeLine* GetClonePipeLine();

	GameEngineRenderingPipeLine* ClonePipeLine(GameEngineRenderingPipeLine* _Rendering);

private:
	GameEngineRenderer* ParentRenderer;

	GameEngineRenderingPipeLine* PipeLine;
};


// �߻�Ŭ����
// ���� �� �ڽĵ��� �ϳ��� �������̽��� ���� �����Դϴ�.
// ���� :
class GameEngineRenderingPipeLine;
class GameEngineShaderResourcesHelper;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;


public:
	RenderOption renderOption;

	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// float4x4 ViewPort;
	void ChangeCamera(CAMERAORDER _Order);

    GameEngineRenderingPipeLine* ClonePipeLine(GameEngineRenderingPipeLine* _Rendering);

    inline int GetRenderingOrder() 
    {
        return RenderingOrder;
    }

    void SetRenderingOrder(int _Order);

	virtual void InstancingOn() 
	{
		IsInstancing_ = true;
	};

	bool IsInstancing(GameEngineRenderingPipeLine* _Rendering);

	void InstancingDataSetting(GameEngineRenderingPipeLine* _Line);

	void EngineShaderResourcesSetting(GameEngineShaderResourcesHelper* _ShaderResources);

	void PushRendererToMainCamera();

	void PushRendererToUICamera();
	
protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

    class GameEngineCamera* Camera;



private:
	CAMERAORDER CameraOrder;
    int RenderingOrder;
	bool IsInstancing_;

	virtual void Render(float _DeltaTime) = 0;

};

