#include"PreCompile.h"
#include"Shuriken.h"
#include"Player.h"
#include"Monster.h"
Shuriken::Shuriken()
	: referenceVector_(),
	shuriKenWeaponInfo_(),
	minHpPair_(),
	monsterList_(),
	resultCos_(),
	firstSerchCheak_(false),
	targerSerchTimer01_(0),
	targerSerchTimer02_(0),
	targerSerchTimer03_(0),
	targetserchCounter_(0),
	shoothingPeojectile_(false),
	istarget_(false)
{

}
Shuriken::~Shuriken()
{


}

void Shuriken::Init()
{

}
void Shuriken::Effect()
{

}

void Shuriken::Start()
{
	projectileGroupList_.reserve(30);
	for (size_t i = 0; i < 30; i++) // ó������ �ִ밹�� ��� ���� ������ ���� �� 
	{
		projectileGroup_.first = CreateComponent<GameEngineTextureRenderer>();
		projectileGroup_.first->GetTransform().SetWorldScale(20, 20, 0);
		projectileGroup_.first->SetTexture("Shuriken.png");
		projectileGroup_.first->Off();

		projectileGroup_.second = CreateComponent<GameEngineCollision>();
		projectileGroup_.second->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
		projectileGroup_.second->GetTransform().SetWorldScale(20, 20, 0);
		projectileGroup_.second->ChangeOrder(ObjectOrder::Projectile);
		projectileGroup_.second->Off();

		projectileGroupList_.push_back(projectileGroup_);
	}


	valueSoulCard_ = SoulCard::Shuriken;
	Off();
}


void Shuriken::Update(float _deltaTime)
{
	StateSet();

	ConsecutiveAtk(3.f, _deltaTime);
	ConsecutiveAtk(3.f, _deltaTime);

	ColCheak();
	TarGetInitialization();
	TimerUpdater(_deltaTime);
}
void Shuriken::End()
{

}


void  Shuriken::StateSet()
{
	if (nowLevel_ < 2)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 10.13f;
		shuriKenWeaponInfo_.weaponAtkSpeed_ = 300.f;//1�ʸ���

		shuriKenWeaponInfo_.weaponPassAtk_ = 0;
		shuriKenWeaponInfo_.weaponPassNum_ = 0;

		shuriKenWeaponInfo_.weaponSize_ = 100;
		shuriKenWeaponInfo_.weaponDuration_ = 100;
		shuriKenWeaponInfo_.weaponSpeed_ = 100;

		shuriKenWeaponInfo_.weaponknockback_ = 100;

		shuriKenWeaponInfo_.weaponProjectileNum_ = 2;
		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 1;

	}
	else if (nowLevel_ < 3)
	{
		//shuriKenWeaponInfo_.weaponAtk_ = 1.58f;
		//shuriKenWeaponInfo_.weaponAtkSpeed_ = 100.f;//1�ʸ���
		//shuriKenWeaponInfo_.weaponProjectileNum_ = 3;
		//shuriKenWeaponInfo_.weaponSpeed_ = 100;

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
void Shuriken::ConsecutiveAtk(float timeSet_, float deltaTime_)
{
	SerchTarget();
	ProjectileSort();
	RenderRotate();
	RangeCheak(deltaTime_);

}
void Shuriken::SerchTarget()
{
	if (targerSerchTimer01_ > 3.f)
	{
		targetserchCounter_ = 0;
		monsterList_ = Monster::GetMonsterList();
		targetInst_.clear();
		for (size_t n = 0; n < shuriKenWeaponInfo_.weaponProjectileNum_; n++)//�ѹ��� ������ ����ü ������ŭ �ݺ��Ұ���
		{
			for (size_t i = 0; i < monsterList_.size(); i++)
			{
 				if (monsterList_[i]->IsSummoned() == true && monsterList_[i]->isTarget_ == false)
				{
					targetserchCounter_ += 1;
					if (monsterList_[i]->GetMonsterInfo().hp_ > 0 && firstSerchCheak_ == false)//hp0�̻�, ù��° �����ϰ��
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
						firstSerchCheak_ = true;
					}
					else if (minHpPair_.second > monsterList_[i]->GetMonsterInfo().hp_)//����˻����� ���� ü���� �� ���ٸ�
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
					}
				}
				if (i == monsterList_.size() - 1)
				{
					targetInst_.push_back(minHpPair_);//Ÿ�ٸ���Ʈ�� �߰�
					monsterList_[minHpPair_.first]->isTarget_ = true;
					firstSerchCheak_ = false;
					istarget_ = true;
				}
				 if (targetserchCounter_ == 0)
				{
					istarget_ = false;
				}
			}
		}
	}
}

void Shuriken::ProjectileSort()
{
	if (targerSerchTimer01_ > 3.f)
	{
		for (size_t i = 0; i < projectileGroupList_.size(); i++)
		{
			if (targetInst_.size() > i) // Ÿ�ټ���ŭ �ʿ�
			{
				projectileGroupList_[i].first->On();
				projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -100)));
				projectileGroupList_[i].second->On();
				projectileGroupList_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
			}
			else	 if (projectileGroupList_[i].first->IsUpdate() == true)
			{
				projectileGroupList_[i].first->Off();
				projectileGroupList_[i].second->Off();
			}
		}
	}
}

void Shuriken::RenderRotate()
{
	if (targerSerchTimer01_ > 3.f)
	{
		referenceVectorList_.clear();
		monsterList_ = Monster::GetMonsterList();

		for (size_t i = 0; i < targetInst_.size(); i++)
		{
			float Mx = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().x;
			float My = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().y;
			float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
			float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//���� �Ű��� ��ġ�� ������
			referenceVector_.x = (Mx - Px); //���� ���ϴ� ����
			referenceVector_.y = (My - Py);
			referenceVector_.w = 0;
			referenceVectorList_.push_back(referenceVector_);

			projectileGroupList_[i].first->GetTransform().SetWorldRotation(0, 0, 0);
			projectileGroupList_[i].first->GetTransform().SetWorldRotation(0, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			projectileGroupList_[i].first->GetTransform().SetWorldRotation(60, 0, 0);
		}
	}
}

void Shuriken::RangeCheak(float _deltaTime)
{
	if (targerSerchTimer01_ <= 3.0f)
	{
		if (istarget_ == true)
		{
			for (size_t i = 0; i < targetInst_.size(); i++)
			{
				projectileGroupList_[i].first->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList_[i].second->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
			}
		}
	}
}


CollisionReturn Shuriken::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other) 
{
	for (size_t i = 0; i < projectileGroupList_.size(); i++) 
	{
		if (projectileGroupList_[i].second == _This)//�߻�ü�� �ε��� �߻�ü ã�Ƽ� ����
		{
			projectileGroupList_[i].first->Off();
			projectileGroupList_[i].second->Off();
		}
	}
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= shuriKenWeaponInfo_.weaponAtk_; //��������
	return CollisionReturn::Stop;
}

void Shuriken::ColCheak()
{
	for (size_t i = 0; i < projectileGroupList_.size(); i++)
	{
		projectileGroupList_[i].second->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void Shuriken::TarGetInitialization()
{
	for (size_t i = 0; i < Monster::GetMonsterList().size() - 1; i++)
	{
		if (Monster::GetMonsterList()[i]->isTarget_ == true)
		{
			Monster::GetMonsterList()[i]->isTarget_ = false;
		}
	}
}

void Shuriken::TimerUpdater(float _deltaTime)
{
	if (targerSerchTimer01_ > 3.f)
	{
		targerSerchTimer01_ = 0;
	}
	else
	{
		targerSerchTimer01_ += _deltaTime;
	}

}
