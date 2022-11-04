#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShader.h"

class GameEngineShaderResourceHelper
{
	//�� Ŭ������ ���� ������ ����?? ���ҽ� �����Լ��� ����?? �ݵ�� �����ص� ��.
	//ID3D11Resource�� �ڽ� ���ҽ����� �ѵΰ��� �ƴѵ� �� ���̴�  ���õ� ���ҽ��鸸 �̷������� Ư�� �����ϴ� ������??
	// 
	//���� ���̴��� �ٸ� ���ҽ�, �ٸ� ������ ����ϴ� ��츦 ���.


	//�Ϲ����� ��� �������� ������ �ӵ� ������ ����, �Ѱ��� ���� ������ ����� ������ �ϳ��� �޶�����, 
	// �� �޶��� �����͸� �ٲ� �� ���� ����� ����, ������ ���ο� ���׸����� ����� �� �� �Ѳ����� �������ϰ� �Ѵ�. 
	// �׷��� �ؼ� Map(), Unmap() �Լ� ȣ�� �󵵸� �ִ��� ���δ�. �̷��� ���Ѵ�.
	//->winapi���� HPEN, HBRUSH ���� ������Ʈ �ڵ����, SelectObject()���� �Լ��� ���� ������ �� ������ ��ü������ ������ 
	// �� ������Ʈ �ڵ��� ���� �Լ��� ����ϴ� ��� ����, �׸����� ���� ��, ���� ����� ���ϵǹ����°Ͱ� ���� �����ΰ�??
	//->�������� �ӵ����ϸ� �����ؼ��� �̹� ������ HPEN���� ������Ʈ���� ���̳� ���⸦ �߰��� �ٲ� �� �ְ� ���شٴ� �ǰ�??

	friend class GameEngineRenderUnit;
	//AllResourcesSetting(), AllResourcesReset() �Լ��� ȣ���� �� �ְ� �ϱ� ���� ������. 


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
	//�Ű������� ���� ���׸����� �ʿ�� �ϴ� ���̴����ҽ����� ���̴����ҽ����ۿ� ����ϴ� �Լ�.
	void ResourceCheck(GameEngineMaterial* _material);

	//�� ���̴� ���ҽ� ���Ͱ� �־��� �̸��� ������۸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsConstantBuffer(const std::string_view& _name);

	//�� ���̴� ���ҽ� ���Ͱ� �־��� �̸��� �ؽ�ó�� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsTexture(const std::string_view& _name);

	//�� ���̴� ���ҽ� ���Ͱ� �־��� �̸��� ���÷��� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsSampler(const std::string_view& _name);

	//�� ���̴� ���ҽ� ���Ͱ� �־��� �̸��� ����ȭ���۸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsStructuredBuffer(const std::string_view& _name);


	void SetConstantBuffer_Link(const std::string_view& _name, const void* _data, unsigned int _dataSize);	//������ ����??
	void SetConstantBuffer_New(const std::string_view& _name, const void* _data, unsigned int _dataSize);	//���� ����??
	//�ܺ� �����͸� ����޾ƾ� �ϴ� ���� SetConstantBufferLink()�� ����� �� ���� �������� ��Ȳ���� ����� ��.

	GameEngineTexture* SetTexture(const std::string& _textureSetterName, const std::string& _textureName);
	GameEngineTexture* SetTexture(const std::string& _textureSetterName, GameEngineTexture* _texture);
	GameEngineTexture* SetTexture(const std::string& _textureSetterName, const std::string& _folderTextureName, int _index);
	
	GameEngineSampler* SetSampler(const std::string& _samplerSetterName, GameEngineSampler* _sampler);
	GameEngineSampler* SetSampler(const std::string& _samplerSetterName, const std::string& _samplerName);

	// �ν��Ͻ��� �Ϸ��� �ϴµ� �� ���̴����� ������۸� ���������.
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
	//		MsgBoxAssert("ã�� ��������� �̸��� ũ�Ⱑ ���� �ʽ��ϴ�.");
	//		return nullptr;
	//	}

	//	Resource* data = reinterpret_cast<Resource*>(&findIter->second.originalData_[0]);
	//	return data;
	//}


protected:
	//���ҽ� �غ������, ¦���� ��ġ�� ������ ������������ ���̴��� �ʿ�� �ϴ� ���̴����ҽ����� ���̴����ҽ����ۿ� ����ϰ�, 
	// �� ���������� ���ŵ� ���̴����ҽ����� ������ ���������ο� �� ���̴����� �䱸�ߴ���� ������ ���������ο� �����ϴ� �Լ�. 
	void ShaderCheck(GameEngineShader* _shader);


private:
	//������۸� ������ �ִٰ� ������ۼ��Ͱ� settingFunction�� ���� ������۸� �䱸�ϸ� ������ ���������ο� �����ϴ� �Լ�. 
	void BindConstantBuffer(GameEngineConstantBufferSetter& _cBufferSetter, GameEngineConstantBuffer* _cBuffer);

	//�ؽ�ó�� ������ �ִٰ� �ؽ�ó���Ͱ� settingFunction�� ���� �ؽ�ó�� �䱸�ϸ� ������ ���������ο� �����ϴ� �Լ�.
	void BindTexture(GameEngineTextureSetter& _textureSetter, GameEngineTexture* _texture);

	//���÷��� ������ �ִٰ� ���÷����Ͱ� settingFunction�� ���� ���÷��� �䱸�ϸ� ������ ���������ο� �����ϴ� �Լ�.
	void BindSampler(GameEngineSamplerSetter& _samplerSetter, GameEngineSampler* _sampler);

	//
	void BindStructuredBuffer(GameEngineStructuredBufferSetter& _sBufferSetter, GameEngineStructuredBuffer* _sBuffer);

	//�ش� ���̴����ҽ����۰� ���� ��� �������, �ؽ�ó, ���÷��� �� �������� �����ϰ� �������̴��� �ȼ����̴��� �����ϴ� �Լ�.
	void AllResourcesSetting();

	//�ش� ���̴����ҽ����۰� ����̽� ���ؽ�Ʈ�� �����ߴ� ��� �������, �ؽ�ó, ���÷��� �������ͷ� ��ü�ϴ� �Լ�.
	void AllResourcesReset();

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> constantBufferSetterMap_;
	std::multimap<std::string, GameEngineTextureSetter> textureSetterMap_;
	std::multimap<std::string, GameEngineSamplerSetter> samplerSetterMap_;
	std::multimap<std::string, GameEngineStructuredBufferSetter> structuredBufferSetterMap_;	//����ȭ���۵� �ᱹ �ؽ�ó.

	//���̴� ���ҽ� ���͵��� ����, ������ ��Ƽ������ �� ����:
	//�׳� std::map���δ� �ߺ��Ǵ� ���ҽ� �̸��� Ű������ �� �� ������ std::multimap���δ� ������ �� �ִٴ� Ư���� �̿���,
	// �̸��� �Ȱ��� �ٸ� ������ۼ��ͳ� �ؽ�ó���� ���� ���ҽ����͵��� ���� ���̴����� ���ÿ� ����ϰ� �Ǵ� ��쿡�� ��Ȱ�ϰ� �����ϱ� ���ؼ�.
	//->���� �̸� �ٸ� ���ҽ��� �������̴��� �ȼ����̴��� ���ÿ� ����� �� �ְ� �Ѵ�.

	//���̴� ���ҽ� ���͵��� �������� �ƴ� �������� �����ϴ� ����:
	//���̴����� ������ ���̴� ���ҽ� ���͵��� ���� �����ؾ� �ϴµ�,
	// ������ ���·� �����ϸ� ������ ���̴� ���ҽ� ���Ͱ� �ƴ϶�, 
	// ���� ���̴� ���ҽ� ���͸� ����Ű�� ������ '������ ����'�� ����� �����ϱ� �����̴�.
	// �װ� ���� ���� �������� �����Ѵ�.

};

