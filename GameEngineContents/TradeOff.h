#pragma once
#include "Skill.h"

// Ό³Έν :
class TradeOff : public Skill
{
public:
	// constrcuter destructer
	TradeOff();
	~TradeOff();

	// delete Function
	TradeOff(const TradeOff& _Other) = delete;
	TradeOff(TradeOff&& _Other) noexcept = delete;
	TradeOff& operator=(const TradeOff& _Other) = delete;
	TradeOff& operator=(TradeOff&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

