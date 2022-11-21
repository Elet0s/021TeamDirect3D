#pragma once


struct PlayerInst
{
public:
	PlayerInst()
		: 
		speed_(200.0f),
		maxHp_(30),
		hp_(30),
		maxExp_(100),
		exp_(0),
		atk_(10),
		def_(10),
		range_(10)
	{

	}
public:
	float speed_;
	float maxHp_;
	float hp_;
	float maxExp_;
	float exp_;
	float atk_;
	float def_;
	float range_;
};
class PlayerUI;
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
	);//�÷��̾� ���� ���� �Լ�.
	//�÷��̾� ������ std::shared_ptr<Player>�� �����ϱ� ���ؼ� ���� �Լ�.




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
		return playerInst_->speed_;
	}

	CollisionReturn MonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	//void SetLevel(GameEngineLevel* _NowLevel);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void MoveDirectionUpdate(float _deltaTime);

private:
	std::shared_ptr<PlayerUI> playerUi_;
	float4 moveDirection_;
	std::shared_ptr<PlayerInst> playerInst_;
	GameEngineLevel* nowLevel_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	std::shared_ptr<GameEngineCollision> collision_;
};

