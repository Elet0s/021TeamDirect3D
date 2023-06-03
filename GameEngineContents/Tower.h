#pragma once
#include "Skill.h"

// 설명 :
class Tower : public Skill
{
public:
	// constrcuter destructer
	Tower();
	~Tower();

	// delete Function
	Tower(const Tower& _Other) = delete;
	Tower(Tower&& _Other) noexcept = delete;
	Tower& operator=(const Tower& _Other) = delete;
	Tower& operator=(Tower&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

