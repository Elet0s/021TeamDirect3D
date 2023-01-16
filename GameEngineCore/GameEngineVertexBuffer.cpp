#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineDevice.h"

GameEngineVertexBuffer::GameEngineVertexBuffer()
	: vertexBuffer_(nullptr),
	vertexBufferDesc_(),
	resData_(),
	vertexSize_(-1),
	vertexCount_(-1),
	offset_(0),
	inputLayoutDesc_(nullptr)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
	if (nullptr != vertexBuffer_)
	{
		vertexBuffer_->Release();
		vertexBuffer_ = nullptr;
	}
}

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(
	const std::string_view& _name,
	const void* _initialData,
	UINT _vertexSize,
	UINT _vertexCount,
	const GameEngineInputLayoutDesc& _info
)
{
	GameEngineVertexBuffer* newRes = CreateNamedRes(_name);
	newRes->inputLayoutDesc_ = &_info;	//const �ڷ���* ������ const �ڷ���&�� �ּҰ��� �־��ֹǷ� �����ϴµ� �ƹ� ���� ����.
	newRes->CreateVertexBuffer(_initialData, _vertexSize, _vertexCount);
	return newRes;
}

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(
	const void* _initialData,
	UINT _vertexSize,
	UINT _vertexCount,
	const GameEngineInputLayoutDesc& _info
)
{
	GameEngineVertexBuffer* newRes = CreateUnnamedRes();
	newRes->inputLayoutDesc_ = &_info;	//const �ڷ���* ������ const �ڷ���&�� �ּҰ��� �־��ֹǷ� �����ϴµ� �ƹ� ���� ����.
	newRes->CreateVertexBuffer(_initialData, _vertexSize, _vertexCount);
	return newRes;
}

void GameEngineVertexBuffer::Set()
{
	if (nullptr == vertexBuffer_)
	{
		MsgBoxAssert("���ؽ� ���۰� �����ϴ�.");
		return;
	}

	//������ �׸� �� �ִ� ����� �����ϱ� ������, �� ���� ���� �� ����.
	GameEngineDevice::GetDC()->IASetVertexBuffers(	//��ǲ ����� �������� ���ؽ����۵��� ���������ο� �����ϴ� �Լ�. 
		0,				//���ؽ����� �迭�� ������ ����̽� ���ؽ�Ʈ�� ���� ��ȣ. �ļ� ���ҵ��� �Ͻ������� ���� ��ȣ ���Կ� ����ȴٰ� �Ѵ�.
		//D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT������ ���� ������ �����ϴٰ� �Ѵ�. ������ �� ���� ���� �� ����. 

		1,				//����̽� ���ؽ�Ʈ�� ������ ���ؽ� ���� �迭�� ���� ����.
		//D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - ù��° ���ҷ� �־��� ��.

		&vertexBuffer_,		//����̽� ���ؽ�Ʈ�� ������ ���� �迭�� �ּҰ�. 
		//�����Ҷ� ���ε��÷��׸� D3D11_BIND_VERTEX_BUFFER�� �������� ���ۿ��� ���⿡ ������ �� �ִ�.

		&vertexSize_,	//���� �迭�� ���Ұ� ���� == ���ؽ����� �Ѱ��� ũ��.

		&offset_		//������ ������ �迭 �� ������ ���� ��ȣ * ���� ũ��.
	);
}

void GameEngineVertexBuffer::CreateVertexBuffer(
	const void* _initialData,
	UINT _vertexSize,
	UINT _vertexCount
)
{
	vertexSize_ = _vertexSize;
	vertexCount_ = _vertexCount;

	if (0 > vertexSize_)
	{
		MsgBoxAssert("���� �Ѱ� ũ�Ⱑ 0�Դϴ�.");
		return;
	}

	if (0 > vertexCount_)
	{
		MsgBoxAssert("���� ������ 0�Դϴ�.");
		return;
	}

	resData_.pSysMem = _initialData;	//���� �ʱⵥ���� ����.
	//GPU�� ���ؽ����� ��ü ũ�⸸ŭ �ڱ� �޸𸮿� �Ҵ��ϴµ� �ʿ��ϹǷ� ���ؽ����ۿ� ���� ������ ��� �Ѵ�.

	vertexBufferDesc_.ByteWidth = vertexSize_ * vertexCount_;	//���� ����ü�� ����Ʈũ�� ���.

	vertexBufferDesc_.CPUAccessFlags = 0;	//CPU�� ���� ���� ��� ����. 0: �б�/���� �Ѵ� �Ұ�. 
	//0���� �ϴ°��� ����ȭ ȿ���� �����Ѵ�.

	vertexBufferDesc_.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;		//�� ���۸� � ������� ������� ���. 
	//D3D11_USAGE::D3D11_USAGE_DEFAULT: GPU�� �б�/���� ������ ���ҽ�. CPU�� ���� �Ұ�.

	vertexBufferDesc_.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//�� ���۸� ���������ο� � �뵵�� ����ϴ°�.
	//D3D11_BIND_VERTEX_BUFFER: ������ ���������ο� ���ؽ����۷� ���.

	vertexBufferDesc_.StructureByteStride = 0;
	//���� ������ �� �� ���� ���̷�ƮX ���� ���۰� �ƴ�, ������ ũ���� ���ҵ�� ������ ����ȭ ���۸� ���� �� �ʿ��ϴٰ� �Ѵ�.
	// 0: ����ȭ ���۸� ������� ����.

	vertexBufferDesc_.MiscFlags = 0;	//���ۿ� ���õ� �ΰ� �ɼ� ����. 0: �ΰ� �ɼ� ������� ����.	

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&vertexBufferDesc_,
		&resData_,
		&vertexBuffer_
	))
	{
		MsgBoxAssert("���ؽ� ���� ���� ����.");
		return;
	}
}

