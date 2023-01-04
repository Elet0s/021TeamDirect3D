#pragma once
#include"Skill.h"
#include"Monster.h"
//���� ü���� ���� ������ �߻�
class Crossbow :public Skill
{
public:
	Crossbow();
	~Crossbow();

	Crossbow(const Crossbow& _Other) = delete;
	Crossbow(Crossbow&& _Other) noexcept = delete;
	Crossbow& operator=(const Crossbow& _Other) = delete;
	Crossbow& operator=(Crossbow&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹
public:
	std::pair< std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>projectileGroup_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//���� ��� Ž��'
	void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	void RenderRotate();// �߻�ü ȸ��
	void RangeCheak(float _deltaTime);//�߻�ü ����
	void StateSet() override;//������ ���� ���� ����
	void ColCheak();//�ݸ��� üũ
	void TarGetInitialization();//Ÿ���ʱ�ȭ
	void TimerUpdater(float _deltaTime);//Ÿ�̸� ������Ʈ

private:
	bool firstSerchCheak_;
	bool istarget_;//Ÿ���� ������ true

	float targerSerchTimer_;

	size_t targetSerchCounter_;

	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 

	WeaponInfo crossbowWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ
	std::pair<size_t, float> minHpPair_;//Ÿ�� ���
	std::vector<std::pair<size_t, float>> targetInst_;//Ÿ�� ����
	std::vector<float4> referenceVectorList_;//���� ����

};