#pragma once
#include "Monster.h"

class NormalKobold :public Monster
{
public:
	NormalKobold();
	~NormalKobold();


	NormalKobold(const NormalKobold& _Other) = delete;
	NormalKobold(NormalKobold&& _Other) noexcept = delete;
	NormalKobold& operator=(const NormalKobold& _Other) = delete;
	NormalKobold& operator=(NormalKobold&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void HpCheak();
};