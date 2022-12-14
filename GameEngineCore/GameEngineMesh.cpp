#include "PreCompile.h"
#include "GameEngineMesh.h"
#include "GameEngineDevice.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInstancingBuffer.h"

GameEngineMesh::GameEngineMesh()
    : vertexBuffer_(nullptr),
    indexBuffer_(nullptr)
{
    SetVertexBuffer_InputAssembler1("RectVertex");
    SetIndexBuffer_InputAssembler2("RectIndex");
}

GameEngineMesh::~GameEngineMesh()
{
}

std::shared_ptr<GameEngineMesh> GameEngineMesh::Create(const std::string_view& _meshName)
{
    return Create(_meshName, _meshName, _meshName);
}

std::shared_ptr<GameEngineMesh> GameEngineMesh::Create(
    const std::string_view& _meshName,
    const std::string_view& _vertexBufferName,
    const std::string_view& _indexBufferName
)
{
    std::shared_ptr<GameEngineMesh> newRes = CreateNamedRes(_meshName);
    newRes->SetVertexBuffer_InputAssembler1(_vertexBufferName);
    newRes->SetIndexBuffer_InputAssembler2(_indexBufferName);
    return newRes;
}

std::shared_ptr<GameEngineMesh> GameEngineMesh::Create(
    std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer,
    std::shared_ptr<GameEngineIndexBuffer> _indexBuffer
)
{
    std::shared_ptr<GameEngineMesh> newRes = CreateUnnamedRes();
    newRes->SetVertexBuffer_InputAssembler1(_vertexBuffer);
    newRes->SetIndexBuffer_InputAssembler2(_indexBuffer);
    return newRes;
}

void GameEngineMesh::SetVertexBuffer_InputAssembler1(const std::string_view& _vertexBufferName)
{
    this->vertexBuffer_ = GameEngineVertexBuffer::Find(_vertexBufferName);

    if (nullptr == vertexBuffer_)
    {
        MsgBoxAssertString(std::string(_vertexBufferName) + ": 그런 이름의 버텍스버퍼가 존재하지 않습니다.");
        return;
    }
}

void GameEngineMesh::SetVertexBuffer_InputAssembler1(std::shared_ptr<GameEngineVertexBuffer> _vertexBuffer)
{
    if (nullptr == _vertexBuffer)
    {
        MsgBoxAssert("버텍스버퍼가 존재하지 않습니다.");
        return;
    }

    this->vertexBuffer_ = _vertexBuffer;
}

void GameEngineMesh::SetIndexBuffer_InputAssembler2(const std::string_view& _indexBufferName)
{
    this->indexBuffer_ = GameEngineIndexBuffer::Find(_indexBufferName);

    if (nullptr == indexBuffer_)
    {
        MsgBoxAssertString(std::string(_indexBufferName) + ": 그런 이름의 인덱스버퍼가 존재하지 않습니다.");
        return;
    }
}

void GameEngineMesh::SetIndexBuffer_InputAssembler2(std::shared_ptr<GameEngineIndexBuffer> _indexBuffer)
{
    if (nullptr == _indexBuffer)
    {
        MsgBoxAssert("인덱스버퍼가 존재하지 않습니다.");
        return;
    }

    this->indexBuffer_ = _indexBuffer;
}

void GameEngineMesh::Setting()
{
    this->InputAssembler1_VertexBufferSetting();
    this->InputAssembler2_IndexBufferSetting();
}

void GameEngineMesh::SettingInstancing(std::shared_ptr<GameEngineInstancingBuffer> _instancingBuffer)
{
    ID3D11Buffer* ArrBuffer[2] = { this->vertexBuffer_->GetBuffer(), _instancingBuffer->GetBuffer() };
    //버퍼 배열.
    //왜 this->vertexBuffer_와 _instancingBuffer를 섞어 쓰지??
    //->버텍스버퍼와 인스턴싱버퍼를 같이 넣어주기 위해서.


    UINT ArrVertexSize[2] = {
        static_cast<UINT>(this->vertexBuffer_->GetVertexSize()),
        static_cast<UINT>(_instancingBuffer->GetDataSize())
    };

    UINT ArrOffset[2] = { 0, 0 };
    //오프셋 바이트.

    GameEngineDevice::GetDC()->IASetVertexBuffers(
        0,
        2,
        ArrBuffer,
        ArrVertexSize,
        ArrOffset
    );

    this->InputAssembler2_IndexBufferSetting();
}

void GameEngineMesh::Render()
{
    GameEngineDevice::GetDC()->DrawIndexed(	//인덱스에 연동된 정점들을 그리는 함수.
        this->indexBuffer_->GetIndexCount(),//인덱스 개수.
        0,									//읽기 시작할 인덱스 버퍼의 원소 번호. 
        0									//읽기 시작할 버텍스 버퍼의 원소 번호. 
    );
    //내가 사용하려는 카메라 렌더타겟이 뭔지 어떻게 알고 거기다 그리는거지??
    //->카메라 렌더하기 전에 카메라의 렌더타겟을 먼저 디바이스 컨텍스트에 세팅하고, 
    // 그 디바이스 컨텍스트를 통해 렌더링 파이프라인 과정을 진행하므로 여기서 렌더타겟을 지정해주지 않아도 
    // 내가 원하는 카메라의 렌더타겟에 렌더할 수 있게 된다.
}

void GameEngineMesh::RenderInstancing(size_t _instancingCount)
{
    GameEngineDevice::GetDC()->DrawIndexedInstanced(   //
        this->indexBuffer_->GetIndexCount(),                //인덱스 개수.
        static_cast<UINT>(_instancingCount),                //인스턴스 수.
        0,                                                  //읽기 시작할 인덱스 버퍼의 원소 번호.
        0,                                                  //읽기 시작할 버텍스 버퍼의 원소 번호.
        0                                                   //읽기 시작할 인스턴스의 번호.
    );
}

const GameEngineInputLayoutDesc& GameEngineMesh::GetInputLayoutDesc() const
{
    if (nullptr == this->vertexBuffer_)
    {
        MsgBoxAssert("버텍스버퍼가 없습니다. 인풋 레이아웃 세팅을 가져올 수 없습니다.");
    }

    return vertexBuffer_->GetInputLayoutDesc();
}

void GameEngineMesh::InputAssembler1_VertexBufferSetting()
{
    this->vertexBuffer_->Set();
}

void GameEngineMesh::InputAssembler2_IndexBufferSetting()
{
    this->indexBuffer_->Set();
}
