#pragma once

class WorldObjectData
{
	friend class WorldMapRenderingActor;

	float4 worldPosition_;	//������Ʈ ������ǥ.
	const float4 worldScale_;	//������Ʈ ������ǥ.
	const int atlasDataIndex_;	//������Ʈ�� ��Ʋ�󽺵����� ��ȣ.

	WorldObjectData(const float4& _worldPosition, const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}
};

// ���� :
class WorldMapRenderingActor : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapRenderingActor();
	~WorldMapRenderingActor();

	// delete Function
	WorldMapRenderingActor(const WorldMapRenderingActor& _Other) = delete;
	WorldMapRenderingActor(WorldMapRenderingActor&& _Other) noexcept = delete;
	WorldMapRenderingActor& operator=(const WorldMapRenderingActor& _Other) = delete;
	WorldMapRenderingActor& operator=(WorldMapRenderingActor&& _Other) noexcept = delete;

public:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	//�ʵ巻�������� �ʱ�ȭ �Լ�.
	void Initialize(
		size_t _totalFieldObjectCount,	//��ü �ʵ������Ʈ ����.
		size_t _objectInWindowCount	//������ �ȿ� ��ġ�� �ִ� �ʵ������Ʈ ����.
	);

private:
	//
	void InitializeFieldRenderer(size_t _objectInWindowCount);

	//
	void InitializeFieldObjects(
		size_t _totalFieldObjectCount,
		size_t _objectInWindowCount
	);


	void UpdateFieldObjectInfos(const float4& _thisWorldPosition);

private:
	void treeObejctSetting();


	const float tileSize_;		//Ÿ���ؽ�ó ���α���. 
	//���簢���̹Ƿ� �Ѱ��� ����ϴ�.

	const float4 windowSize_;

	const float4 tileCountXY_;	//���� Ÿ���ؽ�ó ���μ��� ����.

	const int tileCount_;	//���� Ÿ���ؽ�ó ��ü ����.

	GameEngineInstancingRenderer* worldRenderer_;	//�ν��Ͻ� ������.


	std::vector<AtlasData> worldObjectAtlasDatas_;	//�ʵ� ������Ʈ�� ��Ʋ�󽺵����� ����.

	std::vector<WorldObjectData> allWorldObjectDataVector_;	//�� ���Ͱ� ���� ��� ������Ʈ�� ������ ����(Ÿ�� ����).
	//������ ���̵� ���̵� ������� ���� ������ �ִ´�.

	std::vector<WorldObjectData*> renderingFieldObjectDataVector_;	//ȭ�� �ȿ� ���� �ʵ� ������Ʈ���� ������ ����.
	//������ �ȿ� ���� �ʵ� ������Ʈ���� ������ ������ �ִٰ� �ν��Ͻ����ֵ鿡�� �����Ѵ�.
};


