#pragma once
#include <GameEngineCore\CoreMinimal.h>
#include "Monster.h"

class RedFlyingEyes :public Monster
{
public:
	RedFlyingEyes();
	~RedFlyingEyes();


	RedFlyingEyes(const RedFlyingEyes& _Other) = delete;
	RedFlyingEyes(RedFlyingEyes&& _Other) noexcept = delete;
	RedFlyingEyes& operator=(const RedFlyingEyes& _Other) = delete;
	RedFlyingEyes& operator=(RedFlyingEyes&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};