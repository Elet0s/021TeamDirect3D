#pragma once
#include "GameEngineRes.h"

class GameEngineConstantBuffer : public GameEngineRes<GameEngineConstantBuffer>
{
	//��� ���� ���� �� ���� Ŭ����.

	//��� ����(Constant buffer): ���ؽ����̴� �� �ȼ����̴����� ���� ������� ��� ���� ����. 
	// ���⼭ ����� ���ӿ�������̽� Ŭ������ �ִ� RenderStart()�Լ��� ȣ���� ����, 
	// RenderEnd()�Լ��� ȣ��ɶ�����, �׷��ϱ� ������������������ ����Ǵ� ���� ������ �ʴ� ������ ����Ű�� ���̴�.
	// �Ѹ����, ������ GPU�� �Ѱ��ְ��� �ϴ� ������ ����.
	//��� ���۸� ����ϴ� ������ ���̴����� �Ź� ���Ǵ� ������� cpp ���Ͽ��� �������־�� �Ѵٰ� ������ ��,
	// ���������� �ϳ��ϳ� ���� ������ �ִ� �ͺ��� �Ѳ����� ��Ƶξ��ٰ� �����ؼ� �ű�� ���� ĳ���� ������ ������ ȿ���� �� ����.
	// ���� �ϳ��� ����ü�� ���� �������� �ϱ� ���� ��� ���۶�� ������ ����Ѵ�.
	//��� ������ �޸� ������, ũ�Ⱑ �ݵ�� �ּ� �ϵ���� �Ҵ� ũ��(16 ����Ʈ)�� ������� �Ѵ�.

	//������� ��ü�� ������� ���� ������ �򰥸��� �� ��.
	//������۴� ���̴��� �����ϵǰ� �����Ǵ� ������ ���� �����ȴ�.
	//���������� ������ ������۸� ���� �� ���� ���� �����Ƿ� ���� ����.
	
	
public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

protected:
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) noexcept = delete;

private:
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete;


public:	
	static GameEngineConstantBuffer* Create(
		const std::string_view& _name,	//������۴� �̸��� �ݵ�� �־�� �Ѵ�. �׷��� �ٸ� ���ҽ� �����Լ��ʹ� �ٸ��� �̸� �⺻���� ����.
		const D3D11_SHADER_BUFFER_DESC& _desc
	);
	static GameEngineConstantBuffer* Find(const std::string_view& _name, int _byteWidth);
	static GameEngineConstantBuffer* CreateAndFind(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc
	);



	//�� �������� �ٲ�� Ʈ������ ������ ���� ������۰� ���� ������ �׷���ī���� �޸𸮷� �����ϴ� �Լ�.
	void ChangeData(const void* _data, size_t _dataSize) const;
	//�������� ��������� �����ͼ����� ���⿡�� �Ѵ�.
	//��, ��� �Լ��� ȣ���ϹǷ� �ּ������� ����� ��.

	//������۸� ������ ������������ �������̴��� �����ϴ� �Լ�.
	void VSSetting(int _bindPoint);

	//������۸� ������ ������������ �ȼ����̴��� �����ϴ� �Լ�.
	void PSSetting(int _bindPoint);

	static void ResourceDestroy();

public:
	D3D11_BUFFER_DESC& GetBufferDesc()
	{
		return constantBufferDesc_;
	}

private:
	static GameEngineConstantBuffer* CreateNamedRes(const std::string_view& _name, int _byteWidth);
	void CreateConstantBuffer(const D3D11_SHADER_BUFFER_DESC& _desc);

private:
	static std::map<std::string, std::map<int, GameEngineConstantBuffer*>> allConstantBuffers_;
	//������۸� �̸��� ����Ʈ ũ��α��� �����ϱ� ���� ���� �� ���� ���.
	//�׷��� ���� ���̴����� �Ȱ��� ������۸� ���� ��쿡�� ������ ������ �ʴ´�.

	//typedef struct _D3D11_SHADER_BUFFER_DESC
	//{
	//	LPCSTR                  Name;		������� �̸�.
	//	D3D_CBUFFER_TYPE        Type;		��������� ����.
	//	UINT                    Variables;	��������� ������� ����.
	//	UINT                    Size;		������� ũ��.
	//	UINT                    uFlags;		������۰� ����� ������ �����ϴ� �÷���. 
	//} D3D11_SHADER_BUFFER_DESC;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_BUFFER_DESC constantBufferDesc_;


	ID3D11Buffer* constantBuffer_;


};