#pragma once

class FieldObjectData
{
	friend class FieldRenderingActor;

	float4 worldPosition_;	//오브젝트 월드좌표.
	const float4 worldScale_;	//오브젝트 월드좌표.
	const int atlasDataIndex_;	//오브젝트의 아틀라스데이터 번호.

	FieldObjectData(float4& _worldPosition,const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}

};

class FieldRenderingActor: public GameEngineActor
{
	//이 클래스의 존재 이유: 모든 필드 오브젝트들을 그리기만 하는 액터.

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

	//필드렌더링액터 초기화 함수.
	void Initialize(
		size_t _totalFieldObjectCount,	//전체 필드오브젝트 개수.
		size_t _objectInWindowCount,	//윈도우 안에 배치될 최대 필드오브젝트 개수.
		const float4& _totalFieldSize		//전체 필드 크기.
		//float _diffusionDegree = 1.f	//필드오브젝트 확산도.
		//필드오브젝트 배치 함수.
	);

private:
	//
	void InitializeFieldRenderer(size_t _objectInWindowCount);

	//
	void InitializeFieldObjects(
		size_t _totalFieldObjectCount,
		size_t _objectInWindowCount,
		const float4& _fieldSize
		//float _diffusionDegree = 1.f
	);

	//
	void UpdateTilePosition(const float4& _thisWorldPosition);

	//
	void UpdateFieldObjectInfos(const float4& _thisWorldPosition);


	void LoopFieldObject(const float4& _thisWorldPosition);
private:
	const float tileSize_;		//타일텍스처 가로길이. 
	//정사각형이므로 한개로 충분하다.

	const float4 windowSize_;

	const float4 tileCountXY_;	//사용된 타일텍스처 가로세로 개수.

	const int tileCount_;	//사용된 타일텍스처 전체 개수.

	std::shared_ptr<GameEngineInstancingRenderer> fieldRenderer_;	//인스턴싱 렌더러.

	float4 curPos_;
	float4 moveDir_;


	std::vector<AtlasData> fieldObjectAtlasDatas_;	//필드 오브젝트별 아틀라스데이터 모음.

	std::vector<FieldObjectData> allFieldObjectDataVector_;	//이 액터가 가진 모든 필드오브젝트들의 렌더링 정보.
	//윈도우 안이든 밖이든 상관없이 전부 가지고 있는다.

	std::vector<FieldObjectData*> renderingFieldObjectDataVector_;	//화면 안에 들어온 필드 오브젝트들의 렌더링 정보.
	//윈도우 안에 들어온 필드 오브젝트들의 정보만 가지고 있다가 인스턴싱유닛들에게 전달한다.
};

