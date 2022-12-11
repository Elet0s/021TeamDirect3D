#pragma once

class FieldObjectData
{
	friend class FieldRenderingActor;

	const float4 worldPosition_;	//오브젝트 월드좌표.
	const float4 worldScale_;	//오브젝트 월드좌표.
	const int atlasDataIndex_;	//오브젝트의 아틀라스데이터 번호.

	FieldObjectData(const float4& _worldPosition,const float4& _worldScale, int _atlasDataIndex)
		: worldPosition_(_worldPosition),
		worldScale_(_worldScale),
		atlasDataIndex_(_atlasDataIndex)
	{
	}

};

class FieldRenderingActor: public GameEngineActor
{
	//이 클래스의 존재 이유: 모든 필드 오브젝트들을 그리기만 하는 액터.

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
	const float tileSize_;		//타일텍스처 가로길이. 
	//정사각형이므로 한개로 충분하다.

	const float4 windowSize_;

	const float4 tileCountXY_;	//사용된 타일텍스처 가로세로 개수.

	const int tileCount_;	//사용된 타일텍스처 전체 개수.

	GameEngineInstancingRenderer* fieldRenderer_;	//인스턴싱 렌더러.




	std::vector<AtlasData> fieldObjectAtlasDatas_;	//필드 오브젝트별 아틀라스데이터 모음.

	std::vector<FieldObjectData> allFieldObjectDataVector_;	//이 액터가 가진 모든 필드오브젝트들의 렌더링 정보.
	//윈도우 안이든 밖이든 상관없이 전부 가지고 있는다.

	std::vector<FieldObjectData*> renderingFieldObjectDataVector_;	//화면 안에 들어온 필드 오브젝트들의 렌더링 정보.
	//윈도우 안에 들어온 필드 오브젝트들의 정보만 가지고 있다가 인스턴싱유닛들에게 전달한다.
};

