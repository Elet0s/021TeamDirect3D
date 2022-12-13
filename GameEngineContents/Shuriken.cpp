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
	monsterList_()
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
		shuriKenWeaponInfo_.weaponThrowingSpeed_ = 1.0f;
		shuriKenWeaponInfo_.weaponSpeed_ = 100;

		shuriKenWeaponInfo_.weaponknockback_ = 100;

		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 2;
		shuriKenWeaponInfo_.weaponProjectileNum_ = 2;

}
	else if (nowLevel_ < 3)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 1.58f;
		shuriKenWeaponInfo_.weaponProjectileNum_ = 3;
		shuriKenWeaponInfo_.weaponThrowingSpeed_ = 0.6f;
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

	Off();

}

void Shuriken::RangeCheak(float _deltaTime)
{

		//shuriKenCol_->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
		shuriKenRenderer_->GetTransform().SetWorldMove(referenceVector_.Normalize3D() * _deltaTime * 100.f);
		shuriKenCol_->GetTransform().SetWorldMove(referenceVector_.Normalize3D() * _deltaTime * 100.f);

}
void Shuriken::Update(float _deltaTime)
{
	StateSet();
	renderRotate(_deltaTime);
	RangeCheak(_deltaTime);
	//shuriKenCol_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

}
void Shuriken::End()
{

}
void Shuriken::renderRotate(float _deltaTime)
{
	//ü���� �� ���� ��� ���� ����� �༮�� �����ϴ� ���
	monsterList_ = Monster::GetMonsterList();


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
		if (minHpPair_.second > 0)
		{
			float Mx = monsterList_[minHpPair_.first]->GetTransform().GetWorldPosition().x;
			float My = monsterList_[minHpPair_.first]->GetTransform().GetWorldPosition().y;
			float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
			float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//���� �Ű��� ��ġ�� ������
			referenceVector_.x = (Mx - Px); //���� ���ϴ� ����
			referenceVector_.y = (My - Py);
			float Cos = atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree;
			shuriKenRenderer_->GetTransform().SetWorldRotation(-Cos);
			//float A = acos(Cos);
		}

}

CollisionReturn Shuriken::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) // �߻�ü �ε�����
{
	
	//TargetMonsters_.push_back(dynamic_pointer_cast<Monster>(_Other->GetActor()));

	//���⼭ ������ �����������
	_Other->GetActor()->Off();
	//off�� ���� ��Ȱ �����ִ� �ڷᱸ���� �־��ִ� �κ� �ʿ��� �ڷᱸ���� ��� ������Ʈ ���鼭 ���� �ֵ� ��ġ��������
	return CollisionReturn::Stop;
}