#pragma once
#include "GameEngineRes.h"

class GameEngineStructuredBuffer : public GameEngineRes<GameEngineStructuredBuffer>
{
	friend GameEngineRes<GameEngineStructuredBuffer>;
	//GameEngineStructuredBuffer Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend class GameEngineStructuredBufferSetter;

	friend class GameEngineFBXMesh;

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
	static GameEngineStructuredBuffer* CreateStructuredBuffer(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		int _dataCount
	);
	static GameEngineStructuredBuffer* Find(const std::string_view& _name, int _byteWidth);
	static GameEngineStructuredBuffer* CreateAndFind(
		const std::string_view& _name,
		const D3D11_SHADER_BUFFER_DESC& _desc,
		int _dataCount
	);

	void ChangeData(const void* _data, size_t _dataSize);

	//����ȭ ���۸� ������ ������������ �������̴��� �����ϴ� �Լ�.
	void VSSetting(int _bindPoint);

	//����ȭ ���۸� ������ ������������ �ȼ����̴��� �����ϴ� �Լ�.
	void PSSetting(int _bindPoint);


	void VSReset(int _bindPoint);
	void PSReset(int _bindPoint);


	static void ResourceDestroy();
	//GameEngineRes�� ���ҽ����� �����̳ʸ� �� �� �����Ƿ� ���� �����̳ʸ� ���� ����� ���ҽ� ������ ���� ������ �ٽ� ������ �Ѵ�.


public:
	inline size_t GetDataSize()
	{
		return dataUnitSize_;
	}

protected:
	static GameEngineStructuredBuffer* CreateNamedRes(const std::string_view& _name, int _byteWidth);
	//GameEngineRes�� ���ҽ����� �����̳ʸ� �� �� �����Ƿ� ���� �����̳ʸ� ���� ����� ���ҽ� ������ ���� ������ �ٽ� ������ �Ѵ�.


private:
	void CreateOrResize(
		const D3D11_SHADER_BUFFER_DESC& _desc,
		unsigned int _count,
		void* _initialData = nullptr
	);
	void CreateOrResize(unsigned int _dataUnitSize, unsigned int _count, void* _initialData = nullptr);
	void CreateOrResize(unsigned int _count, void* _initialData = nullptr);

	void Release();


private:
	static std::map<std::string, std::map<int, GameEngineStructuredBuffer*>> allStructuredBuffers_;
	//�Ϲ����� GameEngineRes<ResType> ���ҽ������ �ٸ��� �̸��� ũ�⸦ �� �� �����ϰ� �����غ��� �ϹǷ� 
	// ���߸� ������ ���� �����̳ʿ� �����ϰ� �����Ҷ��� ���� �����Ѵ�.

	ID3D11Buffer* structuredBuffer_;
	D3D11_BUFFER_DESC structuredBufferDesc_;
	D3D11_SHADER_BUFFER_DESC shaderBufferDesc_;
	D3D11_MAPPED_SUBRESOURCE destMemoryPtrInGPU_;	//����ȭ������ �����͸� ���� �׷���ī�� �� �޸��� �ּҰ�.

	ID3D11ShaderResourceView* shaderResourceView_;	//���̴� ���ҽ���.
	//����ȭ���۴� �������� ���̴� ���ҽ��� �з��ǹǷ� ���̴� ���ҽ� �䰡 �ʿ��ϴ�.

	unsigned int dataCount_;	//������ ����.
	unsigned int dataUnitSize_;		//������ ���� ũ��.
	bool isInit_;	//�ʱ�ȭ ����.
};

