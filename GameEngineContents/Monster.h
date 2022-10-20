#pragma once
#include <GameEngineCore\CoreMinimal.h>


class Monster: public GameEngineActor
{



public:

	Monster();
	~Monster();

	Monster(const Monster& _other) = delete;
	Monster(Monster&& _other) noexcept = delete;
	Monster& operator=(const Monster& _other) = delete;
	Monster& operator=(Monster&& _other) = delete;

public:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
};

