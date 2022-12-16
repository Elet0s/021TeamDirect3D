#pragma once
#include "Skill.h"
#include "Monster.h"
//���� ����� ������ �����Ǵ� ���� ����ü�� �߻�
class MagicWand :public Skill
{
public:
	MagicWand();
	~MagicWand();

	MagicWand(const MagicWand& _Other) = delete;
	MagicWand(MagicWand&& _Other) noexcept = delete;
	MagicWand& operator=(const MagicWand& _Other) = delete;
	MagicWand& operator=(MagicWand&& _Other) noexcept = delete;

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

	WeaponInfo magicWandWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ
	std::pair<size_t, float> minHpPair_;//Ÿ�� ���
	std::vector<std::pair<size_t, float>> targetInst_;//Ÿ�� ����


	std::vector<std::shared_ptr<ProjectileGroup>> projectileGroupList_;

};