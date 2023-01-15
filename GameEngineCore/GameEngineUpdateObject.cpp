#include "PreCompile.h"
#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject()
	: order_(0),
	isReleaseUpdate_(false),
	deadTime_(0.f),
	accTime_(0.f),
	isUpdate_(true),
	isDead_(false),
	parent_()
{
}

GameEngineUpdateObject::~GameEngineUpdateObject()
{
}

void GameEngineUpdateObject::SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent)
{
	DetachObject();

	parent_ = _newParent;
	parent_.lock()->children_.push_back(shared_from_this());
}

void GameEngineUpdateObject::ReleaseHierarchy()
{
	//for (std::list<GameEngineUpdateObject*>::iterator iter = children_.begin();
	//	iter != children_.end(); iter++)
	//{
	//	if (nullptr != (*iter))
	//	{
	//		(*iter)->ReleaseHierarchy();	
	//		//���̻��� �ڽ��� ���������� ��� ������� ReleaseHierarchy()�Լ��� ��� ȣ���Ѵ�.
	//	}
	//}

	////�� �̻��� �ڽ��� ���ٸ� �Լ� ȣ���� ���߰� ������� �����´�.
	//delete this;	//�� �����ӿ�ũ���� ��¥�� ������Ʈ�� �޸������� �ϴ� �κ�.
}

void GameEngineUpdateObject::AllUpdate(float _deltaTime)
{
	this->AddAccTime(_deltaTime);
	this->ReleaseUpdate(_deltaTime);	 //deadTime_�� 0�� �� ������Ʈ�鿡�� ��� ������ ������.
	this->Update(GameEngineTime::GetInst().GetTimeScale(this->GetOrder()) * _deltaTime);

	for (std::shared_ptr<GameEngineUpdateObject> child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllUpdate(_deltaTime);
		}
	}
}

void GameEngineUpdateObject::AllLevelStartEvent()
{
	this->LevelStartEvent();

	for (std::shared_ptr<GameEngineUpdateObject> child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllLevelStartEvent();
		}
	}
}

void GameEngineUpdateObject::AllLevelEndEvent()
{
	this->LevelEndEvent();

	for (std::shared_ptr<GameEngineUpdateObject> child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllLevelEndEvent();
		}
	}
}

void GameEngineUpdateObject::AllOnEvent()
{
	this->OnEvent();

	for (std::shared_ptr<GameEngineUpdateObject> child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllOnEvent();
		}
	}
}

void GameEngineUpdateObject::AllOffEvent()
{
	this->OffEvent();

	for (std::shared_ptr<GameEngineUpdateObject> child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllOffEvent();
		}
	}
}

void GameEngineUpdateObject::ReleaseObject(std::list<std::shared_ptr<GameEngineUpdateObject>>& _releaseList)
{
	//�ڱ� �ڽ��� (true == IsDead())���� == ��������� �޾Ҵ��� Ȯ���Ѵ�.
	if (true == shared_from_this()->IsDead())
		//�ڱ� �ڽŸ� Ȯ���ϴ� isDead_ ������ �ƴ϶� �θ���� Ȯ���ϴ� IsDead()�Լ��� Ȯ���ؾ� �Ѵ�.
	{
		DetachObject();		//����������� ��� ������Ʈ���� �θ� ������Ʈ�� chlidren����Ʈ���� �����Ѵ�.
		_releaseList.push_back(shared_from_this());
		//����������� ��� ������Ʈ���� �ش� ������ _releaseObjects�� �ִ´�.

		return;	//�Ʒ��� �������� ���� �ٷ� �Լ� ����.
	}

	//this�� isDead�� false�� ������� ���� �Դٸ� �ڽ� ������Ʈ�� �� ����������� ������Ʈ�� �ִ��� Ž���Ѵ�.
	for (std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator iter = children_.begin();
		iter != children_.end(); /*iter++*/)
	{
		if (true == (*iter)->IsDead())
		{
			//�ڽ� ������Ʈ�� �� ����������� ������Ʈ�� �ִٸ�,
			_releaseList.push_back((*iter));	//_releaseObjects�� �־� ���� ������� ����Ѵ�.

			std::shared_ptr<GameEngineUpdateObject> deleteObject = (*iter);
			++iter;	//chlidren����Ʈ���� ������Ʈ�� �����ϱ� ���� ���ͷ����͸� ���� �̵����ѳ��� ������,
			//���ͷ����Ͱ� ���� ���� �̵��� �� ����.

			deleteObject->DetachObject();	//�θ� ������Ʈ�� chlidren����Ʈ���� �����Ѵ�.
		}
		else
		{
			//�ڽ� ������Ʈ�� �� ����������� ������Ʈ�� ���ٸ� �ڽ��� �ڽĵ���� ��� ������� ���� Ž���Ѵ�.
			(*iter)->ReleaseObject(_releaseList);
			++iter;
		}
	}

}

void GameEngineUpdateObject::DetachObject()
{
	if (nullptr != parent_.lock())
	{
		parent_.lock()->children_.remove(shared_from_this());
	}
}