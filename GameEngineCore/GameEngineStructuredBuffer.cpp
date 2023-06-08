#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineDevice.h"

std::map<std::string, std::map<size_t, GameEngineStructuredBuffer*>> GameEngineStructuredBuffer::allStructuredBuffers_;

GameEngineStructuredBuffer::GameEngineStructuredBuffer()
	: structuredBuffer_(nullptr),
	structuredBufferDesc_(),
	shaderBufferDesc_(),
	mappedPtrInCPU_(),
	shaderResourceView_(nullptr),
	count_(0),
	dataSize_(0),
	isInitialized_(false)
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

GameEngineStructuredBuffer* GameEngineStructuredBuffer::Create(
	const std::string_view& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc,
	size_t _count
)
{
	GameEngineStructuredBuffer* newRes = CreateNamedRes(_name, _desc.Size);
	newRes->CreateOrResize(_desc, _count, nullptr);
	return newRes;
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::Find(const std::string_view& _name, size_t _byteWidth)
{
	std::map<std::string, std::map<size_t, GameEngineStructuredBuffer*>>::iterator nameFindIter
		= allStructuredBuffers_.find(GameEngineString::ToUpperReturn(_name));

	if (allStructuredBuffers_.end() == nameFindIter)
	{
		return nullptr;
	}

	std::map<size_t, GameEngineStructuredBuffer*>::iterator sizeFindIter = nameFindIter->second.find(_byteWidth);

	if (nameFindIter->second.end() == sizeFindIter)
	{
		return nullptr;
	}

	return sizeFindIter->second;
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::FindOrCreate(
	const std::string_view& _name,
	const D3D11_SHADER_BUFFER_DESC& _desc,
	size_t _count
)
{
	GameEngineStructuredBuffer* findBuffer = Find(_name, _desc.Size);

	if (nullptr != findBuffer)
	{
		return findBuffer;
	}
	else
	{
		GameEngineStructuredBuffer* newBuffer = CreateNamedRes(_name, _desc.Size);

		newBuffer->CreateOrResize(_desc, _count);

		return newBuffer;
	}
}

void GameEngineStructuredBuffer::ChangeData(const void* _data, size_t _byteWidth)
{
	if (nullptr == _data)
	{
		MsgBoxAssert("데이터가 없습니다.");
		return;
	}

	//if (this->structuredBufferDesc_.ByteWidth != _byteWidth)
	//{
	//	MsgBoxAssertString(this->GetNameCopy() + ": 데이터의 전체 크기가 서로 맞지 않습니다.");
	//	return;
	//}
	////같은 이름의 최대 크기 구조화 버퍼를 모든 셰이더들이 공유하므로 크기를 정확히 맞출 필요가 없다.

	mappedPtrInCPU_.pData = nullptr;

	HRESULT mapResult = GameEngineDevice::GetDC()->Map(
		structuredBuffer_,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedPtrInCPU_
	);

	if (nullptr == mappedPtrInCPU_.pData)
	{
		MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다.");
		return;
	}

	memcpy_s(
		mappedPtrInCPU_.pData,
		structuredBufferDesc_.ByteWidth,
		_data,
		_byteWidth
	);


	GameEngineDevice::GetDC()->Unmap(structuredBuffer_, 0);
}

void GameEngineStructuredBuffer::VSSetShaderResource(int _bindPoint)
{
	if (nullptr == shaderResourceView_)
	{
		MsgBoxAssert("구조화 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->VSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineStructuredBuffer::CSSetShaderResource(int _bindPoint)
{
	if (nullptr == shaderResourceView_)
	{
		MsgBoxAssert("구조화 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->CSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineStructuredBuffer::PSSetShaderResource(int _bindPoint)
{
	if (nullptr == shaderResourceView_)
	{
		MsgBoxAssert("구조화 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->PSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineStructuredBuffer::VSResetShaderResource(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetDC()->VSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineStructuredBuffer::PSResetShaderResource(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetDC()->PSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineStructuredBuffer::ResourceDestroy()
{
	for (std::pair<std::string, std::map<size_t, GameEngineStructuredBuffer*>> nameSortedBuffer : allStructuredBuffers_)
	{
		for (std::pair<size_t, GameEngineStructuredBuffer*> sizeSortedBuffer : nameSortedBuffer.second)
		{
			delete sizeSortedBuffer.second;
			sizeSortedBuffer.second = nullptr;
		}
	}
}

GameEngineStructuredBuffer* GameEngineStructuredBuffer::CreateNamedRes(const std::string_view& _name, size_t _byteWidth)
{
	GameEngineStructuredBuffer* findBuffer = Find(_name, _byteWidth);

	if (nullptr != findBuffer)
	{
		return findBuffer;
	}
	else
	{
		GameEngineStructuredBuffer* newBuffer = CreateRes(_name);
		//GameEngineRes의 namedRes_에 등록시키지 않기 위해 CreateRes()함수를 직접 호출해서 생성한다.

		allStructuredBuffers_[newBuffer->GetNameCopy()][_byteWidth] = newBuffer;

		return newBuffer;
	}
}

void GameEngineStructuredBuffer::CreateOrResize(
	const D3D11_SHADER_BUFFER_DESC& _desc,
	size_t _count,
	void* _initialData /*= nullptr*/
)
{
	this->shaderBufferDesc_ = _desc;

	CreateStructuredBuffer(shaderBufferDesc_.Size, _count, _initialData);
}

void GameEngineStructuredBuffer::CreateStructuredBuffer(size_t _dataSize, size_t _count, void* _initialData /*= nullptr*/)
{
	if (0 >= _dataSize)
	{
		MsgBoxAssert("데이터 사이즈가 0인 구조화 버퍼를 만들수는 없습니다.");
		return;
	}

	this->dataSize_ = _dataSize;

	if (0 == _count)
	{
		return;
	}

	if (count_ >= _count)	//새 데이터 개수가 이전 데이타 개수보다 작거나 같으면 그냥 넘어간다.
	{
		return;
	}

	this->Release();	//더 크다면 std::vector처럼 지우고 다시 만든다.

	if (false == isInitialized_)
	{
		isInitialized_ = true;
	}

	this->count_ = _count;



	structuredBufferDesc_.ByteWidth = static_cast<UINT>(dataSize_ * count_);
	//GPU에 생성할 구조화 버퍼 메모리의 전체 크기

	structuredBufferDesc_.Usage = D3D11_USAGE_DYNAMIC;	//버퍼의 사용 방식.
	//D3D11_USAGE_DYNAMIC: GPU는 읽기만, CPU는 쓰기만 가능.
	//구조화 버퍼의 데이터와 크기는 지속적으로 바뀌므로 CPU가 갱신할 수 있게 해야 한다.

	structuredBufferDesc_.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//렌더링 파이프라인에 셰이더 리소스로 연결.
	//구조화 버퍼는 버퍼지만 버퍼가 아니라, 버퍼 기반 셰이더 리소스로 활용하므로 셰이더 리소스로 연결한다.
	//구조화 버퍼는 D3D11_BIND_SHADER_RESOURCE와 D3D11_BIND_UNORDERED_ACCESS 두가지 바인드플래그밖에 쓸 수 없다.

	structuredBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//버퍼에 대한 CPU의 접근권한 설정. 
	//D3D11_CPU_ACCESS_WRITE: CPU는 버퍼에 쓰기 가능.
	//구조화 버퍼의 데이터와 크기는 지속적으로 바뀌므로 CPU가 갱신할 수 있게 해야 한다.

	structuredBufferDesc_.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;	//버퍼에 관련된 부가 옵션 설정.
	//D3D11_RESOURCE_MISC_BUFFER_STRUCTURED: 이 버퍼를 구조화 버퍼로 설정.

	structuredBufferDesc_.StructureByteStride = static_cast<UINT>(dataSize_);	//구조화 버퍼 데이터의 단위 크기.
	//사실상 구조화버퍼 전용 기능이므로 반드시 넣어준다.

	D3D11_SUBRESOURCE_DATA initialData = { 0 };
	D3D11_SUBRESOURCE_DATA* initialDataPtr = nullptr;
	if (nullptr != _initialData)
	{
		initialData.pSysMem = _initialData;
		initialData.SysMemPitch = 0;			//2, 3차원 텍스처가 아니므로 0.
		initialData.SysMemSlicePitch = 0;		//3차원 텍스처가 아니므로 0.
		initialDataPtr = &initialData;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&structuredBufferDesc_,
		initialDataPtr,
		//널포인터를 따로 넣어주지 않으면 모든 값이 0인 D3D11_SUBRESOURCE_DATA의 포인터를 넣어준 것으로 알고 
		// 구조화버퍼를 생성하려다가 실패한다.
		&structuredBuffer_
	))
	{
		MsgBoxAssert("구조화 버퍼 생성 실패.");
		return;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	//구조화 버퍼의 셰이더 리소스뷰를 만드는게 필요한 명세서.
	//구조화 버퍼는 버퍼지만 렌더링 파이프라인에서 셰이더 리소스로 사용되므로, 그에 맞게 셰이더 리소스뷰를 생성해야 한다.

	shaderResourceViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	//DXGI_FORMAT::DXGI_FORMAT_UNKNOWN: DXGI_FORMAT의 기존 포맷에 없는 형식.
	//구조화 버퍼의 원소는 사용자정의 구조체이므로 DXGI_FORMAT의 기존 포맷으로 정의 할 수 없다.
	//그러므로 DXGI_FORMAT_UNKNOWN으로 형식을 지정한다.

	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	//D3D11_SRV_DIMENSION_BUFFEREX: 셰이더 리소스뷰를 만들려는 리소스가 텍스처나 텍스처 배열이 아니라, 
	// 정점버퍼나 인덱스버퍼 등으로 가공되지 않은 형식의 버퍼이다.

	shaderResourceViewDesc.BufferEx.FirstElement = 0;
	//버퍼의 첫 원소 인덱스.

	shaderResourceViewDesc.BufferEx.NumElements = static_cast<UINT>(count_);
	//버퍼의 원소 숫자.

	shaderResourceViewDesc.BufferEx.Flags = 0;
	//??


	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(
		structuredBuffer_,
		&shaderResourceViewDesc,
		&this->shaderResourceView_
	))
	{
		MsgBoxAssert("구조화 버퍼의 셰이더 리소스뷰 생성 실패.");
		return;
	}
}

void GameEngineStructuredBuffer::CreateOrResize(size_t _count, void* _initialData /*= nullptr*/)
{
	CreateStructuredBuffer(this->dataSize_, _count, _initialData);
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
