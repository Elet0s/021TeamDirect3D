#pragma once
#include "Monster.h"

class Green :public Monster
{
public:
	Green();
	~Green();


	Green(const Green& _Other) = delete;
	Green(Green&& _Other) noexcept = delete;
	Green& operator=(const Green& _Other) = delete;
	Green& operator=(Green&& _Other) noexcept = delete;
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