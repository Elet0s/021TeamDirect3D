#pragma once
#include "GameEngineRes.h"


class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
	//���̽��ٽ� ������Ʈ ���� �� ���� Ŭ����.

	friend GameEngineRes<GameEngineDepthStencil>;
	//GameEngineDepthStencil Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineDepthStencil();
	~GameEngineDepthStencil();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineDepthStencil(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil&& _other) = delete;


public:
	static GameEngineDepthStencil* Create(
		const std::string_view& _name,
		const D3D11_DEPTH_STENCIL_DESC& _desc
	);
	void Set();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

private:
	void CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& _desc);

private:
	ID3D11DepthStencilState* depthStencilState_;	//������ ���������ο� ������ ���̽��ٽ� ������Ʈ

	//typedef struct D3D11_DEPTH_STENCIL_DESC
	//{
	//	BOOL DepthEnable;						�����׽�Ʈ�� Ȱ��ȭ ����.
	//	D3D11_DEPTH_WRITE_MASK DepthWriteMask;	�����׽�Ʈ ����� ���� ���� �����Ϳ� ���� �� ����??

	//		typedef 
	//		enum D3D11_DEPTH_WRITE_MASK
	//		{
	//			D3D11_DEPTH_WRITE_MASK_ZERO = 0,	���� ���� �����Ϳ� �� �� ��.
	//			D3D11_DEPTH_WRITE_MASK_ALL = 1		���� ���� �����Ϳ� �� ��.
	//		} 	D3D11_DEPTH_WRITE_MASK;
	// 
	// 
	//	D3D11_COMPARISON_FUNC DepthFunc;		�����׽�Ʈ ���.
	//	
	//		typedef 
	//		enum D3D11_COMPARISON_FUNC
	//		{
	//			D3D11_COMPARISON_NEVER = 1,			�ƹ��͵� �����Ű�� ����.
	//			D3D11_COMPARISON_LESS = 2,			���� ���� �͸� ���.
	//			D3D11_COMPARISON_EQUAL = 3,			���� ���� �͸� ���.
	//			D3D11_COMPARISON_LESS_EQUAL = 4,	���� �۰ų� ���� �͸� ���.
	//			D3D11_COMPARISON_GREATER = 5,		���� ū �͸� ���.
	//			D3D11_COMPARISON_NOT_EQUAL = 6,		���� ���� ���� �͸� ���.
	//			D3D11_COMPARISON_GREATER_EQUAL = 7,	���� ũ�ų� ���� �͸� ���.
	//			D3D11_COMPARISON_ALWAYS = 8			������ ���.
	//		} 	D3D11_COMPARISON_FUNC;			
	// 
	// 
	//	BOOL StencilEnable;						���ٽ��׽�Ʈ�� Ȱ��ȭ ����.
	//	UINT8 StencilReadMask;					??
	//	UINT8 StencilWriteMask;					??
	//	D3D11_DEPTH_STENCILOP_DESC FrontFace;	??
	//	D3D11_DEPTH_STENCILOP_DESC BackFace;	??
	//} 	D3D11_DEPTH_STENCIL_DESC;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc_;		//���̽��ٽ� ������Ʈ�� ���鶧 �ʿ��� �� ����.

};

