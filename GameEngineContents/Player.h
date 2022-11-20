#pragma once

class GameEngineDefaultRenderer;
class Player: public GameEngineActor
{
	static std::shared_ptr<Player> mainPlayer_;
	//플레이어를 전역으로 만든 이유: 이 게임 특성상 월드맵과 전투맵 양쪽에서 공유해야 하는 플레이어 정보가 많은데,
	// 그걸 굳이 플레이어와 분리된 구조로 따로 만드느니 플레이어 통째로 전역으로 생성하는게 더 편할 것 같아서.

	static bool isInitialized_;	//true: 플레이어 생성 및 초기화 끝남.

public:
	Player();
	~Player();

	Player(const Player& _other) = delete;
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(Player&& _other) = delete;

public:
	static void CreatePlayer(
		GameEngineLevel* _thisLevel,
		const float4& _initPosition,
		const std::string_view& _playerName = "MainPlayer"
	);



public:
	static std::shared_ptr<Player>& GetPlayerInst()
	{
		return mainPlayer_;
	}

	static std::weak_ptr<Player> GetPlayerWeakPtr()
	{
		return mainPlayer_;
	}

	inline float GetPlayerSpeed()
	{
		return speed_;
	}

	CollisionReturn MonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	void SetLevel(GameEngineLevel* _NowLevel);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void IdleStart(const StateInfo& _info);
	void IdleUpdate(float _deltaTime, const StateInfo& _info);

	//void MoveStart(const StateInfo& _info);
	void MoveUpdate(float _deltaTime, const StateInfo& _info);


private:
	float speed_;

	GameEngineLevel* nowLevel_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	std::shared_ptr<GameEngineCollision> collision_;
	GameEngineStateManager stateManager_;

};

