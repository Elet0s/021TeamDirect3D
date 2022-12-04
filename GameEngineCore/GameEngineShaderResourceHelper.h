#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShader.h"

class GameEngineShaderResourceHelper
{
	//이 클래스의 존재 이유는 무엇?? 리소스 세팅함수들 정리?? 반드시 정리해둘 것.
	//ID3D11Resource의 자식 리소스들이 한두개가 아닌데 왜 셰이더  관련된 리소스들만 이런식으로 특별 관리하는 이유는??
	// 
	//같은 셰이더가 다른 리소스, 다른 세팅을 사용하는 경우를 대비.

	friend class GameEngineRenderUnit;
	//AllResourcesSetting(), AllResourcesReset() 함수를 호출할 수 있게 하기 위해 프렌드. 
	
	friend class GameEngineInstancing;
	//인스턴싱 버텍스셰이더로 ShaderCheck()함수를 써야해서 프렌드. 
	
	friend class GameEngineInstancingRenderer;
	//인스턴싱 버텍스셰이더, 픽셀셰이더로 ShaderCheck()함수를 써야해서 프렌드. 

	friend class GameEngineInstancingRenderUnit;
	//AllResourcesSetting(), AllResourcesReset() 함수를 호출할 수 있게 하기 위해 프렌드. 

public:
	GameEngineShaderResourceHelper();
	~GameEngineShaderResourceHelper();

	//GameEngineShaderResourceHelper(const GameEngineShaderResourceHelper& _other) = delete;
	//GameEngineShaderResourceHelper(GameEngineShaderResourceHelper&& _other) noexcept = delete;
	//GameEngineShaderResourceHelper& operator=(const GameEngineShaderResourceHelper& _other) = delete;
	//GameEngineShaderResourceHelper& operator=(const GameEngineShaderResourceHelper&& _other) = delete;


public:
	//매개변수로 들어온 마테리얼이 필요로 하는 셰이더리소스들을 셰이더리소스헬퍼에 등록하는 함수.
	void ResourceCheck(std::shared_ptr<GameEngineMaterial> _material);

	//이 셰이더 리소스 헬퍼가 주어진 이름의 상수버퍼세터를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsConstantBuffer(const std::string_view& _name);

	//이 셰이더 리소스 헬퍼가 주어진 이름의 텍스처세터를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsTexture(const std::string_view& _name);

	//이 셰이더 리소스 헬퍼가 주어진 이름의 샘플러세터를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsSampler(const std::string_view& _name);

	//이 셰이더 리소스 헬퍼가 주어진 이름의 구조화버퍼세터를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsStructuredBuffer(const std::string_view& _name);

	//이 셰이더 리소스 헬퍼가 주어진 이름의 인스턴싱텍스처세터를 가지고 있는가를 외부에서 확인하는 함수.
	bool IsInstancingTextures(const std::string_view& _name);


	void SetConstantBuffer_Link(const std::string_view& _name, const void* _data, unsigned int _dataSize);	//참조로 연결??
	void SetConstantBuffer_New(const std::string_view& _name, const void* _data, unsigned int _dataSize);	//깊은 복사??
	//외부 데이터를 복사받아야 하는 등의 SetConstantBufferLink()를 사용할 수 없는 예외적인 상황에만 사용할 것.

	std::shared_ptr<GameEngineTexture> SetTexture(const std::string_view& _textureSetterName, const std::string_view& _textureName);
	std::shared_ptr<GameEngineTexture> SetTexture(const std::string_view& _textureSetterName, std::shared_ptr<GameEngineTexture> _texture);
	std::shared_ptr<GameEngineTexture> SetTexture(const std::string_view& _textureSetterName, const std::string_view& _folderTextureName, int _index);

	std::shared_ptr<GameEngineSampler> SetSampler(const std::string_view& _samplerSetterName, std::shared_ptr<GameEngineSampler> _sampler);
	std::shared_ptr<GameEngineSampler> SetSampler(const std::string_view& _samplerSetterName, const std::string_view& _samplerName);
	
	std::shared_ptr<GameEngineInstancingTextures> SetInstancingTextures(const std::string_view& _texturesSetterName, const std::string_view& _texturesName);
	std::shared_ptr<GameEngineInstancingTextures> SetInstancingTextures(const std::string_view& _texturesSetterName, std::shared_ptr<GameEngineInstancingTextures> _textures);

	// 인스턴싱을 하려고 하는데 그 쉐이더에서 상수버퍼를 사용했을때.
	//void AllConstantBufferNew();


	GameEngineStructuredBufferSetter* GetStructuredBufferSetter(const std::string_view& _sBufferName);


	//이 셰이더리소스헬퍼가 가진 구조화버퍼를 전부 넘기는 함수.
	std::multimap<std::string, GameEngineStructuredBufferSetter>& GetStructuredBufferSetterMap();


public:
	template<typename Resource>
	void SetConstantBuffer_Link(const std::string_view& _name, const Resource& _data)
	{
		SetConstantBuffer_Link(_name, &_data, static_cast<UINT>(sizeof(Resource)));
	}

	template<typename Resource>
	void SetConstantBuffer_New(const std::string_view& _name, const Resource& _data)
	{
		SetConstantBuffer_New(_name, &_data, static_cast<UINT>(sizeof(Resource)));
	}

protected:
	//리소스 준비시점에, 짝으로 배치된 마테리얼의 셰이더가 필요로 하는 셰이더리소스들을 셰이더리소스헬퍼에 등록하고, 
	// 매 렌더링마다 갱신된 셰이더리소스들을 각 셰이더들이 요구했던대로 디바이스 컨텍스트에 연결하는 함수. 
	void ShaderCheck(std::shared_ptr<GameEngineShader> _shader);


private:

	//해당 셰이더리소스헬퍼가 가진 모든 상수버퍼, 텍스처, 샘플러를 매 루프마다 갱신하고 정점셰이더나 픽셀셰이더에 연결하는 함수.
	void AllResourcesSetting();

	//해당 셰이더리소스헬퍼가 디바이스 컨텍스트에 연결했던 모든 상수버퍼, 텍스처, 샘플러를 널포인터로 대체하는 함수.
	void AllResourcesReset();

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> constantBufferSetterMap_;
	std::multimap<std::string, GameEngineTextureSetter> textureSetterMap_;
	std::multimap<std::string, GameEngineSamplerSetter> samplerSetterMap_;
	std::multimap<std::string, GameEngineStructuredBufferSetter> structuredBufferSetterMap_;	//구조화버퍼도 결국 텍스처.
	std::multimap<std::string, GameEngineInstancingTexturesSetter> instancingTexturesSetterMap_;

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

