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

GameEngineInstancingBuffer* GameEngineInstancingBuffer::Create(size_t _count, size_t _size)
{
    GameEngineInstancingBuffer* newRes = CreateUnnamedRes();
    newRes->CreateInstancingBuffer(_count, _size);
    return newRes;
}

void GameEngineInstancingBuffer::CreateInstancingBuffer(size_t _count, size_t _size)
{
    this->Release();
    //기존 인스턴싱버퍼의 데이터는 전부 초기화.

    bufferCount_ = _count;
    dataSize_ = _size;

    instancingBufferDesc_ = { 0 };

    instancingBufferDesc_.ByteWidth = static_cast<UINT>(bufferCount_ * dataSize_);
    //인스턴싱버퍼의 전체 크기 등록.

    instancingBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    //수시로 내용을 바꿔줘야 하므로 CPU액세스가 가능하게 한다.

    instancingBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;
    //상수버퍼처럼 런타임 중간에 수시로 내용이 바뀔 예정이니까 동적으로 지정.

    instancingBufferDesc_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    //인스턴싱 버퍼는 정점버퍼와 함께 IA1단계에서 GPU로 전달되어 정점셰이더를 통해 화면에 배치된다.

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

void GameEngineInstancingBuffer::ChangeData(const void* _data, size_t _byteWidth)
{
    if (nullptr == _data)
    {
        MsgBoxAssertString(this->GetNameCopy() + ": 데이터가 없습니다.");
        return;
    }

    if (instancingBufferDesc_.ByteWidth != _byteWidth)
    {
        MsgBoxAssertString(this->GetNameCopy() + ": 인스턴싱 버퍼의 전체 크기가 안 맞습니다.");
        return;
    }

    //구조화버퍼에 해당하는 GPU 내 메모리영역에 매핑시킬 CPU 메모리의 주소값.
    D3D11_MAPPED_SUBRESOURCE mappedPtrInCPU = { 0 };

    memset(&mappedPtrInCPU, 0, sizeof(mappedPtrInCPU));


    HRESULT mapResult = GameEngineDevice::GetDC()->Map(
        this->instancingBuffer_,
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &mappedPtrInCPU
    );

    if (nullptr == mappedPtrInCPU.pData)
    {
        MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다.");
        return;
    }

    memcpy_s(
        mappedPtrInCPU.pData,
        instancingBufferDesc_.ByteWidth,
        _data,
        _byteWidth
    );

    GameEngineDevice::GetDC()->Unmap(this->instancingBuffer_, 0);
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
