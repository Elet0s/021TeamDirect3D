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
	float baseSpeed_; //몬스터 기본속도
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
	static std::vector<std::shared_ptr<Monster>> allMonsters_;

protected:
	static std::shared_ptr<GameEngineInstancingRenderer> allMonstersRenderer_;	//모든 몬스터 렌더러.
	static std::shared_ptr<GameEngineInstancingRenderer> allShadowsRenderer_;	//모든 몬스터 그림자 렌더러.
	static std::shared_ptr<GameItemObjectManager> dropMonsterItemObject_;
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

	static std::shared_ptr<GameItemObjectManager> GetItemObjectManager()
	{
		return	dropMonsterItemObject_;
	}

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

	//몬스터풀 사이즈 예약.
	static void ReserveMonsters(GameEngineLevel* _thisLevel, size_t _allMonsterCount);

	//사망한 몬스터는 풀로 복귀, 대기.
	void Unsummon(); // 게임 중간에 지우는 용도

	//모든 몬스터 풀로 복귀.
	static void UnsummonAllMonsters();

	//몬스터 생성 및 대기.
	static void CreateMonsterWithEnum(
		GameEngineLevel* _thisLevel,
		MonsterType _monsterType,
		size_t _monsterCount
	);

	//몬스터 생성 및 대기.
	template <class MonsterClass>
	static void CreateMonster(GameEngineLevel* _thisLevel, size_t _monsterCount)
	{
		for (size_t i = 0; i < _monsterCount; ++i)
		{
			std::shared_ptr<Monster> newMonster = _thisLevel->CreateActor<MonsterClass>(ObjectOrder::Monster);
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


	//레벨에 몬스터 배치.
	template <typename MonsterClass>
	static void SummonMonster(GameEngineLevel* _thisLevel, size_t _summonCount)
	{
		size_t count = _summonCount;
		for (size_t i = 0; i < allMonsters_.size(); ++i)
		{
			if (nullptr == std::dynamic_pointer_cast<MonsterClass>(allMonsters_[i]))
			{
				//원하는 타입 몬스터가 아니라면 무시.
				continue;
			}

			if (true == allMonsters_[i]->isSummoned_)
			{
				//이미 소환된 몬스터라면 무시.
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

			--count;//소환 대기중인 몬스터라면 소환하고 카운트 감소.
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

	float mx_;//자신의 좌표
	float my_;
	float px_;
	float py_;

	float playerRange_; // 플레이어와의 거리
	float atkDeltaTime_;

	float4 pushToMonsterVector;

	float4 pushVector_;
	float4 reactionVector_;
	float4 range_; // 몬스터에서 플레이어까지의 벡터
	float4 monsterBaseVector_;//충돌값적용안된 가장 기본적인 몬스터 벡터
	float4 monsterResultVector_;// 최종 무브벡터
	float4 playerReactionVector_;// 플레이어 반작용벡터
	float4 monsterReactionVector_;// 몬스터 반작용벡터

	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr <MonsterInfo> monsterInfo_;

	int instancingUnitIndex_;	//이 몬스터를 담당해서 그리고 있는 인스턴싱유닛의 번호.

	float4 monsterScale_;		//각 몬스터 종류별 크기.

	GameEngineAnimation monsterAnimation_;	//시간 지날때마다 인덱스만 바꿔주는 애니메이션 모듈.
	//구조와 기능이 그다지 복잡하지 않고, 각각의 몬스터마다 반드시 한개씩 가져야 하므로 값형으로 저장.

	RenderOption renderOption_;
	PixelData pixelData_;

	std::shared_ptr<GameEngineTextureRenderer> monsterHpMax_;
	std::shared_ptr<GameEngineTextureRenderer> monsterHp_;
	std::shared_ptr<GameEngineFontRenderer>monsterHpScore_;

private:
	std::string monsterTextureName_;	//몬스터 자기 자신의 텍스처 이름. 
	//클래스 이름과 동일하다는 전제로 저장되게 함.

	bool isSummoned_;	//true: 소환되서 필드에서 활동하고 있음.

};