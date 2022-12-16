#pragma once
#include "Skill.h"
#include"Monster.h"
// ������ ������ ���ʴ�� �����ϰ� ��ο� �ִ� �ٸ� ��� ���� ������ �߰� ����ü�� ������ �������� ����
class MagicWisp:public Skill
{
public:
	MagicWisp();
	~MagicWisp();

	MagicWisp(const MagicWisp& _Other) = delete;
	MagicWisp(MagicWisp&& _Other) noexcept = delete;
	MagicWisp& operator=(const MagicWisp& _Other) = delete;
	MagicWisp& operator=(MagicWisp&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);// ������ ���� Ž��(�����Ÿ� ���)

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

	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 

	WeaponInfo magicWispWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ
	std::pair<size_t, float> minHpPair_;//Ÿ�� ���
	std::vector<std::pair<size_t, float>> targetInst_;//Ÿ�� ����


	std::vector<std::shared_ptr<ProjectileGroup>> projectileGroupList_;

};