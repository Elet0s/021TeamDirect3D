#pragma once


struct PlayerInfo
{
public:
	PlayerInfo()
		:
		level_(0),
		speed_(200.0f),
		maxHp_(100),
		hp_(100),
		maxExp_(100),
		exp_(0),
		atk_(10),
		def_(10),
		range_(10),
		RLDirection_(false),
		pushSpeed_(0)
	{

	}
public:
	float level_;
	float speed_;
	float maxHp_;
	float hp_;
	float maxExp_;
	float exp_;
	float atk_;
	float def_;
	float range_;
	float pushSpeed_;
	bool RLDirection_;
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
	//�÷��̾� ���� ���� �Լ�.
	static void CreatePlayer(GameEngineLevel* _thisLevel,const float4& _initPosition,const std::string_view& _playerName = "MainPlayer");
	//�÷��̾� ������ std::shared_ptr<Player>�� �����ϱ� ���ؼ� ���� �Լ�.


	static std::shared_ptr<Player>& GetPlayerInst()
	{
		return mainPlayer_;
	}

	static std::weak_ptr<Player> GetPlayerWeakPtr()
	{
		return mainPlayer_;
	}

	PlayerInfo& GetPlayerInfo()
	{
		return *CastThis<Player>()->playerInfo_;
	}

	CollisionReturn PlayerToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

public:
	std::shared_ptr<GameEngineCollision> collision_;


	//void SetLevel(GameEngineLevel* _NowLevel);
	float4 playerResultDirection_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void MoveDirectionUpdate(float _deltaTime);
	void PlayerDash(float _deltaTime);

private:
	float dashTimer_;
	bool dashState_;

	float4 moveDirection_;
	//std::shared_ptr<SkillManager> playerSkillManager_;
	std::shared_ptr<PlayerInfo> playerInfo_;
	std::shared_ptr<PlayerUI> playerUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;

	
};

