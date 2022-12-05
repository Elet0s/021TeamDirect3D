#pragma once
#include "Skill.h"

class Area : public Skill
{
public:
	// constrcuter destructer
	Area();
	~Area();

	// delete Function
	Area(const Area& _Other) = delete;
	Area(Area&& _Other) noexcept = delete;
	Area& operator=(const Area& _Other) = delete;
	Area& operator=(Area&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

