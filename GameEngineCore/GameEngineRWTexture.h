#pragma once
#include "GameEngineRes.h"

class GameEngineTexture;
class GameEngineRWTexture: public GameEngineRes<GameEngineRWTexture>
{
	//순서없는 액세스뷰 생성, 관리용 클래스.

public:
	GameEngineRWTexture();
	~GameEngineRWTexture();

private:
	GameEngineRWTexture(const GameEngineRWTexture& _other) = delete;
	GameEngineRWTexture(GameEngineRWTexture&& _other) noexcept = delete;
	GameEngineRWTexture& operator=(const GameEngineRWTexture& _other) = delete;
	GameEngineRWTexture& operator=(const GameEngineRWTexture&& _other) = delete;


public:	
	static GameEngineRWTexture* Create(const std::string& _name);
	static GameEngineRWTexture* Create();
	
	void CreateUnorderedAccessTexture(
		D3D11_TEXTURE2D_DESC _desc,
		const float4& _clearColor
	);
	
	void CreateUnorderedAccessTexture(
		GameEngineTexture* _texture,
		const float4& _clearColor
	);

	void CSSetUnorderedAccessView(int _bindPoint);	//해당 리소스를 디바이스 컨텍스트에 연결하는 함수.

	//이 텍스처가 가진 순서없는 접근뷰를 한 가지 값으로 전부 덮어서 초기화하는 함수.
	void Clear();



private:
	//순서없는 연결용으로 사용할 텍스쳐들.
	std::vector<GameEngineTexture*> unorderedAccessTexture_;

	//위 텍스처로 만든 순서없는 연결뷰들.
	std::vector<ID3D11UnorderedAccessView*> unorderedAccessViews_;

	//순서없는 연결뷰 초기화값.
	std::vector<float4> clearColors_;

};

