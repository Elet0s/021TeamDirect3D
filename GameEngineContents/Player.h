#pragma once
#include "SkillManager.h"

// �÷��̾ ���� ����ü�̳� �нú갡 ������ �ִ� ���� ����
struct PlayerPassiveInfo
{
public:
	PlayerPassiveInfo()
		: atkMultiple_Per(100.f),
		defMul_Per(100.f),
		passMul_Per(0.f),
		attackSpeed_Per(100.f),
		projectileSpeed_Per(100.f),
		projectileDuration_Per(100.f),
		projectileSize_Per(100.f),
		atkMultiple_(1.f),
		defMul_(1.f),
		passMul_(1.f),
		attackSpeed_(1.f),
		projectileSize_(1.f),
		projectileDuration_(1.f),
		projectileSpeed_(1.f),
		atkMultiple_Result(0.0f),
		defMul_Result(0.f),
		passMul_Result(0.f),
		projectileDuration_Result(0.f),
		projectileSize_Result(0.f),
		projectileSpeed_Result(0.f)

	{

	}

public:
	float atkMultiple_Per; // 130 
	float defMul_Per;   
	float passMul_Per;
	float attackSpeed_Per;
	float projectileSize_Per;
	float projectileDuration_Per;
	float projectileSpeed_Per;

	float atkMultiple_;  // 0.95
	float defMul_;
	float passMul_;
	float attackSpeed_;
	float projectileSize_;
	float projectileDuration_;
	float projectileSpeed_;
	
	float atkMultiple_Result;	// atkMultiple_Per * atkMultiple_
	float defMul_Result;
	float passMul_Result;
	float attackSpeed_Result;
	float projectileSize_Result;
	float projectileDuration_Result;
	float projectileSpeed_Result;
};


struct PlayerInfo
{
public:
	PlayerInfo()
		:
		level_(0),
		attackSpeed_(100.0f),
		addProjectile_(0),
		passProjectile_(0),
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
		ruting_Range_(4.0f),
		atk_Range_(100.0f),
		RLDirection_(false),
		pushSpeed_(0)
	{

	}
public:
	float level_;
	size_t addProjectile_;
	size_t passProjectile_;

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

	float knockback_;
	float atk_Range_;
	float speed_;
	float maxHp_;
	float hp_;
	float maxExp_;
	float exp_;
	float atk_;
	float attackSpeed_;
	float atkMultiple_;
	float def_;
	float ruting_Range_;
	float pushSpeed_;
	float hpRecuvere_;
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

	PlayerPassiveInfo& GetPlayerPassiveInfo()
	{
		return *CastThis<Player>()->playerPassiveInfo_;
	}

	CollisionReturn PlayerToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

public:
	std::shared_ptr<GameEngineCollision> collision_;

	std::list<float> serchCloseMonster_;
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
	std::shared_ptr<PlayerPassiveInfo> playerPassiveInfo_;
	std::shared_ptr<PlayerUI> playerUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	static std::shared_ptr<SkillManager> playerSkillManager_;


};

