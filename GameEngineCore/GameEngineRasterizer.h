#pragma once
#include "GameEngineRes.h"


class GameEngineRasterizer: public GameEngineRes<GameEngineRasterizer>
{
	//�����Ͷ������� �ϴ� ��
	//1. �߶󳻱�(clipping):
	// ��������(view frustum) �ۿ� �ִ� �͵��� ���������� �����ϰ�, ���� ������ �Ϻθ� ���ܵǾ� �߸� �͵��� 
	// �߸� ���� ���������� �´� �� ���ؽ��� ����� �۾�.
	// �ٸ� �޽��� �������� �޽��� �߶󳻴� ���� Ŭ����(depth clipping), 
	// Ư���� �簢 ������ ������ �߶󳻴� ���� Ŭ����(scissor clipping) ���� �ִ�.
	// 
	//2. ���� ������(perspective division):
	// �ָ��ִ� ������Ʈ���� ���ؽ� ������ ������, ����� ������Ʈ���� ���ؽ����� �ָ� ��ġ�ؼ� ���ٰ��� �����ϴ� ��.
	// 
	//3. �޸� �ԾƳ���(backface culling): 
	// �ٸ��Ϳ� �������� ������ �ʴ� �κ�/�����ؼ� ���ĺ��̴� �κ� ���� �����ؼ� �������� �κа� �׷��� ���� �κ��� �������� �۾�.
	// 
	//4. ����Ʈ ��ȯ(viewport transform):
	// ���������� �°� -1~1 ���̷�(z���� 0~1���̷�) ��ҵ� ���ؽ����� ��ġ�� ����� ������ ũ�⿡ ���缭 Ȯ���Ű�� �۾�.
	// 
	//5. ��ĵ ��ȯ(scan transform):
	// ���������� ���� ���ؽ����� ���̸�, 
	// ���ؽ����� ���������� �޾� ���������ؼ� �̾Ƴ� �� �ȼ��� ������ �����׸�Ʈ(���� �ȼ�)�� ä��� �۾�.
	//
	//�̻��� �������� ���� ������ �ٲ�� �ϴ� �ȼ��� ��󳻼�(��Ī �ȼ� ������) �ȼ����̴��� �ѱ��.
	// 
	//->��ī��Ʈ��ǥ�踦 ������ ��ǥ��� ��ȯ�Ѵ�.


	friend GameEngineRes<GameEngineRasterizer>;
	//GameEngineRasterizer Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineRasterizer();
	~GameEngineRasterizer();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete;


public:	

	static GameEngineRasterizer* Create(
		const std::string& _name,
		const D3D11_RASTERIZER_DESC& _desc
	);
	void Setting();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

private:
	void Create(const D3D11_RASTERIZER_DESC& _desc);

private:
	ID3D11RasterizerState* rasterizerState_;		//�����Ͷ������� ���� ����� ���⿡ �����ؼ� ���������ο� �����Ѵ�.
	//ID3D11RasterizerState* wireState_;	//�ʸ�尡 ���̾��� �����Ͷ����� ������Ʈ.

	//typedef struct D3D11_RASTERIZER_DESC
	//{
	//	D3D11_FILL_MODE FillMode;		�������� �մ� �� ���̸� ä���� ���� �����ϴ� �ɼ�.
	//	D3D11_CULL_MODE CullMode;		�յ޸� �� ��� ���� �ø����� �����ϴ� �ɼ�.
	//	BOOL FrontCounterClockwise;		�ݽð�������� ��ġ�� �������� �������� ��������, �� �ݴ�� ���� �����ϴ� �ɼ�.
	//	INT DepthBias;					���� ���̾ƽ�??
	//	FLOAT DepthBiasClamp;			���� ���̾ƽ� Ŭ����??
	//	FLOAT SlopeScaledDepthBias;		??
	//	BOOL DepthClipEnable;			���� Ŭ���� ���� ����.
	//	BOOL ScissorEnable;				�������ʱ� �ø�(������ �簢�� ���� ��� ��Ҹ� �׸��� ����) ���� ����.
	//	BOOL MultisampleEnable;			��Ƽ���ø� ���� ����.
	//	BOOL AntialiasedLineEnable;		�� ��Ƽ�ٸ���� ���� ����.
	//} 	D3D11_RASTERIZER_DESC;

	D3D11_RASTERIZER_DESC rasterizerDesc_;		//�����Ͷ����� ���� ����.

};

