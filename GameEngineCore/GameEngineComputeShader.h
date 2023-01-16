#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"


class GameEngineComputeShader: public GameEngineRes<GameEngineComputeShader>, public GameEngineShader
{


	friend GameEngineRes<GameEngineComputeShader>;
	//GameEngineComputeShader Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend GameEngineShader;
	//GameEngineComputeShader�� Load() �Լ��� GameEngineShaderŬ�������� ȣ���ϱ� ���� ������.


private:
	GameEngineComputeShader();
	~GameEngineComputeShader();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineComputeShader(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader(GameEngineComputeShader&& _other) noexcept = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader& _other) = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader&& _other) = delete;


public:	
	void Set();	

private:
	static GameEngineComputeShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	static GameEngineComputeShader* Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0
	);
	void CreateComputeShader();

private:
	ID3D11ComputeShader* computeShader_;

};

