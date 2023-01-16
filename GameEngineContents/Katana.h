#pragma once
#include"Skill.h"

//���������� ���� ����� �� �Ҽ��� ����
class Monster;
class Katana :public Skill
{
public:
	Katana();
	~Katana();

	Katana(const Katana& _Other) = delete;
	Katana(Katana&& _Other) noexcept = delete;
	Katana& operator=(const Katana& _Other) = delete;
	Katana& operator=(Katana&& _Other) noexcept = delete;

	//void Init() override;
	//void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SearchTarget();	
	void StateSet() override;

private:
	void Attack();

private:

	WeaponInfo katanaWeaponInfo_;//���� ����
	float squaredWeaponRange_;
	size_t targetLimitation_;
	float attackInterval_;
	
	std::list<Monster*> monstersInRange_;	//���� �� ��� ����.
	//std::pair<size_t, float> minHpPair_;//Ÿ�� ���
	//std::vector<std::pair<size_t, float>> targetInst_;//Ÿ�� ����



	GameEngineTextureRenderer* katanaRenderer_[4];

};