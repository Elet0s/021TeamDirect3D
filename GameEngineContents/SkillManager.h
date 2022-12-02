#pragma once

class SkillManager :public GameEngineActor
{
public:
	SkillManager();
	~SkillManager();


	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
//	std::vector<std::shared_ptr<Skill>> skillList_;
};