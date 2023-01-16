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
	//�⺻ ���콺������ <-> ���Ӷ��� ���콺 ������ ��ü �Լ�. �����ʿ����� ����� ��.
	void ChangeMousePointerRenderer(bool _isAiming);

	//���Ӷ��� �Ǻ� ��ġ ������Ʈ �Լ�. �����ʿ����� ����� ��.
	void UpdatePivotPosition(const float4& _renderPivot);

	//���콺 �����Ͱ� �־��� ������ǥ�� �޽��� ����Ű�� �ִ��� �����ϴ� �Լ�.
	bool IsPointing(const float4x4& _worldWorldMatrix, const float4& _pivot, bool _isUI = false);
	//"Rect"�޽� �������� ������.

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

	float4 mousePositionInWorldSpace_;	//���彺���̽� ���콺 ��ġ.
	float4 pivotWorldPosition_;	//���Ӷ��� �Ǻ��� ���� ������.
	bool isAiming_;	//true: ���Ӷ��� ���콺�����ͷ� ����. false: �⺻ ���콺������ ���.
	float aimLineAngle_;
	float4 localVertexPosition_[4];	//"Rect"�޽��� 4�� ������ ������ǥ ����. 
};