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

GameEngineConstantBuffer* GameEngineConstantBuffer::FindOrCreate(
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
		MsgBoxAssertString(this->GetNameCopy() + ": 세팅해주기로 한 상수버퍼가 없습니다.");
		return;
	}

	if (this->constantBufferDesc_.ByteWidth != _dataSize)
	{
		MsgBoxAssertString(this->GetNameCopy() + ": 상수버퍼의 전체 크기가 서로 맞지 않습니다.");
		return;
	}

	//구조화버퍼에 해당하는 GPU 내 메모리영역에 매핑시킬 CPU 메모리의 주소값.
	static D3D11_MAPPED_SUBRESOURCE mappedPtrInCPU = { 0 };

	memset(
		&mappedPtrInCPU,
		0,
		sizeof(mappedPtrInCPU)
	);
	//destMemoryInGPU의 pData가 가리키는 곳은 어디인가?? 만약 그래픽카드 내 메모리영역의 일부라면 어떻게 Map()
	// 이전에 memset()을 할 수 있는가?? 
	// ->destMemoryInGPU의 pData는 CPU 메모리의 어딘가이며 memset()으로는 널포인터 위치를 가리키게 할 뿐이다. 
	// map()이후엔 버퍼에 해당하는 그래픽카드 메모리 영역의 어딘가와 매핑시킨 CPU 메모리를 가리키게 된다.


	//GPU가 자기 스스로 돌아가는 과정을 멈추고 그래픽 리소스를 건드리지 못하게 관련 작업을 일시정지시키고 
	// 그래픽카드의 메모리의 접근 권한을 개방하는 과정.
	//메모리에 대한 접근이 차단되고 GPU가 일시정지되므로 당연히 속도가 줄어든다. 적절하게 사용해야 한다.
	HRESULT mapResult = GameEngineDevice::GetDC()->Map(	
		//리소스의 데이터를 그래픽카드로 옮기기 위해, 첫번째 인자로 넣어준 버퍼에 해당하는 GPU의 메모리에 대한 접근 제한을 걸고,
		//접근제한이 걸린 GPU 메모리와 매핑(사상: 원본이 되는 것과 1:1 대응시키는 작업)시킨 CPU 메모리의 주소값을 내주는 함수.
		this->constantBuffer_,	//접근 제한이 걸릴 GPU의 특정 메모리 영역.
		0,					//서브리소스 배열의 원소 번호. 배열 없이 한개만 단독으로 넣어주므로 0.
		D3D11_MAP_WRITE_DISCARD,	//CPU의 리소스에 대한 접근권한 설정 플래그.
		//D3D11_MAP_WRITE_DISCARD: 해당 메모리에 있던 이전 내용은 무시하고 새로운 데이터를 덮어씌운다.
		//bufferData_.Usage가 D3D11_USAGE_DYNAMIC으로 설정되어있어야 문제가 생기지 않는다.
		0,					//GPU가 바쁠때 CPU의 행동을 지정하는 플래그. 0: 지정하지 않음.
		&mappedPtrInCPU	//그래픽카드 내 메모리와 매핑시킨 CPU 메모리 포인터.
	);

	//ID3D11Buffer*가 가리키는 곳과 mappedPtrInCPU.pData가 가리키는 곳은 같은 그래픽카드 내 메모리라도 다른 영역인가?
	// 아니면 단순히 인터페이스를 통한 간접조작과 직접조작의 차이인가??
	//->ID3D11Buffer*가 가리키는 곳은 GPU 메모리 내의 특정 영역이고 지정한 인터페이스를 통하지 않은 직접적인 접근은 차단되어 있으며, 
	// mappedPtrInCPU.pData가 가리키는 곳은 ID3D11Buffer*에 대응되게 한 CPU 메모리의 어딘가이다.
	// 둘이 가리키는 영역은 완전히 다르다.

	if (nullptr == mappedPtrInCPU.pData)
	{
		MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다.");
		return;
	}

	memcpy_s(
		mappedPtrInCPU.pData,	//복사한 데이터의 목적지.
		constantBufferDesc_.ByteWidth,	//목적지에 할당해야하는 메모리 크기.
		_data,					//데이터 복사 대상이 될 정보를 가진 메모리의 주소.
		_dataSize				//복사할 데이터 크기.
	);		//상수버퍼에 넣어줄 데이터를, 상수버퍼와 매핑시킨 CPU 메모리로 복사한다.

	//일시정지 해제 과정.
	GameEngineDevice::GetDC()->Unmap(	
		//Map()함수로 걸었던, GPU 메모리에 대한 GPU의 접근 제한을 풀고 
		// 위에서 매핑시켰던 CPU 메모리로 복사된 데이터를 버퍼로 복사하며
		// ID3D11Buffer*와 대응시켰던 CPU 메모리의 매핑을 해제하는 함수.
		this->constantBuffer_,			//접근 제한이 걸렸던 GPU 메모리 영역.
		0								//서브리소스 배열의 원소 번호. 배열 없이 한개만 단독으로 넣어주므로 0.
	);
	//이 과정까지 끝내면 CPU 메모리에 있던 데이터가 GPU 메모리 안에 있는 버퍼로 전달된다.
}

void GameEngineConstantBuffer::VSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("상수 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->VSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::CSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("상수 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->CSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::PSSetConstantBuffer(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("상수 버퍼가 없습니다.");
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

	//같은 이름, 같은 바이트크기의 상수버퍼가 없으면 만들고, 있으면 공유한다.
	if (nullptr != findBuffer)
	{
		return findBuffer;
		//이미 만들어져 있는걸 또 만들어도 터뜨리지 않고, 대신 이미 만들어져 있는걸 공유한다.
	}
	else
	{
		GameEngineConstantBuffer* newCBuffer = CreateRes(_name);
		//GameEngineRes의 namedRes_에 등록시키지 않기 위해 CreateRes()함수를 직접 호출해서 생성한다.
		allConstantBuffers_[newCBuffer->GetNameCopy()][_byteWidth] = newCBuffer;

		return newCBuffer;
	}
}

void GameEngineConstantBuffer::CreateConstantBuffer(
	const D3D11_SHADER_BUFFER_DESC& _desc
)
{
	shaderBufferDesc_ = _desc;

	constantBufferDesc_.ByteWidth = shaderBufferDesc_.Size;	//생성할 상수버퍼 크기.

	constantBufferDesc_.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;	//버퍼의 사용 방식.
	//D3D11_USAGE_DYNAMIC: GPU는 읽기만, CPU는 쓰기만 가능.
	//상수버퍼의 데이터는 지속적으로 바뀌므로 CPU가 갱신할 수 있게 해야 한다.

	constantBufferDesc_.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//렌더링 파이프라인에 상수버퍼로 연결한다.

	constantBufferDesc_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//버퍼에 대한 CPU의 접근권한 설정. 
	//D3D11_CPU_ACCESS_WRITE: CPU는 버퍼에 쓰기만 가능.
	//상수버퍼의 데이터는 지속적으로 바뀌므로 CPU가 갱신할 수 있게 해야 한다.

	constantBufferDesc_.StructureByteStride = 0;
	//내부 구조를 알 수 없는 다이렉트X 제공 버퍼가 아닌, 다이렉트X 제공 버퍼와 동일한 크기의 원소들로 구성된 구조화 버퍼를 만들 때 필요하다고 한다.
	// 0: 구조화 버퍼를 사용하지 않음.

	constantBufferDesc_.MiscFlags = 0;			//버퍼에 관련된 부가 옵션 설정. 0: 부가 옵션 사용하지 않음.	

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(
		&constantBufferDesc_,
		nullptr,	//상수버퍼는 계속 값이 바뀔 예정이므로 초기값이 의미가 없다.
		&constantBuffer_
	))
	{
		MsgBoxAssert("상수버퍼 생성 실패.");
		return;
	}


}