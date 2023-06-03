#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: data_(),
	parentTransform_(nullptr),
	childTranforms_(),
	collisionDataObject_()
{
	CollisionDataSetting();
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::CalculateWorldMatrix()
{
	data_.localWorldMatrix_ = data_.localScaleMatrix_ * data_.localRotationMatrix_ * data_.localPositionMatrix_;
	//크기와 회전이 바뀌면: 크기와 회전이 서로 영향을 주고 받아서 크기만 변경해도 회전을 하고, 
	// 회전만 시켜도 크기가 변경된다.
	//이동 후 회전을 하면: 이동한 만큼 중심점에서 멀어진 상태로 자전이 아닌 공전을 한다.
	//이동 후 크기변경을 하면: 크기변경값이 이동행렬에 적용되어 이동값 * 크기값만큼 
	// 이동한 위치에 오브젝트가 생성된다.

	if (nullptr == parentTransform_)
	{
		data_.worldWorldMatrix_ = data_.localWorldMatrix_;
	}
	else
	{
		data_.worldWorldMatrix_ = this->data_.localWorldMatrix_ * parentTransform_->GetWorldWorld();
	}

	//자식의 자식 트랜스폼들도 월드행렬 계산을 해준다.
	for (GameEngineTransform* const child : childTranforms_)
	{
		child->CalculateWorldMatrix();
	}
}

void GameEngineTransform::CalculateWorldViewProjection()
{
	this->data_.worldViewMatrix_ = data_.worldWorldMatrix_ * data_.viewMatrix_;
	this->data_.worldViewProjectionMatrix_ = data_.worldViewMatrix_ * data_.projectionMatrix_;
}

void GameEngineTransform::SetParentTransform(GameEngineTransform& _newParent)
{
	if (nullptr != parentTransform_)
	{
		parentTransform_->childTranforms_.remove(this);
		parentTransform_ = nullptr;
	}

	parentTransform_ = &_newParent;
	parentTransform_->childTranforms_.push_back(this);

	SetLocalScale(this->data_.localScaleVector_);
	SetLocalRotation(this->data_.localRotationVector_);
	SetLocalPosition(this->data_.localPositionVector_);
}

void GameEngineTransform::DetachTransform()
{
	if (nullptr == parentTransform_)
	{
		return;
	}

	parentTransform_->childTranforms_.remove(this);
	parentTransform_ = nullptr;
}

void GameEngineTransform::PixLocalNegativeX()
{
	if (0.f > data_.localScaleVector_.x)	//이미 x좌표가 -이므로 함수 실행하지 않음.
	{
		return;
	}

	data_.localScaleVector_.x = -data_.localScaleVector_.x;

	SetLocalScale(data_.localScaleVector_);
}

void GameEngineTransform::PixLocalPositiveX()
{
	if (0.f < data_.localScaleVector_.x)	//이미 x좌표가 +이므로 함수 실행하지 않음.
	{
		return;
	}

	data_.localScaleVector_.x = abs(data_.localScaleVector_.x);

	SetLocalScale(data_.localScaleVector_);
}

void GameEngineTransform::Copy(const GameEngineTransform& _transform)
{
	this->data_ = _transform.data_;
	this->collisionDataObject_ = _transform.collisionDataObject_;
	this->parentTransform_ = _transform.parentTransform_;
	this->childTranforms_ = _transform.childTranforms_;

	CalculateWorldScale(this->data_.localScaleVector_);
	CalculateWorldRotation(this->data_.localRotationVector_);
	CalculateWorldPosition(this->data_.localPositionVector_);
	CalculateWorldMatrix();
}


