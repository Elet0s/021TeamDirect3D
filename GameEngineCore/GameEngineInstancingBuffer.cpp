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
    //���� �ν��Ͻ̹����� �����ʹ� ���� �ʱ�ȭ.

    bufferCount_ = _count;
    dataSize_ = _size;

    instancingBufferDesc_ = { 0 };

    instancingBufferDesc_.ByteWidth = static_cast<UINT>(bufferCount_ * dataSize_);
    //�ν��Ͻ̹����� ��ü ũ�� ���.

    instancingBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    //���÷� ������ �ٲ���� �ϹǷ� CPU�׼����� �����ϰ� �Ѵ�.

    instancingBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;
    //�������ó�� ��Ÿ�� �߰��� ���÷� ������ �ٲ� �����̴ϱ� �������� ����.

    instancingBufferDesc_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    //�ν��Ͻ� ���۴� �������ۿ� �Բ� IA1�ܰ迡�� GPU�� ���޵Ǿ� �������̴��� ���� ȭ�鿡 ��ġ�ȴ�.

    if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
        &instancingBufferDesc_,
        nullptr,
        &instancingBuffer_
    ))
    {
        MsgBoxAssert("�ν��Ͻ� ���� ���� ����.");
        return;
    }
}

void GameEngineInstancingBuffer::ChangeData(const void* _data, size_t _byteWidth)
{
    if (nullptr == _data)
    {
        MsgBoxAssertString(this->GetNameCopy() + ": �����Ͱ� �����ϴ�.");
        return;
    }

    if (instancingBufferDesc_.ByteWidth != _byteWidth)
    {
        MsgBoxAssertString(this->GetNameCopy() + ": �ν��Ͻ� ������ ��ü ũ�Ⱑ �� �½��ϴ�.");
        return;
    }

    //����ȭ���ۿ� �ش��ϴ� GPU �� �޸𸮿����� ���ν�ų CPU �޸��� �ּҰ�.
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
        MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�.");
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
