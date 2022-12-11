#pragma once
#include"Skill.h"
//투사체 조준된 방향으로 발사
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
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
	std::shared_ptr<GameEngineTextureRenderer> spearRenderer_;
	std::shared_ptr<GameEngineCollision> spearCol_;
	WeaponInfo spearWeaponInfo_;
	
};