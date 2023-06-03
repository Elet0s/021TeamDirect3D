#pragma once

class GameEngineInputLayoutDesc
{
	//인풋레이아웃 생성시 필요한 D3D11_INPUT_ELEMENT_DESC 구조체들과 부가 정보를 한 묶음으로 관리하는 클래스.
	//일반적인 멤버변수를 가지면 안되는 이유가 무엇??


	friend class GameEngineInputLayout;

public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> descs_;	//인풋 레이아웃 생성시 필요한 정보들.
	std::map<const char*, int> semanticNameIndexPairs_;	//시맨틱네임별 최대 인덱스데이터를 저장하는 맵.
	unsigned int offset_;							//시작 위치.						
	unsigned int instanceDataSize_;		//인스턴싱용으로 넣어준 인스턴스별 인풋레이아웃 데이터들의 단위 크기.


public:
	GameEngineInputLayoutDesc(): offset_(0), instanceDataSize_(0)
	{
	}

public:
	void AddInputLayout(
		const char* _semanticName,
		DXGI_FORMAT _format,
		unsigned int _index = -1,
		unsigned int _inputSlot = 0,
		unsigned int _instanceDataStepRate = 0,
		D3D11_INPUT_CLASSIFICATION _inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA
	);

	void ResetOffset()
	{
		offset_ = 0;
	}

};


struct GameEngineVertex
{
	//각각의 버텍스 하나마다 가져야 하는 정보들을 하나로 모아 관리하는 클래스.

	static GameEngineInputLayoutDesc inputLayoutInfo_;
	//버텍스 하나마다 inputLayoutInfo_ 한개씩만 가진다. 

	float4 POSITION;	//위치.
	float4 COLOR;		//색상.
	float4 TEXCOORD;	//UV좌표.
	float4 NORMAL;		//정점의 법선벡터.
	float4 TANGENT;		//접선.
	float4 BINORMAL;	//종법선.
	float4 WEIGHT;		// 애니메이션 가중치
	int BLENDINDICES[4] = { 0, };		//이 버텍스를 움직이는 모든 본들의 번호.
};
