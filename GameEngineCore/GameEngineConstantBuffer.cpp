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
		MsgBoxAssertString(this->GetNameCopy() + ": 세팅해주기로 한 상수버퍼가 없습니다.");
		return;
	}

	if (this->constantBufferDesc_.ByteWidth != _dataSize)
	{
		MsgBoxAssertString(this->GetNameCopy() + ": 상수버퍼의 전체 크기가 서로 맞지 않습니다.");
		return;
	}

	static D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU = { 0 };
	//이게 멤버변수면 함수 선언 뒤 const를 쓸 수 없다. 

	memset(
		&destMemoryPtrInGPU,
		0,
		sizeof(destMemoryPtrInGPU)
	);
	//destMemoryInGPU의 pData가 가리키는 곳은 어디인가?? 만약 그래픽카드 내 메모리영역의 일부라면 어떻게 Map()
	// 이전에 memset()을 할 수 있는가?? 
	// ->destMemoryInGPU의 pData는 램의 어딘가에 있고 memset()으로는 널포인터 위치를 가리키게 할 뿐이다. 
	// map()이후에 그래픽카드 메모리영역의 어딘가를 가리키게 된다.


	//GPU가 자기 스스로 돌아가는 과정을 멈추고 그래픽 리소스를 건드리지 못하게 관련 작업을 일시정지시키고 
	// 그래픽카드의 메모리의 접근 권한을 개방하는 과정.
	//메모리에 대한 접근이 차단되고 GPU가 일시정지되므로 당연히 속도가 줄어든다. 적절하게 사용해야 한다.
	GameEngineDevice::GetContext()->Map(	//리소스의 데이터를 그래픽카드로 옮기기 위해, GPU에 메모리에 대한 접근 제한을 거는 함수.
		this->constantBuffer_,	//??
		0,					//서브리소스 배열 내 번호. 배열 없이 한개만 단독으로 넣어주므로 0.
		D3D11_MAP_WRITE_DISCARD,	//CPU의 리소스에 대한 접근권한 설정 플래그.
		//D3D11_MAP_WRITE_DISCARD: 해당 메모리에 있던 이전 내용은 무시하고 새로운 데이터를 덮어씌운다.
		//bufferData_.Usage가 D3D11_USAGE_DYNAMIC으로 설정되어있어야 문제가 생기지 않는다.
		0,					//GPU가 바쁠때 CPU의 행동을 지정하는 플래그. 0: 지정하지 않음.
		&destMemoryPtrInGPU	//그래픽카드 내 메모리의 특정 영역을 가리키게 될 포인터.
	);

	//ID3D11Buffer*가 가리키는 곳과 destMemoryPtrInGPU.pData가 가리키는 곳은 같은 그래픽카드 내 메모리라도 다른 영역인가?
	// 아니면 단순히 인터페이스를 통한 간접조작과 직접조작의 차이인가??
	//->ID3D11Buffer*가 가리키는 곳은 램 내의 특정 영역이고, destMemoryPtrInGPU.pData가 가리키는 곳은 그래픽카드 내 메모리의 어딘가이다.
	// 둘이 가리키는 영역은 완전히 다르다.

	if (nullptr == destMemoryPtrInGPU.pData)
	{
		MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다.");
		return;
	}

	memcpy_s(
		destMemoryPtrInGPU.pData,	//복사한 데이터의 목적지가 될 그래픽카드내 메모리의 주소.
		constantBufferDesc_.ByteWidth,	//목적지에 할당해야하는 메모리 크기.
		_data,					//데이터 복사 대상이 될 정보를 가진 메모리의 주소.
		constantBufferDesc_.ByteWidth	//복사할 데이터 크기.
	);		//램에 있는 상수버퍼 데이터를 그래픽카드로 복사한다.

	//일시정지 해제 과정.
	GameEngineDevice::GetContext()->Unmap(	//Map()함수로 걸었던, 메모리에 대한 GPU의 접근 제한을 푸는 함수
		this->constantBuffer_,			//??
		0								//서브리소스 배열의 번호. 배열 없이 한개만 단독으로 넣어주므로 0.
	);

}

void GameEngineConstantBuffer::VSSetting(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("상수 버퍼가 없습니다.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetConstantBuffers(_bindPoint, 1, &constantBuffer_);
}

void GameEngineConstantBuffer::PSSetting(int _bindPoint)
{
	if (nullptr == constantBuffer_)
	{
		MsgBoxAssert("상수 버퍼가 없습니다.");
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

	//같은 이름, 같은 바이트크기의 상수버퍼가 없으면 만들고, 있으면 공유한다.
	if (nullptr != findBuffer)
	{
		return findBuffer;
		//이미 만들어져 있는걸 또 만들어도 터뜨리지 않고, 대신 이미 만들어져 있는걸 공유한다.
	}
	else
	{
		GameEngineConstantBuffer* newCBuffer = CreateRes(uppercaseCBufferName);
		//GameEngineRes의 namedRes_에 등록시키지 않기 위해 CreateRes()함수를 직접 호출해서 생성한다.
		allConstantBuffers_[uppercaseCBufferName][_byteWidth] = newCBuffer;

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