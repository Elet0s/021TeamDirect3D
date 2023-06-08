#pragma once
#include "GameEngineRes.h"

class GameEngineTexture;
class GameEngineRWTexture: public GameEngineRes<GameEngineRWTexture>
{
	//�������� �׼����� ����, ������ Ŭ����.

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

	void CSSetUnorderedAccessView(int _bindPoint);	//�ش� ���ҽ��� ����̽� ���ؽ�Ʈ�� �����ϴ� �Լ�.

	//�� �ؽ�ó�� ���� �������� ���ٺ並 �� ���� ������ ���� ��� �ʱ�ȭ�ϴ� �Լ�.
	void Clear();



private:
	//�������� ��������� ����� �ؽ��ĵ�.
	std::vector<GameEngineTexture*> unorderedAccessTexture_;

	//�� �ؽ�ó�� ���� �������� ������.
	std::vector<ID3D11UnorderedAccessView*> unorderedAccessViews_;

	//�������� ����� �ʱ�ȭ��.
	std::vector<float4> clearColors_;

};

