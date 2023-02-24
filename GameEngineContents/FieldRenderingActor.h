#pragma once

class FieldObjectData
{
	friend class FieldRenderingActor;

	float4 worldPosition_;	//오브젝트 월드좌표.
	const float4 worldScale_;	//오브젝트 월드크기.
	const int atlasDataIndex_;	//오브젝트의 아틀라스데이터 번호.

	FieldObjectData(const float4& _worldPosition, const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}

};

class FieldRenderingActor: public GameEngineActor
{
	//이 클래스의 존재 이유: 모든 필드 오브젝트들과 그 그림자들을 그리기만 하는 액터.

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
		const float4& _totalFieldSize,	//전체 필드 크기.
		float _diffusionDegree = 1.f	//필드오브젝트 확산도.
	);

	inline void SetLightingRotation(float _lightingRotationX, float _lightingRotationY)
	{
		renderOption_.lightingRotationX_ = _lightingRotationX;
		renderOption_.lightingRotationY_ = _lightingRotationY;
	}

private:
	//필드렌더러, 필드오브젝트 그림자 렌더러 초기화.
	void InitializeFieldRenderer(size_t _objectInWindowCount);

	//모든 필드오브젝트 정보 초기화. 
	void InitializeFieldObjects(
		size_t _totalFieldObjectCount,	//전체 필드오브젝트 개수.
		size_t _objectInWindowCount,	//윈도우 안에 배치될 최대 필드오브젝트 개수.
		const float4& _fieldSize,		//전체 필드 크기.
		float _diffusionDegree = 1.f	//필드오브젝트 확산도.
	);

	//타일 텍스처 재배치.
	void UpdateTilePosition(const float4& _thisWorldPosition);

	//화면 안에 들어오는 필드 오브젝트들만 선별해서 그리게 하는 함수.
	void UpdateFieldObjectInfos(const float4& _thisWorldPosition);

	//플레이어 위치에서 너무 많이 벗어난 필드오브젝트들을 재배치하는 함수.
	void LoopFieldObject(const float4& _thisWorldPosition);

private:
	const float tileSize_;		//타일텍스처 가로길이. 
	//타일텍스처가 정사각형이므로 한개로 충분하다.

	const float4 windowSize_;

	const float4 tileCountXY_;	//사용된 타일텍스처 가로세로 개수.

	const int tileCount_;	//사용된 타일텍스처 전체 개수.

	float4 totalFieldSize_;	//전체 필드 크기.

	GameEngineInstanceRenderer* fieldRenderer_;	//인스턴싱 렌더러.
								
	GameEngineInstanceRenderer* fieldObjectShadowRenderer_;	//필드오브젝트 그림자 렌더러.

	std::vector<AtlasData> fieldObjectAtlasDatas_;	//필드 오브젝트별 아틀라스데이터 모음.

	std::vector<FieldObjectData> allFieldObjectDataVector_;	//이 액터가 가진 모든 필드오브젝트들의 렌더링 정보.
	//윈도우 안이든 밖이든 상관없이 전부 가지고 있게 한다.

	std::vector<FieldObjectData*> renderingFieldObjectDataVector_;	//화면 안에 들어온 필드 오브젝트들의 렌더링 정보.
	//윈도우 안에 들어온 필드 오브젝트들의 정보만 가지고 있다가 인스턴싱유닛들에게 전달한다


	RenderOption renderOption_;
};

