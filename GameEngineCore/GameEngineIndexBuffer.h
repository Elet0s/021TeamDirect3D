#pragma once
#include "GameEngineRes.h"


class GameEngineIndexBuffer : public GameEngineRes<GameEngineIndexBuffer>
{
	//�ε�������: ���ؽ����̴��� ���� �Ѿ�� ������ ��� �����ų���� ���� ������ ���� ����.

	//�ε���: ���ؽ��� 1:1 �����Ǵ� ������ ��ȣ. 
	// ���� ������ ���� ���ؽ��� �Ź� �����ϰ� �ҷ����� �ͺ���,
	// �ε����� ���� ���ؽ��� �ʿ��� ��ŭ�� �ҷ����°��� ���귮�� �Ƴ� �� �ִٰ� �Ѵ�.

	//�׷��� ���ҽ��� �� ����(���ؽ� ����, �ε��� ����, ��� ����, ��Ʈ�� ��� ����)�� 
	// ���ҽ��� ���̵� ������ ���������ο� ������ �� �ִ�.

	friend GameEngineRes<GameEngineIndexBuffer>;
	//GameEngineIndexBufferŬ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _other) = delete;


public:
	static GameEngineIndexBuffer* Create(
		const std::string_view& _name,
		const void* _data,
		UINT _indexSize,
		UINT _indexCount
	);

	static GameEngineIndexBuffer* Create(
		const void* _data,
		UINT _indexSize,
		UINT _indexCount
	);

	void Set();

public:
	template<typename IndexType>
	static GameEngineIndexBuffer* Create(
		const std::string_view& _name,
		const std::vector<IndexType>& _indexes
	)
	{
		return Create(
			_name,
			&_indexes[0],
			static_cast<UINT>(sizeof(IndexType)),
			static_cast<UINT>(_indexes.size())
		);
	}

	template<typename IndexType>
	static GameEngineIndexBuffer* Create(
		const std::vector<IndexType>& _indexes
	)
	{
		return Create(
			&_indexes[0],
			static_cast<UINT>(sizeof(IndexType)),
			static_cast<UINT>(_indexes.size())
		);
	}

	inline UINT GetIndexCount() const
	{
		return indexCount_;
	}

private:
	void CreateIndexBuffer(const void* _initialData, UINT _indexSize, UINT _indexCount);

private:
	ID3D11Buffer* indexBuffer_;				//�ε����� ������ ����.

	//���� ���� ���� ����.
	D3D11_SUBRESOURCE_DATA resData_;	//������ �ʱⰪ.
	D3D11_BUFFER_DESC indexBufferDesc_;		//������ ���� ����.

	//���� ���� ���� ����.
	UINT indexSize_;					//�ε��� �Ѱ� ũ��.
	UINT indexCount_;					//�ε��� ����.
	UINT offset_;						//������ ������ ������, ���� ���������κ����� �Ÿ�(byte).

};

