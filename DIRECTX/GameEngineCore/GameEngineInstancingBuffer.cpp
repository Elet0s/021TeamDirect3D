#include "PreCompile.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineDevice.h"

GameEngineInstancingBuffer::GameEngineInstancingBuffer() 
{
}

GameEngineInstancingBuffer::~GameEngineInstancingBuffer() 
{
	BufferRelease();
}

void GameEngineInstancingBuffer::BufferRelease()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


GameEngineInstancingBuffer* GameEngineInstancingBuffer::Create(unsigned int _Count, unsigned int _Size)
{
	GameEngineInstancingBuffer* Buffer = CreateResUnName();

	Buffer->BufferCreate(_Count, _Size);

	return Buffer;
}

void GameEngineInstancingBuffer::BufferCreate(unsigned int _Count, unsigned int _Size)
{
	BufferRelease();

	BufferCount = _Count;
	Size = _Size;
	BufferDesc = {};
	BufferDesc.ByteWidth = _Count * Size;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, nullptr, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}
}


void GameEngineInstancingBuffer::ChangeData(const void* _Data, size_t _Size) const
{
	if (_Data == nullptr)
	{
		MsgBoxAssertString(GetNameCopy() + "  �����͸� ���������� �ʾҽ��ϴ�.");
	}

	if (BufferDesc.ByteWidth != _Size)
	{
		MsgBoxAssertString(GetNameCopy() + "  ��������� ����Ʈ ũ�Ⱑ ���� ���� �ʽ��ϴ�.");
	}

	D3D11_MAPPED_SUBRESOURCE SettingResources = {};
	memset(&SettingResources, 0, sizeof(SettingResources));

	// � �׷��� ���ҽ��� �������� �ƹ��� �ǵ��� ���ϰ� ��.
	// �׷���ī�带 ������ ����ϴ�.
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�..");
	}

	memcpy_s(SettingResources.pData, BufferDesc.ByteWidth, _Data, BufferDesc.ByteWidth);


	// ������ �ٽ� �ݾ���� �մϴ�.
	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}