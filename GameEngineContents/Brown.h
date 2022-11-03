#pragma once
#include <GameEngineCore\CoreMinimal.h>
#include "Monster.h"

class Brown :public Monster
{
public:
	Brown();
	~Brown();


	Brown(const Brown& _Other) = delete;
	Brown(Brown&& _Other) noexcept = delete;
	Brown& operator=(const Brown& _Other) = delete;
	Brown& operator=(Brown&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};