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
	const std::string_view& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc
)
{
	GameEngineConstantBuffer* newBuffer = GameEngineConstantBuffer::CreateNamedRes(_name, _desc.Size);

	newBuffer->CreateConstantBuffer(_desc);

	return newBuffer;
}

GameEngineConstantBuffer* GameEngineConstantBuffer::Find(const std::string_view& _name, int _byteWidth)
{
	std::map<std::string, std::map<int, GameEngineConstantBuffer*>>::iterator namedIter =
		allConstantBuffers_.find(GameEngineString::ToUpperReturn(_name));

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

GameEngineConstantBuffer* GameEngineConstantBuffer::CreateOrFind(
	const std::string_view& _name,
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

	//����ȭ���ۿ� �ش��ϴ� GPU �� �޸𸮿����� ���ν�ų CPU �޸��� �ּҰ�.
	static D3D11_MAPPED_SUBRESOURCE mappedPtrInCPU = { 0 };

	memset(
		&mappedPtrInCPU,
		0,
		sizeof(mappedPtrInCPU)
	);
	//destMemoryInGPU�� pData�� ����Ű�� ���� ����ΰ�?? ���� �׷���ī�� �� �޸𸮿����� �Ϻζ�� ��� Map()
	// ������ memset()�� �� �� �ִ°�?? 
	// ->destMemoryInGPU�� pData�� CPU �޸��� ����̸� memset()���δ� �������� ��ġ�� ����Ű�� �� ���̴�. 
	// map()���Ŀ� ���ۿ� �ش��ϴ� �׷���ī�� �޸� ������ ��򰡿� ���ν�Ų CPU �޸𸮸� ����Ű�� �ȴ�.


	//GPU�� �ڱ� ������ ���ư��� ������ ���߰� �׷��� ���ҽ��� �ǵ帮�� ���ϰ� ���� �۾��� �Ͻ�������Ű�� 
	// �׷���ī���� �޸��� ���� ������ �����ϴ� ����.
	//�޸𸮿� ���� ������ ���ܵǰ� GPU�� �Ͻ������ǹǷ� �翬�� �ӵ��� �پ���. �����ϰ� ����ؾ� �Ѵ�.
	HRESULT mapResult = GameEngineDevice::GetDC()->Map(	
		//���ҽ��� �����͸� �׷���ī��� �ű�� ����, ù��° ���ڷ� �־��� ���ۿ� �ش��ϴ� GPU�� �޸𸮿� ���� ���� ������ �ɰ�,
		//���������� �ɸ� GPU �޸𸮿� ����(���: ������ �Ǵ� �Ͱ� 1:1 ������Ű�� �۾�)��Ų CPU �޸��� �ּҰ��� ���ִ� �Լ�.
		this->constantBuffer_,	//���� ������ �ɸ� GPU�� Ư�� �޸� ����.
		0,					//���긮�ҽ� �迭�� ���� ��ȣ. �迭 ���� �Ѱ��� �ܵ����� �־��ֹǷ� 0.
		D3D11_MAP_WRITE_DISCARD,	//CPU�� ���ҽ��� ���� ���ٱ��� ���� �÷���.
		//D3D11_MAP_WRITE_DISCARD: �ش� �޸𸮿� �ִ� ���� ������ �����ϰ� ���ο� �����͸� ������.
		//bufferData_.Usage�� D3D11_USAGE_DYNAMIC���� �����Ǿ��־�� ������ ������ �ʴ´�.
		0,					//GPU�� �ٻܶ� CPU�� �ൿ�� �����ϴ� �÷���. 0: �������� ����.
		&mappedPtrInCPU	//�׷���ī�� �� �޸𸮿� ���ν�Ų CPU �޸� ������.
	);

	//ID3D11Buffer*�� ����Ű�� ���� mappedPtrInCPU.pData�� ����Ű�� ���� ���� �׷���ī�� �� �޸𸮶� �ٸ� �����ΰ�?
	// �ƴϸ� �ܼ��� �������̽��� ���� �������۰� ���������� �����ΰ�??
	//->ID3D11Buffer*�� ����Ű�� ���� GPU �޸� ���� Ư�� �����̰� ������ �������̽��� ������ ���� �������� ������ ���ܵǾ� ������, 
	// mappedPtrInCPU.pData�� ����Ű�� ���� ID3D11Buffer*�� �����ǰ� �� CPU �޸��� ����̴�.
	// ���� ����Ű�� ������ ������ �ٸ���.

	if (nullptr == mappedPtrInCPU.pData)
	{
		MsgBoxAssert("�׷���ī�� ���ۿ� �������� ���߽��ϴ�.");
		return;
	}

	memcpy_s(
		mappedPtrInCPU.pData,	//������ �������� ������.
		constantBufferDesc_.ByteWidth,	//�������� �Ҵ��ؾ��ϴ� �޸� ũ��.
		_data,					//������ ���� ����� �� ������ ���� �޸��� �ּ�.
		_dataSize				//������ ������ ũ��.
	);		//������ۿ� �־��� �����͸�, ������ۿ� ���ν�Ų CPU �޸𸮷� �����Ѵ�.

	//�Ͻ����� ���� ����.
	GameEngineDevice::GetDC()->Unmap(	
		//Map()�Լ��� �ɾ���, GPU �޸𸮿� ���� GPU�� ���� ������ Ǯ�� 
		// ������ ���ν��״� CPU �޸𸮷� ����� �����͸� ���۷� �����ϸ�
		// ID3D11Buffer*�� �������״� CPU �޸��� ������ �����ϴ� �Լ�.
		this->constantBuffer_,			//���� ������ �ɷȴ� GPU �޸� ����.
		0								//���긮�ҽ� �迭�� ���� ��ȣ. �迭 ���� �Ѱ��� �ܵ����� �־��ֹǷ� 0.
	);
	//�� �������� ������ CPU �޸𸮿� �ִ� �����Ͱ� GPU �޸� �ȿ� �ִ� ���۷� ���޵ȴ�.
}

void GameEngineConstantBuffer::VSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("��� ���۰� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetDC()->VSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::CSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("��� ���۰� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetDC()->CSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::PSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("��� ���۰� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetDC()->PSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
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

GameEngineConstantBuffer* GameEngineConstantBuffer::CreateNamedRes(const std::string_view& _name, int _byteWidth)
{
	GameEngineConstantBuffer* findBuffer = Find(_name, _byteWidth);

	//���� �̸�, ���� ����Ʈũ���� ������۰� ������ �����, ������ �����Ѵ�.
	if (nullptr != findBuffer)
	{
		return findBuffer;
		//�̹� ������� �ִ°� �� ���� �Ͷ߸��� �ʰ�, ��� �̹� ������� �ִ°� �����Ѵ�.
	}
	else
	{
		GameEngineConstantBuffer* newCBuffer = CreateRes(_name);
		//GameEngineRes�� namedRes_�� ��Ͻ�Ű�� �ʱ� ���� CreateRes()�Լ��� ���� ȣ���ؼ� �����Ѵ�.
		allConstantBuffers_[newCBuffer->GetNameCopy()][_byteWidth] = newCBuffer;

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