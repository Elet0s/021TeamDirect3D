#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

enum class CollisionMode	//상대 충돌체별 충돌 횟수.
{
	Single,		//한 충돌체와는 한번만 충돌.	normal
	Multiple	//중복충돌 허용.	ex
};

enum class CollisionReturn	//충돌 이후 반응
{
	Continue,	//계속 충돌 가능한 상태 유지.
	Stop		//충돌했던 충돌체와의 충돌 중단.
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
	//bool IsCollision(		//충돌 여부 판정 함수.
	//	CollisionType _thisType,
	//	int _collisionGroup,
	//	CollisionType _otherType,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _update = nullptr,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _enter = nullptr,
	//	std::function<CollisionReturn(std::shared_ptr<GameEngineCollision> _this, std::shared_ptr<GameEngineCollision> _other)> _exit = nullptr
	//);

	bool IsCollided(		//충돌 여부 판정 함수.
		CollisionType _thisType,
		int _collisionGroup,
		CollisionType _otherType,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _update = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _enter = nullptr,
		std::function<CollisionReturn(GameEngineCollision* _this, GameEngineCollision* _other)> _exit = nullptr
	);
	
	virtual void DebugRender();	//함수 이름과는 다르게, 실제로는 충돌체를 직접 그리지 않고 그리는데 필요한 정보만 저장하는 함수.
	//이 함수에서 저장된 정보대로 GameEngineCoreDebug의 Debug3DRender()함수에서 진짜 렌더링을 한다.

	void SetUIDebugCamera();	//이 콜리전의 렌더링을 UI카메라에서 하게 하는 함수.
	//UI카메라는 엔진 기본제공 카메라이므로 엔진 수준에서 그런 편의함수를 제공할 수 있다.
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

