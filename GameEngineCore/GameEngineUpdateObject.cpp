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

void GameEngineUpdateObject::SetParent(GameEngineUpdateObject* _newParent)
{
	DetachObject();

	parent_ = _newParent;
	parent_->children_.push_back(this);
}

void GameEngineUpdateObject::ReleaseHierarchy()
{
	for (std::list<GameEngineUpdateObject*>::iterator iter = children_.begin();
		iter != children_.end(); iter++)
	{
		if (nullptr != (*iter))
		{
			(*iter)->ReleaseHierarchy();	
			//���̻��� �ڽ��� ���������� ��� ������� ReleaseHierarchy()�Լ��� ��� ȣ���Ѵ�.
		}
	}

	//�� �̻��� �ڽ��� ���ٸ� �Լ� ȣ���� ���߰� ������� �����´�.
	delete this;	//�� �����ӿ�ũ���� ��¥�� ������Ʈ�� �޸������� �ϴ� �κ�.
}

void GameEngineUpdateObject::AllUpdate(float _deltaTime)
{
	this->AddAccTime(_deltaTime);
	this->ReleaseUpdate(_deltaTime);	 //deadTime_�� 0�� �� ������Ʈ�鿡�� ��� ������ ������.
	this->Update(GameEngineTime::GetInst().GetTimeScale(this->GetOrder()) * _deltaTime);

	for (GameEngineUpdateObject* child : children_)
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

	for (GameEngineUpdateObject* child : children_)
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

	for (GameEngineUpdateObject* child : children_)
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

	for (GameEngineUpdateObject* child : children_)
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

	for (GameEngineUpdateObject* child : children_)
	{
		if (true == child->IsUpdate())
		{
			child->AllOffEvent();
		}
	}
}

void GameEngineUpdateObject::ReleaseObject(std::list<GameEngineUpdateObject*>& _releaseList)
{
	//�ڱ� �ڽ��� (true == IsDead())���� == ��������� �޾Ҵ��� Ȯ���Ѵ�.
	if (true == this->IsDead())
		//�ڱ� �ڽŸ� Ȯ���ϴ� isDead_ ������ �ƴ϶� �θ���� Ȯ���ϴ� IsDead()�Լ��� Ȯ���ؾ� �Ѵ�.
	{
		DetachObject();		//����������� ��� ������Ʈ���� �θ� ������Ʈ�� chlidren����Ʈ���� �����Ѵ�.
		_releaseList.push_back(this);
		//����������� ��� ������Ʈ���� �ش� ������ _releaseObjects�� �ִ´�.

		return;	//�Ʒ��� �������� ���� �ٷ� �Լ� ����.
	}

	//this�� isDead�� false�� ������� ���� �Դٸ� �ڽ� ������Ʈ�� �� ����������� ������Ʈ�� �ִ��� Ž���Ѵ�.
	for (std::list<GameEngineUpdateObject*>::iterator iter = children_.begin();
		iter != children_.end(); /*iter++*/)
	{
		if (true == (*iter)->IsDead())
		{
			//�ڽ� ������Ʈ�� �� ����������� ������Ʈ�� �ִٸ�,
			_releaseList.push_back((*iter));	//_releaseObjects�� �־� ���� ������� ����Ѵ�.

			GameEngineUpdateObject* deleteObject = (*iter);
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
	if (nullptr != parent_)
	{
		parent_->children_.remove(this);
	}
}