#pragma once
#include <GameEngineCore\CoreMinimal.h>
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
private:
};