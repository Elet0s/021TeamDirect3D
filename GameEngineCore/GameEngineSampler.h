#pragma once
#include "GameEngineRes.h"

class GameEngineSampler: public GameEngineRes<GameEngineSampler>
{
	//���÷� ���� Ŭ����.
	//���ø�: �ؽ��� Ȯ��/���, �Ӹ��� ���� ���� ���� �߰��� �ȼ� ���� ������ ������ �Ǿ��� �ؼ��� ���� ��Ȳ����
	// Ư�� �ȼ��� ���� ���Ƿ� ���ؾ� �� ��, �ش� �ȼ��� ���� ��� ������ ���� ���� �ɼ��� ���ϴ� ��.
	
	friend GameEngineRes<GameEngineSampler>;
	//GameEngineSampler Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineSampler();
	~GameEngineSampler();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineSampler(const GameEngineSampler& _other) = delete;
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete;
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete;


public:	
	static GameEngineSampler* Create(const std::string& _name, const D3D11_SAMPLER_DESC& _desc);

	void VSSetting(int _bindPoint);	
	void PSSetting(int _bindPoint);	


private:
	void Create(const D3D11_SAMPLER_DESC& _desc);

private:
	ID3D11SamplerState* samplerState_;	//


	//typedef struct D3D11_SAMPLER_DESC
	//	D3D11_FILTER Filter;					�ؽ��ĸ� ���ø��Ҷ� ������ ����.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressU;	UV��ǥ 0~1������ ���η� ��� �޽��� ���� ó�� ���.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressV;	UV��ǥ 0~1������ ���η� ��� �޽��� ���� ó�� ���.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressW;	??
	//	FLOAT MipLODBias;						�Ӹ� ���� ������??
	// 
	//	UINT MaxAnisotropy;						���漺 ���͸� �ִ밪. 1~16 ������ ����. 1�� ���漺 ���͸� ��� ����.
	//�ִ밪�� 16���� �ϸ� 1/16�� ��ҵ� �Ӹ� �̹������� ���� ����Ѵٴ� �ǰ�??
	//Filter�� D3D11_FILTER_ANISOTROPIC, D3D11_FILTER_COMPARISON_ANISOTROPIC�϶��� ����.
	// 
	//	D3D11_COMPARISON_FUNC ComparisonFunc;	���ø� �����͸� ���� ���ø� �����Ϳ� ���� �� ����Ǵ� �ɼ�??
	//Filter�� D3D11_FILTER_COMPARISON_~ ���� ������ ���� ����.
	// 
	//	FLOAT BorderColor[4];					rgba 0~1 ���������� ��輱 ������ ���Ѵ�.
	//AddressU, AddressV, AddressW �� D3D11_TEXTURE_ADDRESS_BORDER�� ������ ������ ����ȴ�.
	// 
	//	FLOAT MinLOD;							�Ӹ� ���� ���� ���� ����. 0�̸� ���� ũ�� ���� �Ӹ� ����.
	//	FLOAT MaxLOD;							�Ӹ� ���� ���� �ְ� ����. 0�̸� ���� ũ�� ���� �Ӹ� ����. �ݵ�� MinLOD���� ũ�ų� ���� ���̾�� �Ѵ�.
	//											
	//} 	D3D11_SAMPLER_DESC;

	D3D11_SAMPLER_DESC samplerDesc_;

};

