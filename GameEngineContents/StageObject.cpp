#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "StageObject.h"

StageInfo StageObject::nextStageInfo_;

StageObject::StageObject() 
	: posY_(0.f),
	myLevel_(0),
	time_(0.0f),
	killCount_(0),
	stageType_(StageType::Max),
	combatType_(CombatType::Max),
	renderer_(nullptr),
	totalMonsterCount_(0)
{
	magic_enum::enum_for_each<MonsterType>(
		[this](MonsterType _monsterType)->void
		{
			this->summoningMonsterCountMap_.insert(std::make_pair(_monsterType, 0));
		}
	);
}

StageObject::~StageObject() 
{
}

void StageObject::Start()
{
	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->SetTexture("Combat.png");
	renderer_->ScaleToTexture();
	renderer_->SetPivot(PivotMode::Bot);
}

void StageObject::Update(float _deltaTime)
{
}

void StageObject::SetStageType(int _num)
{
	switch (_num)
	{
	case 0:
		stageType_ = StageType::Combat;
		combatType_ = CombatType::Kill;
		renderer_->SetTexture("Combat.png");
		break;
	case 1:
		stageType_ = StageType::Chest;
		combatType_ = CombatType::Max;
		renderer_->SetTexture("Chest.png");
		break;
	case 2:
		stageType_ = StageType::Elite;
		combatType_ = CombatType::EilteKill;
		renderer_->SetTexture("Elite.png");
		break;
	case 3:
		stageType_ = StageType::Shop;
		combatType_ = CombatType::Max;
		renderer_->SetTexture("Shop.png");
		break;
	case 4:
		stageType_ = StageType::Boss;
		combatType_ = CombatType::BossKill;
		renderer_->SetTexture("Boss.png");
		break;
	case 5:
		stageType_ = StageType::Swarm;
		combatType_ = CombatType::TimeAttack;
		renderer_->SetTexture("swarm.png");
		break;
	case 6:
		stageType_ = StageType::Empty;
		combatType_ = CombatType::Max;
		renderer_->SetTexture("Empty.png");
		break;

	default:
		MsgBoxAssert("�߸��� �������� Ÿ���Դϴ�.");
		break;
	}

	renderer_->ScaleToTexture();
}



void StageObject::SetMonsterCount(MonsterType _monsterType, size_t _monsterCount)
{
	if (CombatType::Max == this->combatType_)
	{
		MsgBoxAssert("������ ���������Դϴ�.");
		return;
	}

	if (true == summoningMonsterCountMap_.contains(_monsterType))
	{
		totalMonsterCount_ -= summoningMonsterCountMap_[_monsterType];
		//�̹� ���� ��ȯ ���ڸ� �����ߴµ� �ٽ� �����ϴ� ��츦 ����ؼ� totalMonsterCount_���� �������� ����.

		summoningMonsterCountMap_[_monsterType] = _monsterCount;
		//�� �� ����.

		totalMonsterCount_ += summoningMonsterCountMap_[_monsterType];
		//��ü ���� ���� �ջ�.
	}
	else
	{
		MsgBoxAssert("�غ���� ���� ���� Ÿ���Դϴ�.");
		return;
	}
}

void StageObject::PushNextlevel(std::shared_ptr<StageObject> _nextlevel)
{
	nextLevels_.push_back(_nextlevel);
}

bool StageObject::CheckNextLevel(std::shared_ptr<StageObject> _nextlevel)
{
	if (nextLevels_.end() != std::find(nextLevels_.begin(), nextLevels_.end(), _nextlevel))
	{
		return true;
	}
	else
	{
		return false;
	}
}