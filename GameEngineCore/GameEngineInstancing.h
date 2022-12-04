#pragma once
#include "GameEngineShaderResourceHelper.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancing
{
	//�� Ŭ������ ���� ����: �ν��Ͻ��������� �������ְ� �ν��Ͻ̼��̴��� ���� ���� ������ Ŭ����.

	static size_t maxInstancingCount_;

public:
	class InstancingData
	{
		//�� Ŭ������ ���� ����: �������ְ� ������ �յ� ����.
		//Ư�� ���� ������ �����ؼ� �ϱ� ����.

		friend GameEngineInstancing;

	public:
		InstancingData(std::shared_ptr<GameEngineRenderUnit> _renderUnit) : renderUnit_(_renderUnit)
		{
		}

		//InstancingData �ʱ�ȭ �Լ�.
		void Init(const std::set<std::string>& _shaderResourceHelperNames);

		//
		void Link(const std::string_view& _name, const void* _data);

	public:
		template<typename ValueType>
		void Link(const std::string_view& _name, ValueType& _data)
		{
			Link(_name, reinterpret_cast<const void*>(&_data));
		}

	private:
		std::shared_ptr<GameEngineRenderUnit> renderUnit_;	//��������.
		std::map<std::string, const void*> data_;		//
	};

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
	//�� �ν��Ͻ̿� ��������(�������ָ�??)�� ����ϴ� �Լ�.
	void PushUnit(std::shared_ptr<class GameEngineRenderUnit> _renderUnit, std::function<void(InstancingData&)> _function);
	void RenderInstancing(float _deltaTime);

private:
	//renderUnits_�� �� ����Ʈ�� ����, �ʱ�ȭ�ϴ� �Լ�.
	std::list<InstancingData>& CreateInstancingDataList();


private:
	// ���������� Ű�� ���ҵ� �ؾ� �մϴ�.
	// ������ �����ϴٴ°�
	// �Ȱ��� ���̴�
	// �Ȱ��� �Ž�
	// �Ȱ��� �������
	// �Ȱ��� �ؽ�ó�� ���ٴ� ��.
	// �� �� ������ initRenderUnit_.

	std::shared_ptr<class GameEngineRenderUnit> initRenderUnit_;	//�� �ν��Ͻ��� ù��° ��������.
	//�� ���������� �������� ���̴�, �޽�, �������, �ؽ�ó�� ���� �������ֵ鸸 �� �ν��Ͻ̿� ����� �� �ִ�.

	std::vector<std::list<InstancingData>> instancingDatas_;	//�� �ν��Ͻ��� ���� ��� �ν��Ͻ̵����͵�.
	//�� ����Ʈ�� ũ��� �⺻ 100�� ����.


	std::vector<std::shared_ptr<GameEngineInstancingBuffer>> instancingBuffers_;


	std::vector<std::vector<char>> instancingBufferDatas_;



	std::vector<GameEngineShaderResourceHelper> shaderResourceHelpers_;


	std::set<std::string> structuredBufferSetterNames_;    //����ȭ���� ���͵��� �̸� ����. 
	//�ݵ�� ���� �빮�ڷ� ������ ��.
	//�̰� ���� ��Ƽ���̾�� �ϳ�??

};

