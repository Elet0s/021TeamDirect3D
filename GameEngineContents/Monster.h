#pragma once
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"
#include "GameItemObjectManager.h"

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
		monsterType_(MonsterType::BlackEyes),
		bossPattern_(BossPattern::none)
	{

	}
public:
	float baseSpeed_; //���� �⺻�ӵ�
	float ResultSpeed_;
	float maxHp_;
	float hp_;
	float atk_;
	float giveExp_;
	BossPattern bossPattern_;
	MonsterType monsterType_;

};

class GameItemObjectManager;
class GameEngineRandom;
class Monster: public GameEngineActor
{
	static std::vector<Monster*> allMonsters_;

protected:
	static GameEngineInstanceRenderer* allMonstersRenderer_;	//��� ���� ������.
	static GameEngineInstanceRenderer* allShadowsRenderer_;	//��� ���� �׸��� ������.
	static GameItemObjectManager* dropMonsterItemObject_;
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

	static GameItemObjectManager* GetItemObjectManager()
	{
		return	dropMonsterItemObject_;
	}

	static std::vector<Monster*>& GetMonsterList()
	{
		return allMonsters_;
	}
	MonsterInfo& GetMonsterInfo()
	{
		return *monsterInfo_;
	}

	CollisionReturn MonsterToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn MonsterToPlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	//����Ǯ ������ ����.
	static void ReserveMonsters(GameEngineLevel* _thisLevel, size_t _allMonsterCount);

	//����� ���ʹ� Ǯ�� ����, ���.
	void Unsummon(); // ���� �߰��� ����� �뵵

	//��� ���� Ǯ�� ����.
	static void UnsummonAllMonsters();

	//���� ���� �� ���.
	static void CreateMonsterWithEnum(
		GameEngineLevel* _thisLevel,
		MonsterType _monsterType,
		size_t _monsterCount
	);

	//���� ���� �� ���.
	template <class MonsterClass>
	static void CreateMonster(GameEngineLevel* _thisLevel, size_t _monsterCount)
	{
		for (size_t i = 0; i < _monsterCount; ++i)
		{
			Monster* newMonster = _thisLevel->CreateActor<MonsterClass>(ObjectOrder::Monster);
			newMonster->isSummoned_ = false;
			newMonster->GetTransform().SetWorldPosition(float4::Zero);
			newMonster->Off();

			newMonster->monsterTextureName_ = &typeid(MonsterClass).name()[6];
			newMonster->monsterTextureName_ += ".png";
			newMonster->instancingUnitIndex_ = monsterCreationIndex_++;

			allMonstersRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).SetColorTextureIndex(
				GameEngineTexture2DArray::Find("Monster")->GetIndex(newMonster->monsterTextureName_)
			);
			allMonstersRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).SetWorldScale(
				/*newMonster->monsterScale_*/
				float4::Zero
			);

			allShadowsRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).SetColorTextureIndex(
				GameEngineTexture2DArray::Find("Monster")->GetIndex(newMonster->monsterTextureName_)
			);
			allShadowsRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).SetWorldScale(
				/*newMonster->monsterScale_*/
				float4::Zero
			);
			allShadowsRenderer_->GetInstancingUnit(newMonster->instancingUnitIndex_).Link(
				"Inst_RenderOption", newMonster->renderOption_
			);
			allMonsters_.push_back(newMonster);
		}
	}


	//������ ���� ��ġ.
	template <typename MonsterClass>
	static void SummonMonster(GameEngineLevel* _thisLevel, size_t _summonCount)
	{
		size_t count = _summonCount;
		for (size_t i = 0; i < allMonsters_.size(); ++i)
		{
			if (nullptr == dynamic_cast<MonsterClass*>(allMonsters_[i]))
			{
				//���ϴ� Ÿ�� ���Ͱ� �ƴ϶�� ����.
				continue;
			}

			if (true == allMonsters_[i]->isSummoned_)
			{
				//�̹� ��ȯ�� ���Ͷ�� ����.
				continue;
			}

			float cameraX = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().x;
			float cameraY = _thisLevel->GetMainCameraActor()->GetTransform().GetWorldPosition().y;
			float4 monsterPosition_ = GameEngineRandom::mainRandom_.RandomFloat4(
				float4(cameraX - 1280, cameraY - 720),
				float4(cameraX + 1280, cameraY + 720)
			);
			monsterPosition_.z = -199.f;

			if (monsterPosition_.x > cameraX + 640 || monsterPosition_.x < cameraX - 640)
			{
				allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition_);

				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
					allMonsters_[i]->monsterScale_
				);
				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
					monsterPosition_
				);

				allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
					allMonsters_[i]->monsterScale_
				);
				allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
					monsterPosition_.x,
					monsterPosition_.y,
					monsterPosition_.z + 2.f
				);
	
				allMonsters_[i]->On();
				allMonsters_[i]->isSummoned_ = true;
				//allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).Link(
				//	"Inst_RenderOption", allMonsters_[i]->renderOption_
				//);
			}
			else if (monsterPosition_.y > cameraY + 360 || monsterPosition_.y < cameraY - 360)
			{
				allMonsters_[i]->GetTransform().SetWorldPosition(monsterPosition_);

				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
					allMonsters_[i]->monsterScale_
				);
				allMonstersRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
					monsterPosition_
				);

				allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldScale(
					allMonsters_[i]->monsterScale_
				);
				allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).SetWorldPosition(
					monsterPosition_.x,
					monsterPosition_.y,
					monsterPosition_.z + 2.f
				);

				allMonsters_[i]->On();
				allMonsters_[i]->isSummoned_ = true;
				//allShadowsRenderer_->GetInstancingUnit(allMonsters_[i]->instancingUnitIndex_).Link(
				//	"Inst_RenderOption", allMonsters_[i]->renderOption_
				//);
			}
			else
			{
				i--;
				++count;
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

	void FlashMonster(float _deltaTime);

	void RelocationMonster();


public:
	float mxMove_;
	float myMove_;
	bool isTarget_;
	bool flash_;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Chaseplayer(float _deltaTime);
	void HpCheak();
	void ReduceHP();
protected:
	bool flashLoop_;
	float flashTimer_;
	float4 flashPixel_;

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

	GameEngineCollision* monCollision_;
	MonsterInfo* monsterInfo_;

	int instancingUnitIndex_;	//�� ���͸� ����ؼ� �׸��� �ִ� �ν��Ͻ������� ��ȣ.

	float4 monsterScale_;		//�� ���� ������ ũ��.

	GameEngineAnimation monsterAnimation_;	//�ð� ���������� �ε����� �ٲ��ִ� �ִϸ��̼� ���.
	//������ ����� �״��� �������� �ʰ�, ������ ���͸��� �ݵ�� �Ѱ��� ������ �ϹǷ� �������� ����.

	RenderOption renderOption_;
	PixelData pixelData_;

	GameEngineTextureRenderer* monsterHpMax_;
	GameEngineTextureRenderer* monsterHp_;
	GameEngineFontRenderer* monsterHpScore_;

private:
	std::string monsterTextureName_;	//���� �ڱ� �ڽ��� �ؽ�ó �̸�. 
	//Ŭ���� �̸��� �����ϴٴ� ������ ����ǰ� ��.

	bool isSummoned_;	//true: ��ȯ�Ǽ� �ʵ忡�� Ȱ���ϰ� ����.

	bool isToRight_;	//true: ���Ͱ� ������ ���� ����.

};