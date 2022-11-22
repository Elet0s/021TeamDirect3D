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

	//�������� �ʿ��� ���׸����� ����ϰ� �� �������� ���� ī�޶� ����ϴ� �Լ�.
	void SetMaterial(const std::string_view& _materialName);

	//
	void SetMesh(const std::string_view& _meshName);


public:
	inline GameEngineShaderResourceHelper& GetShaderResourceHelper()
		//���̴����ҽ����� ���� �������� ���� �� �����Ƿ� ���۷��� ��ȯ.
	{
		return this->renderUnit_->GetShaderResourceHelper();
	}

	inline std::shared_ptr<GameEngineRenderUnit> GetRenderUnit()
	{
		return this->renderUnit_;
	}

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void End();


	

private:
	std::shared_ptr<GameEngineRenderUnit> renderUnit_;
	//�Ѱ��� ����Ʈ���������� �ּ� �Ѱ��� ���������� ������.
};

