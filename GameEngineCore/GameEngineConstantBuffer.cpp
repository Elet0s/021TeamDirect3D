#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineDevice.h"

std::map<std::string, std::map<int, GameEngineConstantBuffer*>> GameEngineConstantBuffer::allConstantBuffers_;

GameEngineConstantBuffer::GameEngineConstantBuffer()
	: shaderBufferDesc_(),
	constantBufferDesc_(),
	constantBuffer_(nullptr)
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{
	if (nullptr != constantBuffer_)
	{
		constantBuffer_->Release();
		constantBuffer_ = nullptr;
	}
}

GameEngineConstantBuffer* GameEngineConstantBuffer::Create(
	const std::string& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc
)
{
	GameEngineConstantBuffer* newBuffer = GameEngineConstantBuffer::CreateNamedRes(_name, _desc.Size);

	newBuffer->CreateConstantBuffer(_desc);

	return newBuffer;
}

GameEngineConstantBuffer* GameEngineConstantBuffer::Find(const std::string& _name, int _byteWidth)
{
	std::string uppercaseCBufferName = GameEngineString::ToUpperReturn(_name);

	std::map<std::string, std::map<int, GameEngineConstantBuffer*>>::iterator namedIter =
		allConstantBuffers_.find(uppercaseCBufferName);

	if (allConstantBuffers_.end() == namedIter)
	{
		return nullptr;
	}

	std::map<int, GameEngineConstantBuffer*>::iterator sizeIter = namedIter->second.find(_byteWidth);

	if (namedIter->second.end() == sizeIter)
	{
		return nullptr;
	}

	return sizeIter->second;
}

GameEngineConstantBuffer* GameEngineConstantBuffer::CreateAndFind(
	const std::string& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc
)
{
	GameEngineConstantBuffer* findCBuffer = Find(_name, _desc.Size);

	if (nullptr != findCBuffer)
	{
		return findCBuffer;
	}

	GameEngineConstantBuffer* newCBuffer = CreateNamedRes(_name, _desc.Size);
	newCBuffer->CreateConstantBuffer(_desc);
	return newCBuffer;
}

void GameEngineConstantBuffer::ChangeData(const void* _data, size_t _dataSize) const
{
	if (nullptr == _data)
	{
		MsgBoxAssertString(this->GetNameCopy() + ": �������ֱ�� �� ������۰� �����ϴ�.");
		return;
	}

	if (this->constantBufferDesc_.ByteWidth != _dataSize)
	{
		MsgBoxAssertString(this->GetNameCopy() + ": ��������� ��ü ũ�Ⱑ ���� ���� �ʽ��ϴ�.");
		return;
	}

	static D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU = { 0 };
	//�̰� ��������� �Լ� ���� �� const�� �� �� ����. 

	memset(
		&destMemoryPtrInGPU,
		0,
		sizeof(destMemoryPtrInGPU)
	);
	//destMemoryInGPU�� pData�� ����Ű�� ���� ����ΰ�?? ���� �׷���ī�� �� �޸𸮿����� �Ϻζ�� ��� Map()
	// ������ memset()�� �� �� �ִ°�?? 
	// ->destMemoryInGPU�� pData�� ���� ��򰡿� �ְ� memset()���δ� �������� ��ġ�� ����Ű�� �� ���̴�. 
	// map()���Ŀ� �׷���ī�� �޸𸮿����� ��򰡸� ����Ű�� �ȴ�.


	//GPU�� �ڱ� ������ ���ư��� ������ ���߰� �׷��� ���ҽ��� �ǵ帮�� ���ϰ� ���� �۾��� �Ͻ�������Ű�� 
	// �׷���ī���� �޸��� ���� ������ �����ϴ� ����.
	//�޸𸮿� ���� ������ ���ܵǰ� GPU�� �Ͻ������ǹǷ� �翬�� �ӵ��� �پ���. �����ϰ� ����ؾ� �Ѵ�.
	GameEngineDevice::GetContext()->Map(	//���ҽ��� �����͸� �׷���ī��� �ű�� ����, GPU�� �޸𸮿� ���� ���� ������ �Ŵ� �Լ�.
		this->constantBuffer_,	//??
		0,					//���긮�ҽ� �迭 �� ��ȣ. �迭 ���� �Ѱ��� �ܵ����� �־��ֹǷ� 0.
		D3D11_MAP_WRITE_DISCARD,	//CPU�� ���ҽ��� ���� ���ٱ��� ���� �÷���.
		//D3D11_MAP_WRITE_DISCARD: �ش� �޸𸮿� �ִ� ���� ������ �����ϰ� ���ο� �����͸� ������.
		//bufferData_.Usage�� D3D11_USAGE_DYNAMIC���� �����Ǿ��־�� ������ ������ �ʴ´�.
		0,					//GPU�� �ٻܶ� CPU�� �ൿ�� �����ϴ� �÷���. 0: �������� ����.
		&destMemoryPtrInGPU	//�׷���ī�� �� �޸��� Ư�� ������ ����Ű�� �� ������.
	);

	//ID3D11Buffer*�� ����Ű�� ���� destMemoryPtrInGPU.pData�� ����Ű�� ���� ���� �׷���ī�� �� �޸𸮶� �ٸ� �����ΰ�?
	// �ƴϸ� �ܼ��� �������̽��� ���� �������۰� ���������� �����ΰ�??
	//->ID3D11Buffer*�� ����Ű�� ���� �� ���� Ư�� �����̰�, destMemoryPtrInGPU.pData�� ����Ű�� ���� �׷���ī�� �� �޸��� ����̴�.
	// ���� ����Ű�� ������ ������ �ٸ���.

	if (nullptr == destMemoryPtrInGPU.pData)
	{
		MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�.");
		return;
	}

	memcpy_s(
		destMemoryPtrInGPU.pData,	//������ �������� �������� �� �׷���ī�峻 �޸��� �ּ�.
		constantBufferDesc_.ByteWidth,	//�������� �Ҵ��ؾ��ϴ� �޸� ũ��.
		_data,					//������ ���� ����� �� ������ ���� �޸��� �ּ�.
		constantBufferDesc_.ByteWidth	//������ ������ ũ��.
	);		//���� �ִ� ������� �����͸� �׷���ī��� �����Ѵ�.

	//�Ͻ����� ���� ����.
	GameEngineDevice::GetContext()->Unmap(	//Map()�Լ��� �ɾ���, �޸𸮿� ���� GPU�� ���� ������ Ǫ�� �Լ�
		this->constantBuffer_,			//??
		0								//���긮�ҽ� �迭�� ��ȣ. �迭 ���� �Ѱ��� �ܵ����� �־��ֹǷ� 0.
	);

}

void GameEngineConstantBuffer::VSSetting(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("��� ���۰� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::PSSetting(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("��� ���۰� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->PSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::ResourceDestroy()
{
	for (std::pair<std::string, std::map<int, GameEngineConstantBuffer*>> namedPair : allConstantBuffers_)
	{
		for (std::pair<int, GameEngineConstantBuffer*> sizePair : namedPair.second)
		{
			delete sizePair.second;
			sizePair.second = nullptr;
		}
	}
}

GameEngineConstantBuffer* GameEngineConstantBuffer::CreateNamedRes(const std::string& _name, int _byteWidth)
{
	std::string uppercaseCBufferName = GameEngineString::ToUpperReturn(_name);

	GameEngineConstantBuffer* findBuffer = Find(_name, _byteWidth);

	//���� �̸�, ���� ����Ʈũ���� ������۰� ������ �����, ������ �����Ѵ�.
	if (nullptr != findBuffer)
	{
		return findBuffer;
		//�̹� ������� �ִ°� �� ���� �Ͷ߸��� �ʰ�, ��� �̹� ������� �ִ°� �����Ѵ�.
	}
	else
	{
		GameEngineConstantBuffer* newCBuffer = CreateRes(uppercaseCBufferName);
		//GameEngineRes�� namedRes_�� ��Ͻ�Ű�� �ʱ� ���� CreateRes()�Լ��� ���� ȣ���ؼ� �����Ѵ�.
		allConstantBuffers_[uppercaseCBufferName][_byteWidth] = newCBuffer;

		return newCBuffer;
	}
}

void GameEngineConstantBuffer::CreateConstantBuffer(
	const D3D11_SHADER_BUFFER_DESC& _desc
)
{
	shaderBufferDesc_ = _desc;

	constantBufferDesc_.ByteWidth = shaderBufferDesc_.Size;	//������ ������� ũ��.

	constantBufferDesc_.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;	//������ ��� ���.
	//D3D11_USAGE_DYNAMIC: GPU�� �б⸸, CPU�� ���⸸ ����.
	//��������� �����ʹ� ���������� �ٲ�Ƿ� CPU�� ������ �� �ְ� �ؾ� �Ѵ�.

	constantBufferDesc_.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//������ ���������ο� ������۷� �����Ѵ�.

	constantBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//���ۿ� ���� CPU�� ���ٱ��� ����. 
	//D3D11_CPU_ACCESS_WRITE: CPU�� ���ۿ� ���⸸ ����.
	//��������� �����ʹ� ���������� �ٲ�Ƿ� CPU�� ������ �� �ְ� �ؾ� �Ѵ�.

	constantBufferDesc_.StructureByteStride = 0;
	//���� ������ �� �� ���� ���̷�ƮX ���� ���۰� �ƴ�, ���̷�ƮX ���� ���ۿ� ������ ũ���� ���ҵ�� ������ ����ȭ ���۸� ���� �� �ʿ��ϴٰ� �Ѵ�.
	// 0: ����ȭ ���۸� ������� ����.

	constantBufferDesc_.MiscFlags = 0;			//���ۿ� ���õ� �ΰ� �ɼ� ����. 0: �ΰ� �ɼ� ������� ����.	

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&constantBufferDesc_,
		nullptr,	//������۴� ��� ���� �ٲ� �����̹Ƿ� �ʱⰪ�� �ǹ̰� ����.
		&constantBuffer_
	))
	{
		MsgBoxAssert("������� ���� ����.");
		return;
	}


}