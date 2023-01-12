#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
#include "Monster.h"

DeathAura::DeathAura()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
	, addRadian_(0)
	, atkTimer_(0)
{
	name_ = "������ ����";
	SetName(std::string_view("DeathAura"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}

DeathAura::~DeathAura()
{
}



void DeathAura::Init()
{
	std::string sDamege = std::to_string(deathAuraWeaponInfo_.weaponAtk_ ).substr(0, std::to_string(deathAuraWeaponInfo_.weaponAtk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(deathAuraWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(deathAuraWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sRange = std::to_string(deathAuraWeaponInfo_.weaponSize_).substr(0, std::to_string(deathAuraWeaponInfo_.weaponSize_).find(".") + 3);

	etc_ = "���� ���� ��ó ������ ����\n���ظ� �����ϴ�\nġ��Ÿ�� �߻����� �ʽ��ϴ�\n" + sDamege + " �� ����\n" + sAttackSpeed + "�� ���� ����\n���� "
		+ sRange + "m ";
}

void DeathAura::Effect()
{
	currentlevel_ += 1;
}

void  DeathAura::StateSet()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	deathAuraWeaponInfo_.weaponAtk_ = 4.f + (1.f * currentlevel_) * (PlayerInfo_.atk_ * PlayerPInfo_.atkMultiple_Result / 100.f);
	deathAuraWeaponInfo_.weaponAtkSpeed_ = 0.3f * (PlayerInfo_.attackSpeed_ / 100 * PlayerPInfo_.attackSpeed_Result / 100.f);//1�ʸ���

	deathAuraWeaponInfo_.weaponPassAtk_ = 0;
	deathAuraWeaponInfo_.weaponPassNum_ = 2;

	deathAuraWeaponInfo_.weaponSize_ = 100 + (50 * currentlevel_) * (PlayerInfo_.atk_Range_/ 100);
	deathAuraWeaponInfo_.weaponDuration_ = 100;
	deathAuraWeaponInfo_.weaponSpeed_ = 100;


}
void DeathAura::Start()
{
	circleRendererA_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererA_->SetTexture("Death_Circle_A.png");
	circleRendererA_->GetTransform().SetWorldScale(103.f, 103.f, 0);
	circleRendererA_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererA_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererA_->Off();

	circleRendererB_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererB_->SetTexture("Death_Circle_B.png");
	circleRendererB_->GetTransform().SetWorldScale(100.f, 100.f, 0);
	circleRendererB_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	circleRendererB_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererB_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererB_->Off();

	circleRendererC_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererC_->SetTexture("Death_Circle_C.png");
	circleRendererC_->GetTransform().SetWorldScale(95.f, 95.f, 0);
	circleRendererC_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	circleRendererC_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererC_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererC_->Off();

	circleRendererD_ = CreateComponent<GameEngineTextureRenderer>();
	circleRendererD_->SetTexture("Death_Circle_D.png");
	circleRendererD_->GetTransform().SetWorldScale(95.f, 95.f, 0);
	circleRendererD_->GetTransform().SetWorldPosition(0.f, 0.f, -3.f);
	circleRendererD_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleRendererD_->ChangeCamera(CameraOrder::MidCamera);
	circleRendererD_->Off();

	circleCenterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	circleCenterRenderer_->SetTexture("Death_Circle_Center.png");
	circleCenterRenderer_->GetTransform().SetWorldScale(95.f, 95.f, 0);
	circleCenterRenderer_->GetTransform().SetWorldPosition(0.f, 0.f, -4.f);
	circleCenterRenderer_->GetPixelData().mulColor_ = float4(0.0f, 1.5f, 0.0f, 0.5f);
	circleCenterRenderer_->ChangeCamera(CameraOrder::MidCamera);
	circleCenterRenderer_->Off();

	deathAuraCollision01_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision01_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision01_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision01_->GetTransform().SetWorldScale(46.f, 46.f, 0);

	deathAuraCollision02_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision02_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision02_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision02_->GetTransform().SetWorldScale(40.f, 40.f, 0);

	deathAuraCollision03_ = CreateComponent<GameEngineCollision>();
	deathAuraCollision03_->SetDebugSetting(CollisionType::CT_Sphere, float4::Blue);
	deathAuraCollision03_->ChangeOrder(ObjectOrder::Projectile);
	deathAuraCollision03_->GetTransform().SetWorldScale(40.f, 40.f, 0);

	Off();
}
void DeathAura::Update(float _deltaTime)
{
	StateSet();
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y - 40, 0);
	RotateRenderer(_deltaTime);
	GetTransform().SetWorldScale({ deathAuraWeaponInfo_.weaponSize_ });
	deathAuraCollision02_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x + 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	deathAuraCollision03_->GetTransform().SetWorldPosition(deathAuraCollision01_->GetTransform().GetWorldPosition().x - 100.f, deathAuraCollision01_->GetTransform().GetWorldPosition().y, 0.f);
	atkTimer_ += _deltaTime;

	if (atkTimer_ > deathAuraWeaponInfo_.weaponAtkSpeed_)
	{
		if (deathAuraCollision01_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{
			atkTimer_ = 0;
			deathAuraCollision01_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
		else	 if (deathAuraCollision02_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{

			deathAuraCollision02_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
		else if (deathAuraCollision03_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
		{
			deathAuraCollision03_->IsCollision(
				CollisionType::CT_Sphere2D,
				ObjectOrder::Monster,
				CollisionType::CT_Sphere2D,
				std::bind(
					&DeathAura::DeatAuraToMonsterCollision,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			);
		}
	}
}
void DeathAura::RotateRenderer(float _deltaTime)
{

	if (addRadian_ < 360)
	{
		addRadian_ += 10 * _deltaTime;
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
	if (circleRendererA_->IsUpdate() == false)
	{
		circleRendererA_->On();
		circleRendererB_->On();
		circleRendererC_->On();
		circleRendererD_->On();
		circleCenterRenderer_->On();
	}
}
void DeathAura::End()
{

}

CollisionReturn DeathAura::DeatAuraToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // �߻�ü �ε�����
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= deathAuraWeaponInfo_.weaponAtk_; //��������
	return CollisionReturn::Continue;
}