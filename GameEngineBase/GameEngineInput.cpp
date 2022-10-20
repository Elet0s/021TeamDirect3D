#include "PreCompile.h"
#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineInput* GameEngineInput::inst_ = new GameEngineInput();

void GameEngineInput::GameEngineKey::Update(float _deltaTime)
{
	if (0 != GetAsyncKeyState(this->keyValue_))
	{
		if (true == isFree_)
		{
			isDown_ = true;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
			time_ = _deltaTime;
		}
		else if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
			time_ += _deltaTime;
		}
	}
	else
	{
		if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = true;
			isFree_ = false;
			time_ = 0.0f;
		}
		else if (true == isUp_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = false;
			isFree_ = true;
		}
	}
}

void GameEngineInput::CreateKey(const std::string& _keyName, int _keyValue)
{
	if (true == _keyName.empty())	//�̸����� Ű�� ��������.
	{
		MsgBoxAssert("Ű�� �̸��� �����ϴ�.");
		return;
	}

	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	std::pair<std::map<std::string, GameEngineKey>::iterator, bool> insertResult = allKeys_.insert(
		std::make_pair(uppercaseKeyName, GameEngineKey()));

	if (false == insertResult.second)
	{
		MsgBoxAssertString(insertResult.first->first + ": ���� �̸��� Ű�� �̹� �����մϴ�.");
		return;
	}

	allKeys_[uppercaseKeyName].keyValue_ = _keyValue;
	allKeys_[uppercaseKeyName].Reset();
}

void GameEngineInput::Update(float _deltaTime)
{
	curWheelValue_ = wheelValue_;
	wheelValue_ = 0;

	//for (std::pair<std::string, GameEngineKey> keyPair : allKeys_)
	//{
	//	keyPair.second.Update(_deltaTime);
	//}
	//���⼭ keyPair�� Ű �� ��ü�� �ƴ϶� allKeys_�� ����� ���� Ű�� ������� ���纻�̹Ƿ�, 
	//������Ʈ���� ����� ��������� ���� Ű�� '�Ѱ����� �ʰ�' �Ҹ�ȴ�.

	//for (const std::pair<std::string, GameEngineKey>& keyPair : allKeys_)
	//{
	//	GameEngineKey tempKey = keyPair.second;
	//	tempKey.Update(_deltaTime);
	//	�̰͵� �������.
	//}

	for (std::map<std::string, GameEngineKey>::iterator iter = allKeys_.begin();
		iter != allKeys_.end(); iter++)
	{
		iter->second.Update(_deltaTime);
	}

}

void GameEngineInput::Reset()
{
	curWheelValue_ = 0;
	wheelValue_ = 0;

	//for (std::pair<std::string, GameEngineKey> keyPair : allKeys_)
	//{
	//	keyPair.second.Reset();
	//}
	//���⼭ keyPair�� Ű �� ��ü�� �ƴ϶� allKeys_�� ����� ���� Ű�� ������� ���纻�̰�, 
	//������Ʈ���� ����� ��������� ���� Ű�� �Ѱ����� �ʰ� �Ҹ�ȴ�.

	for (std::map<std::string, GameEngineKey>::iterator iter = allKeys_.begin();
		iter != allKeys_.end(); iter++)
	{
		iter->second.Reset();
	}
}

float GameEngineInput::GetTime(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}

	return allKeys_[uppercaseKeyName].time_;
}

bool GameEngineInput::IsDown(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);
	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isDown_;
}

bool GameEngineInput::IsPressed(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isPressed_;
}

bool GameEngineInput::IsUp(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isUp_;
}

bool GameEngineInput::IsFree(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isFree_;
}

bool GameEngineInput::IsKey(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	return allKeys_.end() != allKeys_.find(uppercaseKeyName);
}

GameEngineInput::GameEngineInput() : wheelValue_(0), curWheelValue_(0)
{
}

GameEngineInput::~GameEngineInput()
{
	//Ű���� ���� �������� ���ÿ����� ����Ǿ� �ֱ� ������ Ư���� �޸� ���� ������ �ʿ� ����.
}