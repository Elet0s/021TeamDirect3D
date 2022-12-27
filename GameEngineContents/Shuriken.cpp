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
	firstSort(false),
	firstCheak_(false),
	timeer_(),
	test_(false)
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
	valueSoulCard_ = SoulCard::Shuriken;

	//shuriKenRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//shuriKenRenderer_->GetTransform().SetWorldScale(50, 80, 0);
	//shuriKenRenderer_->SetTexture("Arrow.png");
	//
	//shuriKenCol_ = CreateComponent<GameEngineCollision>();
	//shuriKenCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
	//shuriKenCol_->GetTransform().SetLocalScale({ 35.0f, 35.0f, 1.0f });
	//shuriKenCol_->ChangeOrder(ObjectOrder::Projectile);
	//
	//shuriKenRangeCol_ = CreateComponent<GameEngineCollision>();
	//shuriKenRangeCol_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::White);
	//shuriKenRangeCol_->GetTransform().SetLocalScale({ 350.0f, 350.0f, 1.0f });
	//shuriKenRangeCol_->ChangeOrder(ObjectOrder::Range);


	Off();
}


void Shuriken::Update(float _deltaTime)
{
	StateSet();

	SerchTarget();
	ProjectileSort(_deltaTime);
	RenderRotate();

	RangeCheak(_deltaTime);
	ColCheak();
	TarGetInitialization();
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

void Shuriken::SerchTarget()
{
	monsterList_ = Monster::GetMonsterList();
	shuriKenWeaponInfo_.weaponProjectileNum_;//�̰�����ŭ �̾ƾ���
	if (Shooting == false)
	{
		for (size_t n = 0; n < shuriKenWeaponInfo_.weaponProjectileNum_; n++)//�ѹ��� ������ ����ü ������ŭ �ݺ��Ұ���
		{
			for (size_t i = 0; i < monsterList_.size(); i++)
			{
				if (monsterList_[i]->IsSummoned() == true && monsterList_[i]->isTarget_ == false)
				{

					if (monsterList_[i]->GetMonsterInfo().hp_ > 0 && firstCheak_ == false)//hp0�̻�, ù��° �����ϰ��
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
						firstCheak_ = true;
					}
					else if (minHpPair_.second > monsterList_[i]->GetMonsterInfo().hp_)//����˻����� ���� ü���� �� ���ٸ�
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
					}
					if (i == monsterList_.size() - 1)
					{
						targetInst_.push_back(minHpPair_);//Ÿ�ٸ���Ʈ�� �߰�
						monsterList_[minHpPair_.first]->isTarget_ = true;
						firstCheak_ = false;
						//monsterList_.erase(monsterList_.begin() + minHpPair_.first); //���� ����Ʈ���� ����
					}

				}
			
			}

		}
	}
	else if (timeer_ > 3.f)
	{
		Shooting = false;
		targetInst_.clear();

		for (size_t n = 0; n < shuriKenWeaponInfo_.weaponProjectileNum_; n++)//�ѹ��� ������ ����ü ������ŭ �ݺ��Ұ���
		{
			for (size_t i = 0; i < monsterList_.size(); i++)
			{
				if (monsterList_[i]->IsSummoned() == true && monsterList_[i]->isTarget_ == false)
				{

					if (monsterList_[i]->GetMonsterInfo().hp_ > 0 && firstCheak_ == false)//hp0�̻�, ù��° �����ϰ��
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
						firstCheak_ = true;
					}
					else if (minHpPair_.second > monsterList_[i]->GetMonsterInfo().hp_)//����˻����� ���� ü���� �� ���ٸ�
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
					}
					if (i == monsterList_.size() - 1)
					{
						targetInst_.push_back(minHpPair_);//Ÿ�ٸ���Ʈ�� �߰�
						monsterList_[minHpPair_.first]->isTarget_ = true;
						firstCheak_ = false;
					}

				}

			}

		}
	}

}

void Shuriken::ProjectileSort(float _deltaTime)
{
	if (firstSort == false) //ó���̸� �����
	{
		projectileGroupList_.reserve(30);
		for (size_t i = 0; i < shuriKenWeaponInfo_.weaponProjectileNum_; i++)
		{
			projectileGroup_.first = CreateComponent<GameEngineTextureRenderer>();
			projectileGroup_.first->GetTransform().SetWorldScale(20, 20, 0);
			projectileGroup_.first->SetTexture("Shuriken.png");

			projectileGroup_.second = CreateComponent<GameEngineCollision>();
			projectileGroup_.second->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
			projectileGroup_.second->GetTransform().SetWorldScale(20, 20, 0);
			projectileGroup_.second->ChangeOrder(ObjectOrder::Projectile);


			projectileGroup_.first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -100)));
			projectileGroup_.second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());

			projectileGroupList_.push_back(projectileGroup_);

		}
		firstSort = true;
	}
	else if(timeer_ > 3.f)//�ƴϸ� �ִ°ɷ� ����
	{
		timeer_ = 0.f;

		for (size_t i = 0; i < shuriKenWeaponInfo_.weaponProjectileNum_; i++)
		{
		projectileGroupList_[i].first->On();
		projectileGroupList_[i].second->On();
		projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -100)));
		projectileGroupList_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
		}

	}
}

void Shuriken::RenderRotate()
{
	monsterList_ = Monster::GetMonsterList();
	//ü���� �� ���� ��� ���� ����� �༮�� �����ϴ� ���
	if (Shooting == false)
	{
		for (size_t i = 0; i < shuriKenWeaponInfo_.weaponProjectileNum_; i++)  
		{
				float Mx = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().x;
				float My = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().y;
				float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
				float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//���� �Ű��� ��ġ�� ������
				referenceVector_.x = (Mx - Px); //���� ���ϴ� ����
				referenceVector_.y = (My - Py);
				referenceVector_.w = 0;
				referenceVectorList_.push_back(referenceVector_);

				projectileGroupList_[i].first->GetTransform().SetWorldRotation(0, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
				projectileGroupList_[i].first->GetTransform().SetWorldRotation(60, 0, 0);	
		}
		Shooting = true;
	}
}

void Shuriken::RangeCheak(float _deltaTime)
{
	if (timeer_ <= 3.0f)
	{
		if (test_ == false)
		{
			timeer_ += _deltaTime;
			for (size_t i = 0; i < projectileGroupList_.size(); i++)
			{
				projectileGroupList_[i].first->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList_[i].second->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
			}
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
	
	//TargetMonsters_.push_back();

	//���⼭ ������ �����������
	for (size_t i = 0; i < projectileGroupList_.size(); i++)
	{
		if (projectileGroupList_[i].second == _This)
		{
			projectileGroupList_[i].first->Off();
			projectileGroupList_[i].second->Off();
		}
	}
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= shuriKenWeaponInfo_.weaponAtk_;
	//off�� ���� ��Ȱ �����ִ� �ڷᱸ���� �־��ִ� �κ� �ʿ��� �ڷᱸ���� ��� ������Ʈ ���鼭 ���� �ֵ� ��ġ��������
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