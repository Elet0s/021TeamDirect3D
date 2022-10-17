#pragma once
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineShader.h"

// ���� :
class GameEngineShader;
class GameEngineShaderResourcesHelper
{
	friend GameEngineShader;

// ���ҽ� �����Լ��� ����

	// �� ������۰� �̳༮ �ȿ� �־�?


public:
	// constrcuter destructer
	GameEngineShaderResourcesHelper();
	~GameEngineShaderResourcesHelper();

	// delete Function
	GameEngineShaderResourcesHelper(const GameEngineShaderResourcesHelper& _Other) = delete;
	GameEngineShaderResourcesHelper(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;
	GameEngineShaderResourcesHelper& operator=(const GameEngineShaderResourcesHelper& _Other) = delete;
	GameEngineShaderResourcesHelper& operator=(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;

	void AllResourcesSetting();

	void AllResourcesReset();

	void ResourcesCheck(GameEngineRenderingPipeLine* _Line);

	template<typename Res>
	void SetConstantBufferLink(const std::string& _Name, const Res& Data) 
	{
		SetConstantBufferLink(_Name , &Data, sizeof(Res));
	}

	void SetConstantBufferLink(const std::string& _Name, const void* Data, UINT _Size);

	template<typename Res>
	void SetConstantBufferNew(const std::string& _Name, const Res& Data)
	{
		SetConstantBufferNew(_Name, &Data, sizeof(Res));
	}

	template<typename Res>
	Res* GetConstantBufferNewData(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);


		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSettingMap.find(UpperName);

		if (FindIter == ConstantBufferSettingMap.end())
		{
			return nullptr;
		}
		int TypeSize = sizeof(Res);

		if (TypeSize != FindIter->second.Res->GetBufferDesc().ByteWidth)
		{
			MsgBoxAssert("��������� �����͸� �ٸ� ũ���� �����ͷ� ���������� �߽��ϴ�.");
		}

		// FindIter->second.OriginalData[0] SetData

		// Res* Data = reinterpret_cast<Res*>(&FindIter->second.OriginalData[0]);
		Res* Data = reinterpret_cast<Res*>(&FindIter->second.OriginalData[0]);

		return Data;
	}


	void SetConstantBufferNew(const std::string& _Name, const void* Data, UINT _Size);


	GameEngineTexture* SetTexture(const std::string& _Name, const std::string& _TextureName);

	GameEngineTexture* SetTexture(const std::string& _Name, const std::string& _FolderTextureName, int _Index);

	GameEngineTexture* SetTexture(const std::string& _Name, GameEngineTexture* _TextureName);


	GameEngineSampler* SetSampler(const std::string& _Name, const std::string& _TextureName);

	GameEngineSampler* SetSampler(const std::string& _Name, GameEngineSampler* _SamplerName);

	// �ν��Ͻ��� �Ϸ��� �ϴµ� �� ���̴����� ������۸� ���������.
	void AllConstantBufferNew();


	// Get�Լ�
	bool IsTexture(const std::string& _Name);

	bool IsSampler(const std::string& _Name);

	bool IsConstantBuffer(const std::string& _Name);

	bool IsStructuredBuffer(const std::string& _Name);

	GameEngineStructuredBufferSetter* GetStructuredBuffer(const std::string& _Name);


protected:
	void ShaderCheck(GameEngineShader* _Shader);

private:
	// �÷��� 
	// �ȼ� ���̴������� ���� Color(����Ʈ ���)�ε� ���带 �������ְ� �Ͱ�
	// ���ؽ� ���̴������� ���� Color(����Ʈ ���)�ε� ��縦 �������ְ� �Ͱ�
	// �װ� ���� �������� �ʰڽ��ϴ�.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSettingMap;
	std::multimap<std::string, GameEngineTextureSetter> TextureSettingMap;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSettingMap;
	std::multimap<std::string, GameEngineStructuredBufferSetter> StructuredBufferSettingMap;

	void BindConstantBuffer(GameEngineConstantBufferSetter& _Setter, GameEngineConstantBuffer* _Res);
	void BindSampler(GameEngineSamplerSetter& _Setter, GameEngineSampler* _Res);
	void BindTexture(GameEngineTextureSetter& _Setter, GameEngineTexture* _Res);
	void BindStructuredBuffer(GameEngineStructuredBufferSetter& _Setter, GameEngineStructuredBuffer* _Res);
};

