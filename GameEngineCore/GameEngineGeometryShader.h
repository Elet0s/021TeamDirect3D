#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineGeometryShader: public GameEngineRes<GameEngineGeometryShader>, public GameEngineShader
{
	//������Ʈ�� ���̴�.
	//���ؽ����̴����� �־��� ���� ���� ��, ��, �ﰢ�� ���� ��ü���� �⺻ ������ �����ؼ� �����Ͷ������� �ѱ�� ���̴�.
	//���ؽ����̴� ��, �����Ͷ����� ������ ����ȴ�.

	friend GameEngineShader;

public:
	GameEngineGeometryShader();
	~GameEngineGeometryShader();

private:
	GameEngineGeometryShader(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&& _other) noexcept = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader&& _other) = delete;


public:
	void Set();

private:
	static std::shared_ptr<GameEngineGeometryShader> Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static std::shared_ptr<GameEngineGeometryShader> Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void CreateGeometryShader();

private:
	ID3D11GeometryShader* geometryShader_;

};

