#include "PreCompile.h"
#include "StageObject.h"

StageObject::StageObject() 
	: myLevel_(0),
	time_(0.0f),
	killCount_(0),
	stageType_(StageType::Max),
	comBatType_(ComBatType::Max),
	renderer_(nullptr)
{
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
		stageType_ = StageType::ComBat;
		break;
	case 1:
		stageType_ = StageType::Elite;
		break;
	case 2:
		stageType_ = StageType::Chest;
		break;
	case 3:
		stageType_ = StageType::Boss;
		break;
	case 4:
		stageType_ = StageType::Event;
		break;
	default:
		break;
	}
}

void StageObject::SetComBatType(int _num)
{
	switch (_num)
	{
	case 0:
		comBatType_ = ComBatType::TimeAttack;
		break;
	case 1:
		comBatType_ = ComBatType::Kill;
		break;
	case 2:
		comBatType_ = ComBatType::EilteKill;
		break;
	case 3:
		comBatType_ = ComBatType::BossKill;
		break;
	default:
		break;
	}
}

void StageObject::PushNextlevel(std::shared_ptr<StageObject> _nextlevel)
{
	nextLevels_.push_back(_nextlevel);
}