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
	renderer_(nullptr)
{
}

StageObject::~StageObject() 
{
}

void StageObject::Start()
{
	//col_ = CreateComponent<GameEngineCollision>();
	//col_->GetTransform().SetWorldScale(float4(64.f, 64.f, 1.f));
	//col_->GetTransform().SetLocalPosition(float4(0.f, 32.f, 0.f));
	//col_->SetDebugSetting(CollisionType::CT_OBB, float4::Blue);
	//col_->ChangeOrder(ObjectOrder::MapObject);

	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->SetTexture("Combat.png");
	renderer_->ScaleToTexture();
	renderer_->SetPivot(PivotMode::Bot);
}

void StageObject::Update(float _deltaTime)
{
	//float4 PosK = GetTransform().GetWorldPosition();
	//PosK = GetLevel()->GetMainCamera()->ConvertWorldPositionToScreenPosition(PosK);
	//col_->GetTransform().SetWorldPosition(PosK);
}

void StageObject::SetStageType(int _num)
{
	switch (_num)
	{
	case 0:
		stageType_ = StageType::Combat;
		combatType_ = CombatType::Kill;
		renderer_->SetTexture("Combat.png");
		renderer_->ScaleToTexture();
		break;
	case 1:
		stageType_ = StageType::Chest;
		renderer_->SetTexture("Chest.png");
		renderer_->ScaleToTexture();
		break;
	case 2:
		stageType_ = StageType::Elite;
		combatType_ = CombatType::EilteKill;
		renderer_->SetTexture("Elite.png");
		renderer_->ScaleToTexture();
		break;
	case 3:
		stageType_ = StageType::Shop;
		renderer_->SetTexture("Shop.png");
		renderer_->ScaleToTexture();
		break;
	case 4:
		stageType_ = StageType::Boss;
		combatType_ = CombatType::BossKill;
		renderer_->SetTexture("Boss.png");
		renderer_->ScaleToTexture();
		break;
	case 5:
		stageType_ = StageType::Swarm;
		combatType_ = CombatType::TimeAttack;
		renderer_->SetTexture("swarm.png");
		renderer_->ScaleToTexture();
		break;
	case 6:
		stageType_ = StageType::Empty;
		renderer_->SetTexture("Empty.png");
		renderer_->ScaleToTexture();
		break;
	default:
		break;
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