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
	//인스턴싱에 등록되면 일반 렌더링 대상에서 제외한다.

	if (false == _renderUnit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱용 정점셰이더를 가지지 않은 렌더유닛입니다.");
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
		MsgBoxAssert("인스턴싱에 버퍼가 없습니다.");
		return;
	}

	instancingBuffer_->ChangeData(&dataBuffer_[0], dataBuffer_.size());
}
