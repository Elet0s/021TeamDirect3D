#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
//#include <memory>

DeathAura::DeathAura() 
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
{
	
}

DeathAura::~DeathAura() 
{
}



void DeathAura::Init()
{
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(damege * PlayerInfo_->atk_).substr(0, std::to_string(damege * PlayerInfo_->atk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).substr(0, std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).find(".") + 3);
	std::string sRange = std::to_string(rangeSize * PlayerInfo_->atk_Range_).substr(0, std::to_string(rangeSize * PlayerInfo_->atk_Range_).find(".") + 3);
	
	etc_ = "범위 내의 근처 적에게 지속\n피해를 입힙니다\n치명타가 발생하지 않습니다\n" + sDamege + " 의 피해\n" + sAttackSpeed + "초 마다 공격\n범위 "
		+ sRange + "m ";
}

void DeathAura::Effect()
{
	currentlevel_ += 1;
	if(currentlevel_ >= 5)
	{
		damege += 0.75f;
		rangeSize += 0.25f;
	}

	else if (currentlevel_ % 2 == 0)
	{
		damege += 0.38f;
		rangeSize += 0.5f;
	}

	else if (currentlevel_ % 2 == 1)
	{
		damege += 0.37f;
		rangeSize += 0.5f;
	}
}


void DeathAura::Start()
{
	 circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererA_->SetTexture("Death_Circle_A.png");
	 circleRendererA_->GetTransform().SetWorldScale(500,250,0);

	 circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererB_->SetTexture("Death_Circle_B.png");
	 circleRendererB_->GetTransform().SetWorldScale(500, 250, 0);

	 circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererC_->SetTexture("Death_Circle_C.png");
	 circleRendererC_->GetTransform().SetWorldScale(500, 250, 0);

	 circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererD_->SetTexture("Death_Circle_D.png");
	 circleRendererD_->GetTransform().SetWorldScale(500, 250, 0);

	 circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	 circleCenterRenderer_->SetTexture("Death_Circle_Center.png");
	 circleCenterRenderer_->GetTransform().SetWorldScale(500, 250, 0);
	 Off();
}
void DeathAura::Update(float _deltaTime)
{
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y-40, -80);
}
void DeathAura::End()
{

}

CollisionReturn DeathAura::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // 발사체 부딪히면
{

	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//여기서 데미지 갱신해줘야함
	_Other->GetActor()->Off();
	//off한 몬스터 부활 시켜주는 자료구조에 넣어주는 부분 필요함 자료구조는 계속 업데이트 돌면서 죽은 애들 위치갱신해줌
	return CollisionReturn::Stop;
}