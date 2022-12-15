#pragma once
#include "Skill.h"

// Ό³Έν :
class Student : public Skill
{
public:
	// constrcuter destructer
	Student();
	~Student();

	// delete Function
	Student(const Student& _Other) = delete;
	Student(Student&& _Other) noexcept = delete;
	Student& operator=(const Student& _Other) = delete;
	Student& operator=(Student&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

