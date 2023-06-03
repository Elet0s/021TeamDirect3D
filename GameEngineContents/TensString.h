#pragma once
#include "Skill.h"

// 설명 :
class TensString : public Skill
{
public:
	// constrcuter destructer
	TensString();
	~TensString();

	// delete Function
	TensString(const TensString& _Other) = delete;
	TensString(TensString&& _Other) noexcept = delete;
	TensString& operator=(const TensString& _Other) = delete;
	TensString& operator=(TensString&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

