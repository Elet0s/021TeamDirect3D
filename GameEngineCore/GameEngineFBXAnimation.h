#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"

class GameEngineFBXAnimation: public GameEngineRes<GameEngineFBXAnimation>, public GameEngineFBX
{
	friend GameEngineRes<GameEngineFBXAnimation>;
	//GameEngineFBXAnimation 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	//$resourcetype$ resource_;
	//리소스타입에 맞게 고칠 것.

private:
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineFBXAnimation(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation&& _other) = delete;


public:	
	static GameEngineFBXAnimation* Create(const std::string& _name);

	void Setting();	//해당 리소스를 렌더링 파이프라인에 연결하는 함수.

};

