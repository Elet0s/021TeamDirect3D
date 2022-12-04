#pragma once
#include "GameEngineShaderResourceHelper.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancing
{
	//이 클래스의 존재 이유: 인스턴스렌더링할 렌더유닛과 인스턴싱셰이더로 보낼 정보 보관용 클래스.

	static size_t maxInstancingCount_;

public:
	class InstancingData
	{
		//이 클래스의 존재 이유: 렌더유닛과 데이터 합동 관리.
		//특히 생성 삭제를 통합해서 하기 위해.

		friend GameEngineInstancing;

	public:
		InstancingData(std::shared_ptr<GameEngineRenderUnit> _renderUnit) : renderUnit_(_renderUnit)
		{
		}

		//InstancingData 초기화 함수.
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
		std::shared_ptr<GameEngineRenderUnit> renderUnit_;	//렌더유닛.
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
	//이 인스턴싱에 렌더유닛(렌더유닛만??)을 등록하는 함수.
	void PushUnit(std::shared_ptr<class GameEngineRenderUnit> _renderUnit, std::function<void(InstancingData&)> _function);
	void RenderInstancing(float _deltaTime);

private:
	//renderUnits_에 새 리스트를 생성, 초기화하는 함수.
	std::list<InstancingData>& CreateInstancingDataList();


private:
	// 렌더유닛이 키의 역할도 해야 합니다.
	// 완전히 동일하다는건
	// 똑같은 쉐이더
	// 똑같은 매쉬
	// 똑같은 상수버퍼
	// 똑같은 텍스처를 쓴다는 것.
	// 그 비교 기준이 initRenderUnit_.

	std::shared_ptr<class GameEngineRenderUnit> initRenderUnit_;	//이 인스턴싱의 첫번째 렌더유닛.
	//이 렌더유닛을 기준으로 셰이더, 메쉬, 상수버퍼, 텍스처가 같은 렌더유닛들만 이 인스턴싱에 등록할 수 있다.

	std::vector<std::list<InstancingData>> instancingDatas_;	//이 인스턴싱이 가진 모든 인스턴싱데이터들.
	//각 리스트별 크기는 기본 100개 제한.


	std::vector<std::shared_ptr<GameEngineInstancingBuffer>> instancingBuffers_;


	std::vector<std::vector<char>> instancingBufferDatas_;



	std::vector<GameEngineShaderResourceHelper> shaderResourceHelpers_;


	std::set<std::string> structuredBufferSetterNames_;    //구조화버퍼 세터들의 이름 모음. 
	//반드시 전부 대문자로 구성할 것.
	//이거 굳이 멀티셋이어야 하나??

};

