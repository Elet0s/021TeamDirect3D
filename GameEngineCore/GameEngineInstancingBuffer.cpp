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
    //���� �ν��Ͻ̹����� �����ʹ� ���� �ʱ�ȭ.

    bufferCount_ = _count;
    dataSize_ = _size;

    instancingBufferDesc_ = { 0 };

    instancingBufferDesc_.ByteWidth = bufferCount_ * dataSize_;
    //�ν��Ͻ̹����� ��ü ũ�� ���.

    instancingBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    //���÷� ������ �ٲ���� �ϹǷ� CPU�׼����� �����ϰ� �Ѵ�.

    instancingBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;  
    //�������ó�� ��Ÿ�� �߰��� ���÷� ������ �ٲ� �����̴ϱ� �������� ����.

    instancingBufferDesc_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;    
    //�ν��Ͻ� ���۴� ���������� ����.

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

void GameEngineInstancingBuffer::ChangeData(const void* _data, size_t _dataSize)
{
    if (nullptr == _data)
    {
        MsgBoxAssertString(this->GetNameConstRef() + ": �����Ͱ� �����ϴ�.");
        return;
    }

    if (instancingBufferDesc_.ByteWidth != _dataSize)
    {
        MsgBoxAssertString(this->GetNameConstRef() + ": ������� ��ü ũ�Ⱑ �� �½��ϴ�.");
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
        MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�.");
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
