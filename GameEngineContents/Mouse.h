#pragma once

class Mouse : public GameEngineActor
{

public:
	Mouse();
	~Mouse();

	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

public:
	//기본 마우스포인터 <-> 에임라인 마우스 포인터 교체 함수. 전투맵에서만 사용할 것.
	void ChangeMousePointerRenderer(bool _isAiming);

	//에임라인 피봇 위치 업데이트 함수. 전투맵에서만 사용할 것.
	void UpdatePivotPosition(const float4& _renderPivot);

	//마우스 포인터가 넣어준 월드좌표의 메쉬를 가리키고 있는지 판정하는 함수.
	bool IsPointing(const float4x4& _worldWorldMatrix, const float4& _pivot, bool _isUI = false);
	//"Rect"메쉬 기준으로만 구현함.

public:
	float GetAimLineAngle() const
	{
		return aimLineAngle_;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* defaultPointerRenderer_;
	GameEngineTextureRenderer* crossHairRenderer_;
	GameEngineTextureRenderer* aimLineRenderer_;

	float4 mousePositionInWorldSpace_;	//월드스페이스 마우스 위치.
	float4 pivotWorldPosition_;	//에임라인 피봇의 월드 포지션.
	bool isAiming_;	//true: 에임라인 마우스포인터로 변경. false: 기본 마우스포인터 사용.
	float aimLineAngle_;
	float4 localVertexPosition_[4];	//"Rect"메쉬의 4개 정점의 로컬좌표 모음. 
};