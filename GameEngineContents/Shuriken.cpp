#include"PreCompile.h"
#include"Shuriken.h"
#include"Player.h"
#include"Monster.h"
Shuriken::Shuriken()
	:projectileGroup_(),
	projectileGroupList01_(),
	projectileGroupList02_(),
	projectileGroupList03_(),
	firstSerchCheak_(false),
	istarget_(false),
	targerSerchTimer_(0),
	targerSerchTimer01_(0),
	targerSerchTimer02_(0),
	targerSerchTimer03_(0),
	targetSerchCounter_(0),
	passNum_(),
	resultCos_(),
	referenceVector_(),
	shuriKenWeaponInfo_(),
	monsterList_(),
	minHpPair_(),
	targetInst01_(),
	targetInst02_(),
	targetInst03_(),
	referenceVectorList01_(),
	referenceVectorList02_(),
	referenceVectorList03_()
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
	projectileGroupList01_.reserve(10);
	projectileGroupList02_.reserve(10);
	projectileGroupList03_.reserve(10);
	passNum_.reserve(30);
	for (size_t i = 0; i < 30; i++) // 처음부터 최대갯수 모두 만들어서 가지고 있을 것 
	{
		passNum_.push_back(0);

		projectileGroup_.first = CreateComponent<GameEngineTextureRenderer>();
		projectileGroup_.first->GetTransform().SetWorldScale(30, 30, 0);
		projectileGroup_.first->SetTexture("Shuriken.png");
		projectileGroup_.first->Off();

		projectileGroup_.second = CreateComponent<GameEngineCollision>();
		projectileGroup_.second->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
		projectileGroup_.second->GetTransform().SetWorldScale(30, 30, 0);
		projectileGroup_.second->ChangeOrder(ObjectOrder::Projectile);
		projectileGroup_.second->SetCollisionMode(CollisionMode::Multiple);
		projectileGroup_.second->Off();

		if (i <10)
		{
			projectileGroupList01_.push_back(projectileGroup_);
		}
		else if (i <20)
		{
			projectileGroupList02_.push_back(projectileGroup_);
		}
		else if (i <30)
		{
			projectileGroupList03_.push_back(projectileGroup_);
		}
	}
	targerSerchTimer01_ = targerSerchTimer_;
	targerSerchTimer02_ = targerSerchTimer01_ - 0.1f;
	targerSerchTimer03_ = targerSerchTimer02_ - 0.1f;

	valueSoulCard_ = SoulCard::Shuriken;
	Off();
}


void Shuriken::Update(float _deltaTime)
{
	StateSet();

	SerchTarget();
	ProjectileSort();
	RenderRotate();
	TimerUpdater(_deltaTime);
	RangeCheak(_deltaTime);

	ColCheak();
	TarGetInitialization();

}
void Shuriken::End()
{

}


void  Shuriken::StateSet()
{
	if (currentlevel_ < 2)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 1.f;
		shuriKenWeaponInfo_.weaponAtkSpeed_ = 1000.f;//

		shuriKenWeaponInfo_.weaponPassAtk_ = 0;
		shuriKenWeaponInfo_.weaponPassNum_ = 2;

		shuriKenWeaponInfo_.weaponSize_ = 100;
		shuriKenWeaponInfo_.weaponDuration_ = 100;
		shuriKenWeaponInfo_.weaponSpeed_ = 100;

		shuriKenWeaponInfo_.weaponknockback_ = 100;

		shuriKenWeaponInfo_.weaponProjectileNum_ = 10;
		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 3;

	}
	else if (currentlevel_ < 3)
	{
		shuriKenWeaponInfo_.weaponAtk_ = 1.58f;
		shuriKenWeaponInfo_.weaponAtkSpeed_ = 1000.f;//1초마다
		shuriKenWeaponInfo_.weaponProjectileNum_ = 3;
		shuriKenWeaponInfo_.weaponSpeed_ = 100.f;

	}
	else if (currentlevel_ < 4)
	{
		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 2;
	}
	else if (currentlevel_ < 5)
	{

	}
	else if (currentlevel_ < 6)
	{
		shuriKenWeaponInfo_.weponConsecutiveAtkNum_ = 3;
	}
}

void Shuriken::SerchTarget()
{
	if (targerSerchTimer_ > 1.5f)
	{
		targetSerchCounter_ = 0;
		monsterList_ = Monster::GetMonsterList();
		targetInst01_.clear();
		for (size_t n = 0; n < shuriKenWeaponInfo_.weaponProjectileNum_; n++)//한번에 던지는 투사체 갯수만큼 반복할것임
		{
			for (size_t i = 0; i < monsterList_.size(); i++)
			{
				if (monsterList_[i]->IsSummoned() == true && monsterList_[i]->isTarget_ == false)
				{
					if (monsterList_[i]->GetMonsterInfo().hp_ > 0 && firstSerchCheak_ == false)//hp0이상, 첫번째 순번일경우
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
						firstSerchCheak_ = true;
					}
					else if (minHpPair_.second > monsterList_[i]->GetMonsterInfo().hp_)//현재검사중인 몬스터 체력이 더 낮다면
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
					}
				}
				if (i == monsterList_.size() - 1)
				{
					targetSerchCounter_ += 1;
					targetInst01_.push_back(minHpPair_);//타겟리스트에 추가
					monsterList_[minHpPair_.first]->isTarget_ = true;
					firstSerchCheak_ = false;
					istarget_ = true;
				}
				if (targetSerchCounter_ == 0)
				{
					istarget_ = false;
				}
			}
		}

		if (shuriKenWeaponInfo_.weponConsecutiveAtkNum_ >= 2)
		{
			targetInst02_ = targetInst01_;
		}
		if (shuriKenWeaponInfo_.weponConsecutiveAtkNum_ >= 3)
		{
			targetInst03_ = targetInst01_;
		}
	}
}

void Shuriken::ProjectileSort()
{
	if (istarget_ == true)
	{
		if (targerSerchTimer01_ > 1.5f)
		{
			for (size_t i = 0; i < projectileGroupList01_.size(); i++)
			{
				if (targetInst01_.size() > i) // 타겟수만큼 필요
				{
					passNum_[i] = shuriKenWeaponInfo_.weaponPassNum_;
					projectileGroupList01_[i].first->On();
					projectileGroupList01_[i].second->On();
					projectileGroupList01_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -219)));
					projectileGroupList01_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
				}
				else	 if (projectileGroupList01_[i].first->IsUpdate() == true)
				{
					projectileGroupList01_[i].first->Off();
					projectileGroupList01_[i].second->Off();
				}
			}
		}
		if (targerSerchTimer02_ > 1.5f)
		{
			for (size_t i = 0; i < projectileGroupList02_.size(); i++)
			{
				if (targetInst02_.size() > i) // 타겟수만큼 필요
				{
					passNum_[i+10] = shuriKenWeaponInfo_.weaponPassNum_;
					projectileGroupList02_[i].first->On();
					projectileGroupList02_[i].second->On();
					projectileGroupList02_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -219)));
					projectileGroupList02_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
				}
				else	 if (projectileGroupList02_[i].first->IsUpdate() == true)
				{
					projectileGroupList02_[i].first->Off();
					projectileGroupList02_[i].second->Off();
				}
			}
		}
		if (targerSerchTimer03_ > 1.5f)
		{
			for (size_t i = 0; i < projectileGroupList03_.size(); i++)
			{
				if (targetInst03_.size() > i) // 타겟수만큼 필요
				{
					passNum_[i + 20] = shuriKenWeaponInfo_.weaponPassNum_;
					projectileGroupList03_[i].first->On();
					projectileGroupList03_[i].second->On();
					projectileGroupList03_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -219)));
					projectileGroupList03_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition());
				}
				else	 if (projectileGroupList03_[i].first->IsUpdate() == true)
				{
					projectileGroupList03_[i].first->Off();
					projectileGroupList03_[i].second->Off();
				}
			}
		}
	}
}
	
void Shuriken::RenderRotate()
{
	if (istarget_ == true)
	{
		if (targerSerchTimer01_ > 1.5f)
		{
			referenceVectorList01_.clear();
			monsterList_ = Monster::GetMonsterList();

			for (size_t i = 0; i < targetInst01_.size(); i++)
			{
				float Mx = monsterList_[targetInst01_[i].first]->GetTransform().GetWorldPosition().x;
				float My = monsterList_[targetInst01_[i].first]->GetTransform().GetWorldPosition().y;
				float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
				float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//몬스터 옮겨진 위치로 가야함
				referenceVector_.x = (Mx - Px); //방향 구하는 공식
				referenceVector_.y = (My - Py);
				referenceVector_.w = 0;
				referenceVectorList01_.push_back(referenceVector_);

				projectileGroupList01_[i].first->GetTransform().SetWorldRotation(60, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			}
		}
		if (targerSerchTimer02_ > 1.5f)
		{
			referenceVectorList02_.clear();
			monsterList_ = Monster::GetMonsterList();

			for (size_t i = 0; i < targetInst02_.size(); i++)
			{
				float Mx = monsterList_[targetInst02_[i].first]->GetTransform().GetWorldPosition().x;
				float My = monsterList_[targetInst02_[i].first]->GetTransform().GetWorldPosition().y;
				float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
				float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//몬스터 옮겨진 위치로 가야함
				referenceVector_.x = (Mx - Px); //방향 구하는 공식
				referenceVector_.y = (My - Py);
				referenceVector_.w = 0;
				referenceVectorList02_.push_back(referenceVector_);

				projectileGroupList02_[i].first->GetTransform().SetWorldRotation(60, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			}
		}
		if (targerSerchTimer03_ > 1.5f)
		{
			referenceVectorList03_.clear();
			monsterList_ = Monster::GetMonsterList();

			for (size_t i = 0; i < targetInst03_.size(); i++)
			{
				float Mx = monsterList_[targetInst03_[i].first]->GetTransform().GetWorldPosition().x;
				float My = monsterList_[targetInst03_[i].first]->GetTransform().GetWorldPosition().y;
				float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
				float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//몬스터 옮겨진 위치로 가야함
				referenceVector_.x = (Mx - Px); //방향 구하는 공식
				referenceVector_.y = (My - Py);
				referenceVector_.w = 0;
				referenceVectorList03_.push_back(referenceVector_);

				projectileGroupList03_[i].first->GetTransform().SetWorldRotation(60, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			}
		}
	}
}

void Shuriken::RangeCheak(float _deltaTime)
{
	if (istarget_ == true)
	{
		if (targerSerchTimer01_ <= 1.3f)
		{
			for (size_t i = 0; i < targetInst01_.size(); i++)
			{
				projectileGroupList01_[i].first->GetTransform().SetWorldMove(referenceVectorList01_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList01_[i].second->GetTransform().SetWorldMove(referenceVectorList01_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
			}
		}
		else 
		{
			for (size_t i = 0; i < targetInst01_.size(); i++)
			{
				projectileGroupList01_[i].first->Off();
				projectileGroupList01_[i].second->Off();
			}
		}
		if (targerSerchTimer02_ <= 1.3f)
		{
			for (size_t i = 0; i < targetInst02_.size(); i++)
			{
				projectileGroupList02_[i].first->GetTransform().SetWorldMove(referenceVectorList02_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList02_[i].second->GetTransform().SetWorldMove(referenceVectorList02_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
			}
		}
		else
		{
			for (size_t i = 0; i < targetInst02_.size(); i++)
			{
				projectileGroupList02_[i].first->Off();
				projectileGroupList02_[i].second->Off();
			}
		}
		if (targerSerchTimer03_ <= 1.3f)
		{
			for (size_t i = 0; i < targetInst03_.size(); i++)
			{
				projectileGroupList03_[i].first->GetTransform().SetWorldMove(referenceVectorList03_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList03_[i].second->GetTransform().SetWorldMove(referenceVectorList03_[i].Normalize3D() * _deltaTime * shuriKenWeaponInfo_.weaponAtkSpeed_);
			}
		}
		else
		{
			for (size_t i = 0; i < targetInst03_.size(); i++)
			{
				projectileGroupList03_[i].first->Off();
				projectileGroupList03_[i].second->Off();
			}
		}
	}
}


CollisionReturn Shuriken::ShurikenToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	for (size_t i = 0; i < 30; i++)
	{
		if (i < 10)
		{
			if (projectileGroupList01_[i].second == _This)//발사체중 부딪힌 발사체 찾아서 지움
			{
				if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] > 0)
				{
					dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] -= 1;
				}
				 if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] == 0)
				{
					projectileGroupList01_[i].first->Off();
					projectileGroupList01_[i].second->Off();
				}
			}
		}
		else if (i < 20)
		{
			if (projectileGroupList02_[i - 10].second == _This)
			{
				if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] > 0)
				{
					dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] -= 1;
				}
				 if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] == 0)
				{
					projectileGroupList02_[i - 10].first->Off();
					projectileGroupList02_[i - 10].second->Off();
				}
			}
		}
		else if (i < 30)
		{
			if (projectileGroupList03_[i - 20].second == _This)
			{

				if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] > 0)
				{
					dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] -= 1;
				}
				 if (dynamic_pointer_cast<Shuriken>(_This->GetActor())->passNum_[i] == 0)
				{
					projectileGroupList03_[i - 20].first->Off();
					projectileGroupList03_[i - 20].second->Off();
				}
			}
		}
	}
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= shuriKenWeaponInfo_.weaponAtk_; //데미지줌
	return CollisionReturn::Stop;
}

void Shuriken::ColCheak()
{
	for (size_t i = 0; i < 30; i++)
	{
		if (i < 10)
		{
			projectileGroupList01_[i].second->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ShurikenToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
		else if (i < 20)
		{
			projectileGroupList02_[i-10].second->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ShurikenToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
		else if (i < 30)
		{
			projectileGroupList03_[i-20].second->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Shuriken::ShurikenToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
		}

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
	if (targerSerchTimer_ > 1.5f)
	{
		targerSerchTimer_ = 0;
	}
	else
	{
		targerSerchTimer_ += _deltaTime;
	}

	if (targerSerchTimer01_ > 1.5f)
	{
		targerSerchTimer01_ = 0;
	}
	else
	{
		targerSerchTimer01_ += _deltaTime;
	}

	if (targerSerchTimer02_ > 1.5f)
	{
		targerSerchTimer02_ = 0;
	}
	else
	{
		targerSerchTimer02_ += _deltaTime;
	}

	if (targerSerchTimer03_ > 1.5f)
	{
		targerSerchTimer03_ = 0;
	}
	else
	{
		targerSerchTimer03_ += _deltaTime;
	}
}
