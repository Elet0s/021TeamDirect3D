#include"PreCompile.h"
#include"Spear.h"

#include "Player.h"


Spear::Spear()
	: damege(0.75f)
	, attackSpeed(0.25f)
	, rangeSize(2.0f)
{

}
Spear::~Spear()
{

}

void Spear::Init()
{
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(damege * PlayerInfo_->atk_).substr(0, std::to_string(damege * PlayerInfo_->atk_).find(".") + 3);
	std::string sAttackSpeed = std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).substr(0, std::to_string(attackSpeed * PlayerInfo_->pushSpeed_).find(".") + 3);
	std::string sRange = std::to_string(rangeSize * PlayerInfo_->range_).substr(0, std::to_string(rangeSize * PlayerInfo_->range_).find(".") + 3);

	etc_ = "���� ���� ��ó ������ ����\n���ظ� �����ϴ�\nġ��Ÿ�� �߻����� �ʽ��ϴ�\n" + sDamege + " �� ����\n" + sAttackSpeed + "�� ���� ����\n���� "
		+ sRange + "m ";
}
void Spear::Effect()
{

}