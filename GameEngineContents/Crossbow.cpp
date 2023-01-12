#include"PreCompile.h"
#include"Crossbow.h"
#include"Player.h"
#include"Monster.h"

Crossbow::Crossbow()

	: projectileGroup_(),
	projectileGroupList_(),
	firstSerchCheak_(false),
	istarget_(false),
	targerSerchTimer_(0.f),
	targetSerchCounter_(0),
	passNum_(),
	resultCos_(0),
	referenceVector_(),
	crossbowWeaponInfo_(),
	monsterList_(),
	minHpPair_(),
	targetInst_(),
	referenceVectorList_()
{
	name_ = "석궁";
	SetName(std::string_view("CrossBow"));
	myRank_ = Rank::Epic;
	maxLevel_ = 7;
}
Crossbow::~Crossbow()
{

}
void Crossbow::Init()
{
	StateSet();

	std::string sDamege = std::to_string(crossbowWeaponInfo_.weaponAtk_).substr(0, std::to_string(crossbowWeaponInfo_.weaponAtk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(crossbowWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(crossbowWeaponInfo_.weaponAtkSpeed_).find(".") + 3);

	etc_ = "가장 체력이 많은 적에게\n발사합니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n투사체"
		+ std::to_string(crossbowWeaponInfo_.weaponProjectileNum_) + "개\n" + std::to_string(crossbowWeaponInfo_.weaponPassNum_) + "관통 ";
}
void Crossbow::Effect()
{
	currentlevel_ += 1;
}
void Crossbow::Start()
{
	passNum_.reserve(10);
	for (size_t i = 0; i < 10; i++) // 처음부터 최대갯수 모두 만들어서 가지고 있을 것 
	{
		passNum_.push_back(0);

		projectileGroup_.first = CreateComponent<GameEngineTextureRenderer>();
		projectileGroup_.first->GetTransform().SetWorldScale(30, 30, 0);
		projectileGroup_.first->SetTexture("Bolt.png");
		projectileGroup_.first->Off();

		projectileGroup_.second = CreateComponent<GameEngineCollision>();
		projectileGroup_.second->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
		projectileGroup_.second->GetTransform().SetWorldScale(20, 20, 0);
		projectileGroup_.second->ChangeOrder(ObjectOrder::Projectile);
		projectileGroup_.second->SetCollisionMode(CollisionMode::Single);
		projectileGroup_.second->Off();

		projectileGroupList_.push_back(projectileGroup_);
	}

	valueSoulCard_ = SoulCard::Crossbow;
	Off();
}
void Crossbow::Update(float _deltaTime)
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
void Crossbow::End()
{

}

void Crossbow::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	crossbowWeaponInfo_.weaponAtk_ = round((9.f + (5.f * currentlevel_)) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	crossbowWeaponInfo_.weaponAtkSpeed_ = 150.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	crossbowWeaponInfo_.weaponPassNum_ = 6 + 7 * currentlevel_ + Info->passProjectile_;
	crossbowWeaponInfo_.weaponSize_ = 1 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	crossbowWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100;
	crossbowWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;
	crossbowWeaponInfo_.weaponProjectileNum_ = 1 + Info->addProjectile_;


	if (currentlevel_ < 3)
	{
		crossbowWeaponInfo_.weaponAtkSpeed_ = 125.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
		crossbowWeaponInfo_.weaponProjectileNum_ = 1 + Info->addProjectile_;
	}
	else if (currentlevel_ < 5)
	{
		crossbowWeaponInfo_.weaponAtkSpeed_ = 100.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
		crossbowWeaponInfo_.weaponProjectileNum_ = 2 + Info->addProjectile_;
	}
	else
	{
		crossbowWeaponInfo_.weaponAtkSpeed_ = 75.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
		crossbowWeaponInfo_.weaponProjectileNum_ = 3 + Info->addProjectile_;
	}
	
}

void Crossbow::SerchTarget()
{
	if (targerSerchTimer_ > 3.f)
	{
		targetSerchCounter_ = 0;
		monsterList_ = Monster::GetMonsterList();
		targetInst_.clear();
		for (size_t n = 0; n < crossbowWeaponInfo_.weaponProjectileNum_; n++)//한번에 던지는 투사체 갯수만큼 반복할것임
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
					else if (minHpPair_.second < monsterList_[i]->GetMonsterInfo().hp_)//현재검사중인 몬스터 체력이 더 높다면
					{
						minHpPair_ = std::make_pair(i, monsterList_[i]->GetMonsterInfo().hp_);
					}
				}
				if (i == monsterList_.size() - 1)
				{
					targetSerchCounter_ += 1;
					targetInst_.push_back(minHpPair_);//타겟리스트에 추가
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
	}
}

void Crossbow::ProjectileSort()
{
	if (istarget_ == true)
	{
		if (targerSerchTimer_ > 3.f)
		{
			for (size_t i = 0; i < projectileGroupList_.size(); i++)
			{
				if (targetInst_.size() > i) // 타겟수만큼 필요
				{
					projectileGroupList_[i].first->On();
					projectileGroupList_[i].second->On();
					projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition() + (float4(0, 0, -219)));
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
}
void Crossbow::RenderRotate()
{
	if (istarget_ == true)
	{
		if (targerSerchTimer_ > 3.f)
		{
			referenceVectorList_.clear();
			monsterList_ = Monster::GetMonsterList();

			for (size_t i = 0; i < targetInst_.size(); i++)
			{
				float Mx = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().x;
				float My = monsterList_[targetInst_[i].first]->GetTransform().GetWorldPosition().y;
				float Px = Player::GetPlayerInst()->GetTransform().GetWorldPosition().x;
				float Py = Player::GetPlayerInst()->GetTransform().GetWorldPosition().y;//몬스터 옮겨진 위치로 가야함
				referenceVector_.x = (Mx - Px); //방향 구하는 공식
				referenceVector_.y = (My - Py);
				referenceVector_.w = 0;
				referenceVectorList_.push_back(referenceVector_);

				projectileGroupList_[i].first->GetTransform().SetWorldRotation(60, 0, -atan2f(Mx - Px, My - Py) * GameEngineMath::RadianToDegree);
			}
		}
	}
}
void Crossbow::RangeCheak(float _deltaTime)
{
	if (istarget_ == true)
	{
		if (targerSerchTimer_ <= 3.0f)
		{
			for (size_t i = 0; i < targetInst_.size(); i++)
			{
				projectileGroupList_[i].first->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * crossbowWeaponInfo_.weaponAtkSpeed_);
				projectileGroupList_[i].second->GetTransform().SetWorldMove(referenceVectorList_[i].Normalize3D() * _deltaTime * crossbowWeaponInfo_.weaponAtkSpeed_);
			}
		}
	}
}

CollisionReturn Crossbow::ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	dynamic_pointer_cast<Monster>(_Other->GetActor())->flash_ = true;
	for (size_t i = 0; i < 10; i++)
	{
		if (projectileGroupList_[i].second == _This)//발사체중 부딪힌 발사체 찾아서 지움
		{
			projectileGroupList_[i].first->Off();
			projectileGroupList_[i].second->Off();
		}
	}
	dynamic_pointer_cast<Monster>(_Other->GetActor())->GetMonsterInfo().hp_ -= crossbowWeaponInfo_.weaponAtk_; //데미지줌
	return CollisionReturn::Stop;
}


void Crossbow::ColCheak()
{
	for (size_t i = 0; i < 10; i++)
	{
		projectileGroupList_[i].second->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Crossbow::ProjectileToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
}
void Crossbow::TarGetInitialization()
{
	for (size_t i = 0; i < Monster::GetMonsterList().size() - 1; i++)
	{
		if (Monster::GetMonsterList()[i]->isTarget_ == true)
		{
			Monster::GetMonsterList()[i]->isTarget_ = false;
		}
	}
}
void Crossbow::TimerUpdater(float _deltaTime)
{
	if (targerSerchTimer_ > 3.f)
	{
		targerSerchTimer_ = 0;
	}
	else
	{
		targerSerchTimer_ += _deltaTime;
	}
}