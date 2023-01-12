#pragma once
#include "GameEngineMath.h"
#include "GameEngineDebugObject.h"

enum class CollisionType
{
	CT_Point2D,
	CT_Sphere2D,
	CT_AABB2D,
	CT_OBB2D,

	CT_Point,
	CT_Sphere,
	CT_AABB,
	CT_OBB,
	CT_Max
};

class CollisionData
{
	friend class GameEngineTransform;

	union
	{
		DirectX::BoundingSphere sphere_;
		DirectX::BoundingBox aabb_;
		DirectX::BoundingOrientedBox obb_;
	};

	CollisionData() : obb_()
		//가장 많은 데이터가 필요한 OBB로 초기화를 하면, 
		// 같은 데이터를 쓰는 유니언의 다른 변수들도 같이 초기화가 된다
	{
	}

};

struct TransformData
{
	//공간정보 저장 및 충돌판정.
	//트랜스폼 기본 체계는 알아보기 쉽게 60도법으로 저장한다.

	float4 localScaleVector_;		//로컬 좌표상 크기. 크기가 0인 물체는 존재할 수 없으므로 기본값이 1이 되어야 한다.
	float4 localRotationVector_;	//로컬 좌표상 자전(각도).
	float4 localPositionVector_;	//로컬 좌표상 이동(위치).

	float4x4 localScaleMatrix_;		//크기행렬.
	float4x4 localRotationMatrix_;	//자전행렬(각도/회전). 서로 수직인 3개 기저벡터가 있어야 회전행렬이 된다.
	float4x4 localPositionMatrix_;	//이동행렬(위치).

	float4x4 localWorldMatrix_;
	//오브젝트의 크기, 자전, 이동행렬이 반영된, 부모 오브젝트의 로컬월드상에서의 월드행렬. 행렬의 중간정산.


	float4 worldScaleVector_;	//월드좌표상 크기. 이동하지 않으므로 w는 0으로 설정한다.
	float4 worldRotationVector_;	//월드좌표상 회전량. 이동하지 않으므로 w는 0으로 설정한다.
	float4 worldPositionVector_;	//월드좌표상 위치. 이동량을 반영해야 하므로 w는 1으로 설정한다.


	//오브젝트의 로컬 크기, 로컬 자전, 로컬 이동행렬에 부모의 월드행렬까지 반영된 최종 월드 행렬.
	float4x4 worldWorldMatrix_;
	//여기에 카메라 컴포넌트의 뷰행렬과 투영행렬까지 거치고 나야 비로소 모니터에 띄울 수 있게 된다.
	//부모의 월드행렬까지 반영하면서 자연스럽게 공전까지 반영되므로 따로 분리된 공전행렬을 만들 필요가 없다.

	float4x4 viewMatrix_;		//뷰행렬.
	float4x4 projectionMatrix_;	//투영행렬.

	float4x4 worldViewMatrix_;	//월드행렬에 뷰행렬이 적용된 행렬.
	float4x4 worldViewProjectionMatrix_;	//월드행렬에 뷰행렬 + 투영행렬까지 적용된 행렬.

public:
	TransformData()
		: localScaleVector_(1, 1, 1, 0),
		localRotationVector_(float4::Zero),
		localPositionVector_(float4::Black),
		worldScaleVector_(1, 1, 1, 0),
		worldRotationVector_(float4::Zero),
		worldPositionVector_(float4::Black)
	{
	}


};

class GameEngineTransform: public GameEngineDebugObject
{


public:

	GameEngineTransform();
	~GameEngineTransform();

	GameEngineTransform(const GameEngineTransform& _other) = delete;
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _other) = delete;


public: 

	//최종 월드행렬을 계산하는 함수. 
	void CalculateWorldMatrix();
	// 트랜스폼 변경이 일어날 때마다 매번 호출되어 
	// 자기 자신과 자식 트랜스폼들의 월드행렬까지 전부 계산하므로 
	// 더 이상 다른 곳에서 월드행렬 계산을 할 필요가 없다.

	//월드행렬 * 뷰행렬 * 투영행렬.
	void CalculateWorldViewProjection();

	//자기 자신의 트랜스폼을 부모 오브젝트의 트랜스폼에 붙이는 함수.
	void SetParentTransform(GameEngineTransform& _newParent);

	//자기 자신의 트랜스폼을 부모 오브젝트의 트랜스폼에서 떼어내는 함수.
	void DetachTransform();

	//
	void PixLocalNegativeX();

	//
	void PixLocalPositiveX();

	void Copy(const GameEngineTransform& _transform);


public:
	//충돌 함수들.

	static bool SphereToSphere(const GameEngineTransform& _sphereA, const GameEngineTransform& _sphereB);
	static bool AABBToAABB(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);
	static bool OBBToOBB(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);

	static bool Sphere2DToSphere2D(const GameEngineTransform& _sphereA, const GameEngineTransform& _sphereB);
	static bool AABB2DToAABB2D(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);
	static bool OBB2DToOBB2D(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);

	static bool AABB2DToSphere2D(const GameEngineTransform& _box, const GameEngineTransform& _circle);
	static bool Sphere2DToAABB2D(const GameEngineTransform& _circle, const GameEngineTransform& _box);

public:
	//점차적으로 특정 오브젝트의 크기를 변화시키는 함수.
	inline void AddLocalScale(const float4& _scaleValue)
	{
		SetLocalScale(data_.localScaleVector_ + _scaleValue);
	}

	inline void SetLocalScale(const float4& _localScale)
	{
		CalculateWorldScale(_localScale);
	}
	inline void SetLocalScale(float _localScaleX, float _localScaleY, float _localScaleZ)
	{
		CalculateWorldScale(_localScaleX, _localScaleY, _localScaleZ);
	}
	inline void SetLocalScale(int _localScaleX, int _localScaleY, int _localScaleZ)
	{
		CalculateWorldScale(
			static_cast<float>(_localScaleX),
			static_cast<float>(_localScaleY),
			static_cast<float>(_localScaleZ)
		);
	}


	inline void SetLocalRotation(const float4& _degreeVector)
	{
		CalculateWorldRotation(_degreeVector);
	}
	inline void SetLocalRotationByRadian(const float4& _radianVector)
	{	
		CalculateWorldRotation(_radianVector * GameEngineMath::RadianToDegree);
		//회전 실행은 라디안으로 해도 값 저장은 60분법으로 한다.
	}
	inline void SetLocalRotation(float _degreeX, float _degreeY, float _degreeZ)
	{
		CalculateWorldRotation(_degreeX, _degreeY, _degreeZ);
	}
	inline void SetLocalRotationByRadian(float _radianX, float _radianY, float _radianZ)
	{
		CalculateWorldRotation(
				_radianX * GameEngineMath::RadianToDegree,
				_radianY * GameEngineMath::RadianToDegree,
				_radianZ * GameEngineMath::RadianToDegree
		);
		//회전 실행은 라디안으로 해도 값 저장은 60분법으로 한다.
	}


	inline void SetLocalPosition(const float4& _positionVector)
	{
		CalculateWorldPosition(_positionVector);
	}
	inline void SetLocalPosition(float _positionX, float _positionY, float _positionZ)
	{
		CalculateWorldPosition(_positionX, _positionY, _positionZ);
	}
	inline void SetLocalPosition(int _positionX, int _positionY, int _positionZ)
	{
		CalculateWorldPosition(
			static_cast<float>(_positionX),
			static_cast<float>(_positionY),
			static_cast<float>(_positionZ)
		);
	}

	inline void SetLocalMove(const float4& _distance)
	{
		SetLocalPosition(this->data_.localPositionVector_ + _distance);
	}
	inline void SetLocalRotating(const float4& _rotation)
	{
		SetLocalRotation(this->data_.localRotationVector_ + _rotation);
	}


public:
	inline void SetWorldScale(const float4& _worldScale)
	{
		float4 newLocalScale = _worldScale;
		if (nullptr != parentTransform_)
		{
			newLocalScale /= parentTransform_->data_.worldScaleVector_;
		}

		CalculateWorldScale(newLocalScale);
	}
	inline void SetWorldScale(float _worldScaleX, float _worldScaleY, float _worldScaleZ)
	{
		float newLocalScaleX = _worldScaleX;
		float newLocalScaleY = _worldScaleY;
		float newLocalScaleZ = _worldScaleZ;
		if (nullptr != parentTransform_)
		{
			newLocalScaleX /= parentTransform_->data_.worldScaleVector_.x;
			newLocalScaleY /= parentTransform_->data_.worldScaleVector_.y;
			newLocalScaleZ /= parentTransform_->data_.worldScaleVector_.z;
		}

		CalculateWorldScale(
			newLocalScaleX,
			newLocalScaleY,
			newLocalScaleZ
		);
	}

	inline void SetWorldRotation(const float4& _worldRotation)
	{
		float4 newLocalRotation = _worldRotation;
		if (nullptr != parentTransform_)
		{
			newLocalRotation -= parentTransform_->data_.worldRotationVector_;
		}

		CalculateWorldRotation(newLocalRotation);
	}
	inline void SetWorldRotation(float _worldRotationX, float _worldRotationY, float _worldRotationZ)
	{
		float newLocalRotationX = _worldRotationX;
		float newLocalRotationY = _worldRotationY;
		float newLocalRotationZ = _worldRotationZ;
		if (nullptr != parentTransform_)
		{
			newLocalRotationX -= parentTransform_->data_.worldRotationVector_.x;
			newLocalRotationY -= parentTransform_->data_.worldRotationVector_.y;
			newLocalRotationZ -= parentTransform_->data_.worldRotationVector_.z;
		}

		CalculateWorldRotation(newLocalRotationX, newLocalRotationY, newLocalRotationZ);
	}

	inline void SetAddWorldRotation(const float4& _world)	
	{
		SetWorldRotation(data_.worldRotationVector_ + _world);
	}

	inline void SetWorldPosition(const float4& _worldPosition)
	{
		float4 newLocalPosition = _worldPosition;
		if (nullptr != parentTransform_)
		{
			newLocalPosition *= parentTransform_->data_.worldWorldMatrix_.InverseReturn();
		}

		CalculateWorldPosition(newLocalPosition);
	}
	inline void SetWorldPosition(float _worldPositionX, float _worldPositionY, float _worldPositionZ)
	{
		float4 newLocalPosition = { _worldPositionX, _worldPositionY, _worldPositionZ };
		if (nullptr != parentTransform_)
		{
			newLocalPosition *= parentTransform_->data_.worldWorldMatrix_.InverseReturn();
		}

		CalculateWorldPosition(newLocalPosition);
	}

	inline void SetWorldMove(const float4& _distance)
	{
		SetWorldPosition(this->data_.worldPositionVector_ + _distance);
	}
	inline void SetWorldForwardMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetForwardVector() * _speed * _deltaTime));
	}
	inline void SetWorldBackMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetBackVector() * _speed * _deltaTime));
	}
	inline void SetWorldUpMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetUpVector() * _speed * _deltaTime));
	}
	inline void SetWorldDownMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetDownVector() * _speed * _deltaTime));
	}
	inline void SetWorldLeftMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetLeftVector() * _speed * _deltaTime));
	}
	inline void SetWorldRightMove(const float _speed, const float _deltaTime)
	{
		SetWorldPosition(data_.worldPositionVector_ + (GetRightVector() * _speed * _deltaTime));
	}



public:

	const TransformData& GetTransformData() const
	{
		return data_;
	}

	const float4& GetLocalScale() const 
	{
		return data_.localScaleVector_;
	}
	const float4& GetLocalRotation() const 
	{
		return data_.localRotationVector_;
	}
	const float4& GetLocalPosition() const
	{
		return data_.localPositionVector_;
	}
	const float4& GetWorldScale() const 
	{
		return data_.worldScaleVector_;
	}
	const float4& GetWorldRotation() const 
	{
		return data_.worldRotationVector_;
	}
	const float4& GetWorldPosition() const
	{
		return data_.worldPositionVector_;
	}

	const float4x4& GetLocalWorld() const
	{
		return data_.localWorldMatrix_;
	}
	const float4x4& GetWorldWorld() const
	{
		return data_.worldWorldMatrix_;
	}
	const float4x4& GetWorldViewProjection() const
	{
		return data_.worldViewProjectionMatrix_;
	}


	//기저벡터: 행렬의 축을 이루는 3개의 벡터. 서로 수직인 3개 기저벡터가 있어야 회전행렬이 된다.

	inline float4 GetForwardVector() const
	{
		return float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[2]);
	}
	inline float4 GetUpVector() const
	{
		return float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[1]);
	}	
	inline float4 GetRightVector() const
	{
		return float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[0]);
	}

	inline float4 GetBackVector() const
	{
		return -(float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[2]));
	}
	inline float4 GetDownVector() const
	{
		return -(float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[1]));
	}	
	inline float4 GetLeftVector() const
	{
		return -(float4::Normalize3DReturn(data_.worldWorldMatrix_.arrVector[0]));
	}

	inline void SetViewMatrix(const float4x4& _viewMatrix)
	{
		data_.viewMatrix_ = _viewMatrix;
	}
	inline void SetProjectionMatrix(const float4x4& _projectionMatrix)
	{
		data_.projectionMatrix_ = _projectionMatrix;
	}

	inline const float4x4& GetViewMatrix() const
	{
		return data_.viewMatrix_;
	}
	inline const float4x4& GetProjectionMatrix() const
	{
		return data_.projectionMatrix_;
	}
	

protected:
	virtual void Start() {}
	virtual void Update(float _deltaTime) {}
	virtual void End() {}


private:

	//콜리전 정보 갱신 함수들.

	void CollisionScaleSetting();		
	void CollisionRotationSetting();	
	void CollisionPositionSetting();	
	void CollisionDataSetting();		


private:
	void CalculateWorldScale(const float4& _localScaleVector)
	{
		data_.localScaleVector_ = _localScaleVector;
		data_.localScaleVector_.w = 0.f;	//이동 계산 제외.
		if (nullptr == parentTransform_)
		{
			data_.worldScaleVector_ = this->data_.localScaleVector_;
		}
		else
		{
			data_.worldScaleVector_ = this->data_.localScaleVector_ * parentTransform_->data_.worldScaleVector_;
		}

		data_.localScaleMatrix_.Scale(data_.localScaleVector_);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldScale(child->data_.localScaleVector_);
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}
		CollisionDataSetting();
	}	
	void CalculateWorldScale(float _localScaleX, float _localScaleY, float _localScaleZ)
	{
		
		data_.localScaleVector_.x = _localScaleX;
		data_.localScaleVector_.y = _localScaleY;
		data_.localScaleVector_.z = _localScaleZ;
		data_.localScaleVector_.w = 0.f;			//이동 계산 제외.
		if (nullptr == parentTransform_)
		{
			this->data_.worldScaleVector_ = this->data_.localScaleVector_;
		}
		else
		{
			this->data_.worldScaleVector_ = this->data_.localScaleVector_ * parentTransform_->data_.worldScaleVector_;
		}


		data_.localScaleMatrix_.Scale(
			data_.localScaleVector_.x,
			data_.localScaleVector_.y,
			data_.localScaleVector_.z
		);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldScale(child->data_.localScaleVector_);
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}	
		CollisionDataSetting();
	}	
	
	void CalculateWorldRotation(const float4& _localRotationVector)
	{
		data_.localRotationVector_ = _localRotationVector;
		data_.localRotationVector_.w = 0.f;	//이동 계산 제외.
		if (nullptr == parentTransform_)
		{
			data_.worldRotationVector_ = this->data_.localRotationVector_;
		}
		else
		{
			data_.worldRotationVector_ = this->data_.localRotationVector_ + parentTransform_->data_.worldRotationVector_;
		}


		data_.localRotationMatrix_.Rotate3AxisByDegree(data_.localRotationVector_);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldRotation(child->data_.localRotationVector_);
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}
		CollisionDataSetting();
	}	
	void CalculateWorldRotation(float _degreeX, float _degreeY, float _degreeZ)
	{
		data_.localRotationVector_.x = _degreeX;
		data_.localRotationVector_.y = _degreeY;
		data_.localRotationVector_.z = _degreeZ;
		data_.localRotationVector_.w = 0.f;	//이동 계산 제외.
		//회전 실행은 라디안으로 해도 값 저장은 60분법으로 한다.
		if (nullptr == parentTransform_)
		{
			data_.worldRotationVector_ = this->data_.localRotationVector_;
		}
		else
		{
			data_.worldRotationVector_ = this->data_.localRotationVector_ + parentTransform_->data_.worldRotationVector_;
		}


		data_.localRotationMatrix_.Rotate3AxisByDegree(
			data_.localRotationVector_.x,
			data_.localRotationVector_.y,
			data_.localRotationVector_.z
		);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldRotation(child->data_.localRotationVector_);
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}
		CollisionDataSetting();
	}	
	
	void CalculateWorldPosition(const float4& _localPositionVector)
	{
		data_.localPositionVector_ = _localPositionVector;
		data_.localPositionVector_.w = 1.f;	//이동 계산 포함.
		if (nullptr == parentTransform_)
		{
			data_.worldPositionVector_ = this->data_.localPositionVector_;
		}
		else
		{
			data_.worldPositionVector_ = this->data_.localPositionVector_ * parentTransform_->data_.worldWorldMatrix_;
		}


		data_.localPositionMatrix_.Position(data_.localPositionVector_);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}
		CollisionDataSetting();

	}
	void CalculateWorldPosition(float _positionX, float _positionY, float _positionZ)
	{
		data_.localPositionVector_.x = _positionX;
		data_.localPositionVector_.y = _positionY;
		data_.localPositionVector_.z = _positionZ;
		data_.localPositionVector_.w = 1.f;	//이동 계산 포함.
		if (nullptr == parentTransform_)
		{
			data_.worldPositionVector_ = this->data_.localPositionVector_;
		}
		else
		{
			data_.worldPositionVector_ = this->data_.localPositionVector_ * parentTransform_->data_.worldWorldMatrix_;
		}


		data_.localPositionMatrix_.Position(
			data_.localPositionVector_.x,
			data_.localPositionVector_.y,
			data_.localPositionVector_.z
		);
		CalculateWorldMatrix();

		for (GameEngineTransform* child : childTranforms_)
		{
			child->CalculateWorldPosition(child->data_.localPositionVector_);
		}
		CollisionDataSetting();
	}


private:
	TransformData data_;

	GameEngineTransform* parentTransform_;	//부모 오브젝트의 트랜스폼.

	std::list<GameEngineTransform*> childTranforms_;	//자식 컴포넌트들의 트랜스폼들.

	CollisionData collisionDataObject_;

	//트랜스폼을 즉시 계산하는 이유:
	//1. 간혹 즉각적인 반응을 요구할 때가 있어서(특히 충돌관련).
	//2. 최적화보다는 가독성을 더 신경썼기 때문에.
	//3. 최적화를 해도 낮아진 가독성 대비 생각보다 많이 빨라지지 않아서.

};

