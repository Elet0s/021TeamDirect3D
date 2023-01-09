#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCamera.h"
#include "GameEngineCameraActor.h"
#include "GameEngineDevice.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineGUI.h"
#include "GameEngineCollision.h"
#include "GameEngineCoreDebug.h"
#include "GEngine.h"

GameEngineLevel::GameEngineLevel()
{
	cameras_.resize(static_cast<size_t>(CameraOrder::UICamera) + 1);

	std::shared_ptr<GameEngineCameraActor> mainCameraActor = CreateActor<GameEngineCameraActor>();
	mainCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	mainCameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	mainCameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::MainCamera);

	std::shared_ptr<GameEngineCameraActor> midCameraActor = CreateActor<GameEngineCameraActor>();
	midCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	midCameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	midCameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::MidCamera);
	//마우스포인터 위치 문제와 알파 렌더링 문제를 한번에 해결하기 위해 중간 카메라 추가.

	std::shared_ptr<GameEngineCameraActor> UICameraActor = CreateActor<GameEngineCameraActor>();
	UICameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	UICameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	UICameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::UICamera);
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::shared_ptr<GameEngineUpdateObject> object : deleteObjects_)
	{
		object->ReleaseHierarchy();
		//이전 루프에서 사망판정되서 objectsInDeletion_에 저장된 모든 오브젝트들과 그 자식들을 전부 삭제한다.
	}
	deleteObjects_.clear();
	//오브젝트들을 전부 삭제했다면 objectsInDeletion_리스트를 비운다.

	for (const std::pair<int, std::list<std::shared_ptr<GameEngineActor>>>& actorGroup : allActors_)
	{
		for (std::shared_ptr<GameEngineActor> actor : actorGroup.second)
		{
			if (nullptr != actor)
			{
				//delete actor;
				//actor = nullptr;
				actor->ReleaseHierarchy();
				//더이상 레벨이 가진 액터들을 그냥 삭제하지 않고, ReleaseHierarchy() 함수를 통해
				// 자식으로 가진 컴포넌트들을 삭제하는 과정을 거친 후 삭제한다.	
			}
		}
	}
}

std::shared_ptr<GameEngineCameraActor> GameEngineLevel::GetMainCameraActor()
{
	return cameras_[static_cast<int>(CameraOrder::MainCamera)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return cameras_[static_cast<int>(CameraOrder::MainCamera)]->GetActor()->GetTransform();
}

std::shared_ptr<GameEngineCameraActor> GameEngineLevel::GetUICameraActor()
{
	return cameras_[static_cast<int>(CameraOrder::UICamera)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetUICameraActorTransform()
{
	return cameras_[static_cast<int>(CameraOrder::UICamera)]->GetActor()->GetTransform();
}

std::shared_ptr<GameEngineCameraActor> GameEngineLevel::GetCameraActor(UINT _index)
{
	return cameras_[_index]->GetActor<GameEngineCameraActor>();
}

std::shared_ptr<GameEngineCameraActor> GameEngineLevel::GetCameraActor(CameraOrder _cameraOrder)
{
	return cameras_[static_cast<int>(_cameraOrder)]->GetActor<GameEngineCameraActor>();
}

void GameEngineLevel::AllClear()
{
	allActors_.clear();
	cameras_.clear();
	allCollisions_.clear();
}

void GameEngineLevel::LevelUpdate(float _deltaTime)
{
	this->AddAccTime(_deltaTime);
	this->Update(_deltaTime);		//레벨과 그 자식 클래스들이 가진 요소들 중 액터 제외한 것들을 업데이트 하는 함수.
	this->ActorsUpdate(_deltaTime);	//레벨이 가진 액터들을 업데이트하는 함수.
	this->Render(_deltaTime);
	this->Release(_deltaTime);
}

void GameEngineLevel::ActorsUpdate(float _deltaTime)
{
	for (const std::pair<int, std::list<std::shared_ptr<GameEngineActor>>>& actorListPair : allActors_)
	{
		for (std::shared_ptr<GameEngineActor> const actor : actorListPair.second)
			//이 위치의 const는 actor가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
			//하지만 actor가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
		{
			if (true == actor->IsUpdate())
			{
				actor->AllUpdate(_deltaTime);
				//액터들과 그 아래 컴포넌트들의 업데이트는 전부 AllUpdate로 통합.	
			}
		}
	}
}

void GameEngineLevel::Render(float _deltaTime)
{
	if (true == GEngine::IsCollisionDebug())
	{
		for (std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator collisionGroupIter = allCollisions_.begin();
			collisionGroupIter != this->allCollisions_.end(); collisionGroupIter++)
		{
			std::list<std::shared_ptr<GameEngineCollision>>& collisionGroup = collisionGroupIter->second;

			for (std::list<std::shared_ptr<GameEngineCollision>>::iterator collisionIter = collisionGroup.begin();
				collisionIter != collisionGroup.end(); collisionIter++)
			{
				if (true == (*collisionIter)->IsUpdate())
				{
					(*collisionIter)->DebugRender();
					//진짜 렌더링 과정이 아니므로 RenderStart()와 RenderEnd()사이에 들어가지 않아도 된다.
				}
			}
		}
	}

	GameEngineDevice::RenderStart();
	//RenderStart()와 RenderEnd()사이에 모든 렌더링 과정이 들어가야 한다. 

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->Render(_deltaTime);
			//렌더러들이 가진 렌더링 정보를 각 카메라별로 가진 렌더타겟에 옮긴다.
		}
	}

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->GetConclusionRenderTarget()->EffectProcess();
			//카메라별로 가지고 있는 렌더타겟에, 가지고 있는 블러 등의 후처리 효과가 있다면 적용한다.
		}
	}

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			GameEngineDevice::GetBackBuffer()->Merge(cameras_[i]->conclusionRenderTarget_, 0);
			//다른 카메라들이 가진 렌더타겟의 렌더링 정보들을 백버퍼 렌더타겟으로 합친다.
		}
	}

	GameEngineDevice::GetBackBuffer()->EffectProcess();
	//백버퍼 렌더타겟이 가진, 윈도우 전체에 적용해야 하는 후처리 효과가 있다면 여기서 적용한다.

	GameEngineDebug::Debug3DRender();
	//DebugRender()로 등록된 디버깅 정보는 실제로는 여기서 백버퍼 렌더타겟으로 옮겨진다.

	GameEngineGUI::Render(this, _deltaTime);


	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::RemoveActor(std::shared_ptr<GameEngineActor> _rootActor)
{
	if (allActors_.end() == allActors_.find(_rootActor->GetOrder()))
	{
		MsgBoxAssert("루트 액터가 아닌 액터는 여기서 삭제할 수 없습니다.");
	}
	else
	{
		allActors_[_rootActor->GetOrder()].remove(_rootActor);
	}
}

void GameEngineLevel::Release(float _deltaTime)
{
	for (std::shared_ptr<GameEngineUpdateObject> object : deleteObjects_)
	{
		object->ReleaseHierarchy();
		//이전 루프에서 사망판정되서 deleteObjects_에 저장된 모든 오브젝트들과 그 자식들을 전부 삭제한다.
	}
	deleteObjects_.clear();
	//오브젝트들을 전부 삭제했다면 deleteObjects_리스트를 비운다.


	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->Release(_deltaTime);	//i번째 카메라에서 사망 판정된 렌더러들 등록 해제.
			//렌더러 삭제가 아니라 i번째 카메라의 allRenderers_리스트에서 빼는 등록해제인 것에 유의.
		}
	}

	for (std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator collisionGroupIter = allCollisions_.begin();
		collisionGroupIter != allCollisions_.end(); collisionGroupIter++)
	{
		std::list<std::shared_ptr<GameEngineCollision>>& collisionGroup = collisionGroupIter->second;

		for (std::list<std::shared_ptr<GameEngineCollision>>::iterator collisionIter = collisionGroup.begin();
			collisionIter != collisionGroup.end(); /*collisionIter++*/)
		{
			if (true == (*collisionIter)->IsDead())
			{
				collisionIter = collisionGroup.erase(collisionIter);
				//여기서는 allColiisions_에서 제거하기만 한다.
			}
			else
			{
				++collisionIter;
			}
		}
	}

	for (std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator actorGroupIter = allActors_.begin();
		actorGroupIter != allActors_.end(); actorGroupIter++)
	{
		for (std::list<std::shared_ptr<GameEngineActor>>::iterator actorIter = actorGroupIter->second.begin();
			actorIter != actorGroupIter->second.end(); /*listIter++*/)
		{
			(*actorIter)->ReleaseObject(deleteObjects_);
			//액터와 그 자식 컴포넌트들이 사망 판정을 받았는지 확인하고, 
			//사망 판정받았다면 부모 오브젝트의 children_리스트에서 떼어내 deleteObjects_에 넣는다.

			if (true == (*actorIter)->IsDead())
			{
				//액터가 사망판정받았다면 allActors_맵에서 제거.
				actorIter = actorGroupIter->second.erase(actorIter);
				//delete (*actorIter); 왜 그냥 삭제를 안하고 이렇게 복잡한 삭제/정리 체계를 만들고 있지??
				//->레벨 아래로 액터 업데이트오브젝트 밑에 각종 기능을 가진 컴포넌트 업데이트오브젝트들이 
				// 적층식으로 쌓이고 상호 등록, 관리되는 현재 구조상 무분별하게 삭제하면
				// 업데이트오브젝트 구조가 무너지고 메모리 누수를 막을 수 없게 된다.
				//따라서, 오브젝트를 삭제할 때 업데이트오브젝트 적층 구조에서 완전히 떼어낸 과정을 거친 후 삭제해야 하고
				// 떼어내는 과정을 거쳐야 하기 때문에 삭제하고자하는 루프에서 바로 삭제하지 않고
				// deleteObjects_ 리스트에 넣은 후 다음 루프에서 삭제하는 절차가 필요하다.
			}
			else
			{
				++actorIter;
			}
		}
	}
}


void GameEngineLevel::PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer, int _cameraOrder)
{
	std::shared_ptr<GameEngineCamera> prevCamera = cameras_[static_cast<UINT>(_renderer->cameraOrder_)];

	prevCamera->allRenderers_[_renderer->GetRenderingOrder()].remove(_renderer);

	_renderer->cameraOrder_ = static_cast<CameraOrder>(_cameraOrder);


	std::shared_ptr<GameEngineCamera> nextCamera = cameras_[_cameraOrder];

	cameras_[_cameraOrder]->PushRenderer(_renderer);

	_renderer->camera_ = nextCamera;
}

void GameEngineLevel::PushCamera(std::shared_ptr<GameEngineCamera> _camera, int _cameraOrder)
{
	if (static_cast<int>(CameraOrder::UICamera) < _cameraOrder
		|| static_cast<int>(CameraOrder::MainCamera) > _cameraOrder)
	{
		MsgBoxAssert("카메라 오더가 허용 범위를 넘어섰습니다.");
		return;
	}

	cameras_[_cameraOrder] = _camera;
}

void GameEngineLevel::PushCollision(std::shared_ptr<GameEngineCollision> _collision, int _collisionOrder)
{
	allCollisions_[_collision->GetOrder()].remove(_collision);
	//원래 그룹에서 제거.

	_collision->SetOrder(_collisionOrder);
	//새 오더 부여.

	allCollisions_[_collision->GetOrder()].push_back(_collision);
	//새 그룹에 삽입.
}

void GameEngineLevel::OverChildMove(GameEngineLevel* _nextLevel)
{
	if (this == _nextLevel)
	{
		return;
	}

	std::list<std::shared_ptr<GameEngineActor>> actorOverList;

	for (std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator actorGroupIter = allActors_.begin();
		actorGroupIter != allActors_.end(); actorGroupIter++)
	{

		std::list<std::shared_ptr<GameEngineActor>>& actorGroup = actorGroupIter->second;
		for (std::list<std::shared_ptr<GameEngineActor>>::iterator actorIter = actorGroup.begin();
			actorIter != actorGroup.end(); /*actorIter++*/)
		{
			if (true == (*actorIter)->isLevelOver_)
			{
				actorOverList.push_back(*actorIter);
				actorIter = actorGroup.erase(actorIter);
			}
			else
			{
				++actorIter;
			}
		}
	}

	for (std::shared_ptr<GameEngineActor> overActor : actorOverList)
	{
		overActor->SetLevel(_nextLevel);
		_nextLevel->allActors_[overActor->GetOrder()].push_back(overActor);
	}

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr == cameras_[i])
		{
			continue;
		}

		cameras_[i]->OverRenderer(_nextLevel->cameras_[i]);
	}

	std::list<std::shared_ptr<GameEngineCollision>> collisionOverList;

	for (std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator collisionGroupIter = allCollisions_.begin();
		collisionGroupIter != allCollisions_.end(); collisionGroupIter++)
	{
		std::list<std::shared_ptr<GameEngineCollision>>& collisionGroup = collisionGroupIter->second;

		for (std::list<std::shared_ptr<GameEngineCollision>>::iterator collisionIter = collisionGroup.begin();
			collisionIter != collisionGroup.end(); /*collisionIter++*/)
		{
			if (true == (*collisionIter)->GetRoot<GameEngineActor>()->isLevelOver_)
			{
				collisionOverList.push_back(*collisionIter);
				collisionIter = collisionGroup.erase(collisionIter);
			}
			else
			{
				++collisionIter;
			}
		}
	}

	for (std::shared_ptr<GameEngineCollision> overCollision : collisionOverList)
	{
		_nextLevel->allCollisions_[overCollision->GetOrder()].push_back(overCollision);
	}
}

void GameEngineLevel::ActorLevelStartEvent()
{
	for (const std::pair<int, std::list<std::shared_ptr<GameEngineActor>>>& actorListPair : allActors_)
	{
		for (std::shared_ptr<GameEngineActor> const actor : actorListPair.second)
			//이 위치의 const는 actor가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
			//하지만 actor가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
		{
			if (true == actor->IsUpdate())
			{
				actor->AllLevelStartEvent();
			}
		}
	}
}

void GameEngineLevel::ActorLevelEndEvent()
{
	for (const std::pair<int, std::list<std::shared_ptr<GameEngineActor>>>& actorListPair : allActors_)
	{
		for (std::shared_ptr<GameEngineActor> const actor : actorListPair.second)
			//이 위치의 const는 actor가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
			//하지만 actor가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
		{
			if (true == actor->IsUpdate())
			{
				actor->AllLevelEndEvent();
			}
		}
	}
}

