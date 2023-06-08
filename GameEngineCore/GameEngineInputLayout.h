#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayoutDesc;
class GameEngineVertexShader;
class GameEngineInputLayout : public GameEngineRes<GameEngineInputLayout>
{
	//인풋레이아웃: 
	//인풋 어셈블러 단계에서 그래픽카드 메모리에 저장된 메쉬의 모든 구조정보(버텍스 정보)가 어떤 형식으로 구성되어있는지에 
	// 대한 정보를 버텍스셰이더에게 넘기기 위한 인터페이스.
	//생성하는데 버텍스 정보와 버텍스셰이더가 모두 필요하다.

	friend GameEngineRes<GameEngineInputLayout>;
	//GameEngineInputLayout 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineMaterial;
	//??


private:
	GameEngineInputLayout();
	~GameEngineInputLayout();

	GameEngineInputLayout(const GameEngineInputLayout& _other) = delete;
	GameEngineInputLayout(GameEngineInputLayout&& _other) noexcept = delete;
	GameEngineInputLayout& operator=(const GameEngineInputLayout& _other) = delete;
	GameEngineInputLayout& operator=(const GameEngineInputLayout&& _other) = delete;


public:
	void Set();

	//인풋 레이아웃 생성 함수. 
	static GameEngineInputLayout* Create(
		const GameEngineInputLayoutDesc& _desc,
		GameEngineVertexShader* _vertexShader
	);

private:
	//ID3D11InputLayout* 생성 함수.
	void CreateInputLayout(
		const GameEngineInputLayoutDesc& _desc,
		GameEngineVertexShader* _vertexShader
	);

private:
	ID3D11InputLayout* inputLayout_;

};

