#pragma once

class FieldObjectData
{
	friend class FieldRenderingActor;

	const float4 worldPosition_;	//������Ʈ ������ǥ.
	const float4 worldScale_;	//������Ʈ ������ǥ.
	const int atlasDataIndex_;	//������Ʈ�� ��Ʋ�󽺵����� ��ȣ.

	FieldObjectData(const float4& _worldPosition,const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}

};

class FieldRenderingActor: public GameEngineActor
{
	//�� Ŭ������ ���� ����: ��� �ʵ� ������Ʈ���� �׸��⸸ �ϴ� ����.

	friend class TestLevel;
	friend class ShaderTestLevel;

public:
	FieldRenderingActor();
	~FieldRenderingActor();

protected:
	FieldRenderingActor(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor(FieldRenderingActor&& _other) noexcept = delete;

private:
	FieldRenderingActor& operator=(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor& operator=(const FieldRenderingActor&& _other) = delete;


public:	
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	//
	void InitializeFieldRenderer();
	void InitializeFieldObjects(
		size_t _fieldObjectCount,
		const float4& _fieldSize,
		std::function<void(const std::vector<FieldObjectData>& _fieldObjects)> _objectPlacementFunc = nullptr);
	void UpdateTilePosition(const float4& _thisWorldPosition);
	void UpdateFieldObjectInfos(const float4& _thisWorldPosition);

private:
	const float tileSize_;		//Ÿ���ؽ�ó ���α���. 
	//���簢���̹Ƿ� �Ѱ��� ����ϴ�.

	const float4 windowSize_;

	const float4 tileCountXY_;	//���� Ÿ���ؽ�ó ���μ��� ����.

	const int tileCount_;	//���� Ÿ���ؽ�ó ��ü ����.

	GameEngineInstancingRenderer* fieldRenderer_;	//�ν��Ͻ� ������.




	std::vector<AtlasData> fieldObjectAtlasDatas_;	//�ʵ� ������Ʈ�� ��Ʋ�󽺵����� ����.

	std::vector<FieldObjectData> allFieldObjectDataVector_;	//�� ���Ͱ� ���� ��� �ʵ������Ʈ���� ������ ����.
	//������ ���̵� ���̵� ������� ���� ������ �ִ´�.

	std::vector<FieldObjectData*> renderingFieldObjectDataVector_;	//ȭ�� �ȿ� ���� �ʵ� ������Ʈ���� ������ ����.
	//������ �ȿ� ���� �ʵ� ������Ʈ���� ������ ������ �ִٰ� �ν��Ͻ����ֵ鿡�� �����Ѵ�.
};

