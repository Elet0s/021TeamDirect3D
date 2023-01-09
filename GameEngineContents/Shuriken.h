#pragma once
#include"Skill.h"
#include"Monster.h"
//���� ���� ü���� ���� �����ϴ� �ټ��� �������� ��ô
class Shuriken :public Skill
{
public:
	Shuriken();
	~Shuriken();

	Shuriken(const Shuriken& _Other) = delete;
	Shuriken(Shuriken&& _Other) noexcept = delete;
	Shuriken& operator=(const Shuriken& _Other) = delete;
	Shuriken& operator=(Shuriken&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // �߻�ü �浹

public:
	std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>projectileGroup_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList01_;//�߻�ü ����
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList02_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList03_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//���� ��� Ž��'
	void ProjectileSort();//�߻�ü ������ �÷��̾� ��ġ�� ����
	void RenderRotate( );// �߻�ü ȸ��
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
	float targerSerchTimer03_;

	size_t targetSerchCounter_;//Ÿ�ٰ˻��� ���� �� �� ������Ʈ ����

	std::vector<size_t> passNum_; //�� ����ü ��������

	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 

	WeaponInfo shuriKenWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ

	std::pair<size_t, float> minHpPair_;//Ÿ��

	std::vector<std::pair<size_t, float>> targetInst01_;//Ÿ�� ����
	std::vector<std::pair<size_t, float>> targetInst02_;
	std::vector<std::pair<size_t, float>> targetInst03_;

	std::vector<float4> referenceVectorList01_;//���� ����
	std::vector<float4> referenceVectorList02_;
	std::vector<float4> referenceVectorList03_;


};

