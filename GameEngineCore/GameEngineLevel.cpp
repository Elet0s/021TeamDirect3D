 #include "PreCompile.h"
#include "GameEngineLevel.h"
//#include "GameEngineActor.h"
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

	GameEngineCameraActor* mainCameraActor = CreateActor<GameEngineCameraActor>();
	mainCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	mainCameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	mainCameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::MainCamera);


	GameEngineCameraActor* UICameraActor = CreateActor<GameEngineCameraActor>();
	UICameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	UICameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode::Orthographic);
	UICameraActor->GetCameraComponent()->SetCameraOrder(CameraOrder::UICamera);
}

GameEngineLevel::~GameEngineLevel()
{
	for (GameEngineUpdateObject* object : deleteObjects_)
	{
		object->ReleaseHierarchy();
		//���� �������� ��������Ǽ� objectsInDeletion_�� ����� ��� ������Ʈ��� �� �ڽĵ��� ���� �����Ѵ�.
	}
	deleteObjects_.clear();
	//������Ʈ���� ���� �����ߴٸ� objectsInDeletion_����Ʈ�� ����.

	for (const std::pair<int, std::list<GameEngineActor*>>& actorGroup : allActors_)
	{
		for (GameEngineActor* actor : actorGroup.second)
		{
			if (nullptr != actor)
			{
				//delete actor;
				//actor = nullptr;
				actor->ReleaseHierarchy();	
				//���̻� ������ ���� ���͵��� �׳� �������� �ʰ�, ReleaseHierarchy() �Լ��� ����
				// �ڽ����� ���� ������Ʈ���� �����ϴ� ������ ��ģ �� �����Ѵ�.	
			}
		}
	}
}

GameEngineCameraActor* GameEngineLevel::GetMainCameraActor()
{
	return cameras_[static_cast<int>(CameraOrder::MainCamera)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return cameras_[static_cast<int>(CameraOrder::MainCamera)]->GetActor()->GetTransform();
}

GameEngineCameraActor* GameEngineLevel::GetUICameraActor()
{
	return cameras_[static_cast<int>(CameraOrder::UICamera)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetUICameraActorTransform()
{
	return cameras_[static_cast<int>(CameraOrder::UICamera)]->GetActor()->GetTransform();
}

void GameEngineLevel::AllClear()
{
	for (const std::pair<int, std::list<GameEngineActor*>>& actorListPair : allActors_)
	{
		for (GameEngineActor* const actor : actorListPair.second)
		{
			delete actor;
		}
	}

	//for (std::map<int, std::list<GameEngineActor*>>::iterator actorGroupIter = allActors_.begin();
	//	actorGroupIter != allActors_.end(); actorGroupIter++)
	//{
	//	for (std::list<GameEngineActor*>::iterator actorIter = actorGroupIter->second.begin();
	//		actorIter != actorGroupIter->second.end(); actorIter++)
	//	{
	//		delete *actorIter;
	//	}
	//}
	//�� �ڵ�� ������ ����� �ȵȴٸ� �� �ڵ�� ��ü.

	allActors_.clear();
	cameras_.clear();
	allCollisions_.clear();
}

void GameEngineLevel::LevelUpdate(float _deltaTime)
{
	this->AddAccTime(_deltaTime);
	this->Update(_deltaTime);		//������ �� �ڽ� Ŭ�������� ���� ��ҵ� �� ���� ������ �͵��� ������Ʈ �ϴ� �Լ�.
	this->ActorsUpdate(_deltaTime);	//������ ���� ���͵��� ������Ʈ�ϴ� �Լ�.
	this->Render(_deltaTime);		
	this->Release(_deltaTime);
}

void GameEngineLevel::ActorsUpdate(float _deltaTime)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& actorListPair : allActors_)
	{
		for (GameEngineActor* const actor : actorListPair.second)
			//�� ��ġ�� const�� actor�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
			//������ actor�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
		{
			if (true == actor->IsUpdate())
			{
				actor->AllUpdate(_deltaTime);
				//���͵�� �� �Ʒ� ������Ʈ���� ������Ʈ�� ���� AllUpdate�� ����.	
			}
		}
	}
}

void GameEngineLevel::Render(float _deltaTime)
{
	if (true == GEngine::IsCollisionDebug())
	{
		for (std::map<int, std::list<GameEngineCollision*>>::iterator collisionGroupIter = allCollisions_.begin();
			collisionGroupIter != this->allCollisions_.end(); collisionGroupIter++)
		{
			std::list<GameEngineCollision*>& collisionGroup = collisionGroupIter->second;

			for (std::list<GameEngineCollision*>::iterator collisionIter = collisionGroup.begin();
				collisionIter != collisionGroup.end(); collisionIter++)
			{
				if (true == (*collisionIter)->IsUpdate())
				{
					(*collisionIter)->DebugRender();
					//��¥ ������ ������ �ƴϹǷ� RenderStart()�� RenderEnd()���̿� ���� �ʾƵ� �ȴ�.
				}
			}
		}
	}

	GameEngineDevice::RenderStart();
	//RenderStart()�� RenderEnd()���̿� ��� ������ ������ ���� �Ѵ�. 

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->Render(_deltaTime);
			//���������� ���� ������ ������ �� ī�޶󺰷� ���� ����Ÿ�ٿ� �ű��.
		}
	}

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->GetCameraRenderTarget()->EffectProcess();
			//ī�޶󺰷� ������ �ִ� ����Ÿ�ٿ�, ������ �ִ� �� ���� ��ó�� ȿ���� �ִٸ� �����Ѵ�.
		}
	}

	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			GameEngineDevice::GetBackBuffer()->Merge(cameras_[i]->cameraRenderTarget_, 0);
			//�ٸ� ī�޶���� ���� ����Ÿ���� ������ �������� ����� ����Ÿ������ ��ģ��.
		}
	}

	GameEngineDevice::GetBackBuffer()->EffectProcess();
	//����� ����Ÿ���� ����, ������ ��ü�� �����ؾ� �ϴ� ��ó�� ȿ���� �ִٸ� ���⼭ �����Ѵ�.

	GameEngineDebug::Debug3DRender();
	//DebugRender()�� ��ϵ� ����� ������ �����δ� ���⼭ ����� ����Ÿ������ �Ű�����.

	GameEngineGUI::Render(this, _deltaTime);


	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::RemoveActor(GameEngineActor* _rootActor)
{
	if (allActors_.end() == allActors_.find(_rootActor->GetOrder()))
	{
		MsgBoxAssert("��Ʈ ���Ͱ� �ƴ� ���ʹ� ���⼭ ������ �� �����ϴ�.");
	}
	else
	{
		allActors_[_rootActor->GetOrder()].remove(_rootActor);
	}
}

void GameEngineLevel::Release(float _deltaTime)
{
	for (GameEngineUpdateObject* object : deleteObjects_)
	{
		object->ReleaseHierarchy();
		//���� �������� ��������Ǽ� deleteObjects_�� ����� ��� ������Ʈ��� �� �ڽĵ��� ���� �����Ѵ�.
	}
	deleteObjects_.clear();
	//������Ʈ���� ���� �����ߴٸ� deleteObjects_����Ʈ�� ����.


	for (size_t i = 0; i < cameras_.size(); i++)
	{
		if (nullptr != cameras_[i])
		{
			cameras_[i]->Release(_deltaTime);	//i��° ī�޶󿡼� ��� ������ �������� ��� ����.
			//������ ������ �ƴ϶� i��° ī�޶��� allRenderers_����Ʈ���� ���� ��������� �Ϳ� ����.
		}
	}

	for (std::map<int, std::list<GameEngineCollision*>>::iterator collisionGroupIter = allCollisions_.begin();
		collisionGroupIter != allCollisions_.end(); collisionGroupIter++)
	{
		std::list<GameEngineCollision*>& collisionGroup = collisionGroupIter->second;

		for (std::list<GameEngineCollision*>::iterator collisionIter = collisionGroup.begin();
			collisionIter != collisionGroup.end(); /*collisionIter++*/)
		{
			if (true == (*collisionIter)->IsDead())
			{
				collisionIter = collisionGroup.erase(collisionIter);
				//���⼭�� allColiisions_���� �����ϱ⸸ �Ѵ�.
			}
			else
			{
				++collisionIter;
			}
		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator actorGroupIter = allActors_.begin();
		actorGroupIter != allActors_.end(); actorGroupIter++)
	{
		for (std::list<GameEngineActor*>::iterator actorIter = actorGroupIter->second.begin();
			actorIter != actorGroupIter->second.end(); /*listIter++*/)
		{
			(*actorIter)->ReleaseObject(deleteObjects_);
			//���Ϳ� �� �ڽ� ������Ʈ���� ��� ������ �޾Ҵ��� Ȯ���ϰ�, 
			//��� �����޾Ҵٸ� �θ� ������Ʈ�� children_����Ʈ���� ��� deleteObjects_�� �ִ´�.

			if (true == (*actorIter)->IsDead())
			{
				//���Ͱ� ��������޾Ҵٸ� allActors_�ʿ��� ����.
				actorIter = actorGroupIter->second.erase(actorIter);
				//delete (*actorIter); �� �׳� ������ ���ϰ� �̷��� ������ ����/���� ü�踦 ����� ����??
				//->���� �Ʒ��� ���� ������Ʈ������Ʈ �ؿ� ���� ����� ���� ������Ʈ ������Ʈ������Ʈ���� 
				// ���������� ���̰� ��ȣ ���, �����Ǵ� ���� ������ ���к��ϰ� �����ϸ�
				// ������Ʈ������Ʈ ������ �������� �޸� ������ ���� �� ���� �ȴ�.
				//����, ������Ʈ�� ������ �� ������Ʈ������Ʈ ���� �������� ������ ��� ������ ��ģ �� �����ؾ� �ϰ�
				// ����� ������ ���ľ� �ϱ� ������ �����ϰ����ϴ� �������� �ٷ� �������� �ʰ�
				// deleteObjects_ ����Ʈ�� ���� �� ���� �������� �����ϴ� ������ �ʿ��ϴ�.
			}
			else
			{
				++actorIter;
			}
		}
	}
}


void GameEngineLevel::PushRenderer(GameEngineRenderer* _renderer, int _cameraOrder)
{
	GameEngineCamera* prevCamera = cameras_[static_cast<UINT>(_renderer->cameraOrder_)];

	prevCamera->allRenderers_[_renderer->GetRenderingOrder()].remove(_renderer);

	_renderer->cameraOrder_ = static_cast<CameraOrder>(_cameraOrder);


	GameEngineCamera* nextCamera = cameras_[_cameraOrder];

	cameras_[_cameraOrder]->PushRenderer(_renderer);

	_renderer->camera_ = nextCamera;
}

void GameEngineLevel::PushCamera(GameEngineCamera* _camera, int _cameraOrder)
{
	if (static_cast<int>(CameraOrder::UICamera) < _cameraOrder
		|| static_cast<int>(CameraOrder::MainCamera) > _cameraOrder)
	{
		MsgBoxAssert("ī�޶� ������ ��� ������ �Ѿ���ϴ�.");
		return;
	}

	cameras_[_cameraOrder] = _camera;
}

void GameEngineLevel::PushCollision(GameEngineCollision* _collision, int _collisionOrder)
{
	allCollisions_[_collision->GetOrder()].remove(_collision);
	//���� �׷쿡�� ����.

	_collision->SetOrder(_collisionOrder);
	//�� ���� �ο�.

	allCollisions_[_collision->GetOrder()].push_back(_collision);
	//�� �׷쿡 ����.
}

void GameEngineLevel::OverChildMove(GameEngineLevel* _nextLevel)
{
	if (this == _nextLevel)
	{
		return;
	}

	std::list<GameEngineActor*> actorOverList;

	for (std::map<int, std::list<GameEngineActor*>>::iterator actorGroupIter = allActors_.begin();
		actorGroupIter != allActors_.end(); actorGroupIter++)
	{

		std::list<GameEngineActor*>& actorGroup = actorGroupIter->second;
		for (std::list<GameEngineActor*>::iterator actorIter = actorGroup.begin();
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

	for (GameEngineActor* overActor : actorOverList)
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

	std::list<GameEngineCollision*> collisionOverList;

	for (std::map<int, std::list<GameEngineCollision*>>::iterator collisionGroupIter = allCollisions_.begin();
		collisionGroupIter != allCollisions_.end(); collisionGroupIter++)
	{
		std::list<GameEngineCollision*>& collisionGroup = collisionGroupIter->second;

		for (std::list<GameEngineCollision*>::iterator collisionIter = collisionGroup.begin();
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

	for (GameEngineCollision* overCollision: collisionOverList)
	{
		_nextLevel->allCollisions_[overCollision->GetOrder()].push_back(overCollision);
	}
}

void GameEngineLevel::ActorLevelStartEvent()
{
	for (const std::pair<int, std::list<GameEngineActor*>>& actorListPair : allActors_)
	{
		//float scaleTime = GameEngineTime::GetDeltaTime(actorListPair.first);

		for (GameEngineActor* const actor : actorListPair.second)
			//�� ��ġ�� const�� actor�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
			//������ actor�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
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
	for (const std::pair<int, std::list<GameEngineActor*>>& actorListPair : allActors_)
	{
		//float scaleTime = GameEngineTime::GetDeltaTime(actorListPair.first);

		for (GameEngineActor* const actor : actorListPair.second)
			//�� ��ġ�� const�� actor�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
			//������ actor�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
		{
			if (true == actor->IsUpdate())
			{
				actor->AllLevelEndEvent();
			}
		}
	}
}

