#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayoutDesc;
class GameEngineVertexShader;
class GameEngineInputLayout : public GameEngineRes<GameEngineInputLayout>
{
	//��ǲ���̾ƿ�: 
	//��ǲ ����� �ܰ迡�� �׷���ī�� �޸𸮿� ����� �޽��� ��� ��������(���ؽ� ����)�� � �������� �����Ǿ��ִ����� 
	// ���� ������ ���ؽ����̴����� �ѱ�� ���� �������̽�.

	friend class GameEngineMaterial;


public:
	GameEngineInputLayout();
	~GameEngineInputLayout();

private:
	GameEngineInputLayout(const GameEngineInputLayout& _other) = delete;
	GameEngineInputLayout(GameEngineInputLayout&& _other) noexcept = delete;
	GameEngineInputLayout& operator=(const GameEngineInputLayout& _other) = delete;
	GameEngineInputLayout& operator=(const GameEngineInputLayout&& _other) = delete;


public:
	void Setting();

	//
	static std::shared_ptr<GameEngineInputLayout> Create(
		const GameEngineInputLayoutDesc& _desc,
		std::shared_ptr<GameEngineVertexShader> _vertexShader);

private:
	void CreateInputLayout(
		const GameEngineInputLayoutDesc& _desc,
		std::shared_ptr<GameEngineVertexShader> _vertexShader);

private:
	ID3D11InputLayout* inputLayout_;

};

