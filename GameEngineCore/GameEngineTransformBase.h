#pragma once

class GameEngineTransformBase
{

public:
	GameEngineTransformBase();
	virtual ~GameEngineTransformBase();

protected:
	GameEngineTransformBase(const GameEngineTransformBase& _other) = delete;
	GameEngineTransformBase(GameEngineTransformBase&& _other) noexcept = delete;

private:
	GameEngineTransformBase& operator=(const GameEngineTransformBase& _other) = delete;
	GameEngineTransformBase& operator=(const GameEngineTransformBase&& _other) = delete;


public:	
	GameEngineTransform& GetTransform()
	{
		return transform_;
	}

	const TransformData& GetTransformData()
	{
		return transform_.GetTransformData();
	}


private:
	GameEngineTransform transform_;

	//트랜스폼을 값형으로 저장하는 이유(트랜스폼을 동적할당으로 저장할 때 대비 생기는 이익): 
	//기본적으로 캐시의 지역성 때문에 데이터들은 물리적으로 가깝게 배치할수록 효율이 좋아지지만, 
	// 일반적인 멤버변수들은 숫자가 적고 한개의 크기가 크며 런타임 이전에 메모리 수요를 예측하기 어렵기 때문에 
	// 값형으로 저장해서 물리적으로 데이터를 가깝게 배치해서 캐시 적중률을 끌어올렸을때 생기는 성능 상승보다, 
	// 대규모 값복사 및 메모리 수요 예측 실패를 대비한 대규모 메모리 점유로 인한 성능 저하가 더 크다. 
	// 그래서 동적할당해서 주소값만 저장하는것이 더 효율적이다.
	//하지만 트랜스폼은 상대적으로 크기가 작은 수많은 float값들의 집합이라서, 
	// 동적할당을 해서 데이터가 흩어졌을때 생기는 성능 저하가 다른 멤버변수들에 비해 더 크고,
	// 런타임 전에 메모리 사용량이 예측 가능하므로 동적할당의 필요성이 낮다.
	// 그래서 트랜스폼은 값형으로 저장하는것이 더 효율적이다.


};

