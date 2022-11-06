#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineDevice.h"

std::map<std::string, std::map<int, GameEngineStructuredBuffer*>> GameEngineStructuredBuffer::allStructuredBuffers_;

GameEngineStructuredBuffer::GameEngineStructuredBuffer()
	: structuredBuffer_(nullptr),
	structuredBufferDesc_(),
	shaderBufferDesc_(),
	destMemoryPtrInGPU_(),
	shaderResourceView_(nullptr),
	dataCount_(0),
	dataUnitSize_(0),
	isInit_(false)
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer()
{
	if (nullptr != shaderResourceView_)
	{
		shaderResourceView_->Release();
		shaderResourceView_ = nullptr;
	}

	if (nullptr != structuredBuffer_)
	{
		structuredBuffer_->Release();
		structuredBuffer_ = nullptr;
	}
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::CreateStructuredBuffer(
	const std::string_view& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc,
	int _dataCount
)
{
	GameEngineStructuredBuffer* newRes = CreateNamedRes(_name, _desc.Size);
	newRes->CreateOrResize(_desc, _dataCount, nullptr);
	return newRes;
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::Find(const std::string_view& _name, int _byteWidth)
{
	std::map<std::string, std::map<int, GameEngineStructuredBuffer*>>::iterator nameFindIter
		= allStructuredBuffers_.find(GameEngineString::ToUpperReturn(_name));

	if (allStructuredBuffers_.end() == nameFindIter)
	{
		return nullptr;
	}

	std::map<int, GameEngineStructuredBuffer*>::iterator sizeFindIter = nameFindIter->second.find(_byteWidth);

	if (nameFindIter->second.end() == sizeFindIter)
	{
		return nullptr;
	}

	return sizeFindIter->second;
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::CreateAndFind(
	const std::string_view& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc,
	int _dataCount
)
{
	GameEngineStructuredBuffer* findBuffer = Find(_name, _desc.Size);

	if (nullptr != findBuffer)
	{
		return findBuffer;
	}

	GameEngineStructuredBuffer* newBuffer = CreateNamedRes(_name, _desc.Size);

	newBuffer->CreateOrResize(_desc, _dataCount);

	return newBuffer;
}

void GameEngineStructuredBuffer::ChangeData(const void* _data, unsigned int _dataSize)
{
	// 512 ����Ʈ �����͸� �������ټ� �ִ� ���۸� ������ٰ� �ϴ���
	// ��¥ 512���� ����Ʈ�� �����ϴ°��� �ƴҼ��� �����Ƿ�
	// ������ ���� ���õ��� ���̵� ����Ʈ�� �������� �ʰ�����
	// �����ϴϱ� ����� �ص־� �Ұ̴ϴ�.

	if (nullptr == _data)
	{
		MsgBoxAssert("�����Ͱ� �����ϴ�.");
		return;
	}

	if (structuredBufferDesc_.ByteWidth != _dataSize)
	{
		MsgBoxAssertString(this->GetNameCopy() + ": �������� ��ü ũ�Ⱑ ���� ���� �ʽ��ϴ�.");
		return;
	}

	destMemoryPtrInGPU_.pData = nullptr;

	HRESULT mapResult = GameEngineDevice::GetContext()->Map(
		structuredBuffer_,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&destMemoryPtrInGPU_
	);

	if (nullptr == destMemoryPtrInGPU_.pData)
	{
		MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�.");
		return;
	}

	memcpy_s(
		destMemoryPtrInGPU_.pData,
		structuredBufferDesc_.ByteWidth,
		_data,
		_dataSize
	);


	GameEngineDevice::GetContext()->Unmap(structuredBuffer_, 0);
}

void GameEngineStructuredBuffer::VSSetting(int _bindPoint)
{
	if (nullptr == shaderResourceView_)
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineStructuredBuffer::PSSetting(int _bindPoint)
{
	if (nullptr == shaderResourceView_)
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineStructuredBuffer::VSReset(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetContext()->VSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineStructuredBuffer::PSReset(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetContext()->PSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineStructuredBuffer::ResourceDestroy()
{
	for (std::pair<std::string, std::map<int, GameEngineStructuredBuffer*>> nameSortedBuffer : allStructuredBuffers_)
	{
		for (std::pair<int, GameEngineStructuredBuffer*> sizeSortedBuffer : nameSortedBuffer.second)
		{
			delete sizeSortedBuffer.second;
			sizeSortedBuffer.second = nullptr;
		}
	}
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::CreateNamedRes(const std::string_view& _name, int _byteWidth)
{
	GameEngineStructuredBuffer* findBuffer = Find(_name, _byteWidth);

	if (nullptr != findBuffer)
	{
		return findBuffer;
	}
	else
	{
		GameEngineStructuredBuffer* newBuffer = CreateRes(_name);
		//GameEngineRes�� namedRes_�� ��Ͻ�Ű�� �ʱ� ���� CreateRes()�Լ��� ���� ȣ���ؼ� �����Ѵ�.

		allStructuredBuffers_[newBuffer->GetNameCopy()][_byteWidth] = newBuffer;

		return newBuffer;
	}
}

void GameEngineStructuredBuffer::CreateOrResize(
	const D3D11_SHADER_BUFFER_DESC& _desc,
	unsigned int _count,
	void* _initialData /*= nullptr*/
)
{
	this->shaderBufferDesc_ = _desc;

	CreateOrResize(shaderBufferDesc_.Size, _count, _initialData);
}

void GameEngineStructuredBuffer::CreateOrResize(unsigned int _dataUnitSize, unsigned int _count, void* _initialData /*= nullptr*/)
{
	if (0 >= _dataUnitSize)
	{
		MsgBoxAssert("������ ����� 0�� ����ȭ ���۸� ������� �����ϴ�.");
	}

	if (0 == _count)
	{
		return;
	}

	if (dataCount_ >= _count)	//�� ������ ������ ���� ����Ÿ �������� �۰ų� ������ �׳� �Ѿ��.
	{
		return;
	}

	this->Release();	//�� ũ�ٸ� std::vectoró�� ����� �ٽ� �����.

	if (false == isInit_)
	{
		isInit_ = true;
	}

	this->dataUnitSize_ = _dataUnitSize;
	this->dataCount_ = _count;



	structuredBufferDesc_.ByteWidth = dataUnitSize_ * dataCount_;
	//GPU�� ������ ����ȭ ���� �޸��� ��ü ũ��(�ּҴ��� ??)

	structuredBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;	//������ ��� ���.
	//D3D11_USAGE_DYNAMIC: GPU�� �б⸸, CPU�� ���⸸ ����.
	//����ȭ ������ �����Ϳ� ũ��� ���������� �ٲ�Ƿ� CPU�� ������ �� �ְ� �ؾ� �Ѵ�.

	structuredBufferDesc_.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//������ ���������ο� ���̴� ���ҽ��� ����.
	//����ȭ ���۴� �������� ���۰� �ƴ϶�, ���� ��� ���̴� ���ҽ��� Ȱ���ϹǷ� ���̴� ���ҽ��� �����Ѵ�.
	//����ȭ ���۴� D3D11_BIND_SHADER_RESOURCE�� D3D11_BIND_UNORDERED_ACCESS �ΰ��� ���ε��÷��׹ۿ� �� �� ����.

	structuredBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//���ۿ� ���� CPU�� ���ٱ��� ����. 
	//D3D11_CPU_ACCESS_WRITE: CPU�� ���ۿ� ���⸸ ����.
	//����ȭ ������ �����Ϳ� ũ��� ���������� �ٲ�Ƿ� CPU�� ������ �� �ְ� �ؾ� �Ѵ�.

	structuredBufferDesc_.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;	//���ۿ� ���õ� �ΰ� �ɼ� ����.
	//D3D11_RESOURCE_MISC_BUFFER_STRUCTURED: �� ���۸� ����ȭ ���۷� ����.

	structuredBufferDesc_.StructureByteStride = dataUnitSize_;	//����ȭ ���� �������� ���� ũ��.
	//��ǻ� ����ȭ���� ���� ����̹Ƿ� �ݵ�� �־��ش�.

	D3D11_SUBRESOURCE_DATA initialData = { 0 };
	if (nullptr != _initialData)
	{
		initialData.pSysMem = _initialData;
		initialData.SysMemPitch = 0;			//2, 3���� �ؽ�ó�� �ƴϹǷ� 0.
		initialData.SysMemSlicePitch = 0;		//3���� �ؽ�ó�� �ƴϹǷ� 0.
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&structuredBufferDesc_,
		&initialData,
		&structuredBuffer_
	))
	{
		MsgBoxAssert("����ȭ ���� ���� ����.");
		return;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	//����ȭ ������ ���̴� ���ҽ��並 ����°� �ʿ��� ����.
	//����ȭ ���۴� �������� ������ ���������ο��� ���̴� ���ҽ��� ���ǹǷ�, �׿� �°� ���̴� ���ҽ��並 �����ؾ� �Ѵ�.

	shaderResourceViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	//DXGI_FORMAT::DXGI_FORMAT_UNKNOWN: DXGI_FORMAT�� ���� ���˿� ���� ����.
	//����ȭ ������ ���Ҵ� ��������� ����ü�̹Ƿ� DXGI_FORMAT�� ���� �������� ���� �� �� ����.
	//�׷��Ƿ� DXGI_FORMAT_UNKNOWN���� ������ �����Ѵ�.

	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	//D3D11_SRV_DIMENSION_BUFFEREX: ���̴� ���ҽ��並 ������� ���ҽ��� �ؽ�ó�� �ؽ�ó �迭�� �ƴ϶�, 
	// �������۳� �ε������� ������ �������� ���� ������ �����̴�.

	shaderResourceViewDesc.BufferEx.FirstElement = 0;
	//??

	shaderResourceViewDesc.BufferEx.NumElements = dataCount_;
	//??

	shaderResourceViewDesc.BufferEx.Flags = 0;
	//??


	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(
		structuredBuffer_,
		&shaderResourceViewDesc,
		&this->shaderResourceView_
	))
	{
		MsgBoxAssert("����ȭ ������ ���̴� ���ҽ��� ���� ����.");
		return;
	}
}

void GameEngineStructuredBuffer::CreateOrResize(unsigned int _count, void* _initialData /*= nullptr*/)
{
	CreateOrResize(this->dataUnitSize_, _count, _initialData);
}

void GameEngineStructuredBuffer::Release()
{
	if (nullptr != shaderResourceView_)
	{
		shaderResourceView_->Release();
		shaderResourceView_ = nullptr;
	}

	if (nullptr != structuredBuffer_)
	{
		structuredBuffer_->Release();
		structuredBuffer_ = nullptr;
	}
}
