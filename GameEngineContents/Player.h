#pragma once
#include "SkillManager.h"

// 플레이어가 가진 구조체이나 패시브가 가지고 있는 스텟 모음
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
		atkMultiple_Result(100.0f),
		attackSpeed_Result(100.0f),
		defMul_Result(100.f),
		passMul_Result(100.f),
		projectileDuration_Result(100.f),
		projectileSize_Result(100.f),
		projectileSpeed_Result(100.f),
		hpMax_Per(100.0f),
		hpMax_(1.0f),
		hpMax_Result(100.f),
		speed_Per(100.f)
	{

	}

public:
	float hpMax_Per;
	float atkMultiple_Per; // 퍼센트 합
	float defMul_Per;   
	float passMul_Per;
	float attackSpeed_Per;
	float projectileSize_Per;
	float projectileDuration_Per;
	float projectileSpeed_Per;
	float speed_Per;

	float hpMax_;
	float atkMultiple_;  // 퍼센트 곱
	float defMul_;
	float passMul_;
	float attackSpeed_;
	float projectileSize_;
	float projectileDuration_;
	float projectileSpeed_;
	
	float hpMax_Result;
	float atkMultiple_Result;	// 합과 곱을 곱한 값 무기데미지에 곱해서 사용
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
		attackSpeed_(1.0f),
		addProjectile_(0),
		passProjectile_(0),
		projectileSize_(1.f),
		projectileduration_(1.f),
		projectilespeed_(1.f),
		rangeSize_(1.f),
		knockBack_(100.0f),
		goldMultiple_(100.0f),
		expMultiple_(100.0f),
		dashFullCharge_(4),
		dashCount_(3),
		dashReChargeTime_(3.00f),
		dashReUseTime_(0.3f),
		dashReChargeCount_(1),
		speed_(200.0f),
		maxHp_(100),
		hp_(100),
		hpRecuvere_(0.25f),
		maxExp_(100),
		exp_(0),
		atk_(1.0f),
		def_(0),
		ruting_Range_(4.0f),
		atk_Range_(1.0f),
		RLDirection_(false),
		pushSpeed_(0),
		damageMitigation_(0.0f),
		atkMultiple_(),
		knockback_(),
		gold_(1130000),
		stage_(0),
		targetScore_(0),
		myCombatType_(CombatType::Max),
		eliteTargetScore_(0),
		stageTimer_(0)
	{

	}
public:
	int level_;
	int addProjectile_;
	int passProjectile_;

	float stageTimer_;
	float projectileSize_;
	float projectileduration_;
	float projectilespeed_;
	float rangeSize_;
	float knockBack_;
	float goldMultiple_;
	float expMultiple_;
	int dashFullCharge_;
	int dashCount_;  // 현재 충전된 대시 수
	float dashReChargeTime_;
	float dashReUseTime_;
	int dashReChargeCount_;
	size_t stage_;
	size_t targetScore_;
	size_t eliteTargetScore_;
	CombatType myCombatType_;

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
	float damageMitigation_;
	bool RLDirection_;

	int gold_;
};

class PlayerUI;
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
	//플레이어 공식 생성 함수.
	static void CreatePlayer(GameEngineLevel* _thisLevel,const float4& _initPosition,const std::string_view& _playerName = "MainPlayer");
	//플레이어 전역과 std::shared_ptr<Player>을 유지하기 위해서 만든 함수.


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

	std::shared_ptr<SkillManager> GetSkillManager()
	{
		//return CastThis<Player>()->playerSkillManager_;
		if (nullptr == CastThis<Player>())
		{
			MsgBoxAssert("플레이어가 없습니다.");
			return nullptr;
		}
		else
		{
			return CastThis<Player>()->playerSkillManager_;
		}
	}

	CollisionReturn PlayerToGameItemObjectCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn ItemRangeToGameItemObjectCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	void ResetScore();

	void FlashPlayer(float _deltaTime);
public:
	std::shared_ptr<GameEngineCollision> collision_;

	std::shared_ptr<GameEngineCollision> itemRangeCollision_;

	std::list<float> serchCloseMonster_;
	float4 playerResultDirection_;
	bool hitOnoff_;
	bool flash_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void MoveDirectionUpdate(float _deltaTime);
	void PlayerDash(float _deltaTime);

	void ReChargeDash(float _deltaTime);

	void PlayerDeathEvent();//hp 0이하면 off하고 파티클이벤트
	void LevelUpEvent();//경험치 받고 전부차면 초기화해주고 레벨업해주는부분

	void ColCheak();
private:

	bool flashLoop_;
	float flashTimer_;
	float healingTimer_;
	float dashTimer_;
	bool dashState_;

	float dashRechargeTimer_;

	float4 moveDirection_;
	std::shared_ptr<PlayerInfo> playerInfo_;
	std::shared_ptr<PlayerPassiveInfo> playerPassiveInfo_;
	std::shared_ptr<PlayerUI> playerUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerRenderer_;
	static std::shared_ptr<SkillManager> playerSkillManager_;


};

