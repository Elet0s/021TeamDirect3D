#pragma once
#include"Skill.h"
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


	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	GameEngineCollision* spearRangeCol_;

	std::pair<GameEngineTextureRenderer*, GameEngineCollision*>projectileGroup_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList_;//�߻�ü ����

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void Shoothing(float _deltaTime);//��������
	void StateSet() override;//������ ���� ���� ����
	void AimSet();//���콺 ����


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
	
	float4 range_;
	float4 playerPos_;

	WeaponInfo spearWeaponInfo_;//���� ����


};