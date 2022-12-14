#pragma once
#include "PreCompile.h"

class ContentsCore: public GameEngineCore
{

public:

	ContentsCore();
	~ContentsCore();

	ContentsCore(const ContentsCore& _other) = delete;
	ContentsCore(ContentsCore&& _other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _other) = delete;
	ContentsCore& operator=(ContentsCore&& _other) = delete;

public:

public:
	std::string GetWindowTitle() override
	{
		return "Rogue Genesia";
	}

	float4 StartWindowSize() override
	{
		return float4(1280, 720);
	}

	float4 StartWindowPosition() override
	{
		return float4(100, 100);
	}


	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;



private:
	void LoadContentsShader();
	void LoadContentsResource();

};

