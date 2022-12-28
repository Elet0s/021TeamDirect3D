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

	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineConstantBufferSetter::Bind()
{
	if (nullptr == this->constantBuffer_)
	{
		MsgBoxAssert("������۰� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �غ���� ���� ���̴� Ÿ���Դϴ�.");
		return;
	}
}

void GameEngineTextureSetter::Setting() const
{
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineTextureSetter::Reset() const
{
	resetFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineTextureSetter::Bind()
{
	if (nullptr == this->texture_)
	{
		MsgBoxAssert("�ؽ�ó�� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �غ���� ���� ���̴� Ÿ���Դϴ�.");
		return;
	}
}

void GameEngineSamplerSetter::Setting() const
{
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineSamplerSetter::Bind()
{
	if (nullptr == this->sampler_)
	{
		MsgBoxAssert("���÷��� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �غ���� ���� ���̴� Ÿ���Դϴ�.");
		return;
	}
}

void GameEngineStructuredBufferSetter::Setting() const
{
	structuredBuffer_->ChangeData(settingDataToGPU_, size_ * count_);
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineStructuredBufferSetter::Bind()
{
	if (nullptr == this->structuredBuffer_)
	{
		MsgBoxAssert("����ȭ ���۰� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �غ���� ���� ���̴� Ÿ���Դϴ�.");
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
		MsgBoxAssert("�ؽ�ó �迭�� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �غ���� ���� ���̴� Ÿ���Դϴ�.");
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

	//��ҹ��� ����!
	size_t vsEntryIndex = allHLSLCode.find("_VS(");
	if (std::string::npos != vsEntryIndex)
	{
		std::shared_ptr<GameEngineVertexShader> vertexShader = nullptr;

		size_t firstIndex = allHLSLCode.find_last_of(" ", vsEntryIndex);
		std::string vsEntryName
			= allHLSLCode.substr(	//�־��� ���ڿ��� �Ϻθ� �����ؼ� ��ȯ�ϴ� �Լ�.
				firstIndex + 1,									//���縦 ������ ���� �ε���.
				vsEntryIndex - firstIndex - 1					//���� �� ���� ��.
			);
		vsEntryName += "_VS";
		vertexShader = GameEngineVertexShader::Load(_path, vsEntryName);

		if (nullptr != vertexShader)
		{
			size_t vsInstEntryIndex = allHLSLCode.find("_VSINST(");
			if (std::string::npos != vsInstEntryIndex)
			{
				//allHLSLCode�ȿ� "_VSINST(" ���ڿ��� �ִٸ� �ν��Ͻ� ���ؽ����̴� ������ ����.
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
				//�ȼ����̴� ��ȯ���� float4�� �ƴ϶� "DeferredOutput"��� gBuffer ����Ÿ���� �ؽ�ó�� �������ϴ� �ȼ����̴���� ��.
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
			= allHLSLCode.substr(	//�־��� ���ڿ��� �Ϻθ� �����ؼ� ��ȯ�ϴ� �Լ�.
				firstIndex + 1,									//���縦 ������ ���� �ε���.
				gsEntryIndex - firstIndex - 1					//���� �� ���� ��.
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
		MsgBoxAssertString(_name + ": �׷� �̸��� ������۰� �������� �ʽ��ϴ�.");
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
	compileFlag = D3D10_SHADER_DEBUG;	//����� ����/��/����/��ȣ ������ �����Ѵ�.
#endif // _DEBUG
	compileFlag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;  //�� �߽� ��Ʈ���� ���(���ϸ� ��ġ��� ���).

	ID3DBlob* errorMessage = { 0 };		//������ ���н� �����ڵ带 �޴� ����.

	//���̵彺Ʈ�� ���.
	std::wstring unicodePath = GameEngineString::AnsiToUnicodeReturn(_path);


	if (S_OK != D3DCompileFromFile( //hlsl ������ �Լ�.
		unicodePath.c_str(),          //��ΰ� ���Ե� HLSL ���� �̸�. C��Ÿ�� ���̵彺Ʈ���� �޴´�.
		nullptr,							//�Է��� �ڵ忡�� ����� ��ũ�ΰ� ����ִ� D3D_SHADER_MACRO����ü�� �迭 �ּҰ�.
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  //�Է��� �ڵ忡�� ����� ��ó���Ⱑ ����ִ� ID3DInclude����ü�� �迭 �ּҰ�.
		//D3D_COMPILE_STANDARD_FILE_INCLUDE ��ũ�ΰ� �⺻ ��Ŭ��� �ڵ鷯�� ����Ű�� ������,
		//hlsl�ڵ忡 #include�� ���ԵǾ� ������ �̰� ������ �ȴٰ� �Ѵ�.
		entryPoint_.c_str(),    //���̴� �������Լ� �̸�.
		shaderVersion_.c_str(), //����� HLSL �����Ϸ��� ������ ����. vs_5_0�̶�� HLSL�����Ϸ� 5.0���� �������� ������� ���ؽ� ���̴��� ���ڴٴ� ��.
		compileFlag,			//������ �ɼ� �÷��� 1.
		0,						//������ �ɼ� �÷��� 2. ���̴� �����϶��� ���õ�.
		&binaryCode_,			//�����ϵ� ���̳ʸ� �ڵ带 ���� ID3DBlob �������̽� �ּҰ�.
		&errorMessage			//�����޼����� ���� ID3DBlob �������̽� �ּҰ�.
	))
	{
		std::string errorText = reinterpret_cast<char*>(errorMessage->GetBufferPointer());
		MsgBoxAssertString(entryPoint_ + ": HLSL�ڵ� ������ ����.\n" + errorText);
		errorMessage->Release();
		return;
	}

	//errorMessage->Release();
	//�����Ͽ� ������ �����ٸ� errorMessage�� ���������λ��� �״�� �������Ƿ� �������� ���� ����.
}

void GameEngineShader::ShaderResCheck(const std::string_view& _thisShaderName)
{
	if (nullptr == binaryCode_)
	{
		MsgBoxAssert("���̳ʸ��ڵ尡 �����ϴ�.");
		return;
	}

	//���÷���: ������ ��ü���� Ŭ������ �ڷ����� ���� ���� ����Ʈ�ڵ�� �Ǿ��ִ� ������ ��������� 
	// ������ �����س��� ���α׷� ����̴�. �׷��ϱ� �����ϵ� ���̳ʸ��ڵ忡�� �Ľ��ϴ°Ͱ� ��������.

	ID3D11ShaderReflection* compileInfo = { 0 };

	if (S_OK != D3DReflect(				//�����ϵ� HLSL�ڵ带 �������� ���� ���̴����� ����� ����, �Լ�, ���ڵ鿡 
		// ���� ������ �����ؼ� ���̴� ���÷����̶�� �������̽��� ���� ��ȯ�ϴ� �Լ�.
		binaryCode_->GetBufferPointer(),		//�����ϵ� HLSL �ڵ��� ������.
		binaryCode_->GetBufferSize(),		//�����ϵ� HLSL �ڵ��� ũ��.
		IID_ID3D11ShaderReflection,				//������ HLSL �ڵ� ������ ��ȯ�Ҷ� ������ ID3D11ShaderReflection�� �������̽� �ĺ���(GUID).
		reinterpret_cast<void**>(&compileInfo)	//������ HLSL �ڵ� ������ ��ȯ���� ID3D11ShaderReflection�� ������.
	))
	{
		MsgBoxAssert("���̴� ���� ���� ����.");
		return;
	}



	D3D11_SHADER_DESC shaderInfo = { 0 };
	compileInfo->GetDesc(&shaderInfo);


	//typedef struct _D3D11_SHADER_INPUT_BIND_DESC
	//{
	//	LPCSTR                      Name;			���̴��� ����ϴ� ���ҽ� �̸�.
	//	D3D_SHADER_INPUT_TYPE       Type;			���̴��� ����ϴ� ���ҽ� ����(�ؽ���, ������� ���...)
	//	UINT                        BindPoint;		�ش� ���ҽ��� �������� ��� ��ȣ.
	//	UINT                        BindCount;		������ ���ҽ� ����.
	//	UINT                        uFlags;			Input binding flags
	//	D3D_RESOURCE_RETURN_TYPE    ReturnType;		��ȯ��. 3���� �ؽ�ó���� ���.
	//	D3D_SRV_DIMENSION           Dimension;		Dimension (if texture) 3���� �ؽ�ó���� ���.
	//	UINT                        NumSamples;		��Ƽ���ø��� �ؽ�ó ��. �ؽ��İ� �ƴ϶�� 0. �ؽ�ó�� ��Ƽ���ø����� �ʴ´ٸ� -1.
	//} D3D11_SHADER_INPUT_BIND_DESC;
	D3D11_SHADER_INPUT_BIND_DESC resInfo = { 0 };

	for (UINT i = 0; i < shaderInfo.BoundResources; i++)
		//shaderInfo.BoundResources: �� ���̴����� '����' �� ���ҽ� ��. ������ ���� ���ҽ��� ���õȴ�.
	{
		compileInfo->GetResourceBindingDesc(i, &resInfo);
		//DirectX �ܺο��� ����� �� ���� compileInfo���� D3D11_SHADER_INPUT_BIND_DESC �������� 
		// ���̴��� ����ϰ� �� ���ҽ��� ���������� �����Ѵ�.

		std::string uppercaseResourceName = GameEngineString::ToUpperReturn(resInfo.Name);

		switch (resInfo.Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* cBufferPtr = compileInfo->GetConstantBufferByName(resInfo.Name);
			//DirectX �ܺο��� ����� �� ���� compileInfo���� ������۸� �����Ѵ�.

			//typedef struct _D3D11_SHADER_BUFFER_DESC
			//{
			//	LPCSTR                  Name;		������� �̸�.
			//	D3D_CBUFFER_TYPE        Type;		��������� ����.
			//	UINT                    Variables;	��������� ������� ����.
			//	UINT                    Size;		������� ũ��.
			//	UINT                    uFlags;		������۰� ����� ������ �����ϴ� �÷���. 
			//		hlsl�ڵ忡 ������ �������� �����Ѵٴ� �÷��� �ϳ��ۿ� �����Ƿ� �ǹ� ����.
			//} D3D11_SHADER_BUFFER_DESC;
			D3D11_SHADER_BUFFER_DESC cBufferDesc = { 0 };
			cBufferPtr->GetDesc(&cBufferDesc);


			GameEngineConstantBufferSetter newCBufferSetter;
			//�� ������ۼ��͸� �����ϰ�, ���Ϳ� ���̴��� ������� �� ������۸� ����ϴµ� �ʿ��� �������� �����Ѵ�.

			newCBufferSetter.parentShader_ = this;
			//�� ������ۼ��͸� �����ϴ� ���̴��� �θ� ���̴��� �Ѵ�.

			newCBufferSetter.SetName(uppercaseResourceName);
			//���ҽ������� �̸��� HLSL�ڵ� ���� ����� �ڱ� ���ҽ�Ÿ�� ���� �̸��� �״�� ���󰣴�.

			newCBufferSetter.parentShaderType_ = this->shaderType_;
			//�θ� ���̴��� � ���̴����� �����Ѵ�.

			newCBufferSetter.constantBuffer_ = GameEngineConstantBuffer::CreateAndFind(
				newCBufferSetter.GetName(),	//������� ������۰� ������ �����, �̹� ������ �����Ѵ�.
				cBufferDesc			//���� �̸�, ���� ũ���� ��� ���۴� ���̴����ҽ����۵��� �����͸� �����Ѵ�.
						//�׷��� �̹� ������� �ִ°� �� ���� �Ͷ߸��� �ʰ� ��� �̹� ������� �ִ°� �����Ѵ�.
			);

			newCBufferSetter.bindPoint_ = resInfo.BindPoint;

			std::pair<std::map<std::string, GameEngineConstantBufferSetter>::iterator, bool> insertResult =
				constantBufferSetterMap_.insert(std::make_pair(newCBufferSetter.GetName(), newCBufferSetter));
			//�ʿ� ��ġ�� Ű���� ���� ���Ҹ� �����Ϸ��� �ϸ� �ߺ��� Ű���� ���� ���Ҹ� ����Ű�� 
			//���ͷ����Ϳ� false�� �� �� ��ȯ�ϰ� ���� �õ��� ���õȴ�.
			//������ �����ߴٸ� ������ ���Ҹ� ����Ű�� ���ͷ����Ϳ� true�� ���� �� ��ȯ�Ѵ�.


			if (false == insertResult.second)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ": �̹� ���� �̸��� ������� ���Ͱ� �����մϴ�.");
				//�ߺ����� ��������� ���ܼ� �ȵȴ�.
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
					MsgBoxAssertString(std::string(resInfo.Name) + ":  �̹� ���� �̸��� �ؽ���2D�迭 ���Ͱ� �����մϴ�.");
					return;
				}
				break;
			}
			else if (D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2D == resInfo.Dimension)
			{
				GameEngineTextureSetter newTextureSetter;
				//�� �ؽ�ó���͸� �����ϰ�, ���Ϳ� ���̴��� �ؽ�ó �� �ؽ�ó�� ����ϴµ� �ʿ��� �������� �����Ѵ�.

				newTextureSetter.parentShader_ = this;
				//�� �ؽ�ó���͸� �����ϴ� ���̴��� �θ� ���̴��� �Ѵ�.

				newTextureSetter.SetName(uppercaseResourceName);
				//���ҽ������� �̸��� HLSL�ڵ� ���� ����� Texture2DŸ�� ���� �̸��� �״�� ���󰣴�.

				newTextureSetter.parentShaderType_ = this->shaderType_;
				//�θ� ���̴��� � ���̴����� �����Ѵ�.

				newTextureSetter.texture_ = GameEngineTexture::Find("NSet.png");//<-�ؽ��İ� �ƿ� ���ٴ� ��� �߸� �����.
				//���߿� ������ �ؽ�ó�� �����̵� �ϴ� ���� �⺻���� �ؽ�ó�� "NSet.png"�� �ؽ�ó���Ϳ� �����ؼ� 
				// �߰����� �ؽ�ó ������ ������ ��� �������� "NSet.png"�� �������ǰ� �Ѵ�.

				newTextureSetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineTextureSetter>::iterator, bool> insertResult
					= textureSetterMap_.insert(std::make_pair(newTextureSetter.GetName(), newTextureSetter));
				//�ʿ� ��ġ�� Ű���� ���� ���Ҹ� �����Ϸ��� �ϸ� �ߺ��� Ű���� ���� ���Ҹ� ����Ű�� 
				//���ͷ����Ϳ� false�� �� �� ��ȯ�ϰ� ���� �õ��� ���õȴ�.
				//������ �����ߴٸ� ������ ���Ҹ� ����Ű�� ���ͷ����Ϳ� true�� ���� �� ��ȯ�Ѵ�.

				if (false == insertResult.second)
				{
					MsgBoxAssertString(std::string(resInfo.Name) + ":  �̹� ���� �̸��� �ؽ��� ���Ͱ� �����մϴ�.");
					return;
				}

				break;
			}
			else
			{
				MsgBoxAssert("���� �غ���� ���� ������ �ؽ�ó�Դϴ�.");
				return;
			}
		}

		case D3D_SIT_SAMPLER:
		{
			GameEngineSamplerSetter newSamplerSetter;
			//�� ���÷����͸� �����ϰ�, ���Ϳ� ���̴��� ���÷� �� ���÷��� ����ϴµ� �ʿ��� �������� �����Ѵ�.

			newSamplerSetter.parentShader_ = this;
			//�� ���÷����͸� �����ϴ� ���̴��� �θ� ���̴��� �Ѵ�.

			newSamplerSetter.SetName(uppercaseResourceName);
			//���ҽ������� �̸��� HLSL�ڵ� ���� ����� �ڱ� ���ҽ�Ÿ�� ���� �̸��� �״�� ���󰣴�.

			newSamplerSetter.parentShaderType_ = this->shaderType_;
			//�θ� ���̴��� � ���̴����� �����Ѵ�.

			newSamplerSetter.sampler_ = GameEngineSampler::Find(uppercaseResourceName);

			if (nullptr == newSamplerSetter.sampler_)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ": �׷� �̸��� ���÷��� �������� �ʽ��ϴ�. \nShaderName: " + _thisShaderName.data());
				return;
			}


			newSamplerSetter.bindPoint_ = resInfo.BindPoint;

			std::pair<std::map<std::string, GameEngineSamplerSetter>::iterator, bool> insertResult
				= samplerSetterMap_.insert(std::make_pair(newSamplerSetter.GetName(), newSamplerSetter));
			//�ʿ� ��ġ�� Ű���� ���� ���Ҹ� �����Ϸ��� �ϸ� �ߺ��� Ű���� ���� ���Ҹ� ����Ű�� 
			//���ͷ����Ϳ� false�� �� �� ��ȯ�ϰ� ���� �õ��� ���õȴ�.
			//������ �����ߴٸ� ������ ���Ҹ� ����Ű�� ���ͷ����Ϳ� true�� ���� �� ��ȯ�Ѵ�.

			if (false == insertResult.second)
			{
				MsgBoxAssertString(std::string(resInfo.Name) + ":  �̹� ���� �̸��� ���÷� ���Ͱ� �����մϴ�.");
				return;
			}

			break;
		}

		case D3D_SIT_STRUCTURED:
		{
			//����ȭ���۴� �������� Ư���� ��뷮 �޸𸮸� ����ϴ°��� �⺻�ε�, 
			//���� �Ҵ�Ǵ� Ư���� �̸� ������� ����.

			ID3D11ShaderReflectionConstantBuffer* cBufferPtr = compileInfo->GetConstantBufferByName(resInfo.Name);
			D3D11_SHADER_BUFFER_DESC shaderBufferDesc = { 0 };
			cBufferPtr->GetDesc(&shaderBufferDesc);

			GameEngineStructuredBufferSetter newSBufferSetter;
			newSBufferSetter.parentShader_ = this;
			newSBufferSetter.SetName(uppercaseResourceName);
			newSBufferSetter.parentShaderType_ = this->shaderType_;

			//������ �������� ������� �˼��־ �̰ɷ� �¥�� ���۸� �������� �˼��� ����.
			// �׷��� ���� 0 ���� �ϴ� �����д�.

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
				MsgBoxAssertString(std::string(resInfo.Name) + ": �̹� ���� �̸��� ����ȭ ���� ���Ͱ� �����մϴ�.");
				return;
			}

			break;
		}

		default:
		{
			MsgBoxAssert("���ǵ��� ���� ���̴� ���ҽ� Ÿ���Դϴ�.");
			return;
		}
		}
	}
}
