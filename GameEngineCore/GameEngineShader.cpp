#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineStructuredBuffer.h"



void GameEngineConstantBufferSetter::Setting() const
{
	constantBuffer_->ChangeData(settingDataToGPU_, byteWidth_);

	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineTextureSetter::Setting() const
{
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineTextureSetter::Reset() const
{
	resetFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineSamplerSetter::Setting() const
{
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineStructuredBufferSetter::Setting() const
{
	structuredBuffer_->ChangeData(&settingDataBufferToGPU_[0], static_cast<UINT>(settingDataBufferToGPU_.size()));
	settingFunction_();	//����ġ�� �ѹ� �� ������ ��ų� ���.
}

void GameEngineStructuredBufferSetter::Resize(int _count)
{
	structuredBuffer_->CreateOrResize(_count);
	settingDataBufferToGPU_.resize(
		static_cast<size_t>(structuredBuffer_->GetDataSize()) * static_cast<size_t>(_count));
}

int GameEngineStructuredBufferSetter::GetDataSize()
{
	return structuredBuffer_->GetDataSize();
}

void GameEngineStructuredBufferSetter::PushData(const void* _data, int _count)
{
	int byteWidth = structuredBuffer_->GetDataSize() * _count;
	memcpy_s(
		&settingDataBufferToGPU_[byteWidth],
		settingDataBufferToGPU_.size(),
		_data,
		structuredBuffer_->GetDataSize()
	);
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

void GameEngineShader::AutoCompile(const std::string& _path)
{
	GameEngineFile file = GameEngineFile(_path);
	file.Open(OpenMode::Read, FileMode::Text);

	std::string allHLSLCode = file.GetString();

	//��ҹ��� ����!
	size_t vsEntryIndex = allHLSLCode.find("_VS(");
	if (std::string::npos != vsEntryIndex)
	{
		GameEngineVertexShader* vertexShader = nullptr;

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
				size_t instFirstIndex = allHLSLCode.find_last_of(" ", vsInstEntryIndex);
				std::string vsInstEntryPoint = allHLSLCode.substr(
					instFirstIndex + 1,
					vsInstEntryIndex - instFirstIndex - 1
				);
				vsInstEntryPoint += "_VSINST";
				vertexShader->InstancingShaderCompile(_path, vsInstEntryPoint);
			}

		}


	}
	//else
	//{
	//	MsgBoxAssert("�ڵ� ���� ���ؽ����̴��� �����ϴ�.");
	//	//���̴� �̸� ��Ģ0: ���ؽ����̴��� ��_VS(��, �ȼ����̴��� ��_PS(���� ���ڿ� ���ο� ���ԵǾ� �־�� �Ѵ�.
	//	return;
	//}


	size_t psEntryIndex = allHLSLCode.find("_PS(");
	if (std::string::npos != psEntryIndex)
	{
		size_t firstIndex = allHLSLCode.find_last_of(" ", psEntryIndex);
		std::string psEntryName = allHLSLCode.substr(
			firstIndex + 1,
			psEntryIndex - firstIndex - 1
		);
		psEntryName += "_PS";

		GameEnginePixelShader::Load(_path, psEntryName);
	}
	//else
	//{
	//	MsgBoxAssert("�ڵ� ���� �ȼ����̴��� �����ϴ�.");
	//	//���̴� �̸� ��Ģ 0: ���ؽ����̴��� ��_VS(��, �ȼ����̴��� ��_PS(���� ���ڿ� ���ο� ���ԵǾ� �־�� �Ѵ�.
	//	return;
	//}
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

void GameEngineShader::CreateVersion(const std::string& _shaderType, UINT _versionHigh, UINT _versionLow)
{
	shaderVersion_ = "";
	shaderVersion_ += _shaderType + "_";
	shaderVersion_ += std::to_string(_versionHigh);
	shaderVersion_ += "_";
	shaderVersion_ += std::to_string(_versionLow);
}

void GameEngineShader::CompileHLSLCode(const std::string& _path)
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
		MsgBoxAssertString(entryPoint_ + ": HLSL�ڵ� ������ ����.");
		MsgBoxAssertString(errorText);
		errorMessage->Release();
		return;
	}

	//errorMessage->Release();
	//�����Ͽ� ������ �����ٸ� errorMessage�� ���������λ��� �״�� �������Ƿ� �������� ���� ����.
}

void GameEngineShader::ShaderResCheck()
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
	//	UINT                        NumSamples;		Number of samples (0 if not MS texture) �ؽ��İ� �ƴ϶�� 0.
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
					uppercaseResourceName,	//������� ������۰� ������ �����, �̹� ������ �����Ѵ�.
					cBufferDesc			//���� �̸�, ���� ũ���� ��� ���۴� ���̴����ҽ����۵��� �����͸� �����Ѵ�.
							//�׷��� �̹� ������� �ִ°� �� ���� �Ͷ߸��� �ʰ� ��� �̹� ������� �ִ°� �����Ѵ�.
				);

				newCBufferSetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineConstantBufferSetter>::iterator, bool> insertResult = 
					constantBufferSetterMap_.insert(std::make_pair(uppercaseResourceName, newCBufferSetter));
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
				GameEngineTextureSetter newTextureSetter;
				//�� �ؽ�ó���͸� �����ϰ�, ���Ϳ� ���̴��� �ؽ�ó �� �ؽ�ó�� ����ϴµ� �ʿ��� �������� �����Ѵ�.

				newTextureSetter.parentShader_ = this;
				//�� �ؽ�ó���͸� �����ϴ� ���̴��� �θ� ���̴��� �Ѵ�.

				newTextureSetter.SetName(uppercaseResourceName);
				//���ҽ������� �̸��� HLSL�ڵ� ���� ����� �ڱ� ���ҽ�Ÿ�� ���� �̸��� �״�� ���󰣴�.

				newTextureSetter.parentShaderType_ = this->shaderType_;
				//�θ� ���̴��� � ���̴����� �����Ѵ�.

				newTextureSetter.texture_ = GameEngineTexture::Find("NSet.png");//<-�ؽ��İ� �ƿ� ���ٴ� ��� �߸� �����.
				//���߿� ������ �ؽ�ó�� �����̵� �ϴ� ���� �⺻���� �ؽ�ó�� "NSet.png"�� �ؽ�ó���Ϳ� �����ؼ� 
				// �߰����� �ؽ�ó ������ ������ ��� �������� "NSet.png"�� �������ǰ� �Ѵ�.

				newTextureSetter.bindPoint_ = resInfo.BindPoint;
				
				std::pair<std::map<std::string, GameEngineTextureSetter>::iterator, bool> insertResult
					= textureSetterMap_.insert(std::make_pair(uppercaseResourceName, newTextureSetter));
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

				newSamplerSetter.sampler_ = GameEngineSampler::Find("EngineSampler_Linear");
				//�� ���÷����Ͱ� ���� ���÷��� �ϴ� ���� �⺻���� ���÷��� "EngineSampler_Linear"�� �����ϰ�
				// �ٸ� ���÷��� �ʿ��ϸ� �� ���̴��� ���� ������ �������� �ٸ������� �ٲ��ش�.

				newSamplerSetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineSamplerSetter>::iterator, bool> insertResult
					= samplerSetterMap_.insert(std::make_pair(uppercaseResourceName, newSamplerSetter));
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

				// ������ �������� ������� �˼��־ �̰ɷ� �¥�� ���۸� �������� �˼��� ����.

				newSBufferSetter.structuredBuffer_ = GameEngineStructuredBuffer::CreateAndFind(
					uppercaseResourceName,	//
					shaderBufferDesc,		//
					0						//
				);
				newSBufferSetter.bindPoint_ = resInfo.BindPoint;

				std::pair<std::map<std::string, GameEngineStructuredBufferSetter>::iterator, bool> insertResult 
					= structuredBufferSetterMap_.insert(
						std::make_pair(uppercaseResourceName, newSBufferSetter)
				);

				if (false == insertResult.second)
				{
					MsgBoxAssertString(std::string(resInfo.Name) + ":  �̹� ���� �̸��� ����ȭ ���� ���Ͱ� �����մϴ�.");
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
