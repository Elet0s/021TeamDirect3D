#include "PreCompile.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h" 
#include "GameEngineStructuredBuffer.h"

GameEngineShaderResourceHelper::GameEngineShaderResourceHelper()
{
}

GameEngineShaderResourceHelper::~GameEngineShaderResourceHelper()
{
}

void GameEngineShaderResourceHelper::ResourceCheck(GameEngineRenderingPipeLine* _pipeLine)
{
	if (nullptr == _pipeLine)
	{
		MsgBoxAssert("렌더링 파이프라인이 없습니다.");
		return;
	}
	
	ShaderCheck(_pipeLine->GetVertexShader());
	ShaderCheck(_pipeLine->GetPixelShader());
}

bool GameEngineShaderResourceHelper::IsConstantBuffer(const std::string& _name)
{
	std::string uppercaseCBufferSetterName = GameEngineString::ToUpperReturn(_name);

	if (constantBufferSetterMap_.end() == constantBufferSetterMap_.find(uppercaseCBufferSetterName) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShaderResourceHelper::IsStructuredBuffer(const std::string& _name)
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

bool GameEngineShaderResourceHelper::IsTexture(const std::string& _name)
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

bool GameEngineShaderResourceHelper::IsSampler(const std::string& _name)
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

void GameEngineShaderResourceHelper::SetConstantBuffer_Link(
	const std::string& _name,
	const void* _data,
	unsigned int _dataSize
)
{
	if (false == IsConstantBuffer(_name))
	{
		MsgBoxAssertString(_name + ": 그런 이름의 상수버퍼 세터가 존재하지 않습니다.");
		return;
	}

	if (16 > _dataSize)
	{
		MsgBoxAssert("상수버퍼는 최소 16바이트 이상의 크기를 가져야 합니다.");
		return;
	}

	std::string uppercaseCBufferSetterName = GameEngineString::ToUpperReturn(_name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator nameLowerBound =
		constantBufferSetterMap_.lower_bound(uppercaseCBufferSetterName);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator nameUpperBound =
		constantBufferSetterMap_.upper_bound(uppercaseCBufferSetterName);

	for (std::multimap<std::string, GameEngineConstantBufferSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		//트랜스폼이 바뀌면 변경된 정보가 자동 갱신된다.

		iter->second.settingDataToGPU_ = _data;
		iter->second.byteWidth_ = _dataSize;
		//상수버퍼의 주소값과 크기를 얕은 복사로 셰이더리소스헬퍼에게 넘겨 저장하게 한다.
		//상수버퍼의 정보가 바뀌면 변경된 정보가 자동 갱신된다.
	}
}

void GameEngineShaderResourceHelper::SetConstantBuffer_New(
	const std::string& _name,
	const void* _data, 
	unsigned int _dataSize
)
{
	if (false == IsConstantBuffer(_name))
	{
		MsgBoxAssertString(_name + ": 그런 이름의 상수버퍼가 존재하지 않습니다.");
		return;
	}

	if (16 > _dataSize)
	{
		MsgBoxAssert("상수버퍼는 최소 16바이트 이상의 크기를 가져야 합니다.");
		return;
	}

	std::string uppercaseCBufferSetterName = GameEngineString::ToUpperReturn(_name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator nameLowerBound =
		constantBufferSetterMap_.lower_bound(uppercaseCBufferSetterName);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator nameUpperBound =
		constantBufferSetterMap_.upper_bound(uppercaseCBufferSetterName);

	for (std::multimap<std::string, GameEngineConstantBufferSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		if (0 == iter->second.originalData_.size() 
			|| iter->second.originalData_.size() != _dataSize)
		{
			iter->second.originalData_.resize(_dataSize);
		}

		iter->second.settingDataToGPU_ = &iter->second.originalData_[0];

		memcpy_s(
			&iter->second.originalData_[0],
			_dataSize,
			_data,
			_dataSize
		);	//깊은복사.

		iter->second.byteWidth_ = _dataSize;
	}

}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string& _textureSetterName,
	const std::string& _textureName
)
{
	std::string uppercaseTextureSetterName = GameEngineString::ToUpperReturn(_textureSetterName);

	if (false == IsTexture(uppercaseTextureSetterName))
	{
		MsgBoxAssertString(_textureSetterName + ": 그런 이름의 텍스쳐 세터가 존재하지 않습니다.");
		return nullptr;
	}

	return SetTexture(_textureSetterName, GameEngineTexture::Find(_textureName));
}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string& _textureSetterName,
	GameEngineTexture* _texture
)
{
	std::string uppercaseTextureSetterName = GameEngineString::ToUpperReturn(_textureSetterName);

	if (false == this->IsTexture(uppercaseTextureSetterName))
	{
		MsgBoxAssertString(_textureSetterName + ":그런 이름의 텍스쳐 세터가 존재하지 않습니다.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator nameLowerBound
		= textureSetterMap_.lower_bound(uppercaseTextureSetterName);

	std::multimap<std::string, GameEngineTextureSetter>::iterator nameUpperBound
		= textureSetterMap_.upper_bound(uppercaseTextureSetterName);

	for(std::multimap<std::string, GameEngineTextureSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound ; ++iter)
	{
		BindTexture(iter->second, _texture);
	}

	return _texture;
}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string& _textureSetterName, const std::string& _folderTextureName, int _index)
{
	if (false == IsTexture(_textureSetterName))
	{
		MsgBoxAssertString(_textureSetterName + ": 그런 이름의 텍스터 세터가 존재하지 않습니다.");
		return nullptr;
	}

	std::string uppercaseFolderTextureName = GameEngineString::ToUpperReturn(_folderTextureName);

	GameEngineFolderTexture* folderTexture = GameEngineFolderTexture::Find(uppercaseFolderTextureName);

	if (nullptr == folderTexture)
	{
		MsgBoxAssertString(_folderTextureName + ": 그런 이름의 폴더 텍스처가 존재하지 않습니다.");
	}

	return SetTexture(_textureSetterName, folderTexture->GetTexture(_index));
}

GameEngineSampler* GameEngineShaderResourceHelper::SetSampler(const std::string& _samplerSetterName, GameEngineSampler* _sampler)
{
	std::string uppercaseSamplerSetterName = GameEngineString::ToUpperReturn(_samplerSetterName);

	if (false == IsSampler(_samplerSetterName))
	{
		MsgBoxAssertString(_samplerSetterName + ": 그런 이름의 샘플러 세터가 존재하지 않습니다.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineSamplerSetter>::iterator nameLowerBound
		= samplerSetterMap_.lower_bound(uppercaseSamplerSetterName);

	std::multimap<std::string, GameEngineSamplerSetter>::iterator nameUpperBound
		= samplerSetterMap_.upper_bound(uppercaseSamplerSetterName);

	for (std::multimap<std::string, GameEngineSamplerSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		BindSampler(iter->second, _sampler);
	}

	return _sampler;
}

GameEngineSampler* GameEngineShaderResourceHelper::SetSampler(const std::string& _samplerSetterName, const std::string& _samplerName)
{
	std::string uppercaseSamplerSetterName = GameEngineString::ToUpperReturn(_samplerSetterName);

	if (false == IsSampler(_samplerSetterName))
	{
		MsgBoxAssertString(_samplerSetterName + ": 그런 이름의 샘플러 세터가 존재하지 않습니다.");
		return nullptr;
	}

	return SetSampler(_samplerSetterName, GameEngineSampler::Find(_samplerName));
}

void GameEngineShaderResourceHelper::AllConstantBufferNew()
{
	for (std::multimap<std::string, GameEngineConstantBufferSetter>::iterator iter = constantBufferSetterMap_.begin();
		iter != constantBufferSetterMap_.end(); iter++)
	{
		unsigned int cBufferByteWidth = iter->second.constantBuffer_->GetBufferDesc().ByteWidth;

		iter->second.originalData_.resize(static_cast<size_t>(cBufferByteWidth));
		iter->second.settingDataToGPU_ = &iter->second.originalData_[0];
		iter->second.byteWidth_ = cBufferByteWidth;
	}
}

GameEngineStructuredBufferSetter* GameEngineShaderResourceHelper::GetStructuredBufferSetter(const std::string& _name)
{
	std::string uppercaseSBufferName = GameEngineString::ToUpperReturn(_name);

	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator findIter
		= structuredBufferSetterMap_.find(uppercaseSBufferName);

	if (structuredBufferSetterMap_.end() == findIter)
	{
		return nullptr;
	}
	else
	{
		return &findIter->second;
	}
}

void GameEngineShaderResourceHelper::ShaderCheck(GameEngineShader* _shader)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& setterPair 
		: _shader->constantBufferSetterMap_)
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator insertIter =
			constantBufferSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		BindConstantBuffer(insertIter->second, setterPair.second.constantBuffer_);
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& setterPair
		: _shader->textureSetterMap_)
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator insertIter  
			= textureSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));


		BindTexture(insertIter->second, setterPair.second.texture_);
	}


	for (const std::pair<std::string, GameEngineSamplerSetter>& setterPair 
		: _shader->samplerSetterMap_)
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator insertIter
			= samplerSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		BindSampler(insertIter->second, setterPair.second.sampler_);
	}

	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& setterPair 
		: _shader->structuredBufferSetterMap_)
	{
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator insertIter
			= structuredBufferSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		BindStructuredBuffer(insertIter->second, setterPair.second.structuredBuffer_);
	}
}

void GameEngineShaderResourceHelper::BindConstantBuffer(GameEngineConstantBufferSetter& _cBufferSetter, GameEngineConstantBuffer* _cBuffer)
{
	_cBufferSetter.constantBuffer_ = _cBuffer;

	if (nullptr == _cBufferSetter.constantBuffer_)
	{
		MsgBoxAssert("상수버퍼가 존재하지 않습니다.");
		return;
	}

	switch (_cBufferSetter.parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		_cBufferSetter.settingFunction_ = std::bind(
			&GameEngineConstantBuffer::VSSetting,
			_cBufferSetter.constantBuffer_,
			_cBufferSetter.bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		_cBufferSetter.settingFunction_ = std::bind(
			&GameEngineConstantBuffer::PSSetting,
			_cBufferSetter.constantBuffer_,
			_cBufferSetter.bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineShaderResourceHelper::BindTexture(GameEngineTextureSetter& _textureSetter, GameEngineTexture* _texture)
{
	_textureSetter.texture_ = _texture;

	if (nullptr == _textureSetter.texture_)
	{
		MsgBoxAssert("텍스처가 존재하지 않습니다.");
		return;
	}

	switch (_textureSetter.parentShaderType_)
	{	
	case ShaderType::VertexShader:
	{	
		_textureSetter.settingFunction_ = std::bind(
			&GameEngineTexture::VSSetting,
			_textureSetter.texture_,
			_textureSetter.bindPoint_
		);

		_textureSetter.resetFunction_ = std::bind(
			&GameEngineTexture::VSReset,
			_textureSetter.texture_,
			_textureSetter.bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		_textureSetter.settingFunction_ = std::bind(
			&GameEngineTexture::PSSetting,
			_textureSetter.texture_,
			_textureSetter.bindPoint_
		);

		_textureSetter.resetFunction_ = std::bind(
			&GameEngineTexture::PSReset,
			_textureSetter.texture_,
			_textureSetter.bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}


}

void GameEngineShaderResourceHelper::BindSampler(GameEngineSamplerSetter& _samplerSetter, GameEngineSampler* _sampler)
{
	_samplerSetter.sampler_ = _sampler;

	if (nullptr == _samplerSetter.sampler_)
	{
		MsgBoxAssert("샘플러가 존재하지 않습니다.");
		return;
	}

	switch (_samplerSetter.parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		_samplerSetter.settingFunction_ = std::bind(
			&GameEngineSampler::VSSetting,
			_samplerSetter.sampler_,
			_samplerSetter.bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		_samplerSetter.settingFunction_ = std::bind(
			&GameEngineSampler::PSSetting,
			_samplerSetter.sampler_,
			_samplerSetter.bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineShaderResourceHelper::BindStructuredBuffer(GameEngineStructuredBufferSetter& _sBufferSetter, GameEngineStructuredBuffer* _sBuffer)
{
	_sBufferSetter.structuredBuffer_ = _sBuffer;

	if (nullptr == _sBufferSetter.structuredBuffer_)
	{
		MsgBoxAssert("구조화 버퍼가 존재하지 않습니다.");
		return;
	}

	switch (_sBufferSetter.parentShaderType_)
	{
	case ShaderType::VertexShader:
	{
		_sBufferSetter.settingFunction_ = std::bind(
			&GameEngineStructuredBuffer::VSSetting,
			_sBufferSetter.structuredBuffer_, 
			_sBufferSetter.bindPoint_
		);
		break;
	}

	case ShaderType::PixelShader:
	{
		_sBufferSetter.settingFunction_ = std::bind(
			&GameEngineStructuredBuffer::PSSetting,
			_sBufferSetter.structuredBuffer_,
			_sBufferSetter.bindPoint_
		);
		break;
	}

	default:
		MsgBoxAssert("아직 준비되지 않은 셰이더 타입입니다.");
		return;
	}
}

void GameEngineShaderResourceHelper::AllResourcesSetting()
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& cBufferSetterPair
		: constantBufferSetterMap_)
	{
		cBufferSetterPair.second.Setting();
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& textureSetterPair
		: textureSetterMap_)
	{
		textureSetterPair.second.Setting();
	}

	for (const std::pair<std::string, GameEngineSamplerSetter>& samplerSetterPair
		: samplerSetterMap_)
	{
		samplerSetterPair.second.Setting();
	}

	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetterPair
		: structuredBufferSetterMap_)
	{
		structuredBufferSetterPair.second.Setting();
	}
}

void GameEngineShaderResourceHelper::AllResourcesReset()
{
	for (const std::pair<std::string, GameEngineTextureSetter>& textureSetterPair : textureSetterMap_)
	{
		textureSetterPair.second.Reset();
	}
}