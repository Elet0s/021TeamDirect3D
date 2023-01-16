#pragma once

//class MyLock
//{
//public:
//	std::mutex& LockInst;
//
//public:
//	MyLock(std::mutex& _Lock)
//		: LockInst(_Lock)
//	{
//		LockInst.lock();
//	}
//
//	~MyLock()
//	{
//		LockInst.unlock();
//	}
//};

template<typename ResType>
class GameEngineRes : public GameEngineNameObject
{
	//리소스 클래스들의 중복되는 코드를 재활용하기 위한 템플릿 목적의 클래스.

	//템플릿 클래스를 상속하면, 상속받은 클래스 형식의 새 클래스가 만들어지는것과 같다.
	// 그러므로, 아래 컨테이너도 상속받은 클래스 개수만큼 생성된다.


protected:
	GameEngineRes() /*: isOriginal_(true)*/ {}
	~GameEngineRes() {}	//ResourceDestroy()함수에서 각 리소스클래스 소멸자들을 직접 호출하므로 virtual을 붙이지 않아도 문제 없다.

	GameEngineRes(const GameEngineRes& _other) = delete;
	GameEngineRes(GameEngineRes&& _other) noexcept = delete;
	GameEngineRes& operator=(const GameEngineRes& _other) = delete;
	GameEngineRes& operator=(GameEngineRes&& _other) = delete;

public:
	static ResType* Find(const std::string_view& _resName)
	{
		typename std::map<std::string, ResType*>::iterator findIter;
		{
			std::lock_guard<std::mutex> lockInst(namedResLock_);
			//std::lock_guard<std::mutex>: std::mutex의 래퍼 클래스.
			//지역변수로 생성되면서 생성자 매개변수로 넣어진 std::mutex 객체의 lock() 함수를 호출해서 메모리에 접근제한을 걸고,
			//스코프가 닫히고 소멸될 때 소멸자에서 std::mutex의 unlock() 함수를 호출해서 메모리에 걸린 접근제한을 해제하게 한다.
			//그래서 한번 생성만 해 두면 자동으로 잠금과 해제를 해 준다.

			findIter = namedRes_.find(GameEngineString::ToUpperReturn(_resName));
			if (namedRes_.end() == findIter)
			{
				return  nullptr;
			}
		}

		return findIter->second;
	}

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

	//bool IsOriginal()
	//{
	//	return isOriginal_;
	//}

	void SetPath(const std::string& _path)
	{
		path_ = _path;
	}

	void SetPath(const std::string_view& _path)
	{
		path_ = _path;
	}

	const std::string& GetPath() const
	{
		return path_;
	}


protected:
	static ResType* CreateNamedRes(const std::string_view& _resName = "")
	{
		ResType* newRes = CreateRes(_resName);

		std::pair<std::map<std::string, ResType*>::iterator, bool> insertResult;

		{
			std::lock_guard<std::mutex> lockInst(namedResLock_);
			//std::lock_guard<std::mutex>: std::mutex의 래퍼 클래스.
			//지역변수로 생성되면서 생성자 매개변수로 넣어진 std::mutex 객체의 lock() 함수를 호출해서 메모리에 접근제한을 걸고,
			//스코프가 닫히고 소멸될 때 소멸자에서 std::mutex의 unlock() 함수를 호출해서 메모리에 걸린 접근제한을 해제하게 한다.
			//그래서 한번 생성만 해 두면 자동으로 잠금과 해제를 해 준다.
			insertResult = namedRes_.insert(std::make_pair(newRes->GetNameCopy(), newRes));
		}

		if (false == insertResult.second)
		{
			MsgBoxAssertString(newRes->GetNameCopy() + ": 이미 존재하는 리소스 이름입니다.");
			return nullptr;
		}

		return newRes;
	}

	static ResType* CreateUnnamedRes()
	{
		ResType* newRes = CreateRes();
		std::lock_guard<std::mutex> lockInst(unnamedResLock_);
		unnamedRes_.push_back(newRes);
		return newRes;
	}

	static ResType* CreateRes(const std::string_view& _resName = "")
	{
		ResType* newRes = new ResType();
		if (nullptr == newRes)
		{
			MsgBoxAssert("newRes 생성 실패!");
			return nullptr;
		}
		newRes->SetName(GameEngineString::ToUpperReturn(_resName));

		return newRes;
	}

protected:
	//bool isOriginal_;
	std::string path_;

private:
	static std::map<std::string, ResType*> namedRes_;
	static std::list<ResType*> unnamedRes_;

	static std::mutex namedResLock_;	//namedRes_의 뮤텍스.
	static std::mutex unnamedResLock_;	//unnamedRes_의 뮤텍스.
	//0번스레드가 1번스레드가 namedRes_와 unnamedRes_에 뭔가 작업하는 동안 2번스레드가 어느 컨테이너에 접근할 지
	// 알 수 없으므로 각 컨테이너마다 각각의 뮤텍스가 필요하다.

	//std::mutex: 여러 스레드들이 공유할 수 있는 특정 메모리 영역에 한개 스레드만 접근할 수 있게 해서
	// 경쟁 상태(Race Condition) 발생을 예방하는 클래스.
	// 잠긴 메모리는 사실상 싱글스레딩 상태가 되어 멀티스레딩의 의미가 사라지므로 남발해선 안된다.
	//lock()함수로 메모리를 잠근 상태에서 같은 스레드에서 한번 더 lock() 함수를 호출하거나 unlock()함수 호출을 잊어버리면
	//잠금 해제가 안되는 deadlock상태가 되어 다시는 그 메모리에 접근할 수 없게 된다.
	//mutex는 mutual exclusion(상호 배제)의 줄임말이라고 한다.

	//경쟁 상태(Race Condition): 여러 스레드가 공유하는 메모리의 데이터에 동시에 접근해서 연산의 결과가 왜곡되는 상태. 
};

//템플릿을 가진 정적 멤버변수는 초기화를 여기서 한다.
template<typename ResType>
std::map<std::string, ResType*> GameEngineRes<ResType>::namedRes_;

template<typename ResType>
std::list<ResType*> GameEngineRes<ResType>::unnamedRes_;

template<typename ResType>
std::mutex GameEngineRes<ResType>::namedResLock_;

template<typename ResType>
std::mutex GameEngineRes<ResType>::unnamedResLock_;