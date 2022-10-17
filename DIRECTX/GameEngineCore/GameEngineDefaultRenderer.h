#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

// ���� :
class GameEngineRenderingPipeLine;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	// �ϳ��� ������ ������������
	// �ϳ��� �Ž�
	// �ϳ��� ���׸���

	// �ϳ��� ����Ÿ��


public:

	// GameEngineShaderResourcesHelper ShaderResources;

	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	// delete Function
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);

	void SetPipeLine(const std::string& _Name);

	virtual void InstancingOn();

	inline GameEngineShaderResourcesHelper& GetShaderResources()
	{
		return Unit.ShaderResources;
	}

	inline GameEngineRenderUnit& GetRenderUnit()
	{
		return Unit;
	}

protected:

	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	GameEngineRenderUnit Unit;

	// �������� �޸� �����ϴ� �޷θ����� ��� �ְ�
	// GameEngineRenderingPipeLine* PipeLine;


};

