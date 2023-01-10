#pragma once
#include "Monster.h"

class NormalGoblin :public Monster
{
public:
	NormalGoblin();
	~NormalGoblin();


	NormalGoblin(const NormalGoblin& _Other) = delete;
	NormalGoblin(NormalGoblin&& _Other) noexcept = delete;
	NormalGoblin& operator=(const NormalGoblin& _Other) = delete;
	NormalGoblin& operator=(NormalGoblin&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};