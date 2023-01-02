#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineCoreDebug.h"
#include "GameEngineCore.h"

bool (*GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_Max)][static_cast<int>(CollisionType::CT_Max)])
(const GameEngineTransform& _transformA, const GameEngineTransform& _transformB);

class GameEngineCollisionFunctionInit
{
	//이 클래스의 존재 이유: 
public:
	GameEngineCollisionFunctionInit()
	{
		memset(
			GameEngineCollision::collisionFunctions_,
			0,
			sizeof(GameEngineCollision::collisionFunctions_));

		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_Sphere)][static_cast<int>(CollisionType::CT_Sphere)]
			= &GameEngineTransform::SphereToSphere;

		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_AABB)][static_cast<int>(CollisionType::CT_AABB)]
			= &GameEngineTransform::AABBToAABB;

		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_OBB)][static_cast<int>(CollisionType::CT_OBB)]
			= &GameEngineTransform::OBBToOBB;



		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_Sphere2D)][static_cast<int>(CollisionType::CT_Sphere2D)]
			= &GameEngineTransform::Sphere2DToSphere2D;

		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_AABB2D)][static_cast<int>(CollisionType::CT_AABB2D)]
			= &GameEngineTransform::AABB2DToAABB2D;

		GameEngineCollision::collisionFunctions_[static_cast<int>(CollisionType::CT_OBB2D)][static_cast<int>(CollisionType::CT_OBB2D)]
			= &GameEngineTransform::OBB2DToOBB2D;

		//추가 함수가 필요하다면 그때그때 만들어서 추가할 것.
	}

	~GameEngineCollisionFunctionInit()
	{
	}
};

GameEngineCollisionFunctionInit inst_;

GameEngineCollision::GameEngineCollision()
	: debugType_(CollisionType::CT_Max),
	collisionMode_(CollisionMode::Single),
	color_(1.f, 0.f, 0.f, 0.5f),
	debugCameraOrder_(CameraOrder::MainCamera)	//기본 디버그카메라 세팅: 메인카메라.
	//메인카메라는 엔진 기본제공 카메라이므로 엔진 수준에서 그런 편의기능을 제공할 수 있다.
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::ChangeOrder(int _collisionOrder)
{
	this->GetActor()->GetLevel()->PushCollision(
		std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), _collisionOrder);
}

bool GameEngineCollision::IsCollision(
	CollisionType _thisType,
	int _collisionGroup,
	CollisionType _otherType,
	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _update /*= nullptr*/,
	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _enter /*= nullptr*/,
	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _exit /*= nullptr*/
)
{
	if (false == this->IsUpdate())
	{
		return false;
	}

	int thisType = static_cast<int>(_thisType);
	int otherType = static_cast<int>(_otherType);

	if (nullptr == GameEngineCollision::collisionFunctions_[thisType][otherType])
	{
		MsgBoxAssert("아직 준비되지 않은 충돌 처리입니다.");
		return false;
	}

	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>& allCollisions
		= this->GetActor()->GetLevel()->allCollisions_;

	std::list<std::shared_ptr<GameEngineCollision>>& collisionGroup = allCollisions[_collisionGroup];

	bool isCollided = false;	//충돌 여부.

	for (std::shared_ptr<GameEngineCollision> otherCollision : collisionGroup)
	{
		if (shared_from_this() == otherCollision)
		{
			continue;
		}

		if (false == otherCollision->IsUpdate())
		{
			continue;
		}

		if (true == GameEngineCollision::collisionFunctions_[thisType][otherType](this->GetTransform(), otherCollision->GetTransform()))
		{
			isCollided = true;		//여기까지 들어온 것이 이미 충돌했다는 의미.

			if (CollisionMode::Multiple == collisionMode_)
			{
				if (collisionCheck_.end() == collisionCheck_.find(otherCollision))
				{
					//첫 충돌.
					std::pair<std::set<std::shared_ptr<GameEngineCollision>>::iterator, bool> insertResult
						= collisionCheck_.insert(otherCollision);

					if (false == insertResult.second)
					{
						MsgBoxAssertString(otherCollision->GetNameCopy()
							+ ": 이미 충돌했던 충돌체가 아직 정리되지 않은 상태에서 다시 충돌했습니다.");
						return true;
					}

					if (nullptr != _enter && CollisionReturn::Stop == _enter(
						std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), otherCollision))
					{
						return true;
					}
				}
				else
				{
					if (nullptr != _update && CollisionReturn::Stop == _update(
						std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), otherCollision))
					{
						return true;
					}
				}
			}
			else if (CollisionMode::Single == collisionMode_)
			{
				if (nullptr != _update)
				{
					if (CollisionReturn::Stop == _update(
						std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), otherCollision))
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			if (CollisionMode::Multiple == collisionMode_)
			{
				if (collisionCheck_.end() != collisionCheck_.find(otherCollision))
				{
					if (0 == collisionCheck_.erase(otherCollision))
					{
						MsgBoxAssertString(otherCollision->GetNameCopy()
							+ ": 충돌한 적 없는 충돌체를 제거하려고 했습니다.");
						return false;
					}

					if (nullptr != _exit && CollisionReturn::Stop == _exit(
						std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), otherCollision))
					{
						return false;
					}
					//collisionCheck_.erase(otherCollision);
				}
			}
		}
	}

	return isCollided;
}

void GameEngineCollision::DebugRender()
{
	std::shared_ptr<GameEngineCamera> debugCamera
		= this->GetActor()->GetLevel()->cameras_[static_cast<UINT>(debugCameraOrder_)];

	switch (this->debugType_)
	{
		//case CollisionType::CT_Point2D:
		//	break;

	case CollisionType::CT_Sphere2D:
		GameEngineDebug::DrawSphere(GetTransform(), debugCamera, color_);
		break;

	case CollisionType::CT_AABB2D:
		GameEngineDebug::DrawBox(GetTransform(), debugCamera, color_);
		break;

	case CollisionType::CT_OBB2D:
		GameEngineDebug::DrawBox(GetTransform(), debugCamera, color_);
		break;



		//case CollisionType::CT_Point:
		//	break;

	case CollisionType::CT_Sphere:
		GameEngineDebug::DrawSphere(GetTransform(), debugCamera, color_);
		break;

	case CollisionType::CT_AABB:
		GameEngineDebug::DrawBox(GetTransform(), debugCamera, color_);
		break;

	case CollisionType::CT_OBB:
		GameEngineDebug::DrawBox(GetTransform(), debugCamera, color_);
		break;


	default:
		MsgBoxAssert("지원되지 않는 콜리전 타입입니다. 콜리전타입이 Max가 아닌지 확인하십시오.");
		break;
	}
}

void GameEngineCollision::SetUIDebugCamera()
{
	debugCameraOrder_ = CameraOrder::UICamera;
}

void GameEngineCollision::Start()
{
	this->GetActor()->GetLevel()->PushCollision(
		std::dynamic_pointer_cast<GameEngineCollision>(shared_from_this()), this->GetOrder());
}
