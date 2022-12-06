#pragma once

class FieldRenderingActor: public GameEngineActor
{
	//�� Ŭ������ ���� ����:
public:
	FieldRenderingActor();
	~FieldRenderingActor();

protected:
	FieldRenderingActor(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor(FieldRenderingActor&& _other) noexcept = delete;

private:
	FieldRenderingActor& operator=(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor& operator=(const FieldRenderingActor&& _other) = delete;


public:	
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	const float tileSize_;		//Ÿ���ؽ�ó ���α���. 
	//���簢���̹Ƿ� �Ѱ��� ����ϴ�.

	const float4 tileCount_;	//���� Ÿ���ؽ�ó ���μ��� ����.


	GameEngineInstancingRenderer* tileRenderer_;



};

