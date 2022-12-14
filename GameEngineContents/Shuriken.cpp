#include"PreCompile.h"
#include"Shuriken.h"
#include"Player.h"
#include"Monster.h"

Shuriken::Shuriken()
	: referenceVector_(),
	shuriKenRenderer_(),
	shuriKenCol_(),
	shuriKenWeaponInfo_(),
	minHpPair_(),
	monsterList_(),
	resultCos_()
{

}
Shuriken::~Shuriken()
{


}
void  Shuriken::StateSet()
{
	if (nowLevel_ < 2)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 1.13f;
		shuriKenWeaponInfo_.weaponAtkSpeed_ = 100.f;//1�ʸ���

		shuriKenWeaponInfo_.weaponPassAtk_ = 0;
		shuriKenWeaponInfo_.weaponPassNum_ = 0;

		shuriKenWeaponInfo_.weaponSize_ = 100;
		shuriKenWeaponInfo_.weaponDuration_ = 100;
		shuriKenWeaponInfo_.weaponSpeed_ = 100;

		shuriKenWeaponInfo_.weaponknockback_ = 100;

		shuriKenWeaponInfo_.weaponProjectileNum_ = 2;
		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 2;

}
	else if (nowLevel_ < 3)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 1.58f;
		shuriKenWeaponInfo_.weaponAtkSpeed_ = 100.f;//1�ʸ���
		shuriKenWeaponInfo_.weaponProjectileNum_ = 3;
		shuriKenWeaponInfo_.weaponSpeed_ = 100;

	}
	else if (nowLevel_ < 4)
	{

	}
	else if (nowLevel_ < 5)
	{

	}
	else if (nowLevel_ < 6)
	{

	}
}

void Shuriken::Start()
{
	valueSoulCard_ = SoulCard::Shuriken;
	GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
	shuriKenRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	shuriKenRenderer_->GetTransform().SetWorldScale(50, 80, 0);
	shuriKenRenderer_->SetTexture("Arrow.png");

	shuriKenCol_ = CreateComponent<GameEngineCollision>();
	shuriKenCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	shuriKenCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	shuriKenCol_->ChangeOrder(ObjectOrder::Projectile);

	shuriKenRangeCol_ = CreateComponent<GameEngineCollision>();
	shuriKenRangeCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::White);
	shuriKenRangeCol_->GetTransform().SetLocalScale({ 350.0f, 350.0f, 1.0f });
	shuriKenRangeCol_->ChangeOrder(ObjectOrder::Range);

	Off();
}

void Shuriken::RangeCheak(float _deltaTime)
{
	float4 A;
	float4 B;
	A = referenceVector_;
	B = A.Normalize3D() * _deltaTime * 100.f;
		shuriKenRenderer_->GetTransform().SetWorldMove(A.Normalize3D() * _deltaTime * 100.f);
		shuriKenCol_->GetTransform().SetWorldMove(A.Normalize3D() * _deltaTime * 100.f);
}
void Shuriken::Update(float _deltaTime)
{
	StateSet();
	SerchTarget();
	RenderRotate();
	RangeCheak(_deltaTime);
	shuriKenCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
}
void Shuriken::End()
{

}
void Shuriken::SerchTarget()
{
	monsterList_ = Monster::GetMonsterList();
	if (Shooting == false)
	{
		for (size_t i = 0; i < monsterList_.size(); i++)
		{
			if (monsterList_[i]->isSummoned_ == true)
			{
				if (monsterList_[i]->GetMonsterInfo().hp_ > 0 && i == 0)//hp0�̻�, ù��° �����ϰ��
				{
					minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
				}
				else if (minHpPair_.second > monsterList_[i]->GetMonsterInfo().hp_)//����˻����� ���� ü���� �� ������
				{
					minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
				}
			}
		}
	}
}
void Shuriken::RenderRotate()
{
	//ü���� �� ���� ��� ���� ����� �༮�� �����ϴ� ���
	if (Shooting == false)
	{


		if (minHpPair_.second > 0)
		{
			float Mx = monsterList_[minHpPair_.first]->GetTransform().GetWorldPosition().x;
			float My = monsterList_[minHpPair_.first]->GetTransform().GetWorldPosition().y;
			float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
			float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//���� �Ű��� ��ġ�� ������
			referenceVector_.x = (Mx - Px); //���� ���ϴ� ����
			referenceVector_.y = (My - Py);
			referenceVector_.w = 0;
			shuriKenRenderer_->GetTransform().SetWorldRotation(0, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			Shooting = true;
			//float A = acos(Cos);
		}
	}
}
CollisionReturn Shuriken::RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{

	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//���⼭ ������ �����������

	//off�� ���� ��Ȱ �����ִ� �ڷᱸ���� �־��ִ� �κ� �ʿ��� �ڷᱸ���� ��� ������Ʈ ���鼭 ���� �ֵ� ��ġ��������
	return CollisionReturn::Stop;
}

CollisionReturn Shuriken::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) 
{
	
	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//���⼭ ������ �����������
	_Other->GetActor()->Off();
	//off�� ���� ��Ȱ �����ִ� �ڷᱸ���� �־��ִ� �κ� �ʿ��� �ڷᱸ���� ��� ������Ʈ ���鼭 ���� �ֵ� ��ġ��������
	return CollisionReturn::Stop;
}