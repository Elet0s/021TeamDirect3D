#pragma once
#include "Skill.h"

class SkillManager//:GameEngineUpdateObject // ��ų�Ŵ����� ���� = ���ӽ����Ҷ� ��� ��ų�� �ϳ��� ����� ��ų������ ���� Ȱ�������ִ� ����
{
public:

	SkillManager();
	~SkillManager();


	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;


	void SetLevel(GameEngineLevel* _thisLevel)
	{
		myLevel_ = _thisLevel;
	}
	std::vector <std::vector<std::shared_ptr <Skill>>>& GetSkillList()
	{
		return skillList_;
	}

	void CreatePlayerAllSkill();// ��ų���� �����ϳ�������� �ڷᱸ���ȿ� ����־��ִ� �Լ� 1ȸ�� ����
	void SkillLevelCheak(); //��ų ����0���� ũ�� ������Ʈ �����ִ� �Լ�
private:

	 GameEngineLevel* myLevel_;
	std::vector <std::vector<std::shared_ptr <Skill>>> skillList_;
};