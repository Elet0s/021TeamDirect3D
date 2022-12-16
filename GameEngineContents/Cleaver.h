#pragma once
#include"Skill.h"
#include"Mouse.h"

//���� ���� �������� �о�� �������� ū ����ü�� �߻�
class Cleaver : public Skill
{
public:
	Cleaver();
	~Cleaver();

	Cleaver(const Cleaver& _Other) = delete;
	Cleaver(Cleaver&& _Other) noexcept = delete;
	Cleaver& operator=(const Cleaver& _Other) = delete;
	Cleaver& operator=(Cleaver&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);// ������ ���� Ž��(�����Ÿ� ���)

	std::shared_ptr<GameEngineCollision> crossbowRangeCol_;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	//void SerchTarget();//���� ��� Ž��'
	//void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	//void RenderRotate();// �߻�ü ȸ��
	//void RangeCheak(float _deltaTime);//�߻�ü ����
	//void StateSet() override;//������ ���� ���� ����

private:

	float resultCos_;//���콺 ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���콺�� ���� ���� 

	WeaponInfo crossbowWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<ProjectileGroup>> projectileGroupList_;

};