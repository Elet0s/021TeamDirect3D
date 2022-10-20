#pragma once

template<typename ResType>
class GameEngineRes: public GameEngineNameObject
{
	//리소스 클래스들의 중복되는 코드를 재활용하기 위한 템플릿 목적의 클래스.

	//템플릿 클래스를 상속하면, 상속받은 클래스 형식의 새 클래스가 만들어지는것과 같다.
	// 그러므로, 아래 컨테이너도 상속받은 클래스 개수만큼 생성된다.


protected:
	GameEngineRes(): isOriginal_(true) {}
	~GameEngineRes() {}	//ResourceDestroy()함수에서 각 리소스클래스 소멸자들을 직접 호출하므로 virtual을 붙이지 않아도 문제 없다.

	GameEngineRes(const GameEngineRes& _other) = delete;
	GameEngineRes(GameEngineRes&& _other) noexcept = delete;
	GameEngineRes& operator=(const GameEngineRes& _other) = delete;
	GameEngineRes& operator=(GameEngineRes&& _other) = delete;

public:
	static ResType* Find(const std::string& _resName)
	{
		std::string uppercaseResName = GameEngineString::ToUpperReturn(_resName);

		typename std::map<std::string, ResType*>::iterator findIter = namedRes_.find(uppercaseResName);
		if (namedRes_.end() == findIter)
		{
			return  nullptr;
		}
		else
		{
			return findIter->second;
		}
	}

	//리소스 전체 삭제 함수. 이 프로그램의 모든 리소스는 이 함수로 삭제/정리되어야만 한다.
	static void ResourceDestroy()
	{
		for (std::pair<std::string, ResType*> resPair : namedRes_)
		{
			if (nullptr != resPair.second)
			{
				delete resPair.second;
				resPair.second = nullptr;
			}
		}

		for (ResType* res : unnamedRes_)
		{
			if (nullptr != res)
			{
				delete res;
				res = nullptr;
			}
		}

		//사실 리소스를 프로그램 끝날때까지 안 지워도 해결되는 문제지만,
		//그래도 막을 수 있는건 최대한 다 막아둔다.
	}

	bool IsOriginal()
	{
		return isOriginal_;
	}


protected:
	static std::map<std::string, ResType*> namedRes_;
	static std::list<ResType*> unnamedRes_;
	bool isOriginal_;

protected:
	static ResType* CreateNamedRes(const std::string& _resName = "")
	{
		ResType* newRes = CreateRes(_resName);
		std::pair<std::map<std::string, ResType*>::iterator, bool> insertResult = 
			namedRes_.insert(std::make_pair(newRes->GetNameConstRef(), newRes));

		if (false == insertResult.second)
		{
			MsgBoxAssertString(newRes->GetNameConstRef() + ": 이미 존재하는 리소스 이름입니다.");
			return nullptr;
		}

		return newRes;
	}

	static ResType* CreateUnnamedRes()
	{
		ResType* newRes = CreateRes();
		unnamedRes_.push_back(newRes);
		return newRes;
	}

	static ResType* CreateRes(const std::string& _resName = "")
	{
		std::string uppercaseResName = GameEngineString::ToUpperReturn(_resName);

		ResType* newRes = new ResType();
		newRes->SetName(uppercaseResName);

		return newRes;
	}

private:




};

//템플릿을 가진 정적 멤버변수는 초기화를 여기서 한다.
template<typename ResType>
std::map<std::string, ResType*> GameEngineRes<ResType>::namedRes_;

template<typename ResType>
std::list<ResType*> GameEngineRes<ResType>::unnamedRes_;
