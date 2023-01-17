#pragma once
#include "GameEngineRes.h"

class GameEngineStructuredBuffer : public GameEngineRes<GameEngineStructuredBuffer>
{
	//

	friend GameEngineRes<GameEngineStructuredBuffer>;
	//GameEngineStructuredBuffer Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend class GameEngineStructuredBufferSetter;
	//GameEngineStructuredBufferSetter Ŭ�������� ���ҽ����� �Լ��� ȣ���ϱ� ���� ������.

private:
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _other) = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer&& _other) = delete;

public:
	//�̸���Ģ: �ν��Ͻ̿� ����ȭ���۴� Inst_�� ����.

	static GameEngineStructuredBuffer* Create(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);
	static GameEngineStructuredBuffer* Find(const std::string_view& _name, size_t _byteWidth);
	static GameEngineStructuredBuffer* CreateOrFind(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count
	);

private:
	void ChangeData(const void* _data, size_t _byteWidth);

	//����ȭ ���۸� �������̴��� �����ϴ� �Լ�.
	void VSSetShaderResource(int _bindPoint);

	//����ȭ ���۸� ��ǻƮ���̴��� �����ϴ� �Լ�.
	void CSSetShaderResource(int _bindPoint);

	//����ȭ ���۸� �ȼ����̴��� �����ϴ� �Լ�.
	void PSSetShaderResource(int _bindPoint);


	void VSResetShaderResource(int _bindPoint);
	void PSResetShaderResource(int _bindPoint);

public:
	static void ResourceDestroy();
	//GameEngineRes�� ���ҽ����� �����̳ʸ� �� �� �����Ƿ� ���� �����̳ʸ� ���� ����� ���ҽ� ������ ���� ������ �ٽ� ������ �Ѵ�.


public:
	inline size_t GetDataSize()
	{
		return dataUnitSize_;
	}

protected:
	static GameEngineStructuredBuffer* CreateNamedRes(const std::string_view& _name, size_t _byteWidth);
	//GameEngineRes�� ���ҽ����� �����̳ʸ� �� �� �����Ƿ� ���� �����̳ʸ� ���� ����� ���ҽ� ������ ���� ������ �ٽ� ������ �Ѵ�.


private:
	void CreateOrResize(
		const D3D11_SHADER_BUFFER_DESC& _desc,
		size_t _count,
		void* _initialData = nullptr
	);
	void CreateStructuredBuffer(size_t _dataUnitSize, size_t _count, void* _initialData = nullptr);

	void CreateOrResize(size_t _count, void* _initialData = nullptr);

	void Release();


private:
	static std::map<std::string, std::map<size_t, GameEngineStructuredBuffer*>> allStructuredBuffers_;
	//�Ϲ����� GameEngineRes<ResType> ���ҽ������ �ٸ��� �̸��� ũ�⸦ �� �� �����ϰ� �����غ��� �ϹǷ� 
	// ���߸� ������ ���� �����̳ʿ� �����ϰ� �����Ҷ��� ���� �����Ѵ�.

	ID3D11Buffer* structuredBuffer_;
	D3D11_BUFFER_DESC structuredBufferDesc_;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU_;	//����ȭ������ �����͸� ���� �׷���ī�� �� �޸��� �ּҰ�.

	ID3D11ShaderResourceView* shaderResourceView_;	//���̴� ���ҽ���.
	//����ȭ���۴� �������� ���̴� ���ҽ��� �з��ǹǷ� ���̴� ���ҽ� �䰡 �ʿ��ϴ�.

	size_t count_;	//������ ����.
	size_t dataUnitSize_;		//������ ���� ũ��.
	bool isInitialized_;	//�ʱ�ȭ ����.
};

