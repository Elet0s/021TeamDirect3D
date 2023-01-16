#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

enum class CollisionMode	//��� �浹ü�� �浹 Ƚ��.
{
	Single,		//�� �浹ü�ʹ� �ѹ��� �浹.	normal
	Multiple	//�ߺ��浹 ���.	ex
};

enum class CollisionReturn	//�浹 ���� ����
{
	Continue,	//��� �浹 ������ ���� ����.
	Stop		//�浹�ߴ� �浹ü���� �浹 �ߴ�.
};

class GameEngineCollision : public GameEngineTransformComponent
{
	friend class GameEngineCollisionFunctionInit;

	static bool (*collisionFunctions_[static_cast<int>(CollisionType::CT_Max)][static_cast<int>(CollisionType::CT_Max)])
		(const GameEngineTransform& _transformA, const GameEngineTransform& _transformB);

public:

	GameEngineCollision();
	~GameEngineCollision();

	GameEngineCollision(const GameEngineCollision& _other) = delete;
	GameEngineCollision(GameEngineCollision&& _other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _other) = delete;

public:
	void ChangeOrder(int _collisionOrder);
	//bool IsCollision(		//�浹 ���� ���� �Լ�.
	//	CollisionType _thisType,
	//	int _collisionGroup,
	//	CollisionType _otherType,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _update = nullptr,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _enter = nullptr,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _exit = nullptr
	//);

	bool IsCollided(		//�浹 ���� ���� �Լ�.
		CollisionType _thisType,
		int _collisionGroup,
		CollisionType _otherType,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _update = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _enter = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _exit = nullptr
	);
	
	virtual void DebugRender();	//�Լ� �̸����� �ٸ���, �����δ� �浹ü�� ���� �׸��� �ʰ� �׸��µ� �ʿ��� ������ �����ϴ� �Լ�.
	//�� �Լ����� ����� ������� GameEngineCoreDebug�� Debug3DRender()�Լ����� ��¥ �������� �Ѵ�.

	void SetUIDebugCamera();	//�� �ݸ����� �������� UIī�޶󿡼� �ϰ� �ϴ� �Լ�.
	//UIī�޶�� ���� �⺻���� ī�޶��̹Ƿ� ���� ���ؿ��� �׷� �����Լ��� ������ �� �ִ�.
public:
	template<typename EnumType>
	void ChangeOrder(EnumType _collisionOrder)
	{
		ChangeOrder(static_cast<int>(_collisionOrder));
	}

	template<typename EnumType>
	bool IsCollision(
		CollisionType _thisType,
		EnumType _collisionGroup,
		CollisionType _otherType,
		std::function<CollisionReturn(GameEngineCollision* _this,
			GameEngineCollision* _other)> _function = nullptr
	)
	{
		return IsCollided(_thisType, static_cast<int>(_collisionGroup), _otherType, _function);
	}

	bool IsCollisionEnterBase(
		CollisionType _thisType,
		int _groupOrder,
		CollisionType _otherType,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _enter = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _update = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _exit = nullptr
	)
	{
		return IsCollided(_thisType, _groupOrder, _otherType, _update, _enter, _exit);
	}

	bool IsCollisionExitBase(
		CollisionType _thisType,
		int _groupOrder,
		CollisionType _otherType,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _enter = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _update = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _exit = nullptr
	)
	{
		return IsCollided(_thisType, _groupOrder, _otherType, _update, _enter, _exit);
	}

	inline void SetDebugSetting(CollisionType _debugType, const float4& _color)
	{
		debugType_ = _debugType;
		color_ = _color;
	}

	inline void SetDebugCamera(CameraOrder _cameraOrder)
	{
		debugCameraOrder_ = _cameraOrder;
	}

	inline void SetCollisionMode(CollisionMode _mode)
	{
		collisionMode_ = _mode;
	}

	void OffEvent() override
	{
		ResetExData();
	}

	void ResetExData()
	{
		collisionCheck_.clear();
	}

private:
	void Start() override;


private:
	std::map<GameEngineCollision*, CollisionReturn> collisionCheck_;

	CollisionType debugType_;
	CollisionMode collisionMode_;

	float4 color_;
	CameraOrder debugCameraOrder_;

};

