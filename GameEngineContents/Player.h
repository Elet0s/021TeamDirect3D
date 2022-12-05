#pragma once
#include "SkillManager.h"

struct PlayerInfo
{
public:
	PlayerInfo()
		:
		level_(0),
		atkMultiple_(100.f),
		attackSpeed_(100.0f),
		addProjectile_(0),
		throughProjectile_(0),
		projectileSize_(100.0f),
		projectileduration_(100.0f),
		projectilespeed_(100.0f),
		rangeSize_(100.0f),
		knockBack_(100.0f),
		goldMultiple_(100.0f),
		expMultiple_(100.0f),
		dashFullCharge_(0.f),
		dashReChargeTime_(3.0f),
		dashReUseTime_(0.3f),
		dashReChargeCount_(1.0f),
		speed_(200.0f),
		maxHp_(100),
		hp_(100),
		maxExp_(100),
		exp_(0),
		atk_(1.50f),
		def_(0),
		range_(1.0f),
		RLDirection_(false),
		pushSpeed_(0)
	{

	}
public:
	float level_;
	float attackSpeed_;
	float addProjectile_;
	float throughProjectile_;
	float projectileSize_;
	float projectileduration_;
	float projectilespeed_;
	float rangeSize_;
	float knockBack_;
	float goldMultiple_;
	float expMultiple_;
	float dashFullCharge_;
	float dashReChargeTime_;
	float dashReUseTime_;
	float dashReChargeCount_;

	float speed_;
	float maxHp_;
	float hp_;
	float maxExp_;
	float exp_;
	float atk_;
	float atkMultiple_;
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
	bool hitOnoff_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void MoveDirectionUpdate(float _deltaTime);
	void PlayerDash(float _deltaTime);

	void PlayerDeathEvent();//hp 0���ϸ� off�ϰ� ��ƼŬ�̺�Ʈ
	void LevelUpEvent();//����ġ �ް� �������� �ʱ�ȭ���ְ� ���������ִºκ�


private:
	float dashTimer_;
	bool dashState_;

	float4 moveDirection_;
	std::shared_ptr<PlayerInfo> playerInfo_;
	std::shared_ptr<PlayerUI> playerUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	static std::shared_ptr<SkillManager> playerSkillManager_;
	
};

