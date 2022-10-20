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
	if (true == _keyName.empty())	//이름없는 키는 생성금지.
	{
		MsgBoxAssert("키의 이름이 없습니다.");
		return;
	}

	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	std::pair<std::map<std::string, GameEngineKey>::iterator, bool> insertResult = allKeys_.insert(
		std::make_pair(uppercaseKeyName, GameEngineKey()));

	if (false == insertResult.second)
	{
		MsgBoxAssertString(insertResult.first->first + ": 같은 이름의 키가 이미 존재합니다.");
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
	//여기서 keyPair는 키 그 자체가 아니라 allKeys_에 저장된 원본 키의 값복사된 복사본이므로, 
	//업데이트에서 변경된 변경사항을 원본 키로 '넘겨주지 않고' 소멸된다.

	//for (const std::pair<std::string, GameEngineKey>& keyPair : allKeys_)
	//{
	//	GameEngineKey tempKey = keyPair.second;
	//	tempKey.Update(_deltaTime);
	//	이것도 복사생성.
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
	//여기서 keyPair는 키 그 자체가 아니라 allKeys_에 저장된 원본 키의 값복사된 복사본이고, 
	//업데이트에서 변경된 변경사항을 원본 키로 넘겨주지 않고 소멸된다.

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
		MsgBoxAssertString(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}

	return allKeys_[uppercaseKeyName].time_;
}

bool GameEngineInput::IsDown(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);
	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isDown_;
}

bool GameEngineInput::IsPressed(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isPressed_;
}

bool GameEngineInput::IsUp(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}

	return allKeys_[uppercaseKeyName].isUp_;
}

bool GameEngineInput::IsFree(const std::string& _keyName)
{
	std::string uppercaseKeyName = GameEngineString::ToUpperReturn(_keyName);

	if (allKeys_.end() == allKeys_.find(uppercaseKeyName))
	{
		MsgBoxAssertString(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
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
	//키들이 전부 값형으로 스택영역에 저장되어 있기 때문에 특별한 메모리 해제 절차가 필요 없다.
}