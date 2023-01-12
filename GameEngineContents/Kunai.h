#pragma once
#include"Skill.h"
//�������߻�
class Kunai : public Skill
{
public:
	Kunai();
	~Kunai();

	Kunai(const Kunai& _Other) = delete;
	Kunai(Kunai&& _Other) noexcept = delete;
	Kunai& operator=(const Kunai& _Other) = delete;
	Kunai& operator=(Kunai&& _Other) noexcept = delete;


	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);// ������ ���� Ž��(�����Ÿ� ���)

	std::shared_ptr<GameEngineCollision> spearRangeCol_;

	std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>projectileGroup_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList_;//�߻�ü ����

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void Shoothing(float _deltaTime);//���� ��� Ž��'
	void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	void RenderRotate();// �߻�ü ȸ��
	void RangeCheak(float _deltaTime);//�߻�ü ����
	void StateSet() override;//������ ���� ���� ����
	void AimSet();
	//void SerchTarget();//���� ��� Ž��'
	//void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	//void RenderRotate();// �߻�ü ȸ��
	//void RangeCheak(float _deltaTime);//�߻�ü ����
	//void StateSet() override;//������ ���� ���� ����

private:
	bool Shooting_;
	bool setAim_;
	float timer_;
	float duringtime_;
	size_t consecutiveCounter_;
	float angle_;
	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 
	float4 mouseAimPos_;
	float consecutiveAngle_;
	float4 range_;
	float4 playerPos_;

	WeaponInfo spearWeaponInfo_;//���� ����


};