#pragma once
#include "Skill.h"

class SkillManager//:GameEngineUpdateObject // 스킬매니저의 역할 = 게임시작할때 모든 스킬을 하나씩 만들고 스킬레벨에 따라 활성시켜주는 역할
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

	void CreatePlayerAllSkill();// 스킬별로 엑터하나씩만들고 자료구조안에 집어넣어주는 함수 1회만 실행
	void SkillLevelCheak(); //스킬 레벨0보다 크면 업데이트 시켜주는 함수
private:

	 GameEngineLevel* myLevel_;
	std::vector <std::vector<std::shared_ptr <Skill>>> skillList_;
};