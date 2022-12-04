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
    //버퍼 원소 크기 배열.
    //왜 this->vertexBuffer_와 _instancingBuffer를 섞어 쓰지??

    UINT ArrOffset[2] = { 0, 0 };
    //오프셋 바이트.



    GameEngineDevice::GetContext()->IASetVertexBuffers(
        0,
        2,
        ArrBuffer,
        ArrVertexSize,
        ArrOffset
    );

    this->InputAssembler2_IndexBufferSetting();

    //[in] IndexCountPerInstance 유형 : UINT
    //각 인스턴스에 대해 인덱스 버퍼에서 읽은 인덱스 수입니다.
    
    //[in] InstanceCount 유형 : UINT
    //그릴 인스턴스 수입니다.
    
    //[in] StartIndexLocation
    //유형 : UINT GPU가 인덱스 버퍼에서 읽은 첫 번째 인덱스의 위치입니다.
    
    //[in] BaseVertexLocation 유형 : 지능
    //정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값입니다.
    
    //[in] StartInstanceLocation 유형 : UINT
    //정점 버퍼에서 인스턴스별 데이터를 읽기 전에 각 인덱스에 추가된 값입니다.
    
    
    ////나눠서 그릴 수 있는 기능을 지원하긴 하지만, 쓸 일은 없을 것 같다.
    //GameEngineDevice::GetContext()->IASetVertexBuffers(	//인풋 어셈블러 과정에서 버텍스버퍼들을 파이프라인에 연결하는 함수. 
    //    0,				//버텍스버퍼 배열을 세팅할 렌더링파이프라인의 슬롯 번호. 후속 원소들은 암시적으로 다음 번호 슬롯에 연결된다고 한다.
    //    //D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT개까지 동시 세팅이 가능하다고 한다. 하지만 쓸 일은 없을 것 같다. 
    
    //    1,				//렌더링 파이프라인에 세팅할 버텍스 버퍼 배열의 원소 개수.
    //    //D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 첫번째 원소로 넣어준 값.
    
    //    &vertexBuffer_,		//파이프라인에 세팅할 버퍼 배열의 주소값. 
    //    //생성할때 바인드플래그를 D3D11_BIND_VERTEX_BUFFER로 설정해준 버퍼여야 여기에 연결할 수 있다.
    
    //    &vertexSize_,	//버퍼 배열의 원소간 간격 == 버텍스버퍼 한개의 크기.
    
    //    &offset_		//세팅을 시작할 배열 내 버퍼의 원소 번호 * 버퍼 크기.
    //);
}

void GameEngineMesh::Render()
{
    GameEngineDevice::GetContext()->DrawIndexed(	//인덱스에 연동된 정점들을 그리는 함수.
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
    GameEngineDevice::GetContext()->DrawIndexedInstanced(   //
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
    this->vertexBuffer_->Setting();
}

void GameEngineMesh::InputAssembler2_IndexBufferSetting()
{
    this->indexBuffer_->Setting();
}
