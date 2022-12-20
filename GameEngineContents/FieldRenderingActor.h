#pragma once

class FieldObjectData
{
	friend class FieldRenderingActor;

	float4 worldPosition_;	//������Ʈ ������ǥ.
	const float4 worldScale_;	//������Ʈ ����ũ��.
	const int atlasDataIndex_;	//������Ʈ�� ��Ʋ�󽺵����� ��ȣ.

	FieldObjectData(const float4& _worldPosition, const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}

};

class FieldRenderingActor: public GameEngineActor
{
	//�� Ŭ������ ���� ����: ��� �ʵ� ������Ʈ���� �׸��⸸ �ϴ� ����.

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

	//�ʵ巻�������� �ʱ�ȭ �Լ�.
	void Initialize(
		size_t _totalFieldObjectCount,	//��ü �ʵ������Ʈ ����.
		size_t _objectInWindowCount,	//������ �ȿ� ��ġ�� �ִ� �ʵ������Ʈ ����.
		const float4& _totalFieldSize,	//��ü �ʵ� ũ��.
		float _diffusionDegree = 1.f	//�ʵ������Ʈ Ȯ�굵.
	);

private:
	//
	void InitializeFieldRenderer(size_t _objectInWindowCount);

	//
	void InitializeFieldObjects(
		size_t _totalFieldObjectCount,	//��ü �ʵ������Ʈ ����.
		size_t _objectInWindowCount,	//������ �ȿ� ��ġ�� �ִ� �ʵ������Ʈ ����.
		const float4& _fieldSize,		//��ü �ʵ� ũ��.
		float _diffusionDegree = 1.f	//�ʵ������Ʈ Ȯ�굵.
	);

	//Ÿ�� �ؽ�ó ���ġ.
	void UpdateTilePosition(const float4& _thisWorldPosition);

	//ȭ�� �ȿ� ������ �ʵ� ������Ʈ�鸸 �����ؼ� �׸��� �ϴ� �Լ�.
	void UpdateFieldObjectInfos(const float4& _thisWorldPosition);

	//�÷��̾� ��ġ���� �ʹ� ���� ��� �ʵ������Ʈ���� ���ġ�ϴ� �Լ�.
	void LoopFieldObject(const float4& _thisWorldPosition);

private:
	const float tileSize_;		//Ÿ���ؽ�ó ���α���. 
	//���簢���̹Ƿ� �Ѱ��� ����ϴ�.

	const float4 windowSize_;

	const float4 tileCountXY_;	//���� Ÿ���ؽ�ó ���μ��� ����.

	const int tileCount_;	//���� Ÿ���ؽ�ó ��ü ����.

	float4 totalFieldSize_;	//��ü �ʵ� ũ��.

	std::shared_ptr<GameEngineInstancingRenderer> fieldRenderer_;	//�ν��Ͻ� ������.

	std::shared_ptr<GameEngineInstancingRenderer> fieldObjectShadowRenderer_;	//�ʵ������Ʈ �׸��� ������.

	std::vector<AtlasData> fieldObjectAtlasDatas_;	//�ʵ� ������Ʈ�� ��Ʋ�󽺵����� ����.

	std::vector<FieldObjectData> allFieldObjectDataVector_;	//�� ���Ͱ� ���� ��� �ʵ������Ʈ���� ������ ����.
	//������ ���̵� ���̵� ������� ���� ������ �ְ� �Ѵ�.

	std::vector<FieldObjectData*> renderingFieldObjectDataVector_;	//ȭ�� �ȿ� ���� �ʵ� ������Ʈ���� ������ ����.
	//������ �ȿ� ���� �ʵ� ������Ʈ���� ������ ������ �ִٰ� �ν��Ͻ����ֵ鿡�� �����Ѵ�


	RenderOption renderOption_;
};

