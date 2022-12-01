#include "PreCompile.h"
#include "DeathAura.h"
#include "Player.h"
//#include <memory>

DeathAura::DeathAura() 
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
{
	
}

DeathAura::~DeathAura() 
{
}



void DeathAura::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(damege * PlayerInfo_.atk_).substr(0, std::to_string(damege * PlayerInfo_.atk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(attackSpeed * PlayerInfo_.pushSpeed_).substr(0, std::to_string(attackSpeed * PlayerInfo_.pushSpeed_).find(".") + 3);
	std::string sRange = std::to_string(rangeSize * PlayerInfo_.range_).substr(0, std::to_string(rangeSize * PlayerInfo_.range_).find(".") + 3);
	
	etc_ = "���� ���� ��ó ������ ����\n���ظ� �����ϴ�\nġ��Ÿ�� �߻����� �ʽ��ϴ�\n" + sDamege + " �� ����\n" + sAttackSpeed + "�� ���� ����\n���� "
		+ sRange + "m ";
}

void DeathAura::Effect()
{
	level_ += 1;
	if(level_ >= 5)
	{
		damege += 0.75f;
		rangeSize += 0.25f;
	}

	else if (level_ % 2 == 0)
	{
		damege += 0.38f;
		rangeSize += 0.5f;
	}

	else if (level_ % 2 == 1)
	{
		damege += 0.37f;
		rangeSize += 0.5f;
	}
}
