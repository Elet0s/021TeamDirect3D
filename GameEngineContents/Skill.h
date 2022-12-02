#pragma once

class Skill : public GameEngineActor
{
public:
	Skill();
	virtual ~Skill();

	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;
	
	
	virtual void Init() {};
	virtual void Effect() {};

	int Getlevel()
	{
		return level_;
	}

	int GetMaxLevel()
	{
		return maxLevel_;
	}

	void CreatSkill();

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	std::string etc_;
	int level_;
	int maxLevel_;
private:
};

