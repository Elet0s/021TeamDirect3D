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
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList_;//�߻�ü ����

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//���� ��� Ž��'
	void ProjectileSort(float _deltaTime);//�߻�ü ������ �÷��̾� ��ġ�� ����
	void RenderRotate( );// �߻�ü ȸ��
	void RangeCheak(float _deltaTime);//�߻�ü ����
	void StateSet() override;//������ ���� ���� ����
	void ColCheak();//�ݸ��� üũ
	void TarGetInitialization();//Ÿ���ʱ�ȭ
	void TimerUpdater(float _deltaTime);//Ÿ�̸� ������Ʈ


private:
	bool shoothingPeojectile_;
	bool firstCheak_;
	bool firstSort;
	bool Istarger;//Ÿ���� ������ true

	float targerSerchTimer_;//Ÿ�� �˻� �ֱ�=���ݼӵ�
	size_t targetserchCounter_;//Ÿ�ٰ˻��� ���� �� �� ������Ʈ ����
	float timer02_;
	float timer03_;
	float timer04_;
	float timer05_;




	float resultCos_;//���� ��ǥ, �÷��̾� ��ǥ x�� ���� ���� 
	float4 referenceVector_;//�÷��̾� ���� ���ͷ� ���� ���� 



	WeaponInfo shuriKenWeaponInfo_;//���� ����

	std::vector<std::shared_ptr<Monster>> monsterList_; //��ü ���� ����Ʈ
	std::pair<size_t, float> minHpPair_;//Ÿ�� ���
	std::vector<std::pair<size_t, float>> targetInst_;//Ÿ�� ����
	std::vector<float4> referenceVectorList_;//���� ����




};

