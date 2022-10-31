#pragma once
#include "GameEngineRes.h"

enum class ShaderType
{
	VertexShader,
	PixelShader,
	Max
};

class GameEngineShader;
class ShaderResSetter: public GameEngineNameObject
{
	//각각의 셰이더들끼리 상수버퍼나 다른 셰이더 리소스들은 공유하더라도, 바인드포인트 등의
	// 셰이더 리소스 스스로가 알 수 없는 정보가 다른 경우에 대응하기 위해 만든, 셰이더리소스 외부정보 전담관리용 클래스.
	//셰이더리소스 그 자체가 업데이트의 대상은 아니므로 네임오브젝트만 상속받아서 관리할 때 필요한 이름 관련 기능만 추가한다.

public:
	GameEngineShader* parentShader_;	//이 리소스세터가 가진 리소스를 사용할 부모 셰이더.
	int bindPoint_;		//해당 셰이더리소스의 바인드포인트(레지스터 등록 번호).
	ShaderType parentShaderType_;	//이 리소스세터를 생성하고 가지게 될 부모 셰이더의 종류.
	std::function<void()> settingFunction_;	//셰이더가 가진 리소스들을 세팅하는 함수.
	std::function<void()> resetFunction_;	//셰이더가 가진 리소스들을 리셋하는 함수.

protected:
	ShaderResSetter()
		: parentShader_(nullptr),
		bindPoint_(-1),
		parentShaderType_(ShaderType::Max),
		settingFunction_(nullptr),
		resetFunction_(nullptr)
	{
	}

	~ShaderResSetter() {}
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter: public ShaderResSetter
{
	//셰이더들이 필요로 하는 각각의 상수버퍼가 가져야 하는 정보 관리 클래스.


	friend class GameEngineShader;

public:
	//이 상수버퍼 세터가 담당한, 부모 셰이더가 필요로 하는 상수버퍼.
	GameEngineConstantBuffer* constantBuffer_;
	//여러 상수버퍼 세터가 하나의 상수버퍼를 공유할 수 있다.

	//Map()함수를 통해 GPU로 보내질, 각각의 상수버퍼들이 가진 데이터의 주소값. 
	const void* settingDataToGPU_;

	UINT byteWidth_;	//상수버퍼 전체 크기. 
	//상수버퍼는 크기와 이름 두가지로 분류되어 저장하고 있으므로 
	//상수버퍼세터도 자기가 담당하는 상수버퍼를 정확히 찾기 위해 둘 다 저장한다.

	std::vector<char> originalData_;
	// 아예 자기 메모리로 만든다??

	void Setting() const;

//private:	<-일일히 다 막기엔 일이 너무 복잡해져서 막지는 않지만 외부에서 사용해선 안된다.
// 여기서 외부는 이 리소스를 직접 사용할 GameEngineShader의 자식 클래스들과 셰이더를 사용할 GameEngineRenderingPipeLine,
// 렌더링 파이프라인을 사용할 GameEngineDefaultRenderer클래스와 그 자식클래스들을 제외하고는 다 외부이다.

	GameEngineConstantBufferSetter()
		: constantBuffer_(nullptr),
		settingDataToGPU_(nullptr),
		byteWidth_(-1)
	{
	}

};

class GameEngineTexture;
class GameEngineTextureSetter: public ShaderResSetter
{
	//이 클래스의 목적은??

	friend class GameEngineShader;

public:
	//이 텍스처세터가 가지는 텍스처. 
	GameEngineTexture* texture_;
	//추가적인 텍스처를 세팅해주지 않으면 경고 차원에서 "NSet.png"이 그대로 렌더되게 한다. 

	void Setting() const;
	void Reset() const;

//private:	<-일일히 다 막기엔 일이 너무 복잡해져서 막지는 않지만 외부에서 사용해선 안된다.
// 여기서 외부는 이 리소스를 직접 사용할 GameEngineShader의 자식 클래스들과 셰이더를 사용할 GameEngineRenderingPipeLine,
// 렌더링 파이프라인을 사용할 GameEngineDefaultRenderer클래스와 그 자식클래스들을 제외하고는 다 외부이다.

	GameEngineTextureSetter(): texture_(nullptr)
	{
	}
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{



public:
	//이 샘플러세터가 가지는 샘플러.
	GameEngineSampler* sampler_;

	void Setting() const;

//private:	<-일일히 다 막기엔 일이 너무 복잡해져서 막지는 않지만 외부에서 사용해선 안된다.
// 여기서 외부는 이 리소스를 직접 사용할 GameEngineShader의 자식 클래스들과 셰이더를 사용할 GameEngineRenderingPipeLine,
// 렌더링 파이프라인을 사용할 GameEngineDefaultRenderer클래스와 그 자식클래스들을 제외하고는 다 외부이다.

	GameEngineSamplerSetter(): sampler_(nullptr)
	{
	}
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter: public ShaderResSetter
{
public: 
	void Setting() const;
	void Resize(int _count);
	int GetDataSize();

	GameEngineStructuredBuffer* structuredBuffer_;
	std::vector<char> settingDataBufferToGPU_;

public:
	template <typename DataType>
	void Push(DataType& _data, int _count)
	{
		int leftSize = sizeof(DataType);
		int rightSize = this->GetDataSize();

		if (leftSize != rightSize)
		{
			MsgBoxAssert("구조화버퍼에 넣으려는 데이터의 크기가 다릅니다.");
		}

		PushData(&_data, _count);
	}

	GameEngineStructuredBufferSetter(): structuredBuffer_(nullptr)
	{
	}


private:
	void PushData(const void* _data, int _count);
};


class GameEngineShader
{
	//이 프레임워크 내 모든 셰이더와 셰이더에서 사용하는 리소스들을 관리하는 클래스.
	friend class GameEngineShaderResourceHelper;

public:
	GameEngineShader();
	virtual ~GameEngineShader();

protected:
	GameEngineShader(const GameEngineShader& _other) = delete;
	GameEngineShader(GameEngineShader&& _other) noexcept = delete;

private:
	GameEngineShader& operator=(const GameEngineShader& _other) = delete;
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete;


public:	
	//지정한 경로의 HLSL코드를 해석하고 그 내용대로 셰이더와 셰이더리소스를 만드는 함수.
	static void AutoCompile(const std::string& _path);

public:
	GameEngineConstantBufferSetter& GetConstantBufferSetter(const std::string& _name);


protected:
	//읽어들인 HLSL코드를 컴파일하는데 필요한 HLSL 버전을 생성하는 함수.
	void CreateVersion(const std::string& _shaderType, UINT _versionHigh, UINT _versionLow);

	//ShaderCompile()함수를 대체하는, 셰이더 공용 HLSL코드 컴파일 함수.
	void CompileHLSLCode(const std::string& _path);

	//내가 입력한 HLSL코드의 내용대로 셰이더의 리소스가 있는지 확인하고, 리소스세터를 통해 리소스 정보를 저장한다.
	//상수버퍼는 찾아봐서 있으면 가져오고 없다면 생성한다.
	//텍스처와 샘플러는 일단 엔진 기본제공 리소스를 세팅한다. 
	void ShaderResCheck(const std::string_view& _thisShaderName);
	//이 과정을 통해 이 프레임워크의 셰이더는 스스로가 어떤 셰이더리소스를 필요로 하는지 전부 알 수 있다.

protected:
	std::string entryPoint_;	//HLSL 코드의 진입점함수 이름.
	std::string shaderVersion_;	//HLSL 코드의 사용 목적과 컴파일러의 버전.
	ID3DBlob* binaryCode_;		//HLSL 코드를 컴파일한 결과물(바이트코드).
	ShaderType shaderType_;		//이 셰이더의 종류.

	std::map<std::string, GameEngineConstantBufferSetter> constantBufferSetterMap_;
	std::map<std::string, GameEngineTextureSetter> textureSetterMap_;
	std::map<std::string, GameEngineSamplerSetter> samplerSetterMap_;
	std::map<std::string, GameEngineStructuredBufferSetter> structuredBufferSetterMap_;

	//셰이더리소스세터들을 값형으로 저장한 이유는??
	//->셰이더 리소스 종류가 다양하지 않아서 값형으로 보관해도 많은 컨테이너들을 만들 필요가 없고, 
	// 각각의 리소스들을 분리해서 보다 세밀하게 관리할 수 있다는 장점을 이용할 수 있기 때문.

	//std::map<std::string, ShaderResSetter*> resSetterMap_;
	//이렇게 동적할당해서 셰이더리소스들을 보관한다면, 다형성을 이용해서 ShaderResSetter를 상속받은 모든 셰이더리소스들을 
	// 하나의 컨테이너로 더 적은 메모리로 관리할 수 있다.
	// 하지만 그정도로 최적화된 메모리관리가 아직은 필요 없으므로 위와같이 저장한다.

protected:
	inline void SetEntrtyPoint(const std::string& _entryPoint)
	{
		entryPoint_ = _entryPoint;
	}

	
};

