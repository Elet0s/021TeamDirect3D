#pragma once

class GameEngineTransformBase
{

public:
	GameEngineTransformBase();
	virtual ~GameEngineTransformBase();

protected:
	GameEngineTransformBase(const GameEngineTransformBase& _other) = delete;
	GameEngineTransformBase(GameEngineTransformBase&& _other) noexcept = delete;

private:
	GameEngineTransformBase& operator=(const GameEngineTransformBase& _other) = delete;
	GameEngineTransformBase& operator=(const GameEngineTransformBase&& _other) = delete;


public:	
	GameEngineTransform& GetTransform()
	{
		return transform_;
	}

	const TransformData& GetTransformData()
	{
		return transform_.GetTransformData();
	}


private:
	GameEngineTransform transform_;

	//Ʈ�������� �������� �����ϴ� ����(Ʈ�������� �����Ҵ����� ������ �� ��� ����� ����): 
	//�⺻������ ĳ���� ������ ������ �����͵��� ���������� ������ ��ġ�Ҽ��� ȿ���� ����������, 
	// �Ϲ����� ����������� ���ڰ� ���� �Ѱ��� ũ�Ⱑ ũ�� ��Ÿ�� ������ �޸� ���並 �����ϱ� ��Ʊ� ������ 
	// �������� �����ؼ� ���������� �����͸� ������ ��ġ�ؼ� ĳ�� ���߷��� ����÷����� ����� ���� ��º���, 
	// ��Ը� ������ �� �޸� ���� ���� ���и� ����� ��Ը� �޸� ������ ���� ���� ���ϰ� �� ũ��. 
	// �׷��� �����Ҵ��ؼ� �ּҰ��� �����ϴ°��� �� ȿ�����̴�.
	//������ Ʈ�������� ��������� ũ�Ⱑ ���� ������ float������ �����̶�, 
	// �����Ҵ��� �ؼ� �����Ͱ� ��������� ����� ���� ���ϰ� �ٸ� ��������鿡 ���� �� ũ��,
	// ��Ÿ�� ���� �޸� ��뷮�� ���� �����ϹǷ� �����Ҵ��� �ʿ伺�� ����.
	// �׷��� Ʈ�������� �������� �����ϴ°��� �� ȿ�����̴�.


};

