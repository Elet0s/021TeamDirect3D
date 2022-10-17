#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

// ������ 1���� ������.
std::map<std::string, std::map<int, GameEngineStructuredBuffer*>> GameEngineStructuredBuffer::StructuredBufferRes;


GameEngineStructuredBuffer::GameEngineStructuredBuffer() 
	: Buffer(nullptr)
	,BufferDesc()
	,ShaderDesc()
	,SettingResources()
	, ShaderResourceView(nullptr)
	, DataSize(0)
	, DataCount(0)
	, IsInit(false)
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer() 
{
	Release();
}

void GameEngineStructuredBuffer::Release() 
{
	if (nullptr != ShaderResourceView)
	{
		ShaderResourceView->Release();
		ShaderResourceView = nullptr;
	}

	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


void GameEngineStructuredBuffer::CreateResize(const D3D11_SHADER_BUFFER_DESC& _Desc, int Count, void* _StartData)
{
	if (false == IsInit)
	{
		ShaderDesc = _Desc;
		IsInit = true;
	}

	CreateResize(ShaderDesc.Size, Count, _StartData);
}

void GameEngineStructuredBuffer::CreateResize(int Count, void* _StartData /*= nullptr*/)
{
	CreateResize(DataSize, Count, _StartData);
}

void GameEngineStructuredBuffer::CreateResize(int _DataSize, int Count, void* _StartData/* = nullptr*/)
{
	if (0 == _DataSize)
	{
		MsgBoxAssert("������ ����� 0�� ����ȭ ���۸� ������� �����ϴ�.");
	}

	DataSize = _DataSize;

	if (0 == Count)
	{
		return;
	}

	if (DataCount >= Count)
	{
		return;
	}

	Release();
	DataCount = Count;

	BufferDesc.ByteWidth = ShaderDesc.Size * DataCount; // GPU �� ������ ����ȭ ���� �޸� ũ��(�ּҴ��� ??)
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	BufferDesc.StructureByteStride = ShaderDesc.Size; // 1�� ũ�⵵ �־���� �Ѵ�.

	D3D11_SUBRESOURCE_DATA* StartDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA StartData = {0};
	if (nullptr != _StartData)
	{
		StartData.SysMemPitch = 0;
		StartData.SysMemSlicePitch = 0;
		StartData.pSysMem = _StartData;
		StartDataPtr = &StartData;
	}



	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, StartDataPtr, &Buffer))
	{
		MsgBoxAssert("��Ʈ��ó�� ���� ������ �����߽��ϴ�.");
	}

	// Shader Resource View
	// ���̴� ���ҽ��� ����µ� ���۱�� 
	// D3D11_SRV_DIMENSION_BUFFEREX ���۱�� ���̴� ���ҽ� ���°��� �˷��ֱ� ���� �뵵
	D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
	tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	tSRVDesc.BufferEx.FirstElement = 0;
	tSRVDesc.BufferEx.Flags = 0;
	tSRVDesc.BufferEx.NumElements = DataCount; // 10���� �츮���� m_pSRV�� �־�޶�.

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(Buffer, &tSRVDesc, &ShaderResourceView))
	{
		MsgBoxAssert("FAIL (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(GetBuffer(), &tSRVDesc, &m_pSRV))");
	}
}


void GameEngineStructuredBuffer::ChangeData(const void* _Data, size_t _Size)
{
	// 512 ����Ʈ �����͸� �������ټ� �ִ� ���۸� ������ٰ� �ϴ���
// ��¥ 512���� ����Ʈ�� �����ϴ°��� �ƴҼ��� �����Ƿ�
// ������ ���� ���õ��� ���̵� ����Ʈ�� �������� �ʰ�����
// �����ϴϱ� ����� �ص־� �Ұ̴ϴ�.

// ���⿡�� ���� �����͸� �������ְ� �Ǵµ�.
#ifdef _DEBUG
	//if (m_BufferInfo.ByteWidth != _Size)
	//{
	//	GameEngineDebug::AssertMsg("if (m_BufferInfo.ByteWidth != _Size)");
	//}
	SettingResources.pData = nullptr;
#endif

	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

#ifdef _DEBUG
	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("if (nullptr == m_Res.pData)");
	}
#endif 

	const float4x4* Ptr = reinterpret_cast<const float4x4*>(_Data);

	float4x4 Test = *Ptr;

	memcpy_s(SettingResources.pData, BufferDesc.ByteWidth, _Data, _Size);

	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}


void GameEngineStructuredBuffer::VSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &Nullptr);
}
void GameEngineStructuredBuffer::PSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &Nullptr);
}

void GameEngineStructuredBuffer::VSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����� �� �����ϴ�.");
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}

void GameEngineStructuredBuffer::PSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����� �� �����ϴ�.");
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}
