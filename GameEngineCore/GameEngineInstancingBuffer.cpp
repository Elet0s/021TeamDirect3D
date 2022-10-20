#include "PreCompile.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineDevice.h"

GameEngineInstancingBuffer::GameEngineInstancingBuffer()
    : instancingBuffer_(nullptr),
    instancingBufferDesc_(),
    bufferCount_(0),
    dataSize_(0)
{
}

GameEngineInstancingBuffer::~GameEngineInstancingBuffer()
{
    if (nullptr != instancingBuffer_)
    {
        instancingBuffer_->Release();
        instancingBuffer_ = nullptr;
    }
}

GameEngineInstancingBuffer* GameEngineInstancingBuffer::Create(unsigned int _count, unsigned int _size)
{
    GameEngineInstancingBuffer* newRes = CreateUnnamedRes();
    newRes->CreateInstancingBuffer(_count, _size);
    return newRes;
}

void GameEngineInstancingBuffer::CreateInstancingBuffer(unsigned int _count, unsigned int _size)
{
    this->Release();
    //기존 인스턴싱버퍼의 데이터는 전부 초기화.

    bufferCount_ = _count;
    dataSize_ = _size;

    instancingBufferDesc_ = { 0 };

    instancingBufferDesc_.ByteWidth = bufferCount_ * dataSize_;
    //인스턴싱버퍼의 전체 크기 등록.

    instancingBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    //수시로 내용을 바꿔줘야 하므로 CPU액세스가 가능하게 한다.

    instancingBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;  
    //상수버퍼처럼 런타임 중간에 수시로 내용이 바뀔 예정이니까 동적으로 지정.

    instancingBufferDesc_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;    
    //인스턴싱 버퍼는 정점버퍼의 일종.

    if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
        &instancingBufferDesc_,
        nullptr,
        &instancingBuffer_
    ))
    {
        MsgBoxAssert("인스턴싱 버퍼 생성 실패.");
        return;
    }
}

void GameEngineInstancingBuffer::ChangeData(const void* _data, size_t _dataSize)
{
    if (nullptr == _data)
    {
        MsgBoxAssertString(this->GetNameConstRef() + ": 데이터가 없습니다.");
        return;
    }

    if (instancingBufferDesc_.ByteWidth != _dataSize)
    {
        MsgBoxAssertString(this->GetNameConstRef() + ": 상수버퍼 전체 크기가 안 맞습니다.");
        return;
    }

    D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU = { 0 };
    memset(&destMemoryPtrInGPU, 0, sizeof(destMemoryPtrInGPU));


    GameEngineDevice::GetContext()->Map(
        this->instancingBuffer_,
        0, 
        D3D11_MAP_WRITE_DISCARD,
        0,
        &destMemoryPtrInGPU
    );

    if (nullptr == destMemoryPtrInGPU.pData)
    {
        MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다.");
        return;
    }

    memcpy_s(
        destMemoryPtrInGPU.pData,
        instancingBufferDesc_.ByteWidth,
        _data,
        _dataSize
    );
     
    GameEngineDevice::GetContext()->Unmap(this->instancingBuffer_, 0);
}

void GameEngineInstancingBuffer::Release()
{
    if (nullptr != instancingBuffer_)
    {
        instancingBuffer_->Release();
        instancingBuffer_ = nullptr;
        bufferCount_ = 0;
        dataSize_ = 0; 
    }
}
