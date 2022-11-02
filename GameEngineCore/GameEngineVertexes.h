#pragma once

class GameEngineInputLayoutDesc
{
	//��ǲ���̾ƿ� ������ �ʿ��� D3D11_INPUT_ELEMENT_DESC ����ü��� �ΰ� ������ �� �������� �����ϴ� Ŭ����.
	//�Ϲ����� ��������� ������ �ȵǴ� ������ ����??


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
	//���ؽ� �ϳ����� ������ �ϴ� �������� �ϳ��� ��� �����ϴ� Ŭ����.

	static GameEngineInputLayoutDesc inputLayoutInfo_;
	//���ؽ� �ϳ����� inputLayoutInfo_ �Ѱ����� ������. 

	float4 position_;
	float4 color_;
	float4 texcoord_;
	float4 normal_;
	float4 binormal_;
	float4 tangent_;
	float4 weight_;		// �ִϸ��̼� ����ġ
	int blendedIndices_[4] = { 0, };		//�� ���ؽ��� �����̴� ��� ������ ��ȣ.
};
