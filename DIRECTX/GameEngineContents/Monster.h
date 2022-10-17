#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �ڽ��� ��ó�� ���ִ� ��ġ�� ���
// ������Ʈ���� DeathUpdate���� death �ִϸ��̼��� ����Ǹ� �ڽ��� ��� �������� off
// LiveTime = 5.0f
// // dj

// ���� :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	void Start() override;

	GameEngineActor* NewActor;
	float4 StartPostion;
	float4 DirPower;

	//void Update(float _DeltaTime) 
	//{
	//	if (hp�� 0�̶��)
	//	{
	//		LiveTime -= ��ŸŸ��
	//		if (0.0 >= LiveTime)
	//		{
	//			�������� �ٽ� �� �Ѱ�
	//			GetTransform()->worldpostition(StartPostion);
	//			Renderer->ChangeAnimation(idle);
	//		}
	//		return;
	//	}
	//	// �Ϲ����� �ڵ�
	//}

	void End() {}

	virtual void Update(float _DeltaTime) override;

private:
	float4 Pos;

};

