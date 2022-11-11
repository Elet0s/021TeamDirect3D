#pragma once
#include "GameEngineRes.h"


class GameEngineBlend : public GameEngineRes<GameEngineBlend>
{
	//���彺����Ʈ ����, ���� ���� ��� Ŭ����.
	//����: ���� ȥ�� �� �������� �����ϴ� ���.

public:
	GameEngineBlend();
	~GameEngineBlend();

private:

	GameEngineBlend(const GameEngineBlend& _other) = delete;
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete;


public:
	static std::shared_ptr<GameEngineBlend> Create(
		const std::string_view& _name,
		const D3D11_BLEND_DESC& _desc
	);
	void Setting();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

private:
	void Create(const D3D11_BLEND_DESC& _desc);

private:
	ID3D11BlendState* blendState_;	//������ ���������� �ƿ�ǲ���� �ܰ迡 ������ ���彺����Ʈ.

	//typedef struct D3D11_BLEND_DESC
	//{
	//	BOOL AlphaToCoverageEnable;							���ĺ������� ��Ƽ�ٸ������ �ϴ� ����� ���� �� Ŀ�������� ������ �� ����.
	//	BOOL IndependentBlendEnable;						���� ������ �������� ���� �������� ������ �� �� ����. 
	//														 true: 8���� ���� �������� ����.
	//														 false: 0�� �������� ������ �����.
	// 
	//	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];		����Ÿ�ٿ� ����� ���ĺ��� ������ ������ ������ D3D11_RENDER_TARGET_BLEND_DESC����ü �迭.
	//														 �ִ� 8�� ����Ÿ�ٿ� ���� �ٸ� ���ĺ��� ����� ������ �� �ִ�.

	//	typedef struct D3D11_RENDER_TARGET_BLEND_DESC
	//	{
	//		BOOL BlendEnable;						���ĺ����� �� �� ����.
	//		D3D11_BLEND SrcBlend;					���ĺ��� ������ srcFactor�� 4�� ���Ҹ� ��� ä���� �����ϴ� �ɼ�.
	//		D3D11_BLEND DestBlend;					���ĺ��� ������ destFactor�� 4�� ���Ҹ� ��� ä���� �����ϴ� �ɼ�.
	//		D3D11_BLEND_OP BlendOp;					���ĺ��� ������ �ɼ� �κп� � ������ �������� �����ϴ� �ɼ�.
	//		D3D11_BLEND SrcBlendAlpha;				srcColor�� ���İ� ����.
	//		D3D11_BLEND DestBlendAlpha;				destColor�� ���İ� ����.
	//		D3D11_BLEND_OP BlendOpAlpha;			���ĺ��� ������ �ɼ� �׸� ���ϱ� ����. ���İ� ��꿡�� ����ȴ�.
	//		UINT8 RenderTargetWriteMask;			������ ������ ����. RGBA�� ����� �����ؼ� ���ĺ����� ������ ���� �ִ�.
	//	} 	D3D11_RENDER_TARGET_BLEND_DESC;
	//
	//} 	D3D11_BLEND_DESC;

	// 
	//���ĺ��� ����.
	//output: ���� �����.
	//dest: ������� ���� ����.
	//src: ������� ����� ������ ������ ����.
	//�ɼ�: BlendOp���� �����ϴ� ���� ���� ���.
	//outputColor = (srcColor * srcFactor) �ɼ� (destColor * destFactor)


	D3D11_BLEND_DESC blendDesc_;		//���彺����Ʈ�� ���鶧 ����� ��������.
	float4 factor_;				//srcFactor�� destFactor�� ���� �Է��Ҷ� ����� ��. ����� ������� ����.
	unsigned int mask_;			//������ ������ ����. �����ϸ� �⺻���� ��� ���󿡼� �մ��� �� ��.

};

