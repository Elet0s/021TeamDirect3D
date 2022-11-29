#pragma once
#include <GameEngineCore\CoreMinimal.h>
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

struct MonsterInfo
{
public:
	MonsterInfo()
		:baseSpeed_(0),
		colSpeed_(0),
		ResultSpeed_(0),
		maxHp_(0),
		hp_(0),
		atk_(0),
		giveExp_(0),
		monsterOrder_(MonsterOrder::BlackEyes)
	{

	}
public:
	float baseSpeed_;
	float colSpeed_;
	float ResultSpeed_;
	float maxHp_;
	float hp_;
	float atk_;
	float giveExp_;
	MonsterOrder monsterOrder_;
};


class GameEngineRandom;
class Monster: public GameEngineActor
{
	static std::vector<std::shared_ptr<Monster>> allMonsters_;
public:
	Monster();
	~Monster();

	Monster(const Monster& _other) = delete;
	Monster(Monster&& _other) noexcept = delete;
	Monster& operator=(const Monster& _other) = delete;
	Monster& operator=(Monster&& _other) = delete;

	void Death() = delete;
	void Death(float _time) = delete;

public:

	MonsterInfo& GetMonsterInfo()
	{
		return *CastThis<Monster>()->monsterInfo_;
	}
	CollisionReturn MonsterToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	//몬스터풀 사이즈 예약.
	static void ReserveMonsters(size_t _allMonsterCount);

	//사망한 몬스터는 풀로 복귀, 대기.
	void Unsummon();

	//몬스터 생성 및 대기.
	template <typename MonsterType>
	static void CreateMonster(GameEngineLevel* _thisLevel, size_t _monsterCount)
	{
		for (size_t i = 0; i < _monsterCount; ++i)
		{
			std::shared_ptr<Monster> newMonster = _thisLevel->CreateActor<MonsterType>(ObjectOrder::Monster);

			allMonsters_.push_back(newMonster);
		}
	}

	//레벨에 몬스터 배치.
	template <typename MonsterType>
	static void SummonMonster(GameEngineLevel* _thisLevel, UINT _summonCount)
	{
		UINT count = _summonCount;
		for (size_t i = 0; i < allMonsters_.size(); ++i)
		{
			if (nullptr == std::dynamic_pointer_cast<MonsterType>(allMonsters_[i]))
			{
				//원하는 타입 몬스터가 아니라면 무시.
				continue;
			}

			if (true == allMonsters_[i]->isSummoned_)
			{
				//이미 소환된 몬스터라면 무시.
				continue;
			}

			allMonsters_[i]->isSummoned_ = true;
			allMonsters_[i]->monCollision_->On();
			allMonsters_[i]->monRenderer_->On();
			allMonsters_[i]->shadowRenderer_->On();
			//콜리전, 렌더러, 그림자렌더러 사용 준비.
			
			float cameraX = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().x;
			float cameraY = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().y;
			float4 monsterPosition = GameEngineRandom::mainRandom_.RandomFloat4(
				float4(cameraX - 640, cameraY - 360),
				float4(cameraX + 640, cameraY + 360)
			);
			monsterPosition.z = 0.f;
			allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition);
			--count;
			//소환 대기중인 몬스터라면 소환하고 카운트 감소.

			if (0 == count)
			{
				//다 소환했다면 종료.
				break;
			}
		}

		if (0 != count)
		{
			//소환하기에 충분한 몬스터가 없었다면 경고.
			MsgBoxAssert("충분한 숫자의 몬스터가 없었습니다.");
			return;
		}
	}



public:
	float mxMove_;
	float myMove_;


protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Chaseplayer(float _deltaTime);
	void SummonMon();

protected:
	bool colCheak_;
	int playerRange_;
	float mx_;
	float my_;
	float4 range_;
	float4 resultRange_;
	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr <MonsterInfo> monsterInfo_;
	std::shared_ptr<GameEngineTextureRenderer> monRenderer_;
	std::shared_ptr<class Texture2DShadowRenderer> shadowRenderer_;

private:
	bool isSummoned_;	//true: 소환되서 필드에서 활동하고 있음.

};