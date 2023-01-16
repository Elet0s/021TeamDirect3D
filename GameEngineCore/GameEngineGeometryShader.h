#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineGeometryShader: public GameEngineRes<GameEngineGeometryShader>, public GameEngineShader
{
	//������Ʈ�� ���̴�.
	//���ؽ����̴����� �־��� ���� ���� ��, ��, �ﰢ�� ���� ��ü���� �⺻ ������ �����ؼ� �����Ͷ������� �ѱ�� ���̴�.
	//���ؽ����̴� ��, �����Ͷ����� ������ ����ȴ�.

	friend GameEngineRes<GameEngineGeometryShader>;
	//GameEngineGeometryShader Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend GameEngineShader;
	//GameEngineGeometryShader�� Load() �Լ��� GameEngineShaderŬ�������� ȣ���ϱ� ���� ������.

private:
	GameEngineGeometryShader();
	~GameEngineGeometryShader();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineGeometryShader(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&& _other) noexcept = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader& _other) = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader&& _other) = delete;


public:
	void Set();

private:
	static GameEngineGeometryShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEngineGeometryShader* Load(
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

