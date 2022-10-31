#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineDevice.h"

GameEngineIndexBuffer::GameEngineIndexBuffer()
	: indexBuffer_(nullptr),
	resData_(),
	indexBufferDesc_(),
	indexSize_(-1),
	indexCount_(-1),
	offset_(0)
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer()
{
	if (nullptr != indexBuffer_)
	{
		indexBuffer_->Release();
		indexBuffer_ = nullptr;
	}
}

GameEngineIndexBuffer* GameEngineIndexBuffer::Create(
	const std::string& _name,
	const void* _data,
	UINT _indexSize,
	UINT _indexCount
)
{
	GameEngineIndexBuffer* newRes = CreateNamedRes(_name);
	newRes->CreateIndexBuffer(_data, _indexSize, _indexCount);
	return newRes;
}

GameEngineIndexBuffer* GameEngineIndexBuffer::Create(const void* _data, UINT _indexSize, UINT _indexCount)
{
	GameEngineIndexBuffer* newRes = CreateUnnamedRes();
	newRes->CreateIndexBuffer(_data, _indexSize, _indexCount);
	return newRes;
}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == indexBuffer_)
	{
		MsgBoxAssert("인덱스버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetContext()->IASetIndexBuffer(//인풋 어셈블러 과정에서 인덱스버퍼를 파이프라인에 연결하는 함수.
		indexBuffer_,							//파이프라인에 세팅할 버퍼. 2차원배열 하나만 넣어줌.
		//생성할때 바인드플래그를 D3D11_BIND_INDEX_BUFFER로 설정해준 버퍼여야 여기에 연결할 수 있다.
		DXGI_FORMAT::DXGI_FORMAT_R32_UINT,		//인덱스버퍼의 데이터 형식. 
		0										//세팅을 시작할 버퍼의 원소 번호 * 각 버퍼의 크기.
	);
}

void GameEngineIndexBuffer::CreateIndexBuffer(const void* _initialData, UINT _indexSize, UINT _indexCount)
{
	indexSize_ = _indexSize;
	indexCount_ = _indexCount;

	resData_.pSysMem = _initialData;	//버퍼 초기데이터 설정.
	//그래픽카드가 n바이트만큼 자기 메모리에 할당하는데 필요하므로 버퍼에 대한 정보를 줘야 한다.

	indexBufferDesc_.ByteWidth = indexSize_ * indexCount_;	//버퍼 구조체의 바이트크기 등록.

	indexBufferDesc_.CPUAccessFlags = 0;	//CPU의 버퍼 접근 허용 여부. 0: 읽기/쓰기 둘다 불가. 
	//0으로 하는것이 최적화 효율이 증가한다.

	indexBufferDesc_.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;		//이 버퍼를 어떤 방식으로 사용할지 등록. 
	//D3D11_USAGE::D3D11_USAGE_DEFAULT: GPU가 읽기/쓰기 가능한 리소스. CPU는 접근 불가.

	indexBufferDesc_.BindFlags = D3D11_BIND_INDEX_BUFFER;	//이 버퍼를 파이프라인에 어떤 용도로 사용하는가.
	//D3D11_BIND_INDEX_BUFFER: 렌더링 파이프라인에 인덱스버퍼로 사용.

	indexBufferDesc_.StructureByteStride = 0;
	//내부 구조를 알 수 없는 다이렉트X 제공 버퍼가 아닌, 동일한 크기의 원소들로 구성된 구조체로 버퍼를 만들 때 필요하다고 한다.
	// 0: 구조체 버퍼를 사용하지 않음.

	indexBufferDesc_.MiscFlags = 0;	//버퍼에 관련된 부가 옵션 설정. 0: 부가 옵션 사용하지 않음.	

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&indexBufferDesc_,
		&resData_,
		&indexBuffer_
	))
	{
		MsgBoxAssert("인덱스 버퍼 생성 실패.");
		return;
	}
}
