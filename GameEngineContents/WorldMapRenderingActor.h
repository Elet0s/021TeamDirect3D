#pragma once

class WorldObjectData
{
	friend class WorldMapRenderingActor;

	float4 worldPosition_;	//오브젝트 월드좌표.
	const float4 worldScale_;	//오브젝트 월드좌표.
	const int atlasDataIndex_;	//오브젝트의 아틀라스데이터 번호.

	WorldObjectData(const float4& _worldPosition, const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}
};

// 설명 :
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

	//필드렌더링액터 초기화 함수.
	void Initialize(
		size_t _totalFieldObjectCount,	//전체 필드오브젝트 개수.
		size_t _objectInWindowCount	//윈도우 안에 배치될 최대 필드오브젝트 개수.
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


	const float tileSize_;		//타일텍스처 가로길이. 
	//정사각형이므로 한개로 충분하다.

	const float4 windowSize_;

	const float4 tileCountXY_;	//사용된 타일텍스처 가로세로 개수.

	const int tileCount_;	//사용된 타일텍스처 전체 개수.

	GameEngineInstancingRenderer* worldRenderer_;	//인스턴싱 렌더러.


	std::vector<AtlasData> worldObjectAtlasDatas_;	//필드 오브젝트별 아틀라스데이터 모음.

	std::vector<WorldObjectData> allWorldObjectDataVector_;	//이 액터가 가진 모든 오브젝트의 렌더링 정보(타일 포함).
	//윈도우 안이든 밖이든 상관없이 전부 가지고 있는다.

	std::vector<WorldObjectData*> renderingFieldObjectDataVector_;	//화면 안에 들어온 필드 오브젝트들의 렌더링 정보.
	//윈도우 안에 들어온 필드 오브젝트들의 정보만 가지고 있다가 인스턴싱유닛들에게 전달한다.
};


