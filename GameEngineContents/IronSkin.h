#pragma once
#include "Skill.h"

// Ό³Έν :
class IronSkin : public Skill
{
public:
	// constrcuter destructer
	IronSkin();
	~IronSkin();

	// delete Function
	IronSkin(const IronSkin& _Other) = delete;
	IronSkin(IronSkin&& _Other) noexcept = delete;
	IronSkin& operator=(const IronSkin& _Other) = delete;
	IronSkin& operator=(IronSkin&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

