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
public:

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void renderRotate(float _deltaTime);
private:
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
	std::shared_ptr<GameEngineTextureRenderer> spearRenderer_;
	std::shared_ptr<GameEngineCollision> spearCol_;
	WeaponInfo spearWeaponInfo_;
	
};