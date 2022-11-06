#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

class GameEnginePixelShader: public GameEngineRes<GameEnginePixelShader>, public GameEngineShader
{
	//�ȼ����̴�: �� �ȼ��� ������ �����Ѵ�.

	friend GameEngineRes<GameEnginePixelShader>;
	//GameEnginePixelShader Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend GameEngineShader;

private:
	GameEnginePixelShader();
	~GameEnginePixelShader();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete;


public:
	void Setting();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

private:
	static GameEnginePixelShader* Load(
		const std::string_view& _path,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0);
	static GameEnginePixelShader* Load(
		const std::string_view& _path,
		const std::string_view& _name,
		const std::string_view& _entryPoint,
		UINT _versionHigh = 5,
		UINT _versionLow = 0);
	void CreatePixelShader();

private:
	ID3D11PixelShader* pixelShader_;

};

