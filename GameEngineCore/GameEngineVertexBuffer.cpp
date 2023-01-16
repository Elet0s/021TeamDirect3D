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
	newRes->inputLayoutDesc_ = &_info;	//const 자료형* 변수에 const 자료형&의 주소값을 넣어주므로 복사하는데 아무 문제 없다.
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
	newRes->inputLayoutDesc_ = &_info;	//const 자료형* 변수에 const 자료형&의 주소값을 넣어주므로 복사하는데 아무 문제 없다.
	newRes->CreateVertexBuffer(_initialData, _vertexSize, _vertexCount);
	return newRes;
}

void GameEngineVertexBuffer::Set()
{
	if (nullptr == vertexBuffer_)
	{
		MsgBoxAssert("버텍스 버퍼가 없습니다.");
		return;
	}

	//나눠서 그릴 수 있는 기능을 지원하긴 하지만, 쓸 일은 없을 것 같다.
	GameEngineDevice::GetDC()->IASetVertexBuffers(	//인풋 어셈블러 과정에서 버텍스버퍼들을 파이프라인에 연결하는 함수. 
		0,				//버텍스버퍼 배열을 세팅할 디바이스 컨텍스트의 슬롯 번호. 후속 원소들은 암시적으로 다음 번호 슬롯에 연결된다고 한다.
		//D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT개까지 동시 세팅이 가능하다고 한다. 하지만 쓸 일은 없을 것 같다. 

		1,				//디바이스 컨텍스트에 세팅할 버텍스 버퍼 배열의 원소 개수.
		//D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 첫번째 원소로 넣어준 값.

		&vertexBuffer_,		//디바이스 컨텍스트에 세팅할 버퍼 배열의 주소값. 
		//생성할때 바인드플래그를 D3D11_BIND_VERTEX_BUFFER로 설정해준 버퍼여야 여기에 연결할 수 있다.

		&vertexSize_,	//버퍼 배열의 원소간 간격 == 버텍스버퍼 한개의 크기.

		&offset_		//세팅을 시작할 배열 내 버퍼의 원소 번호 * 버퍼 크기.
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
		MsgBoxAssert("정점 한개 크기가 0입니다.");
		return;
	}

	if (0 > vertexCount_)
	{
		MsgBoxAssert("정점 개수가 0입니다.");
		return;
	}

	resData_.pSysMem = _initialData;	//버퍼 초기데이터 설정.
	//GPU가 버텍스버퍼 전체 크기만큼 자기 메모리에 할당하는데 필요하므로 버텍스버퍼에 대한 정보를 줘야 한다.

	vertexBufferDesc_.ByteWidth = vertexSize_ * vertexCount_;	//버퍼 구조체의 바이트크기 등록.

	vertexBufferDesc_.CPUAccessFlags = 0;	//CPU의 버퍼 접근 허용 여부. 0: 읽기/쓰기 둘다 불가. 
	//0으로 하는것이 최적화 효율이 증가한다.

	vertexBufferDesc_.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;		//이 버퍼를 어떤 방식으로 사용할지 등록. 
	//D3D11_USAGE::D3D11_USAGE_DEFAULT: GPU가 읽기/쓰기 가능한 리소스. CPU는 접근 불가.

	vertexBufferDesc_.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//이 버퍼를 파이프라인에 어떤 용도로 사용하는가.
	//D3D11_BIND_VERTEX_BUFFER: 렌더링 파이프라인에 버텍스버퍼로 사용.

	vertexBufferDesc_.StructureByteStride = 0;
	//내부 구조를 알 수 없는 다이렉트X 제공 버퍼가 아닌, 동일한 크기의 원소들로 구성된 구조화 버퍼를 만들 때 필요하다고 한다.
	// 0: 구조화 버퍼를 사용하지 않음.

	vertexBufferDesc_.MiscFlags = 0;	//버퍼에 관련된 부가 옵션 설정. 0: 부가 옵션 사용하지 않음.	

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&vertexBufferDesc_,
		&resData_,
		&vertexBuffer_
	))
	{
		MsgBoxAssert("버텍스 버퍼 생성 실패.");
		return;
	}
}

