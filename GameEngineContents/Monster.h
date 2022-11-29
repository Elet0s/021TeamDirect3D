#pragma once
#include <GameEngineCore\CoreMinimal.h>
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

struct MonsterInfo
{
public:
	MonsterInfo()
		:baseSpeed_(0),
		ResultSpeed_(0),
		maxHp_(0),
		hp_(0),
		atk_(0),
		giveExp_(0),
		monsterOrder_(MonsterOrder::BlackEyes)
	{

	}
public:
	float baseSpeed_; //���� �⺻�ӵ�
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

	//����Ǯ ������ ����.
	static void ReserveMonsters(size_t _allMonsterCount);

	//����� ���ʹ� Ǯ�� ����, ���.
	void Unsummon(); // ���� �߰��� ����� �뵵

	//���� ���� �� ���.
	template <typename MonsterType>
	static void CreateMonster(GameEngineLevel* _thisLevel, size_t _monsterCount)
	{
		for (size_t i = 0; i < _monsterCount; ++i)
		{
			std::shared_ptr<Monster> newMonster = _thisLevel->CreateActor<MonsterType>(ObjectOrder::Monster);
			newMonster->isSummoned_ = false;
			newMonster->monCollision_->Off();
			newMonster->monRenderer_->Off();
			newMonster->shadowRenderer_->Off();
			newMonster->GetTransform().SetWorldPosition(float4::Zero);

			allMonsters_.push_back(newMonster);
		}
	}

	//������ ���� ��ġ.
	template <typename MonsterType>
	static void SummonMonster(GameEngineLevel* _thisLevel, UINT _summonCount)
	{
		UINT count = _summonCount;
		for (size_t i = 0; i < allMonsters_.size(); ++i)
		{
			if (nullptr == std::dynamic_pointer_cast<MonsterType>(allMonsters_[i]))
			{
				//���ϴ� Ÿ�� ���Ͱ� �ƴ϶�� ����.
				continue;
			}

			if (true == allMonsters_[i]->isSummoned_)
			{
				//�̹� ��ȯ�� ���Ͷ�� ����.
				continue;
			}

			allMonsters_[i]->isSummoned_ = true;
			allMonsters_[i]->monCollision_->On();
			allMonsters_[i]->monRenderer_->On();
			allMonsters_[i]->shadowRenderer_->On();
			//�ݸ���, ������, �׸��ڷ����� ��� �غ�.
			
			float cameraX = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().x;
			float cameraY = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().y;
			float4 monsterPosition_ = GameEngineRandom::mainRandom_.RandomFloat4(float4(cameraX - 640, cameraY - 360),float4(cameraX + 640, cameraY + 360));
			monsterPosition_.z = 0.f;

			allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition_);
			--count;//��ȯ ������� ���Ͷ�� ��ȯ�ϰ� ī��Ʈ ����.
			if (0 == count)
			{
				//�� ��ȯ�ߴٸ� ����.
				break;
			}
		}

		if (0 != count)
		{
			//��ȯ�ϱ⿡ ����� ���Ͱ� �����ٸ� ���.
			MsgBoxAssert("����� ������ ���Ͱ� �������ϴ�.");
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
	bool colCheakToPlayer_;

	float mx_;//�ڽ��� ��ǥ
	float my_;
	float px_;
	float py_;

	float playerRange_; // �÷��̾���� �Ÿ�

	float4 pushVector_;
	float4 range_; // ���Ϳ��� �÷��̾������ ����
	float4 monsterResultVector_;// ���� ���꺤��
	float4 reactionVector_;// ���ۿ뺤��\

	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr <MonsterInfo> monsterInfo_;
	std::shared_ptr<GameEngineTextureRenderer> monRenderer_;
	std::shared_ptr<class Texture2DShadowRenderer> shadowRenderer_;

private:
	bool isSummoned_;	//true: ��ȯ�Ǽ� �ʵ忡�� Ȱ���ϰ� ����.

};