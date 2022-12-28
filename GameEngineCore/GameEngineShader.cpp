#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineGeometryShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineTexture2DArray.h"



void GameEngineConstantBufferSetter::Setting() const
{
	constantBuffer_->ChangeData(settingDataToGPU_, size_);

	settingFunction_();	//스위치문 한번 덜 쓰려고 펑셔널 사용.
}

void GameEngineConstantBufferSetter::Bind()
{
	if (nullptr == this->constantBuffer_)
	{
		MsgBoxAssert("상수버퍼가 존재하지 않습니다.");
		return;
	}

	switch (this->parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineConstantBuffer::VSSetting,
			this->constantBuffer_,
			this->bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineConstantBuffer::PSSetting,
			this->constantBuffer_,
			this->bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineTextureSetter::Setting() const
{
	settingFunction_();	//스위치문 한번 덜 쓰려고 펑셔널 사용.
}

void GameEngineTextureSetter::Reset() const
{
	resetFunction_();	//스위치문 한번 덜 쓰려고 펑셔널 사용.
}

void GameEngineTextureSetter::Bind()
{
	if (nullptr == this->texture_)
	{
		MsgBoxAssert("텍스처가 존재하지 않습니다.");
		return;
	}

	switch (this->parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineTexture::VSSetting,
			this->texture_,
			this->bindPoint_
		);

		this->resetFunction_ = std::bind(
			&GameEngineTexture::VSReset,
			this->texture_,
			this->bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineTexture::PSSetting,
			this->texture_,
			this->bindPoint_
		);

		this->resetFunction_ = std::bind(
			&GameEngineTexture::PSReset,
			this->texture_,
			this->bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineSamplerSetter::Setting() const
{
	settingFunction_();	//스위치문 한번 덜 쓰려고 펑셔널 사용.
}

void GameEngineSamplerSetter::Bind()
{
	if (nullptr == this->sampler_)
	{
		MsgBoxAssert("샘플러가 존재하지 않습니다.");
		return;
	}

	switch (this->parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineSampler::VSSetting,
			this->sampler_,
			this->bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineSampler::PSSetting,
			this->sampler_,
			this->bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineStructuredBufferSetter::Setting() const
{
	structuredBuffer_->ChangeData(settingDataToGPU_, size_ * count_);
	settingFunction_();	//스위치문 한번 덜 쓰려고 펑셔널 사용.
}

void GameEngineStructuredBufferSetter::Bind()
{
	if (nullptr == this->structuredBuffer_)
	{
		MsgBoxAssert("구조화 버퍼가 존재하지 않습니다.");
		return;
	}

	switch (this->parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineStructuredBuffer::VSSetting,
			this->structuredBuffer_,
			this->bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineStructuredBuffer::PSSetting,
			this->structuredBuffer_,
			this->bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineStructuredBufferSetter::Resize(size_t _count)
{
	this->structuredBuffer_->CreateOrResize(_count);
	this->size_ = structuredBuffer_->GetDataSize();
	this->count_ = _count;
	this->originalData_.resize(size_ * count_);
	this->settingDataToGPU_ = &originalData_[0];
}

size_t GameEngineStructuredBufferSetter::GetDataSize()
{
	return structuredBuffer_->GetDataSize();
}

void GameEngineStructuredBufferSetter::PushData(const void* _data, UINT _count)
{
	size_t byteWidth = structuredBuffer_->GetDataSize() * _count;
	memcpy_s(
		&originalData_[byteWidth],
		originalData_.size(),
		_data,
		structuredBuffer_->GetDataSize()
	);
}

void GameEngineTexture2DArraySetter::Setting() const
{
	settingFunction_();
}

void GameEngineTexture2DArraySetter::Reset() const
{
	resetFunction_();
}

void GameEngineTexture2DArraySetter::Bind()
{
	if (nullptr == this->texture2DArray_)
	{
		MsgBoxAssert("텍스처 배열이 존재하지 않습니다.");
		return;
	}

	switch (this->parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineTexture2DArray::VSSetting,
			this->texture2DArray_,
			this->bindPoint_
		);

		this->resetFunction_ = std::bind(
			&GameEngineTexture2DArray::VSReset,
			this->texture2DArray_,
			this->bindPoint_
		);

		break;
	}

	case ShaderType::PixelShader:
	{
		this->settingFunction_ = std::bind(
			&GameEngineTexture2DArray::PSSetting,
			this->texture2DArray_,
			this->bindPoint_
		);

		this->resetFunction_ = std::bind(
			&GameEngineTexture2DArray::PSReset,
			this->texture2DArray_,
			this->bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

GameEngineShader::GameEngineShader()
	: shaderVersion_(""),
	entryPoint_(""),
	binaryCode_(nullptr),
	shaderType_(ShaderType::Max)
{
}

GameEngineShader::~GameEngineShader()
{
	if (nullptr != binaryCode_)
	{
		binaryCode_->Release();
		binaryCode_ = nullptr;
	}
}

void GameEngineShader::AutoCompile(const std::string_view& _path)
{
	GameEngineFile file = GameEngineFile(_path);
	file.Open(OpenMode::Read, FileMode::Text);

	std::string allHLSLCode = file.GetString();

	//대소문자 주의!
	size_t vsEntryIndex = allHLSLCode.find("_VS(");
	if (std::string::npos != vsEntryIndex)
	{
		std::shared_ptr<GameEngineVertexShader> vertexShader = nullptr;

		size_t firstIndex = allHLSLCode.find_last_of(" ", vsEntryIndex);
		std::string vsEntryName
			= allHLSLCode.substr(	//주어진 문자열의 일부를 복사해서 반환하는 함수.
				firstIndex + 1,									//복사를 시작할 글자 인덱스.
				vsEntryIndex - firstIndex - 1					//복사 할 글자 수.
			);
		vsEntryName += "_VS";
		vertexShader = GameEngineVertexShader::Load(_path, vsEntryName);

		if (nullptr != vertexShader)
		{
			size_t vsInstEntryIndex = allHLSLCode.find("_VSINST(");
			if (std::string::npos != vsInstEntryIndex)
			{
				//allHLSLCode안에 "_VSINST(" 문자열이 있다면 인스턴스 버텍스셰이더 컴파일 시작.
				size_t instFirstIndex = allHLSLCode.find_last_of(" ", vsInstEntryIndex);
				std::string vsInstEntryPoint = allHLSLCode.substr(
					instFirstIndex + 1,
					vsInstEntryIndex - instFirstIndex - 1
				);
				vsInstEntryPoint += "_VSINST";
				vertexShader->InstancingVertexShaderCompile(_path, vsInstEntryPoint);
			}
		}
	}



	size_t psEntryIndex = allHLSLCode.find("_PS(");
	if (std::string::npos != psEntryIndex)
	{
		std::shared_ptr<GameEnginePixelShader> pixelShader = nullptr;

		size_t firstIndex = allHLSLCode.find_last_of(" ", psEntryIndex);
		std::string psEntryName = allHLSLCode.substr(
			firstIndex + 1,
			psEntryIndex - firstIndex - 1
		);
		psEntryName += "_PS";

		pixelShader = GameEnginePixelShader::Load(_path, psEntryName);

		if (nullptr != pixelShader)
		{
			size_t psInstEntryIndex = allHLSLCode.find("_PSINST(");
			if (std::string::npos != psInstEntryIndex)
			{
				size_t instFirstIndex = allHLSLCode.find_last_of(" ", psInstEntryIndex);
				std::string psInstEntryPoint = allHLSLCode.substr(
					instFirstIndex + 1,
					psInstEntryIndex - instFirstIndex - 1
				);
				psInstEntryPoint += "_PSINST";
				pixelShader->InstancingPixelShaderCompile(_path, psInstEntryPoint);
			}

			size_t psReturnTypeEntry = allHLSLCode.rfind("\n", psEntryIndex);
			std::string psReturnType = allHLSLCode.substr(
				psReturnTypeEntry + 1,
				psEntryIndex - psReturnTypeEntry
			);

			if (std::string::npos != psReturnType.find("DeferredOutput"))
			{
				//픽셀셰이더 반환형이 float4가 아니라 "DeferredOutput"라면 gBuffer 렌더타겟의 텍스처에 렌더링하는 픽셀셰이더라는 뜻.
				pixelShader->isDeferredRendering_ = true;
			}
		}
	}

	size_t gsEntryIndex = allHLSLCode.find("_GS(");
	if (std::string::npos != gsEntryIndex)
	{
		std::shared_ptr<GameEngineGeometryShader> geometryShader = nullptr;

		size_t firstIndex = allHLSLCode.find_last_of(" ", gsEntryIndex);
		std::string gsEntryName
			= allHLSLCode.substr(	//주어진 문자열의 일부를 복사해서 반환하는 함수.
				firstIndex + 1,									//복사를 시작할 글자 인덱스.
				gsEntryIndex - firstIndex - 1					//복사 할 글자 수.
			);
		gsEntryName += "_GS";
		geometryShader = GameEngineGeometryShader::Load(_path, gsEntryName);
	}
}

GameEngineConstantBufferSetter& GameEngineShader::GetConstantBufferSetter(const std::string& _name)
{
	std::string uppercaseSetterName = GameEngineString::ToUpperReturn(_name);

	if (constantBufferSetterMap_.end() == constantBufferSetterMap_.find(uppercaseSetterName))
	{
		MsgBoxAssertString(_name + ": 그런 이름의 상수버퍼가 존재하지 않습니다.");
	}

	return constantBufferSetterMap_[uppercaseSetterName];
}

bool GameEngineShader::IsConstantBuffer(const std::string_view& _name)
{
	std::string uppercaseCBufferSetterName = GameEngineString::ToUpperReturn(_name);

	if (constantBufferSetterMap_.end() == constantBufferSetterMap_.find(uppercaseCBufferSetterName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShader::IsTexture(const std::string_view& _name)
{
	const std::string uppercaseTextureSetterName = GameEngineString::ToUpperReturn(_name);

	if (textureSetterMap_.end() == textureSetterMap_.find(uppercaseTextureSetterName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShader::IsSampler(const std::string_view& _name)
{
	std::string uppercaseSamplerName = GameEngineString::ToUpperReturn(_name);

	if (samplerSetterMap_.end() == samplerSetterMap_.find(uppercaseSamplerName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShader::IsStructuredBuffer(const std::string_view& _name)
{
	std::string uppercaseSBufferSetterName = GameEngineString::ToUpperReturn(_name);

	if (structuredBufferSetterMap_.end() == structuredBufferSetterMap_.find(uppercaseSBufferSetterName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShader::IsTexture2DArray(const std::string_view& _name)
{
	std::string uppercaseTexture2DArraySetterName = GameEngineString::ToUpperReturn(_name);

	if (texture2DArraySetterMap_.end() == texture2DArraySetterMap_.find(uppercaseTexture2DArraySetterName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameEngineShader::CreateVersion(const std::string_view& _shaderType, UINT _versionHigh, UINT _versionLow)
{
	shaderVersion_ = "";
	shaderVersion_ += _shaderType;
	shaderVersion_ += "_";
	shaderVersion_ += std::to_string(_versionHigh);
	shaderVersion_ += "_";
	shaderVersion_ += std::to_string(_versionLow);
}

void GameEngineShader::CompileHLSLCode(const std::string_view& _path)
{
	unsigned int compileFlag = 0;
#ifdef _DEBUG
	compileFlag = D3D10_SHADER_DEBUG;	//디버그 파일/줄/유형/기호 정보를 삽입한다.
#endif // _DEBUG
	compileFlag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;  //행 중심 매트릭스 사용(안하면 전치행렬 사용).

	ID3DBlob* errorMessage = { 0 };		//컴파일 실패시 에러코드를 받는 변수.

	//와이드스트링 경로.
	std::wstring unicodePath = GameEngineString::AnsiToUnicodeReturn(_path);


	if (S_OK != D3DCompileFromFile( //hlsl 컴파일 함수.
		unicodePath.c_str(),          //경로가 포함된 HLSL 파일 이름. C스타일 와이드스트링만 받는다.
		nullptr,							//입력할 코드에서 사용할 매크로가 들어있는 D3D_SHADER_MACRO구조체의 배열 주소값.
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  //입력할 코드에서 사용할 전처리기가 들어있는 ID3DInclude구조체의 배열 주소값.
		//D3D_COMPILE_STANDARD_FILE_INCLUDE 매크로가 기본 인클루드 핸들러를 가리키고 있으니,
		//hlsl코드에 #include가 포함되어 있으면 이걸 넣으면 된다고 한다.
		entryPoint_.c_str(),    //셰이더 진입점함수 이름.
		shaderVersion_.c_str(), //사용할 HLSL 컴파일러의 목적과 버전. vs_5_0이라면 HLSL컴파일러 5.0으로 컴파일한 결과물을 버텍스 셰이더로 쓰겠다는 뜻.
		compileFlag,			//컴파일 옵션 플래그 1.
		0,						//컴파일 옵션 플래그 2. 셰이더 컴파일때는 무시됨.
		&binaryCode_,			//컴파일된 바이너리 코드를 받을 ID3DBlob 인터페이스 주소값.
		&errorMessage			//에러메세지를 받을 ID3DBlob 인터페이스 주소값.
	))
	{
		std::string errorText = reinterpret_cast<char*>(errorMessage->GetBufferPointer());
		MsgBoxAssertString(entryPoint_ + ": HLSL코드 컴파일 실패.\n" + errorText);
		errorMessage->Release();
		return;
	}

	//errorMessage->Release();
	//컴파일에 문제가 없었다면 errorMessage는 널포인터인상태 그대로 내려오므로 릴리즈할 것이 없다.
}

void GameEngineShader::ShaderResCheck(const std::string_view& _thisShaderName)
{
	if (nullptr == binaryCode_)
	{
		MsgBoxAssert("바이너리코드가 없습니다.");
		return;
	}

	//리플렉션: 원래의 구체적인 클래스나 자료형에 대해 몰라도 바이트코드로 되어있는 컴파일 결과물에서 
	// 정보를 추출해내는 프로그램 기법이다. 그러니까 컴파일된 바이너리코드에서 파싱하는것과 마찬가지.

	ID3D11ShaderReflection* compileInfo = { 0 };

	if (S_OK != D3DReflect(				//컴파일된 HLSL코드를 바탕으로 내가 셰이더에서 사용한 변수, 함수, 인자들에 
		// 대한 정보를 추출해서 셰이더 리플렉션이라는 인터페이스를 통해 반환하는 함수.
		binaryCode_->GetBufferPointer(),		//컴파일된 HLSL 코드의 포인터.
		binaryCode_->GetBufferSize(),		//컴파일된 HLSL 코드의 크기.
		IID_ID3D11ShaderReflection,				//추출한 HLSL 코드 정보를 반환할때 참조할 ID3D11ShaderReflection의 인터페이스 식별자(GUID).
		reinterpret_cast<void**>(&compileInfo)	//추출한 HLSL 코드 정보를 반환받을 ID3D11ShaderReflection의 포인터.
	))
	{
		MsgBoxAssert("셰이더 정보 추출 실패.");
		return;
	}



	D3D11_SHADER_DESC shaderInfo = { 0 };
	compileInfo->GetDesc(&shaderInfo);


	//typedef struct _D3D11_SHADER_INPUT_BIND_DESC
	//{
	//	LPCSTR                      Name;			셰이더가 사용하는 리소스 이름.
	//	D3D_SHADER_INPUT_TYPE       Type;			셰이더가 사용하는 리소스 종류(텍스쳐, 상수버퍼 등등...)
	//	UINT                        BindPoint;		해당 리소스의 레지스터 등록 번호.
	//	UINT                        BindCount;		연결할 리소스 개수.
	//	UINT                        uFlags;			Input binding flags
	//	D3D_RESOURCE_RETURN_TYPE    ReturnType;		반환형. 3차원 텍스처에만 사용.
	//	D3D_SRV_DIMENSION           Dimension;		Dimension (if texture) 3차원 텍스처에만 사용.
	//	UINT                        NumSamples;		멀티샘플링용 텍스처 수. 텍스쳐가 아니라면 0. 텍스처라도 멀티샘플링하지 않는다면 -1.
	//} D3D11_SHADER_INPUT_BIND_DESC;
	D3D11_SHADER_INPUT_BIND_DESC resInfo = { 0 };

	for (UINT i = 0; i < shaderInfo.BoundResources; i++)
		//shaderInfo.BoundResources: 이 셰이더에서 '사용된' 총 리소스 양. 사용되지 않은 리소스는 무시된다.
	{
		compileInfo->GetResourceBindingDesc(i, &resInfo);
		//DirectX 외부에서 사용할 수 없는 compileInfo에서 D3D11_SHADER_INPUT_BIND_DESC 형식으로 
		// 셰이더가 사용하게 될 리소스의 세부정보를 추출한다.

		std::string uppercaseResourceName = GameEngineString::ToUpperReturn(resInfo.Name);

		switch (resInfo.Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* cBufferPtr = compileInfo->GetConstantBufferByName(resInfo.Name);
			//DirectX 외부에서 사용할 수 없는 compileInfo에서 상수버퍼를 추출한다.

			//typedef struct _D3D11_SHADER_BUFFER_DESC
			//{
			//	LPCSTR                  Name;		상수버퍼 이름.
			//	D3D_CBUFFER_TYPE        Type;		상수버퍼의 종류.
			//	UINT                    Variables;	상수버퍼의 멤버변수 개수.
			//	UINT                    Size;		상수버퍼 크기.
			//	UINT                    uFlags;		상수버퍼가 연결될 슬롯을 지정하는 플래그. 
			//		hlsl코드에 지정된 슬롯으로 연결한다는 플래그 하나밖에 없으므로 의미 없음.
			//} D3D11_SHADER_BUFFER_DESC;
			D3D11_SHADER_BUFFER_DESC cBufferDesc = { 0 };
			cBufferPtr->GetDesc(&cBufferDesc);


			GameEngineConstantBufferSetter newCBufferSetter;
			//새 상수버퍼세터를 생성하고, 세터에 셰이더가 상수버퍼 및 상수버퍼를 사용하는데 필요한 정보들을 저장한다.

			newCBufferSetter.parentShader_ = this;
			//이 상수버퍼세터를 생성하는 셰이더를 부모 셰이더로 한다.

			newCBufferSetter.SetName(uppercaseResourceName);
			//리소스세터의 이름은 HLSL코드 내에 선언된 자기 리소스타입 변수 이름을 그대로 따라간다.

			newCBufferSetter.parentShaderType_ = this->shaderType_;
			//부모 셰이더가 어떤 셰이더인지 저장한다.

			newCBufferSetter.constantBuffer_ = GameEngineConstantBuffer::CreateAndFind(
				newCBufferSetter.GetName(),	//만들려는 상수버퍼가 없으면 만들고, 이미 있으면 공유한다.
				cBufferDesc			//같은 이름, 같은 크기의 상수 버퍼는 셰이더리소스헬퍼들이 포인터를 공유한다.
						//그래서 이미 만들어져 있는걸 또 만들어도 터뜨리지 않고 대신 이미 만들어져 있는걸 공유한다.
			);

			newCBufferSetter.bindPoint_ = resInfo.BindPoint;

			std::pair<std::map<std::string, GameEngineConstantBufferSetter>::iterator, bool> insertResult =
				constantBufferSetterMap_.insert(std::make_pair(newCBufferSetter.GetName(), newCBufferSetter));
			//맵에 겹치는 키값을 가진 원소를 삽입하려고 하면 중복된 키값을 가진 원소를 가리키는 
			//이터레이터와 false가 든 페어를 반환하고 삽입 시도는 무시된다.
			//삽입이 성공했다면 삽입한 원소를 가리키는 이터레이터와 true를 가진 페어를 반환한다.


			if (false == insertResult.second)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ": 이미 같은 이름의 상수버퍼 세터가 존재합니다.");
				//중복으로 만드는일이 생겨선 안된다.
				return;
			}

			break;
		}

		case D3D_SIT_TEXTURE:
		{
			if (D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DARRAY == resInfo.Dimension)
			{
				GameEngineTexture2DArraySetter newTexture2DArraySetter;

				newTexture2DArraySetter.parentShader_ = this;

				newTexture2DArraySetter.SetName(uppercaseResourceName);

				newTexture2DArraySetter.parentShaderType_ = this->shaderType_;

				newTexture2DArraySetter.texture2DArray_ = GameEngineTexture2DArray::Find("NSet5Colors");

				newTexture2DArraySetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineTexture2DArraySetter>::iterator, bool> insertResult
					= texture2DArraySetterMap_.insert(std::make_pair(newTexture2DArraySetter.GetName(), newTexture2DArraySetter));

				if (false == insertResult.second)
				{
					MsgBoxAssertString(std::string(resInfo.Name) + ":  이미 같은 이름의 텍스쳐2D배열 세터가 존재합니다.");
					return;
				}
				break;
			}
			else if (D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2D == resInfo.Dimension)
			{
				GameEngineTextureSetter newTextureSetter;
				//새 텍스처세터를 생성하고, 세터에 셰이더가 텍스처 및 텍스처를 사용하는데 필요한 정보들을 저장한다.

				newTextureSetter.parentShader_ = this;
				//이 텍스처세터를 생성하는 셰이더를 부모 셰이더로 한다.

				newTextureSetter.SetName(uppercaseResourceName);
				//리소스세터의 이름은 HLSL코드 내에 선언된 Texture2D타입 변수 이름을 그대로 따라간다.

				newTextureSetter.parentShaderType_ = this->shaderType_;
				//부모 셰이더가 어떤 셰이더인지 저장한다.

				newTextureSetter.texture_ = GameEngineTexture::Find("NSet.png");//<-텍스쳐가 아예 없다는 경고가 뜨면 여기로.
				//나중에 지정할 텍스처가 무엇이든 일단 엔진 기본제공 텍스처인 "NSet.png"를 텍스처세터에 저장해서 
				// 추가적인 텍스처 세팅이 없으면 경고 차원에서 "NSet.png"가 렌더링되게 한다.

				newTextureSetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineTextureSetter>::iterator, bool> insertResult
					= textureSetterMap_.insert(std::make_pair(newTextureSetter.GetName(), newTextureSetter));
				//맵에 겹치는 키값을 가진 원소를 삽입하려고 하면 중복된 키값을 가진 원소를 가리키는 
				//이터레이터와 false가 든 페어를 반환하고 삽입 시도는 무시된다.
				//삽입이 성공했다면 삽입한 원소를 가리키는 이터레이터와 true를 가진 페어를 반환한다.

				if (false == insertResult.second)
				{
					MsgBoxAssertString(std::string(resInfo.Name) + ":  이미 같은 이름의 텍스쳐 세터가 존재합니다.");
					return;
				}

				break;
			}
			else
			{
				MsgBoxAssert("아직 준비되지 않은 형식의 텍스처입니다.");
				return;
			}
		}

		case D3D_SIT_SAMPLER:
		{
			GameEngineSamplerSetter newSamplerSetter;
			//새 샘플러세터를 생성하고, 세터에 셰이더가 샘플러 및 샘플러를 사용하는데 필요한 정보들을 저장한다.

			newSamplerSetter.parentShader_ = this;
			//이 샘플러세터를 생성하는 셰이더를 부모 셰이더로 한다.

			newSamplerSetter.SetName(uppercaseResourceName);
			//리소스세터의 이름은 HLSL코드 내에 선언된 자기 리소스타입 변수 이름을 그대로 따라간다.

			newSamplerSetter.parentShaderType_ = this->shaderType_;
			//부모 셰이더가 어떤 셰이더인지 저장한다.

			newSamplerSetter.sampler_ = GameEngineSampler::Find(uppercaseResourceName);

			if (nullptr == newSamplerSetter.sampler_)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ": 그런 이름의 샘플러가 존재하지 않습니다. \nShaderName: " + _thisShaderName.data());
				return;
			}


			newSamplerSetter.bindPoint_ = resInfo.BindPoint;

			std::pair<std::map<std::string, GameEngineSamplerSetter>::iterator, bool> insertResult
				= samplerSetterMap_.insert(std::make_pair(newSamplerSetter.GetName(), newSamplerSetter));
			//맵에 겹치는 키값을 가진 원소를 삽입하려고 하면 중복된 키값을 가진 원소를 가리키는 
			//이터레이터와 false가 든 페어를 반환하고 삽입 시도는 무시된다.
			//삽입이 성공했다면 삽입한 원소를 가리키는 이터레이터와 true를 가진 페어를 반환한다.

			if (false == insertResult.second)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ":  이미 같은 이름의 샘플러 세터가 존재합니다.");
				return;
			}

			break;
		}

		case D3D_SIT_STRUCTURED:
		{
			//구조화버퍼는 구조적인 특성상 대용량 메모리를 사용하는것이 기본인데, 
			//동적 할당되는 특성상 미리 만들수도 없다.

			ID3D11ShaderReflectionConstantBuffer* cBufferPtr = compileInfo->GetConstantBufferByName(resInfo.Name);
			D3D11_SHADER_BUFFER_DESC shaderBufferDesc = { 0 };
			cBufferPtr->GetDesc(&shaderBufferDesc);

			GameEngineStructuredBufferSetter newSBufferSetter;
			newSBufferSetter.parentShader_ = this;
			newSBufferSetter.SetName(uppercaseResourceName);
			newSBufferSetter.parentShaderType_ = this->shaderType_;

			//아직은 데이터의 사이즈는 알수있어도 이걸로 몇개짜리 버퍼를 만들지는 알수가 없다.
			// 그래서 개수 0 으로 일단 만들어둔다.

			newSBufferSetter.structuredBuffer_ = GameEngineStructuredBuffer::CreateAndFind(
				newSBufferSetter.GetName(),	//
				shaderBufferDesc,		//
				0						//
			);
			newSBufferSetter.bindPoint_ = resInfo.BindPoint;

			std::pair<std::map<std::string, GameEngineStructuredBufferSetter>::iterator, bool> insertResult
				= structuredBufferSetterMap_.insert(
					std::make_pair(newSBufferSetter.GetName(), newSBufferSetter)
				);

			if (false == insertResult.second)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ": 이미 같은 이름의 구조화 버퍼 세터가 존재합니다.");
				return;
			}

			break;
		}

		default:
		{
			MsgBoxAssert("정의되지 않은 셰이더 리소스 타입입니다.");
			return;
		}
		}
	}
}
