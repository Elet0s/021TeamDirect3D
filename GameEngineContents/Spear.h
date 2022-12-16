#pragma once
#include"Skill.h"
#include"Mouse.h"
//����ü ���ص� �������� �߻�
class Spear : public Skill
{
public:
	Spear();
	~Spear();

	Spear(const Spear& _Other) = delete;
	Spear(Spear&& _Other) noexcept = delete;
	Spear& operator=(const Spear& _Other) = delete;
	Spear& operator=(Spear&& _Other) noexcept = delete;
public:

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

	void SerchTarget();//���� ��� Ž��'
	void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	void RenderRotate();// �߻�ü ȸ��
	void RangeCheak(float _deltaTime);//�߻�ü ����
	void StateSet() override;//������ ���� ���� ����

private:

	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 

	WeaponInfo crossbowWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<ProjectileGroup>> projectileGroupList_;

};