#pragma once
//#include <GameEngineCore\CoreMinimal.h>
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

protected:
	static std::shared_ptr<GameEngineInstancingRenderer> allMonstersRenderer_;

	static int monsterCreationIndex_;
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


	static std::vector<std::shared_ptr<Monster>>& GetMonsterList()
	{
		return allMonsters_;
	}
	MonsterInfo& GetMonsterInfo()
	{
		return *CastThis<Monster>()->monsterInfo_;
	}
	CollisionReturn MonsterToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	//����Ǯ ������ ����.
	static void ReserveMonsters(GameEngineLevel* _thisLevel, size_t _allMonsterCount);

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
			newMonster->GetTransform().SetWorldPosition(float4::Zero);
			newMonster->Off();

			allMonsters_.push_back(newMonster);


			newMonster->monsterTextureName_ = &typeid(MonsterType).name()[6];
			newMonster->monsterTextureName_ += ".png";
			newMonster->instancingUnitIndex_ = monsterCreationIndex_++;
			allMonstersRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).SetTextureIndex(
				GameEngineTexture2DArray::Find("Monster")->GetIndex(newMonster->monsterTextureName_)
			);
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

			allMonsters_[i]->On();
			allMonsters_[i]->isSummoned_ = true;
			
			float cameraX = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().x;
			float cameraY = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().y;
			float4 monsterPosition_ = GameEngineRandom::mainRandom_.RandomFloat4(float4(cameraX - 1280, cameraY - 720),float4(cameraX + 1280, cameraY + 720));
			monsterPosition_.z = -6.f;



		if (monsterPosition_.x > cameraX + 640 || monsterPosition_.x < cameraX - 640)
		{
			allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition_);

			allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
				allMonsters_[i]->monsterScale_
			);
			allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
				monsterPosition_
			);
		}
		else if (monsterPosition_.x< cameraX + 640 && monsterPosition_.x>cameraX -640)
		{
			if (monsterPosition_.y > cameraY + 360 || monsterPosition_.y < cameraY - 360)
			{
				allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition_);

				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
					allMonsters_[i]->monsterScale_
				);
				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
					monsterPosition_
				);
			}
			else
			{
				i--;
			}
		}
		else
		{
			i--;
		}


		
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

	inline bool IsSummoned() const
	{
		return this->isSummoned_;
	}


public:
	float mxMove_;
	float myMove_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Chaseplayer(float _deltaTime);
	void Attack();



protected:
	bool colCheakToPlayer_;
	bool colCheakToMonster_;

	float mx_;//�ڽ��� ��ǥ
	float my_;
	float px_;
	float py_;

	float playerRange_; // �÷��̾���� �Ÿ�
	float atkDeltaTime_;

	float4 pushToMonsterVector;

	float4 pushVector_;
	float4 reactionVector_;
	float4 range_; // ���Ϳ��� �÷��̾������ ����
	float4 monsterBaseVector_;//�浹������ȵ� ���� �⺻���� ���� ����
	float4 monsterResultVector_;// ���� ���꺤��
	float4 playerReactionVector_;// �÷��̾� ���ۿ뺤��
	float4 monsterReactionVector_;// ���� ���ۿ뺤��

	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr <MonsterInfo> monsterInfo_;
	//std::shared_ptr<GameEngineTextureRenderer> monRenderer_;
	//std::shared_ptr<class Texture2DShadowRenderer> shadowRenderer_;

	int instancingUnitIndex_;	//�� ���͸� ����ؼ� �׸��� �ִ� �ν��Ͻ������� ��ȣ.

	float4 monsterScale_;		//�� ���� ������ ũ��.

	GameEngineAnimation monsterAnimation_;	//�ð� ���������� �ε����� �ٲ��ִ� �ִϸ��̼� ���.


private:
	std::string monsterTextureName_;	//���� �ڱ� �ڽ��� �ؽ�ó �̸�. 
	//Ŭ���� �̸��� �����ϴٴ� ������ ����ǰ� ��.

	bool isSummoned_;	//true: ��ȯ�Ǽ� �ʵ忡�� Ȱ���ϰ� ����.

};