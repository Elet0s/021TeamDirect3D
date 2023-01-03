#pragma once
//only Box
class BoxObject : public GameEngineActor
{
public:
	BoxObject();
	~BoxObject();


	BoxObject(const BoxObject& _Other) = delete;
	BoxObject(BoxObject&& _Other) noexcept = delete;
	BoxObject& operator=(const BoxObject& _Other) = delete;
	BoxObject& operator=(BoxObject&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:

};