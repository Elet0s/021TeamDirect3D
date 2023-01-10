#pragma once
#include "Monster.h"

class BlackEyes :public Monster
{
public:
	BlackEyes();
	~BlackEyes();


	BlackEyes(const BlackEyes& _Other) = delete;
	BlackEyes(BlackEyes&& _Other) noexcept = delete;
	BlackEyes& operator=(const BlackEyes& _Other) = delete;
	BlackEyes& operator=(BlackEyes&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void ReduceHP(float _deltaTime);
private:

	std::shared_ptr<GameEngineTextureRenderer> monsterHpMax_;
	std::shared_ptr<GameEngineTextureRenderer> monsterHp_;
	std::shared_ptr<GameEngineFontRenderer>monsterHpScore_;
};