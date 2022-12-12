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
	
	etc_ = "���� ���� ��ó ������ ����\n���ظ� �����ϴ�\nġ��Ÿ�� �߻����� �ʽ��ϴ�\n" + sDamege + " �� ����\n" + sAttackSpeed + "�� ���� ����\n���� "
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

CollisionReturn DeathAura::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // �߻�ü �ε�����
{

	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//���⼭ ������ �����������
	_Other->GetActor()->Off();
	//off�� ���� ��Ȱ �����ִ� �ڷᱸ���� �־��ִ� �κ� �ʿ��� �ڷᱸ���� ��� ������Ʈ ���鼭 ���� �ֵ� ��ġ��������
	return CollisionReturn::Stop;
}