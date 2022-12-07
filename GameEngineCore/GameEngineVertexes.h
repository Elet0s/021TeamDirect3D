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
	unsigned int instancingSize_;					//�ν��Ͻ� ���� ũ��.


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

	float4 POSITION;	//��ġ.
	float4 COLOR;		//����.
	float4 TEXCOORD;	//UV��ǥ.
	float4 NORMAL;		//��������.
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;		// �ִϸ��̼� ����ġ
	int BLENDINDICES[4] = { 0, };		//�� ���ؽ��� �����̴� ��� ������ ��ȣ.
};
