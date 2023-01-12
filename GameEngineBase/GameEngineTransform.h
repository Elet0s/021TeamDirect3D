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
		//���� ���� �����Ͱ� �ʿ��� OBB�� �ʱ�ȭ�� �ϸ�, 
		// ���� �����͸� ���� ���Ͼ��� �ٸ� �����鵵 ���� �ʱ�ȭ�� �ȴ�
	{
	}

};

struct TransformData
{
	//�������� ���� �� �浹����.
	//Ʈ������ �⺻ ü��� �˾ƺ��� ���� 60�������� �����Ѵ�.

	float4 localScaleVector_;		//���� ��ǥ�� ũ��. ũ�Ⱑ 0�� ��ü�� ������ �� �����Ƿ� �⺻���� 1�� �Ǿ�� �Ѵ�.
	float4 localRotationVector_;	//���� ��ǥ�� ����(����).
	float4 localPositionVector_;	//���� ��ǥ�� �̵�(��ġ).

	float4x4 localScaleMatrix_;		//ũ�����.
	float4x4 localRotationMatrix_;	//�������(����/ȸ��). ���� ������ 3�� �������Ͱ� �־�� ȸ������� �ȴ�.
	float4x4 localPositionMatrix_;	//�̵����(��ġ).

	float4x4 localWorldMatrix_;
	//������Ʈ�� ũ��, ����, �̵������ �ݿ���, �θ� ������Ʈ�� ���ÿ���󿡼��� �������. ����� �߰�����.


	float4 worldScaleVector_;	//������ǥ�� ũ��. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
	float4 worldRotationVector_;	//������ǥ�� ȸ����. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
	float4 worldPositionVector_;	//������ǥ�� ��ġ. �̵����� �ݿ��ؾ� �ϹǷ� w�� 1���� �����Ѵ�.


	//������Ʈ�� ���� ũ��, ���� ����, ���� �̵���Ŀ� �θ��� ������ı��� �ݿ��� ���� ���� ���.
	float4x4 worldWorldMatrix_;
	//���⿡ ī�޶� ������Ʈ�� ����İ� ������ı��� ��ġ�� ���� ��μ� ����Ϳ� ��� �� �ְ� �ȴ�.
	//�θ��� ������ı��� �ݿ��ϸ鼭 �ڿ������� �������� �ݿ��ǹǷ� ���� �и��� ��������� ���� �ʿ䰡 ����.

	float4x4 viewMatrix_;		//�����.
	float4x4 projectionMatrix_;	//�������.

	float4x4 worldViewMatrix_;	//������Ŀ� ������� ����� ���.
	float4x4 worldViewProjectionMatrix_;	//������Ŀ� ����� + ������ı��� ����� ���.

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

	//���� ��������� ����ϴ� �Լ�. 
	void CalculateWorldMatrix();
	// Ʈ������ ������ �Ͼ ������ �Ź� ȣ��Ǿ� 
	// �ڱ� �ڽŰ� �ڽ� Ʈ���������� ������ı��� ���� ����ϹǷ� 
	// �� �̻� �ٸ� ������ ������� ����� �� �ʿ䰡 ����.

	//������� * ����� * �������.
	void CalculateWorldViewProjection();

	//�ڱ� �ڽ��� Ʈ�������� �θ� ������Ʈ�� Ʈ�������� ���̴� �Լ�.
	void SetParentTransform(GameEngineTransform& _newParent);

	//�ڱ� �ڽ��� Ʈ�������� �θ� ������Ʈ�� Ʈ���������� ����� �Լ�.
	void DetachTransform();

	//
	void PixLocalNegativeX();

	//
	void PixLocalPositiveX();

	void Copy(const GameEngineTransform& _transform);


public:
	//�浹 �Լ���.

	static bool SphereToSphere(const GameEngineTransform& _sphereA, const GameEngineTransform& _sphereB);
	static bool AABBToAABB(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);
	static bool OBBToOBB(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);

	static bool Sphere2DToSphere2D(const GameEngineTransform& _sphereA, const GameEngineTransform& _sphereB);
	static bool AABB2DToAABB2D(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);
	static bool OBB2DToOBB2D(const GameEngineTransform& _boxA, const GameEngineTransform& _boxB);

	static bool AABB2DToSphere2D(const GameEngineTransform& _box, const GameEngineTransform& _circle);
	static bool Sphere2DToAABB2D(const GameEngineTransform& _circle, const GameEngineTransform& _box);

public:
	//���������� Ư�� ������Ʈ�� ũ�⸦ ��ȭ��Ű�� �Լ�.
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
		//ȸ�� ������ �������� �ص� �� ������ 60�й����� �Ѵ�.
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
		//ȸ�� ������ �������� �ص� �� ������ 60�й����� �Ѵ�.
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


	//��������: ����� ���� �̷�� 3���� ����. ���� ������ 3�� �������Ͱ� �־�� ȸ������� �ȴ�.

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

	//�ݸ��� ���� ���� �Լ���.

	void CollisionScaleSetting();		
	void CollisionRotationSetting();	
	void CollisionPositionSetting();	
	void CollisionDataSetting();		


private:
	void CalculateWorldScale(const float4& _localScaleVector)
	{
		data_.localScaleVector_ = _localScaleVector;
		data_.localScaleVector_.w = 0.f;	//�̵� ��� ����.
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
		data_.localScaleVector_.w = 0.f;			//�̵� ��� ����.
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
		data_.localRotationVector_.w = 0.f;	//�̵� ��� ����.
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
		data_.localRotationVector_.w = 0.f;	//�̵� ��� ����.
		//ȸ�� ������ �������� �ص� �� ������ 60�й����� �Ѵ�.
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
		data_.localPositionVector_.w = 1.f;	//�̵� ��� ����.
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
		data_.localPositionVector_.w = 1.f;	//�̵� ��� ����.
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

	GameEngineTransform* parentTransform_;	//�θ� ������Ʈ�� Ʈ������.

	std::list<GameEngineTransform*> childTranforms_;	//�ڽ� ������Ʈ���� Ʈ��������.

	CollisionData collisionDataObject_;

	//Ʈ�������� ��� ����ϴ� ����:
	//1. ��Ȥ �ﰢ���� ������ �䱸�� ���� �־(Ư�� �浹����).
	//2. ����ȭ���ٴ� �������� �� �Ű��� ������.
	//3. ����ȭ�� �ص� ������ ������ ��� �������� ���� �������� �ʾƼ�.

};

