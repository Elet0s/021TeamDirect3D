#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayoutDesc;
class GameEngineVertexShader;
class GameEngineInputLayout : public GameEngineRes<GameEngineInputLayout>
{
	//��ǲ���̾ƿ�: 
	//��ǲ ����� �ܰ迡�� �׷���ī�� �޸𸮿� ����� �޽��� ��� ��������(���ؽ� ����)�� � �������� �����Ǿ��ִ����� 
	// ���� ������ ���ؽ����̴����� �ѱ�� ���� �������̽�.
	//�����ϴµ� ���ؽ� ������ ���ؽ����̴��� ��� �ʿ��ϴ�.

	friend GameEngineRes<GameEngineInputLayout>;
	//GameEngineInputLayout Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

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

	//??
	static GameEngineInputLayout* Create(
		const GameEngineInputLayoutDesc& _desc,
		GameEngineVertexShader* _vertexShader
	);

private:
	//??
	void CreateInputLayout(
		const GameEngineInputLayoutDesc& _desc,
		GameEngineVertexShader* _vertexShader
	);

private:
	ID3D11InputLayout* inputLayout_;

};

