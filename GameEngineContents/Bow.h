#pragma once
#include"Skill.h"
#include"Monster.h"
//���� ����� ������ �߻�
class Bow :public Skill
{
public:
	Bow();
	~Bow();

	Bow(const Bow& _Other) = delete;
	Bow(Bow&& _Other) noexcept = delete;
	Bow& operator=(const Bow& _Other) = delete;
	Bow& operator=(Bow&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹
public:
	std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>projectileGroup_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList01_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList02_;
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
	float targerSerchTimer01_;//Ÿ�� �˻� �ֱ�=���ݼӵ�
	float targerSerchTimer02_;

	std::vector<size_t> passNum_;

	size_t targetSerchCounter_;//Ÿ�ٰ˻��� ���� �� �� ������Ʈ ����

	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 

	WeaponInfo bowWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ

	std::pair<size_t, float> minHpPair_;//Ÿ�� ���

	std::vector<std::pair<size_t, float>> targetInst01_;//Ÿ�� ����
	std::vector<std::pair<size_t, float>> targetInst02_;

	std::vector<float4> referenceVectorList01_;//���� ����
	std::vector<float4> referenceVectorList02_;
};