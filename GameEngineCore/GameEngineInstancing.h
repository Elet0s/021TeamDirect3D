#pragma once
#include "GameEngineShaderResourceHelper.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancing
{
	//이 클래스의 존재 이유:

	friend class GameEngineCamera;
	//인스턴스는 셰이더리소스이므로 게임엔진카메라가 필요로 하는 정보가 매우 많아서 프렌드로 한다.

	friend class GameEngineRenderer;
	//게임엔진렌더러 클래스가 인스턴싱의 셰이더리소스헬퍼와 카운트를 필요로 하는 이유는??


public:
	static unsigned int minInstancingCount_;
	static unsigned int startInstancingCount_;

public:
	GameEngineInstancing();
	~GameEngineInstancing();

protected:
	GameEngineInstancing(const GameEngineInstancing& _other) = delete;
	GameEngineInstancing(GameEngineInstancing&& _other) noexcept = delete;

private:
	GameEngineInstancing& operator=(const GameEngineInstancing& _other) = delete;
	GameEngineInstancing& operator=(const GameEngineInstancing&& _other) = delete;


public:
	void InstancingBufferChangeData();

public:



private:
	// 렌더유닛이 키의 역할도 해야 합니다.
	// 완전히 동일하다는건
	// 똑같은 쉐이더
	// 똑같은 매쉬
	// 똑같은 상수버퍼
	// 똑같은 텍스처를 쓴다는 것.

	std::shared_ptr<class GameEngineRenderUnit> renderUnit_;

	GameEngineInstancingBuffer* instancingBuffer_;

	std::vector<char> dataBuffer_;
	GameEngineShaderResourceHelper shaderResourceHelper_;

	int dataInsert_;
	size_t size_;
	unsigned int count_;
	int maxDataCount_;


};

