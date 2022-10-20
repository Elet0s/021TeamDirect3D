#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include "GlobalContentsValue.h"

class Player;
class Monster;
class PlayLevel: public GameEngineLevel
{

public:

	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _other) = delete;
	PlayLevel(PlayLevel&& _other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _other) = delete;
	PlayLevel& operator=(PlayLevel&& _other) = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;
	Monster* monsterActor_;
};

