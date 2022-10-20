#pragma once
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShader.h"

class GameEngineShaderResourceHelper
{
	//이 클래스의 존재 이유는 무엇?? 리소스 세팅함수들 정리?? 반드시 정리해둘 것.
	//ID3D11Resource의 자식 리소스들이 한두개가 아닌데 왜 셰이더  관련된 리소스들만 이런식으로 특별 관리하는 이유는??
	// 
	//같은 셰이더가 다른 리소스, 다른 세팅을 사용하는 경우를 대비.


	//일반적인 상용 엔진들은 렌더링 속도 개선을 위해, 한가지 색상값 정도의 사소한 데이터 하나만 달라져도, 
	// 그 달라진 데이터를 바뀔 일 없는 상수로 가진, 완전히 새로운 메테리얼을 만들게 한 후 한꺼번에 렌더링하게 한다. 
	// 그렇게 해서 Map(), Unmap() 함수 호출 빈도를 최대한 줄인다. 이렇게 안한다.
	//->winapi에서 HPEN, HBRUSH 같은 오브젝트 핸들들을, SelectObject()같은 함수를 통해 일일히 쓸 때마다 교체해주지 않으면 
	// 그 오브젝트 핸들을 쓰는 함수로 출력하는 모든 문자, 그림들이 같은 색, 같은 굵기로 통일되버리는것과 같은 원리인가??
	//->선생님은 속도저하를 감수해서라도 이미 생성한 HPEN같은 오브젝트들의 색이나 굵기를 중간에 바꿀 수 있게 해준다는 건가??

	friend class GameEngineRenderUnit;
	//AllResourcesSetting(), AllResourcesReset() 함수를 호출할 수 있게 하기 위해 프렌드. 


public:
	GameEngineShaderResourceHelper();
	~GameEngineShaderResourceHelper();

protected:
	GameEngineShaderResourceHelper(const GameEngineShaderResourceHelper& _other) = delete;
	GameEngineShaderResourceHelper(GameEngineShaderResourceHelper&& _other) noexcept = delete;

private:
	GameEngineShaderResourceHelper& operator=(const GameEngineShaderResourceHelper& _other) = delete;
	GameEngineShaderResourceHelper& operator=(const GameEngineShaderResourceHelper&& _other) = delete;


public:	
	//매개변수로 들어온 렌더링 파이프라인이 필요로 하는 셰이더리소스들을 셰이더리소스헬퍼에 등록하는 함수.
	void ResourceCheck(GameEngineRenderingPipeLine* _pipeLine);

	//이 셰이더 리소스 세터가 주어진 이름의 상수버퍼를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsConstantBuffer(const std::string& _name);

	//이 셰이더 리소스 세터가 주어진 이름의 텍스처를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsTexture(const std::string& _name);

	//이 셰이더 리소스 세터가 주어진 이름의 샘플러를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsSampler(const std::string& _name);

	//이 셰이더 리소스 세터가 주어진 이름의 구조화버퍼를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsStructuredBuffer(const std::string& _name);


	void SetConstantBuffer_Link(const std::string& _name, const void* _data, unsigned int _dataSize);	//참조로 연결??
	void SetConstantBuffer_New(const std::string& _name, const void* _data, unsigned int _dataSize);	//깊은 복사??
	//외부 데이터를 복사받아야 하는 등의 SetConstantBufferLink()를 사용할 수 없는 예외적인 상황에만 사용할 것.

	GameEngineTexture* SetTexture(const std::string& _textureSetterName, const std::string& _textureName);
	GameEngineTexture* SetTexture(const std::string& _textureSetterName, GameEngineTexture* _texture);
	GameEngineTexture* SetTexture(const std::string& _textureSetterName, const std::string& _folderTextureName, int _index);
	
	GameEngineSampler* SetSampler(const std::string& _samplerSetterName, GameEngineSampler* _sampler);
	GameEngineSampler* SetSampler(const std::string& _samplerSetterName, const std::string& _samplerName);

	// 인스턴싱을 하려고 하는데 그 쉐이더에서 상수버퍼를 사용했을때.
	void AllConstantBufferNew();


	GameEngineStructuredBufferSetter* GetStructuredBufferSetter(const std::string& _name);


public:
	template<typename Resource>
	void SetConstantBuffer_Link(const std::string& _name, const Resource& _data)
	{
		SetConstantBuffer_Link(_name, &_data, static_cast<UINT>(sizeof(Resource)));
	}

	template<typename Resource>
	void SetConstantBuffer_New(const std::string& _name, const Resource& _data)
	{
		SetConstantBuffer_New(_name, &_data, static_cast<UINT>(sizeof(Resource)));
	}

	//template<typename Resource>
	//Resource* GetConstantBufferNewData(const std::string& _cBufferName)
	//{
	//	std::string uppercaseCBufferName = GameEngineString::ToUpperReturn(_cBufferName);

	//	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator findIter
	//		= constantBufferSetterMap_.find(uppercaseCBufferName);

	//	if (constantBufferSetterMap_.end() == findIter)
	//	{
	//		return nullptr;
	//	}

	//	int resourceSize = sizeof(Resource);

	//	if (resourceSize != findIter->second.constantBuffer_->GetBufferDesc().ByteWidth)
	//	{
	//		MsgBoxAssert("찾는 상수버퍼의 이름과 크기가 맞지 않습니다.");
	//		return nullptr;
	//	}

	//	Resource* data = reinterpret_cast<Resource*>(&findIter->second.originalData_[0]);
	//	return data;
	//}


protected:
	//리소스 준비시점에, 짝으로 배치된 렌더링 파이프라인의 셰이더가 필요로 하는 셰이더리소스들을 셰이더리소스헬퍼에 등록하고, 
	// 매 렌더링마다 갱신된 셰이더리소스들을 렌더링 파이프라인에 각 셰이더들이 요구했던대로 렌더링 파이프라인에 연결하는 함수. 
	void ShaderCheck(GameEngineShader* _shader);


private:
	//상수버퍼를 가지고 있다가 상수버퍼세터가 settingFunction을 통해 상수버퍼를 요구하면 렌더링 파이프라인에 연결하는 함수. 
	void BindConstantBuffer(GameEngineConstantBufferSetter& _cBufferSetter, GameEngineConstantBuffer* _cBuffer);

	//텍스처를 가지고 있다가 텍스처세터가 settingFunction을 통해 텍스처를 요구하면 렌더링 파이프라인에 연결하는 함수.
	void BindTexture(GameEngineTextureSetter& _textureSetter, GameEngineTexture* _texture);

	//샘플러를 가지고 있다가 샘플러세터가 settingFunction을 통해 샘플러를 요구하면 렌더링 파이프라인에 연결하는 함수.
	void BindSampler(GameEngineSamplerSetter& _samplerSetter, GameEngineSampler* _sampler);

	//
	void BindStructuredBuffer(GameEngineStructuredBufferSetter& _sBufferSetter, GameEngineStructuredBuffer* _sBuffer);

	//해당 셰이더리소스헬퍼가 가진 모든 상수버퍼, 텍스처, 샘플러를 매 루프마다 갱신하고 정점셰이더나 픽셀셰이더에 연결하는 함수.
	void AllResourcesSetting();

	//
	void AllResourcesReset();

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> constantBufferSetterMap_;
	std::multimap<std::string, GameEngineTextureSetter> textureSetterMap_;
	std::multimap<std::string, GameEngineSamplerSetter> samplerSetterMap_;
	std::multimap<std::string, GameEngineStructuredBufferSetter> structuredBufferSetterMap_;	//구조화버퍼도 결국 텍스처.

	//셰이더 리소스 세터들의 저장, 관리를 멀티맵으로 한 이유:
	//그냥 std::map으로는 중복되는 리소스 이름을 키값으로 쓸 수 없지만 std::multimap으로는 저장할 수 있다는 특성을 이용해,
	// 이름만 똑같은 다른 상수버퍼세터나 텍스처세터 등의 리소스세터들을 여러 셰이더들이 동시에 사용하게 되는 경우에도 원활하게 저장하기 위해서.
	//->같은 이름 다른 리소스를 정점셰이더와 픽셀셰이더가 동시에 사용할 수 있게 한다.

	//셰이더 리소스 세터들을 참조형이 아닌 값형으로 저장하는 이유:
	//셰이더마다 각각의 셰이더 리소스 세터들을 만들어서 저장해야 하는데,
	// 포인터 형태로 저장하면 각각의 셰이더 리소스 세터가 아니라, 
	// 같은 셰이더 리소스 세터를 가리키는 각각의 '포인터 변수'를 만들어 저장하기 때문이다.
	// 그걸 막기 위해 값형으로 저장한다.

};

