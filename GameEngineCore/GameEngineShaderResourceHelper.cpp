#include "PreCompile.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineMaterial.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h" 
#include "GameEngineStructuredBuffer.h"
#include "GameEngineTexture2DArray.h"

GameEngineShaderResourceHelper::GameEngineShaderResourceHelper()
{
}

GameEngineShaderResourceHelper::~GameEngineShaderResourceHelper()
{
}

void GameEngineShaderResourceHelper::ResourceCheck(GameEngineMaterial* _material)
{
	if (nullptr == _material)
	{
		MsgBoxAssert("���׸����� �����ϴ�.");
		return;
	}

	ShaderCheck(_material->GetVertexShader());
	ShaderCheck(_material->GetPixelShader());
}

bool GameEngineShaderResourceHelper::IsConstantBuffer(const std::string_view& _name)
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

bool GameEngineShaderResourceHelper::IsTexture(const std::string_view& _name)
{
	std::string uppercaseTextureSetterName = GameEngineString::ToUpperReturn(_name);

	if (textureSetterMap_.end() == textureSetterMap_.find(uppercaseTextureSetterName))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameEngineShaderResourceHelper::IsSampler(const std::string_view& _name)
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

bool GameEngineShaderResourceHelper::IsStructuredBuffer(const std::string_view& _name)
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

bool GameEngineShaderResourceHelper::IsTexture2DArray(const std::string_view& _name)
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

void GameEngineShaderResourceHelper::SetConstantBuffer_Link(
	const std::string_view& _name,
	const void* _data,
	unsigned int _dataSize
)
{
	if (false == IsConstantBuffer(_name))
	{
		MsgBoxAssertString(std::string(_name) + ": �׷� �̸��� ������� ���Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	if (16 > _dataSize)
	{
		MsgBoxAssert("������۴� �ּ� 16����Ʈ �̻��� ũ�⸦ ������ �մϴ�.");
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
		iter->second.settingDataToGPU_ = _data;
		iter->second.size_ = _dataSize;
		//��������� �ּҰ��� ũ�⸦ ���� ����� ���̴����ҽ����ۿ��� �Ѱ� �����ϰ� �Ѵ�.
		//��������� ������ �ٲ�� ����� ������ �ڵ� ���ŵȴ�.
	}
}

void GameEngineShaderResourceHelper::SetConstantBuffer_New(
	const std::string_view& _name,
	const void* _data,
	unsigned int _byteWidth
)
{
	if (false == IsConstantBuffer(_name))
	{
		MsgBoxAssertString(std::string(_name) + ": �׷� �̸��� ������۰� �������� �ʽ��ϴ�.");
		return;
	}

	if (16 > _byteWidth)
	{
		MsgBoxAssert("������۴� �ּ� 16����Ʈ �̻��� ũ�⸦ ������ �մϴ�.");
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
			|| iter->second.originalData_.size() != _byteWidth)
		{
			iter->second.originalData_.resize(_byteWidth);
		}

		iter->second.settingDataToGPU_ = &iter->second.originalData_[0];

		memcpy_s(
			&iter->second.originalData_[0],
			_byteWidth,
			_data,
			_byteWidth
		);	//������ ��ü�� �����ϴ� ��������.

		iter->second.size_ = _byteWidth;
	}

}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string_view& _textureSetterName,
	const std::string_view& _textureName
)
{
	if (false == IsTexture(_textureSetterName))
	{
		MsgBoxAssertString(std::string(_textureSetterName) + ": �׷� �̸��� �ؽ��� ���Ͱ� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	return SetTexture(_textureSetterName, GameEngineTexture::Find(_textureName));
}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string_view& _textureSetterName,
	GameEngineTexture* _texture
)
{
	std::string uppercaseTextureSetterName = GameEngineString::ToUpperReturn(_textureSetterName);

	if (false == this->IsTexture(_textureSetterName))
	{
		MsgBoxAssertString(std::string(_textureSetterName) + ":�׷� �̸��� �ؽ��� ���Ͱ� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator nameLowerBound
		= textureSetterMap_.lower_bound(uppercaseTextureSetterName);

	std::multimap<std::string, GameEngineTextureSetter>::iterator nameUpperBound
		= textureSetterMap_.upper_bound(uppercaseTextureSetterName);

	for (std::multimap<std::string, GameEngineTextureSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		iter->second.texture_ = _texture;
		iter->second.Bind();
	}

	return _texture;
}

GameEngineTexture* GameEngineShaderResourceHelper::SetTexture(
	const std::string_view& _textureSetterName,
	const std::string_view& _folderTextureName,
	int _index
)
{
	if (false == IsTexture(_textureSetterName))
	{
		MsgBoxAssertString(std::string(_textureSetterName) + ": �׷� �̸��� �ؽ��� ���Ͱ� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	GameEngineFolderTexture* folderTexture = GameEngineFolderTexture::Find(_folderTextureName);

	if (nullptr == folderTexture)
	{
		MsgBoxAssertString(std::string(_folderTextureName) + ": �׷� �̸��� ���� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return SetTexture(_textureSetterName, folderTexture->GetTexture(_index));
}

GameEngineSampler* GameEngineShaderResourceHelper::SetSampler(
	const std::string_view& _samplerSetterName,
	GameEngineSampler* _sampler
)
{
	std::string uppercaseSamplerSetterName = GameEngineString::ToUpperReturn(_samplerSetterName);

	if (false == IsSampler(_samplerSetterName))
	{
		MsgBoxAssertString(std::string(_samplerSetterName) + ": �׷� �̸��� ���÷� ���Ͱ� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineSamplerSetter>::iterator nameLowerBound
		= samplerSetterMap_.lower_bound(uppercaseSamplerSetterName);

	std::multimap<std::string, GameEngineSamplerSetter>::iterator nameUpperBound
		= samplerSetterMap_.upper_bound(uppercaseSamplerSetterName);

	for (std::multimap<std::string, GameEngineSamplerSetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		iter->second.sampler_ = _sampler;
		iter->second.Bind();
	}

	return _sampler;
}

GameEngineSampler* GameEngineShaderResourceHelper::SetSampler(
	const std::string_view& _samplerSetterName,
	const std::string_view& _samplerName
)
{
	return SetSampler(_samplerSetterName, GameEngineSampler::Find(_samplerName));
}

GameEngineTexture2DArray* GameEngineShaderResourceHelper::SetTexture2DArray(
	const std::string_view& _textureArraySetterName,
	const std::string_view& _texturesName
)
{
	return SetTexture2DArray(_textureArraySetterName, GameEngineTexture2DArray::Find(_texturesName));
}

GameEngineTexture2DArray* GameEngineShaderResourceHelper::SetTexture2DArray(
	const std::string_view& _textureArraySetterName,
	GameEngineTexture2DArray* _textureArray
)
{
	std::string uppercaseTexturesSetterName = GameEngineString::ToUpperReturn(_textureArraySetterName);

	if (false == IsTexture2DArray(_textureArraySetterName))
	{
		MsgBoxAssertString(std::string(_textureArraySetterName) + ": �׷� �̸��� �ؽ�ó�迭 ���Ͱ� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineTexture2DArraySetter>::iterator nameLowerBound
		= texture2DArraySetterMap_.lower_bound(uppercaseTexturesSetterName);
	std::multimap<std::string, GameEngineTexture2DArraySetter>::iterator nameUpperBound
		= texture2DArraySetterMap_.upper_bound(uppercaseTexturesSetterName);

	for (std::multimap<std::string, GameEngineTexture2DArraySetter>::iterator iter = nameLowerBound;
		iter != nameUpperBound; ++iter)
	{
		iter->second.texture2DArray_ = _textureArray;
		iter->second.Bind();
	}

	return _textureArray;
}

GameEngineStructuredBufferSetter* GameEngineShaderResourceHelper::GetStructuredBufferSetter(const std::string_view& _sBufferName)
{
	std::string uppercaseSBufferName = GameEngineString::ToUpperReturn(_sBufferName);

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

std::multimap<std::string, GameEngineStructuredBufferSetter>& GameEngineShaderResourceHelper::GetStructuredBufferSetterMap()
{
	return structuredBufferSetterMap_;
}

void GameEngineShaderResourceHelper::ShaderCheck(GameEngineShader* _shader)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& setterPair
		: _shader->constantBufferSetterMap_)
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator insertIter =
			constantBufferSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		insertIter->second.Bind();
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& setterPair
		: _shader->textureSetterMap_)
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator insertIter
			= textureSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		insertIter->second.Bind();
	}


	for (const std::pair<std::string, GameEngineSamplerSetter>& setterPair
		: _shader->samplerSetterMap_)
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator insertIter
			= samplerSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		insertIter->second.Bind();
	}

	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& setterPair
		: _shader->structuredBufferSetterMap_)
	{
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator insertIter
			= structuredBufferSetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		insertIter->second.Bind();
	}

	for (const std::pair<std::string, GameEngineTexture2DArraySetter>& setterPair
		: _shader->texture2DArraySetterMap_)
	{
		std::multimap<std::string, GameEngineTexture2DArraySetter>::iterator insertIter
			= texture2DArraySetterMap_.insert(std::make_pair(setterPair.first, setterPair.second));

		insertIter->second.Bind();
	}
}

void GameEngineShaderResourceHelper::AllResourcesSetting()
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& cBufferSetterPair
		: constantBufferSetterMap_)
	{
		cBufferSetterPair.second.Set();
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& textureSetterPair
		: textureSetterMap_)
	{
		textureSetterPair.second.Set();
	}

	for (const std::pair<std::string, GameEngineSamplerSetter>& samplerSetterPair
		: samplerSetterMap_)
	{
		samplerSetterPair.second.Set();
	}

	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetterPair
		: structuredBufferSetterMap_)
	{
		structuredBufferSetterPair.second.Set();
	}

	for (const std::pair<std::string, GameEngineTexture2DArraySetter>& texture2DArraySetterPair
		: texture2DArraySetterMap_)
	{
		texture2DArraySetterPair.second.Set();
	}
}

void GameEngineShaderResourceHelper::AllResourcesReset()
{
	for (const std::pair<std::string, GameEngineTextureSetter>& textureSetterPair : textureSetterMap_)
	{
		textureSetterPair.second.Reset();
	}

	for (const std::pair<std::string, GameEngineTexture2DArraySetter>& texture2DArraySetterPair
		: texture2DArraySetterMap_)
	{
		texture2DArraySetterPair.second.Reset();
	}
}