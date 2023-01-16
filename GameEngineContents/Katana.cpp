#include "PreCompile.h"
#include "Katana.h"
#include "Player.h"
#include "Monster.h"

Katana::Katana(): squaredWeaponRange_(0.f), targetLimitation_(4), attackInterval_(0.f)
{
}

Katana::~Katana()
{
}

void Katana::Start()
{
	this->GetTransform().SetLocalScale(float4::White);
	this->GetTransform().SetWorldScale(float4::White);

	if (0 == GameEngineTexture::Find("KatanaSlashV2.png")->GetCutCount())
	{
		GameEngineTexture::Cut("KatanaSlashV2.png", 12, 1);
	}

	for (size_t i = 0; i < 4; ++i)
	{
		katanaRenderer_[i] = CreateComponent<GameEngineTextureRenderer>("KatanaRenderer");
		katanaRenderer_[i]->SetTexture("KatanaSlashV2.png");
		katanaRenderer_[i]->GetTransform().SetWorldScale(64.f, 64.f, 1.f);
		katanaRenderer_[i]->CreateFrameAnimation_CutTexture(
			"KatanaSlash",
			FrameAnimation_Desc("KatanaSlashV2.png", 0.01f)
		);
		katanaRenderer_[i]->ChangeFrameAnimation("KatanaSlash");
		katanaRenderer_[i]->ChangeCamera(CameraOrder::MidCamera);

		katanaRenderer_[i]->AnimationBindEnd(
			"KatanaSlash",
			[this, i](const FrameAnimation_Desc& _desc)->void
			{
				this->katanaRenderer_[i]->CurAnimationReset();
				this->katanaRenderer_[i]->Off();
			}
		);
		//katanaRenderer_[i]->SetRenderingOrder();
		katanaRenderer_[i]->Off();
	}



}

void Katana::Update(float _deltaTime)
{
	StateSet();

	static float currentInterval = 0.f;
	currentInterval += _deltaTime;
	if (currentInterval >= katanaWeaponInfo_.weaponAtkSpeed_)
	{
		currentInterval = 0.f;
		SearchTarget();
		Attack();
	}




}

void Katana::End()
{
}

void Katana::SearchTarget()
{
	for (std::list<Monster*>::iterator iter = monstersInRange_.begin();
		iter != monstersInRange_.end(); ++iter)
	{
		if (false == (*iter)->IsSummoned())
		{
			monstersInRange_.erase(iter);
		}
	}

	this->squaredWeaponRange_ = pow(katanaWeaponInfo_.weaponRange_, 2.f) * 10000.f;

	for (Monster* const singleMonster : Monster::GetMonsterList())
	{
		if (monstersInRange_.size() >= targetLimitation_)
		{
			break;
		}

		if (false == singleMonster->IsSummoned() || false == singleMonster->IsUpdate())
		{
			continue;
		}

		float4 distanceFromPlayer =
			singleMonster->GetTransform().GetWorldPosition() 
			- Player::GetPlayerInst().GetTransform().GetWorldPosition();

		if (squaredWeaponRange_ < abs(distanceFromPlayer.x * distanceFromPlayer.y))
		{
			continue;
		}

		monstersInRange_.push_back(singleMonster);
	}
}

void Katana::StateSet()
{
	switch (currentlevel_)
	{
	case 1:
	{
		katanaWeaponInfo_.weaponAtk_ = 10.f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
		katanaWeaponInfo_.weaponPassAtk_ = 0;
		katanaWeaponInfo_.weaponPassNum_ = 0;
		katanaWeaponInfo_.weaponSize_ = 1.f;
		katanaWeaponInfo_.weaponDuration_ = 1.f;
		katanaWeaponInfo_.weaponSpeed_ = 0.f;
		katanaWeaponInfo_.weaponknockback_ = 0.f;
		katanaWeaponInfo_.weaponProjectileNum_ = 1;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 1;
		katanaWeaponInfo_.weaponRange_ = 3.f;
		break;
	}

	case 2:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
	
		katanaWeaponInfo_.weaponProjectileNum_ = 2;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 2;
		katanaWeaponInfo_.weaponRange_ = 3.25f;
		break;
	}

	case 3:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
		
		katanaWeaponInfo_.weaponProjectileNum_ = 2;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 2;
		katanaWeaponInfo_.weaponRange_ = 3.5f;
		break;
	}

	case 4:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
	
		katanaWeaponInfo_.weaponProjectileNum_ = 3;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 3;
		katanaWeaponInfo_.weaponRange_ = 3.75f;
		break;
	}

	case 5:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
	
		katanaWeaponInfo_.weaponProjectileNum_ = 1;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 1;
		katanaWeaponInfo_.weaponRange_ = 4.f;
		break;
	}

	case 6:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
	
		katanaWeaponInfo_.weaponProjectileNum_ = 4;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 4;
		katanaWeaponInfo_.weaponRange_ = 4.25f;
		break;
	}

	case 7:
	{
		katanaWeaponInfo_.weaponAtk_ = 1.5f;
		katanaWeaponInfo_.weaponAtkSpeed_ = 3.f;
	
		katanaWeaponInfo_.weaponProjectileNum_ = 4;
		katanaWeaponInfo_.weponConsecutiveAtkNum_ = 4;
		katanaWeaponInfo_.weaponRange_ = 4.5f;
		break;
	}


	default:
		break;
	}

	targetLimitation_ = katanaWeaponInfo_.weaponProjectileNum_;

}

void Katana::Attack()
{
	int rendererIndex = 0;
	for (std::list<Monster*>::iterator iter = monstersInRange_.begin();
		iter != monstersInRange_.end(); ++iter)
	{
		(*iter)->GetMonsterInfo().hp_ -= katanaWeaponInfo_.weaponAtk_;
		float rotation = GameEngineRandom::mainRandom_.RandomFloat(0, 360);

		katanaRenderer_[rendererIndex]->On();
		katanaRenderer_[rendererIndex]->GetTransform().SetWorldPosition((*iter)->GetTransform().GetWorldPosition());
		katanaRenderer_[rendererIndex]->GetTransform().SetWorldRotation(0, 0, rotation);
		if (++rendererIndex >= targetLimitation_)
		{
			break;
		}
	}
}
