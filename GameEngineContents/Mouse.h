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
	void ChangeMousePointerRenderer(bool _isAiming);
	void UpdateAimingPivot(const float4& _pivot);


	//inline void GetCurPos()
	//{
	//	POINT Pos_;
	//	GetCursorPos(&Pos_);
	//	mousePositionInWorldSpace_.x =(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x);
	//	mousePositionInWorldSpace_.y =(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y);
	//	ScreenToClient(GameEngineWindow::GetHWND(), &Pos_);
	//	mousePositionInWindow_.x = static_cast<float>(Pos_.x);
	//	mousePositionInWindow_.y = static_cast<float>(Pos_.y);
	//}

	//static std::shared_ptr<Mouse> GetMouseInfo()
	//{
	//	return mainMouse_;
	//}

	//inline float4  IsCurPosToWindow()
	//{
	//	return mousePositionInWindow_;
	//}

	//inline float4  IsCurPosToClient()
	//{
	//	 return mousePositionInWorldSpace_;
	//}

	const float4& GetCurrentWorldPosition()
	{
		return this->GetTransform().GetWorldPosition();
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> defaultPointerRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> crossHairRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> aimLineRenderer_;
	std::shared_ptr<GameEngineCollision> mouseCollision_;

	float4 mousePositionInWindow_;		//������ ��ǥ�� ���콺 ��ġ.
	float4 mousePositionInWorldSpace_;	//���彺���̽� ���콺 ��ġ.
	float4 pivotWorldPosition_;	//���Ӷ��� �Ǻ��� ���� ������.
	bool isAiming_;
};