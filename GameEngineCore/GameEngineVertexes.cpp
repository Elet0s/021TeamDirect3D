#include "PreCompile.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDevice.h"

GameEngineInputLayoutDesc GameEngineVertex::inputLayoutInfo_;
unsigned int ConvertFormatToByteScale(DXGI_FORMAT _format);

void GameEngineInputLayoutDesc::AddInputLayout(
	const char* _semanticName,
	DXGI_FORMAT _format,
	unsigned int _index /*= -1*/,
	unsigned int _inputSlot /*= 0*/,
	unsigned int _instanceDataStepRate /*= 0*/,
	D3D11_INPUT_CLASSIFICATION _inputSlotClass /*= D3D11_INPUT_PER_VERTEX_DATA*/
)
{
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc = { 0 };

	int semanticIndex = _index;

	if (-1 == semanticIndex)	
		//_index가 기본값인 -1이라면 사용자가 인덱스에 대해 신경쓰지 않겠다는 의미이므로 자동으로 처리되게 한다.
	{
		if (semanticIndexData_.end() == semanticIndexData_.find(_semanticName))	//같은 시맨틱네임이 없다면
		{
			semanticIndexData_[_semanticName] = -1;	//value인 인덱스값에 -1 저장.
		}
		semanticIndex = ++semanticIndexData_[_semanticName];
		//맵에 저장된 시맨틱네임의 인덱스를 1 증가시키면서 semanticIndex에 대입한다.
	}

	//typedef struct D3D11_INPUT_ELEMENT_DESC		인풋레이아웃을 생성할때 필요한 세부설정 정보를 담는 구조체.
	//{
	//	LPCSTR SemanticName;						이 인풋레이아웃이 가리키는 데이터의 시맨틱의 이름. 대소문자 구분 안함.
	//	UINT SemanticIndex;							이 인풋레이아웃이 가리키는 데이터의 시맨틱의 번호.  COLOR[n]의 n.
	//	DXGI_FORMAT Format;							이 인풋레이아웃이 가리키는 데이터의 데이터타입. 
	//	UINT InputSlot;								렌더링 파이프라인에 버텍스버퍼를 등록할 슬롯 번호. 0~15까지 가능.
	//	UINT AlignedByteOffset;						이 인풋레이아웃이 가리키는 데이터의 오프셋(메모리 시작점에서부터의 바이트 거리).
	//	D3D11_INPUT_CLASSIFICATION InputSlotClass;	이 인풋레이아웃으로 등록되는것이 단순 버텍스 정보인지, 인스턴스 데이터를 포함하는지를 알려주는 값.
	//	UINT InstanceDataStepRate;					위의 InputSlotClass에서 D3D11_INPUT_PER_INSTANCE_DATA를 선택했을때만 필요한 값이라고 한다.
	//} 	D3D11_INPUT_ELEMENT_DESC;

	inputLayoutDesc.SemanticName = _semanticName;
	inputLayoutDesc.SemanticIndex = semanticIndex;
	inputLayoutDesc.Format = _format;
	inputLayoutDesc.InputSlot = _inputSlot;				//인스턴스 버퍼용.
	inputLayoutDesc.AlignedByteOffset = offset_;
	inputLayoutDesc.InputSlotClass = _inputSlotClass;
	inputLayoutDesc.InstanceDataStepRate = _instanceDataStepRate;		//인스턴스 버퍼용.

	unsigned int formatSize = ConvertFormatToByteScale(inputLayoutDesc.Format);
	offset_ += formatSize;

	if (D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA == inputLayoutDesc.InputSlotClass)
	{
		instancingSize_ += formatSize;
	}

	descs_.push_back(inputLayoutDesc);
}

unsigned int ConvertFormatToByteScale(DXGI_FORMAT _format)
{
	switch (_format)
	{
	case DXGI_FORMAT_UNKNOWN:
		MsgBoxAssert("포맷이 정해지지 않았습니다.");
		return -1;

	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;

	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
		return 4;


	default:
		MsgBoxAssert("크기를 아직 책정하지 않은 포맷입니다.");
		return -1;
	}
}