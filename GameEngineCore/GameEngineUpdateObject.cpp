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
			//더이상의 자식이 없을때까지 재귀 방식으로 ReleaseHierarchy()함수를 계속 호출한다.
		}
	}

	//더 이상의 자식이 없다면 함수 호출을 멈추고 여기까지 내려온다.
	delete this;	//이 프레임워크에서 진짜로 오브젝트의 메모리해제를 하는 부분.
}

void GameEngineUpdateObject::AllUpdate(float _deltaTime)
{
	this->AddAccTime(_deltaTime);
	this->ReleaseUpdate(_deltaTime);	 //deadTime_이 0이 된 오브젝트들에게 사망 판정을 내린다.
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
	//자기 자신이 (true == IsDead())인지 == 사망판정을 받았는지 확인한다.
	if (true == this->IsDead())
		//자기 자신만 확인하는 isDead_ 변수가 아니라 부모까지 확인하는 IsDead()함수로 확인해야 한다.
	{
		DetachObject();		//사망판정받은 모든 오브젝트들을 부모 오브젝트의 chlidren리스트에서 제거한다.
		_releaseList.push_back(this);
		//사망판정받은 모든 오브젝트들을 해당 레벨의 _releaseObjects에 넣는다.

		return;	//아래로 내려가지 말고 바로 함수 종료.
	}

	//this의 isDead가 false라서 여기까지 내려 왔다면 자식 오브젝트들 중 사망판정받은 오브젝트가 있는지 탐색한다.
	for (std::list<GameEngineUpdateObject*>::iterator iter = children_.begin();
		iter != children_.end(); /*iter++*/)
	{
		if (true == (*iter)->IsDead())
		{
			//자식 오브젝트들 중 사망판정받은 오브젝트가 있다면,
			_releaseList.push_back((*iter));	//_releaseObjects에 넣어 삭제 대상으로 등록한다.

			GameEngineUpdateObject* deleteObject = (*iter);
			++iter;	//chlidren리스트에서 오브젝트를 제거하기 전에 이터레이터를 먼저 이동시켜놓지 않으면,
			//이터레이터가 다음 노드로 이동할 수 없다.

			deleteObject->DetachObject();	//부모 오브젝트의 chlidren리스트에서 제거한다.
		}
		else
		{
			//자식 오브젝트들 중 사망판정받은 오브젝트가 없다면 자식의 자식들까지 재귀 방식으로 전부 탐색한다.
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