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
	//ũ��� ȸ���� �ٲ��: ũ��� ȸ���� ���� ������ �ְ� �޾Ƽ� ũ�⸸ �����ص� ȸ���� �ϰ�, 
	// ȸ���� ���ѵ� ũ�Ⱑ ����ȴ�.
	//�̵� �� ȸ���� �ϸ�: �̵��� ��ŭ �߽������� �־��� ���·� ������ �ƴ� ������ �Ѵ�.
	//�̵� �� ũ�⺯���� �ϸ�: ũ�⺯�氪�� �̵���Ŀ� ����Ǿ� �̵��� * ũ�Ⱚ��ŭ 
	// �̵��� ��ġ�� ������Ʈ�� �����ȴ�.

	if (nullptr == parentTransform_)
	{
		data_.worldWorldMatrix_ = data_.localWorldMatrix_;
	}
	else
	{
		data_.worldWorldMatrix_ = this->data_.localWorldMatrix_ * parentTransform_->GetWorldWorld();
	}

	//�ڽ��� �ڽ� Ʈ�������鵵 ������� ����� ���ش�.
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
	if (0.f > data_.localScaleVector_.x)	//�̹� x��ǥ�� -�̹Ƿ� �Լ� �������� ����.
	{
		return;
	}

	data_.localScaleVector_.x = -data_.localScaleVector_.x;

	SetLocalScale(data_.localScaleVector_);
}

void GameEngineTransform::PixLocalPositiveX()
{
	if (0.f < data_.localScaleVector_.x)	//�̹� x��ǥ�� +�̹Ƿ� �Լ� �������� ����.
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


