#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourceHelper.h"

class GameEngineRenderUnit;
class GameEngineDefaultRenderer: public GameEngineRenderer
{
	//�� �����ӿ�ũ���� �������� �ʿ��� �ּ����� ���� ����� ������ ���������ΰ� ���̴����ҽ����۸� ������ 
	// �ڱⰡ ���� ������ ���ӿ���ī�޶��� ������ ü�迡�� �亯ȯ, ������ȯ, ����Ʈ��ȯ�� ���� ������ ���
	// ������ ������������ ���� ������ ���� ���� �ȼ��� �������� �ٲ� ����Ÿ�ٿ� �����ϴ� ������Ʈ.
	//�������� �������� �����ϴ� ������Ʈ�̴�.

	//���������� �ݵ�� ������ ������������ ���Ե� ���������� ��� �ִ�. ������ ������������ ���̷�ƮX�� ���������� ����Ǿ� �ִ�.
	//�ϳ��� ������ ������������ �ϳ��� �޽�, �ϳ��� ���׸���, �ϳ��� ����Ÿ���� ������.


public:
	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

protected:
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _other) noexcept = delete;

private:
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _other) = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer&& _other) = delete;


public:	
	virtual void Render(float _deltaTime) override;

	//�������� �ʿ��� ������ ������������ ����ϰ� �� �������� ���� ī�޶� ����ϴ� �Լ�.
	void SetPipeLine(const std::string& _renderingPipeLineName);

	void SetMesh(const std::string& _meshName);


	virtual void InstancingOn();


public:
	inline GameEngineShaderResourceHelper& GetShaderResourceHelper()	
		//���̴����ҽ����� ���� �������� ���� �� �����Ƿ� ���۷��� ��ȯ.
	{
		return this->renderUnit_.GetShaderResourceHelper();
	}


	inline GameEngineRenderUnit& GetRenderUnit()	
		//�������� ���� �������� ���� �� �����Ƿ� ���۷��� ��ȯ.
	{
		return this->renderUnit_;
	}

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void End();


	

private:
	GameEngineRenderUnit renderUnit_;
	//�Ѱ��� ����Ʈ���������� �ּ� �Ѱ��� ���������� ������.
};

