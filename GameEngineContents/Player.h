#pragma once

class GameEngineDefaultRenderer;
class Player: public GameEngineActor
{
	static std::shared_ptr<Player> mainPlayer_;
	//�÷��̾ �������� ���� ����: �� ���� Ư���� ����ʰ� ������ ���ʿ��� �����ؾ� �ϴ� �÷��̾� ������ ������,
	// �װ� ���� �÷��̾�� �и��� ������ ���� ������� �÷��̾� ��°�� �������� �����ϴ°� �� ���� �� ���Ƽ�.

	static bool isInitialized_;	//true: �÷��̾� ���� �� �ʱ�ȭ ����.

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
	);	//�÷��̾� ���� ���� �Լ�.
	//�÷��̾� ������ std::shared_ptr<Player>�� �����ϱ� ���ؼ� ���� �Լ�.



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

	//void IdleStart(const StateInfo& _info);
	//void IdleUpdate(float _deltaTime, const StateInfo& _info);

	//void MoveStart(const StateInfo& _info);
	//void MoveUpdate(float _deltaTime, const StateInfo& _info);

	void MoveDirectionUpdate(float _deltaTime);

private:

	float4 moveDirection_;
	float speed_;
	float maxHp_;
	float hp_;
	float maxExp_;
	float exp_;
	float atk_;
	float def_;
	float range_;

	GameEngineLevel* nowLevel_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	std::shared_ptr<GameEngineCollision> collision_;
	//GameEngineStateManager stateManager_;

};

