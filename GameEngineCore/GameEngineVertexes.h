#pragma once

class GameEngineInputLayoutDesc
{
	//인풋레이아웃 생성시 필요한 D3D11_INPUT_ELEMENT_DESC 구조체들과 부가 정보를 한 묶음으로 관리하는 클래스.
	//일반적인 멤버변수를 가지면 안되는 이유가 무엇??


	friend class GameEngineInputLayout;

public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> descs_;	//
	std::map<const char*, int> semanticIndexData_;	//
	unsigned int offset_;							//
	unsigned int instancingSize_;					//


public:
	GameEngineInputLayoutDesc(): offset_(0), instancingSize_(0)
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
	//버텍스 하나마다 가져야 하는 정보들을 하나로 모아 관리하는 클래스.

	static GameEngineInputLayoutDesc inputLayoutInfo_;
	//버텍스 하나마다 inputLayoutInfo_ 한개씩만 가진다. 

	float4 position_;
	float4 color_;
	float4 texcoord_;
	float4 normal_;
	float4 binormal_;
	float4 tangent_;
	float4 weight_;		// 애니메이션 가중치
	int blendedIndices_[4] = { 0, };		//이 버텍스를 움직이는 모든 본들의 번호.
};
