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
	//����: ��� ������ ������Ʈ������Ʈ���� �����ϴ� ������Ʈ.

	friend class GameEngineCore;
	friend GameEngineRenderer;
	friend GameEngineCamera;
	friend GameEngineActor;
	friend GameEngineCollision;

protected:
	GameEngineLevel();	//������ ���� �����ڿ��� ����ī�޶�� UIī�޶� �����ϰ� �����Ѵ�.
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
	//����ī�޶� ������Ʈ�� �������� �Լ�.
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

	//���͵� �� Ư�� ������ �������� �Լ�.
	template<typename GroupIndexType>
	std::list<std::shared_ptr<GameEngineActor>> GetGroup(GroupIndexType _objectGroupIndex)
	{
		return allActors_[static_cast<int>(_objectGroupIndex)];
	}
	//���͵� �� Ư�� ������ �������� �Լ�.
	std::list<std::shared_ptr<GameEngineActor>> GetGroup(int _objectGroupIndex)
	{
		return allActors_[_objectGroupIndex];
	}

	//���͵� �� Ư�� ������ ���ϴ� ���·� ����ȯ�ؼ� �������� �Լ�.
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
	//���͵� �� Ư�� ������ ���ϴ� ���·� ����ȯ�ؼ� �������� �Լ�.
	template<typename ObjectType, typename GroupIndexType>
	std::list<std::shared_ptr<ObjectType>> GetConvertedGroup(GroupIndexType _objectGroupIndex)
	{
		return GetConvertedGroup<ObjectType>(static_cast<int>(_objectGroupIndex));
	}

	//���� ���� �Լ�.
	template<typename ActorType, typename GroupIndexType>
	std::shared_ptr<ActorType> CreateActor(GroupIndexType _type, const std::string_view& _actorName = "")
	{
		return CreateActor<ActorType>(static_cast<int>(_type), _actorName);
	}

	//���� ���� �Լ�.
	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _objectGroupIndex = 0, const std::string_view& _actorName = "")
	{
		std::shared_ptr<GameEngineActor> newActor = std::make_shared<ActorType>();

		newActor->SetLevel(this);
		newActor->SetOrder(_objectGroupIndex);
		newActor->SetName(_actorName);
		newActor->Start();

		std::list<std::shared_ptr<GameEngineActor>>& actorGroup = allActors_[_objectGroupIndex];
		//allActors_ �ȿ� _objectGroupIndex�� Ű������ ���� �� �ִٸ� �װ� ã�Ƽ� ��ȯ�ϰ�,
		// ���ٸ� ���� ��ȯ�Ѵ�. 
		//�� allActors_.find(_objectGroupIndex) + 
		// allActors_.insert(std::make_pair(_objectGroupIndex, std::list<GameEngineActor*>(newActor));
		// ������ �ڵ��̴�.

		actorGroup.push_back(newActor);

		return std::dynamic_pointer_cast<ActorType>(newActor);
	}


private:

	void LevelUpdate(float _deltaTime);

	//�� ������ ���� ���͵��� ������Ʈ�ϴ� �Լ�.
	void ActorsUpdate(float _deltaTime);

	//�� ������ ī�޶���� ���� ���������� ������ ������� ������ ī�޶���� ���� ����Ÿ�ٿ� �����ؼ� 
	// ����� ����Ÿ������ ��ġ�� ���� ���ۿ� ��ü���� �ϴ� �Լ�.
	void Render(float _deltaTime);

	//allActors_�ʿ��� ���͸� �����ϴ� �Լ�.
	void RemoveActor(std::shared_ptr<GameEngineActor> _actor);

	//�� �����ӿ�ũ�� ���� ������Ʈ ���� ����.
	void Release(float _deltaTime);

	//ī�޶� �������� ����ϴ� �Լ�. 
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer, int _cameraOrder);

	//�� ������ ī�޶� ����ϴ� �Լ�.
	void PushCamera(std::shared_ptr<GameEngineCamera> _camera, int _cameraOrder);

	//�� ������ �浹ü�� ����ϴ� �Լ�.
	void PushCollision(std::shared_ptr<GameEngineCollision> _collision, int _order);

	//������Ʈ�� ���� ������ ������Ű�� �Լ�.
	void OverChildMove(GameEngineLevel* _nextLevel);

	//������ ��ü�Ǽ� ù ������Ʈ�� ������ �� ���͵��� ���� AllLevelStartEvent() �Լ����� ���� ȣ���ϴ� �Լ�.
	void ActorLevelStartEvent();

	//������ ��ü�Ǽ� ���̻� ������Ʈ�� ���� ���� �� ���͵��� ���� AllLevelEndEvent() �Լ����� ���� ȣ���ϴ� �Լ�.
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
	//�� ������ ��� ���͵��� ����� ��.
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> allActors_;

	//���� ������ ��� ������Ʈ���� ���� �ҹ��ϰ� ��� ����Ǵ� ������ ������.
	std::list<std::shared_ptr<GameEngineUpdateObject>> deleteObjects_;

	//�� ������ ����ϴ� ��� ī�޶��.
	std::vector<std::shared_ptr<GameEngineCamera>> cameras_;

	//�� ������ ��� �浹ü��.	
	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>> allCollisions_;

};

