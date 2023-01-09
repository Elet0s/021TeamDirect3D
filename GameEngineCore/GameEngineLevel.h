#pragma once
#include "GameEngineUpdateObject.h"
#include "GameEngineActor.h"

enum class CameraOrder
{
	MainCamera,
	MidCamera,
	User1,
	User2,
	User3,
	User4,
	User5,
	User6,
	User7,
	UICamera,
};

class GameEngineCamera;
class GameEngineCameraActor;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCollision;
class GameEngineLevel : public GameEngineNameObject, public GameEngineUpdateObject
{
	//레벨: 모든 형태의 업데이트오브젝트들을 관리하는 오브젝트.

	friend class GameEngineCore;
	friend GameEngineRenderer;
	friend GameEngineCamera;
	friend GameEngineActor;
	friend GameEngineCollision;

protected:
	GameEngineLevel();	//이제는 레벨 생성자에서 메인카메라와 UI카메라를 생성하고 시작한다.
	virtual ~GameEngineLevel() = 0;

	GameEngineLevel(const GameEngineLevel& _other) = delete;
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _other) = delete;

public:
	std::shared_ptr<GameEngineCameraActor> GetMainCameraActor();
	GameEngineTransform& GetMainCameraActorTransform();
	std::shared_ptr<GameEngineCameraActor> GetUICameraActor();
	GameEngineTransform& GetUICameraActorTransform();
	std::shared_ptr<GameEngineCameraActor> GetCameraActor(UINT _index);
	std::shared_ptr<GameEngineCameraActor> GetCameraActor(CameraOrder _cameraOrder);

	void AllClear();

public:
	//메인카메라 컴포넌트를 가져오는 함수.
	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return cameras_[static_cast<int>(CameraOrder::MainCamera)];
	}

	std::shared_ptr<GameEngineCamera> GetUICamera()
	{
		return cameras_[static_cast<int>(CameraOrder::UICamera)];
	}

	std::shared_ptr<GameEngineCamera> GetCamera(UINT _cameraIndex)
	{
		return cameras_[_cameraIndex];
	}

	std::shared_ptr<GameEngineCamera> GetCamera(CameraOrder _cameraOrder)
	{
		return cameras_[static_cast<int>(_cameraOrder)];
	}

	//액터들 중 특정 종류만 가져오는 함수.
	template<typename GroupIndexType>
	std::list<std::shared_ptr<GameEngineActor>> GetGroup(GroupIndexType _objectGroupIndex)
	{
		return allActors_[static_cast<int>(_objectGroupIndex)];
	}
	//액터들 중 특정 종류만 가져오는 함수.
	std::list<std::shared_ptr<GameEngineActor>> GetGroup(int _objectGroupIndex)
	{
		return allActors_[_objectGroupIndex];
	}

	//액터들 중 특정 종류만 원하는 형태로 형변환해서 가져오는 함수.
	template<typename ObjectType>
	std::list<std::shared_ptr<ObjectType>> GetConvertedGroup(int _objectGroupIndex)
	{
		std::list<std::shared_ptr<ObjectType>> result;
		for (std::shared_ptr<GameEngineActor> actor : allActors_[_objectGroupIndex])
		{
			result.push_back(std::dynamic_pointer_cast<ObjectType>(actor));
		}
		return result;
	}
	//액터들 중 특정 종류만 원하는 형태로 형변환해서 가져오는 함수.
	template<typename ObjectType, typename GroupIndexType>
	std::list<std::shared_ptr<ObjectType>> GetConvertedGroup(GroupIndexType _objectGroupIndex)
	{
		return GetConvertedGroup<ObjectType>(static_cast<int>(_objectGroupIndex));
	}

	//액터 생성 함수.
	template<typename ActorType, typename GroupIndexType>
	std::shared_ptr<ActorType> CreateActor(GroupIndexType _type, const std::string_view& _actorName = "")
	{
		return CreateActor<ActorType>(static_cast<int>(_type), _actorName);
	}

	//액터 생성 함수.
	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _objectGroupIndex = 0, const std::string_view& _actorName = "")
	{
		std::shared_ptr<GameEngineActor> newActor = std::make_shared<ActorType>();

		newActor->SetLevel(this);
		newActor->SetOrder(_objectGroupIndex);
		newActor->SetName(_actorName);
		newActor->Start();

		std::list<std::shared_ptr<GameEngineActor>>& actorGroup = allActors_[_objectGroupIndex];
		//allActors_ 안에 _objectGroupIndex를 키값으로 가진 페어가 있다면 그걸 찾아서 반환하고,
		// 없다면 만들어서 반환한다. 
		//즉 allActors_.find(_objectGroupIndex) + 
		// allActors_.insert(std::make_pair(_objectGroupIndex, std::list<GameEngineActor*>(newActor));
		// 형태의 코드이다.

		actorGroup.push_back(newActor);

		return std::dynamic_pointer_cast<ActorType>(newActor);
	}


private:

	void LevelUpdate(float _deltaTime);

	//이 레벨이 가진 액터들을 업데이트하는 함수.
	void ActorsUpdate(float _deltaTime);

	//이 레벨의 카메라들이 가진 렌더러들의 렌더링 정보대로 각각의 카메라들이 가진 렌더타겟에 렌더해서 
	// 백버퍼 렌더타겟으로 합치고 전면 버퍼와 교체까지 하는 함수.
	void Render(float _deltaTime);

	//allActors_맵에서 액터를 제거하는 함수.
	void RemoveActor(std::shared_ptr<GameEngineActor> _actor);

	//이 프레임워크의 정식 오브젝트 삭제 절차.
	void Release(float _deltaTime);

	//카메라에 렌더러를 등록하는 함수. 
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer, int _cameraOrder);

	//이 레벨에 카메라를 등록하는 함수.
	void PushCamera(std::shared_ptr<GameEngineCamera> _camera, int _cameraOrder);

	//이 레벨에 충돌체를 등록하는 함수.
	void PushCollision(std::shared_ptr<GameEngineCollision> _collision, int _order);

	//오브젝트를 다음 레벨로 이전시키는 함수.
	void OverChildMove(GameEngineLevel* _nextLevel);

	//레벨이 교체되서 첫 업데이트를 시작할 때 액터들이 가진 AllLevelStartEvent() 함수들을 전부 호출하는 함수.
	void ActorLevelStartEvent();

	//레벨이 교체되서 더이상 업데이트를 하지 않을 때 액터들이 가진 AllLevelEndEvent() 함수들을 전부 호출하는 함수.
	void ActorLevelEndEvent();

private:
	void PushCamera(std::shared_ptr<GameEngineCamera> _camera, CameraOrder _order)
	{
		PushCamera(_camera, static_cast<int>(_order));
	}

	void PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer, CameraOrder _order)
	{
		PushRenderer(_renderer, static_cast<int>(_order));
	}

	void PushRendererToMainCamera(std::shared_ptr<GameEngineRenderer> _renderer)
	{
		PushRenderer(_renderer, static_cast<int>(CameraOrder::MainCamera));
	}

	void PushRendererToUICamera(std::shared_ptr<GameEngineRenderer> _renderer)
	{
		PushRenderer(_renderer, static_cast<int>(CameraOrder::UICamera));
	}

	void PushActor(std::shared_ptr<GameEngineActor> _actor, int _objectGroupIndex)
	{
		std::list<std::shared_ptr<GameEngineActor>>& actorGroup = allActors_[_objectGroupIndex];
		actorGroup.push_back(_actor);
	}

private:
	//이 레벨의 모든 액터들이 저장된 맵.
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> allActors_;

	//삭제 예정인 모든 오브젝트들이 종류 불문하고 잠시 저장되는 일종의 휴지통.
	std::list<std::shared_ptr<GameEngineUpdateObject>> deleteObjects_;

	//이 레벨이 사용하는 모든 카메라들.
	std::vector<std::shared_ptr<GameEngineCamera>> cameras_;

	//이 레벨의 모든 충돌체들.	
	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>> allCollisions_;

};

