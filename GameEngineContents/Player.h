#pragma once

class GameEngineDefaultRenderer;
class Player: public GameEngineActor
{
	static Player* mainPlayer_;

public:

	Player();
	~Player();

	Player(const Player& _other) = delete;
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(Player&& _other) = delete;

public:



public:
	static Player* GetMainPlayer()
	{
		return mainPlayer_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void IdleStart(const StateInfo& _info);
	void IdleUpdate(float _deltaTime, const StateInfo& _info);

	//void MoveStart(const StateInfo& _info);
	void MoveUpdate(float _deltaTime, const StateInfo& _info);


private:
	GameEngineTextureRenderer* playerRenderer_;

	GameEngineStateManager stateManager_;

};

