#pragma once

template<typename ResType>
class GameEngineRes: public GameEngineNameObject
{
	//���ҽ� Ŭ�������� �ߺ��Ǵ� �ڵ带 ��Ȱ���ϱ� ���� ���ø� ������ Ŭ����.

	//���ø� Ŭ������ ����ϸ�, ��ӹ��� Ŭ���� ������ �� Ŭ������ ��������°Ͱ� ����.
	// �׷��Ƿ�, �Ʒ� �����̳ʵ� ��ӹ��� Ŭ���� ������ŭ �����ȴ�.


protected:
	GameEngineRes(): isOriginal_(true) {}
	~GameEngineRes() {}	//ResourceDestroy()�Լ����� �� ���ҽ�Ŭ���� �Ҹ��ڵ��� ���� ȣ���ϹǷ� virtual�� ������ �ʾƵ� ���� ����.

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

	//���ҽ� ��ü ���� �Լ�. �� ���α׷��� ��� ���ҽ��� �� �Լ��� ����/�����Ǿ�߸� �Ѵ�.
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

		//��� ���ҽ��� ���α׷� ���������� �� ������ �ذ�Ǵ� ��������,
		//�׷��� ���� �� �ִ°� �ִ��� �� ���Ƶд�.
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
			MsgBoxAssertString(newRes->GetNameConstRef() + ": �̹� �����ϴ� ���ҽ� �̸��Դϴ�.");
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

//���ø��� ���� ���� ��������� �ʱ�ȭ�� ���⼭ �Ѵ�.
template<typename ResType>
std::map<std::string, ResType*> GameEngineRes<ResType>::namedRes_;

template<typename ResType>
std::list<ResType*> GameEngineRes<ResType>::unnamedRes_;
