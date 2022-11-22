#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderer.h"
#include "GameEngineVertexShader.h"

GameEngineInstancing::GameEngineInstancing()
	: initRenderUnit_(nullptr),
	instancingBuffer_(nullptr),
	dataInsert_(0),
	size_(0),
	count_(0),
	maxDataCount_(0)
{
}

GameEngineInstancing::~GameEngineInstancing()
{
}

void GameEngineInstancing::PushUnit(std::shared_ptr<GameEngineRenderUnit> _renderUnit)
{
	if (nullptr == initRenderUnit_)
	{
		initRenderUnit_ = _renderUnit;
	}

	_renderUnit->Off();
	//�ν��Ͻ̿� ��ϵǸ� �Ϲ� ������ ��󿡼� �����Ѵ�.

	if (false == _renderUnit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("�ν��Ͻ̿� �������̴��� ������ ���� ���������Դϴ�.");
		return;
	}

	//for (size_t i = 0; i < renderUnits_.size(); ++i)
	//{
	//
	//}
}

void GameEngineInstancing::InstancingBufferChangeData()
{
	if (nullptr == instancingBuffer_)
	{
		MsgBoxAssert("�ν��Ͻ̿� ���۰� �����ϴ�.");
		return;
	}

	instancingBuffer_->ChangeData(&dataBuffer_[0], dataBuffer_.size());
}
