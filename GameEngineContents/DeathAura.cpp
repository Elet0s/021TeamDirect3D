#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
//#include <memory>

DeathAura::DeathAura() 
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
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
	 circleRendererA_->GetTransform().SetWorldScale(515,515,0);
	 circleRendererA_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	 circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererB_->SetTexture("Death_Circle_B.png");
	 circleRendererB_->GetTransform().SetWorldScale(500, 500,0);
	 circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	 circleRendererB_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	 circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererC_->SetTexture("Death_Circle_C.png");
	 circleRendererC_->GetTransform().SetWorldScale(475, 475, 0);
	 circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	 circleRendererC_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	 circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	 circleRendererD_->SetTexture("Death_Circle_D.png");
	 circleRendererD_->GetTransform().SetWorldScale(475, 475, 0);
	 circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	 circleRendererD_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	 circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	 circleCenterRenderer_->SetTexture("Death_Circle_Center.png");
	 circleCenterRenderer_->GetTransform().SetWorldScale(475, 475, 0);
	 circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	 circleCenterRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.7f);

	 Off();
}
void DeathAura::Update(float _deltaTime)
{
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y-40, 0);
	RotateRenderer(_deltaTime);
}
void DeathAura::RotateRenderer(float _deltaTime)
{
	
	if (addRadian_ <360)
	{
		addRadian_ += 10*_deltaTime;
	}
	else
	{
		addRadian_ = 0;
	}

	circleRendererA_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererB_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleRendererC_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	circleRendererD_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	circleCenterRenderer_->GetTransform().SetWorldRotation(60, 0, addRadian_);
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