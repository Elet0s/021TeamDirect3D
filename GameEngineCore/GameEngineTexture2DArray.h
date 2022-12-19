#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

class GameEngineTexture2DArray: public GameEngineRes<GameEngineTexture2DArray>
{
	//�ؽ�ó2D�迭 ���� Ŭ����.

	friend class GameEngineTexture2DArraySetter;
public:
	GameEngineTexture2DArray();
	~GameEngineTexture2DArray();

	GameEngineTexture2DArray(const GameEngineTexture2DArray& _other) = delete;
	GameEngineTexture2DArray(GameEngineTexture2DArray&& _other) noexcept = delete;
	GameEngineTexture2DArray& operator=(const GameEngineTexture2DArray& _other) = delete;
	GameEngineTexture2DArray& operator=(const GameEngineTexture2DArray&& _other) = delete;


public:	
	static std::shared_ptr<GameEngineTexture2DArray> Load(const std::string_view& _path);
	static std::shared_ptr<GameEngineTexture2DArray> Load(const std::string_view& _path, const std::string_view& _name);

	void Cut(const std::string_view& _textureName, int _x, int _y);
	void Cut(int _textureIndex, int _x, int _y);

public:
	int GetIndex(const std::string_view& _textureFileName)
	{
		if (nameIndexPairs_.end() != nameIndexPairs_.find(GameEngineString::ToUpperReturn(_textureFileName)))
		{
			return nameIndexPairs_.find(GameEngineString::ToUpperReturn(_textureFileName))->second;
		}
		else
		{
			MsgBoxAssertString(std::string(_textureFileName) + ": �׷� �̸��� �ؽ�ó�� �� �ؽ�ó �迭�� �����ϴ�.");
			return -1;
		}
	}

	size_t GetCutCount(int _textureIndex)
	{
		return cutData_[_textureIndex].size();
	}

	size_t GetCutCount(const std::string_view& _textureName)
	{
		return cutData_[this->GetIndex(_textureName)].size();
	}

	const float4& GetCutData(const std::string_view& _textureName, int _cutDataIndex)
	{
		std::map<std::string, int>::iterator findIter 
			= nameIndexPairs_.find(GameEngineString::ToUpperReturn(_textureName));

		if (nameIndexPairs_.end() == findIter)
		{
			MsgBoxAssertString(std::string(_textureName) + ": �׷� �̸��� �ؽ�ó�� �����ϴ�.");
			return float4::Zero;
		}

		return GetCutData(findIter->second, _cutDataIndex);
	}

	const float4& GetCutData(int _textureIndex, int _cutDataIndex)
	{
		if (true == this->cutData_[_textureIndex].empty())
		{
			MsgBoxAssertString(this->GetNameCopy()+ "-" + std::to_string(_textureIndex) + ": ���� �ڸ��� ���� �ؽ����Դϴ�.");
			return float4::Zero;
		}

		if (cutData_[_textureIndex].size() <= _cutDataIndex)
		{
			MsgBoxAssertString(this->GetNameCopy() + "-" + std::to_string(_textureIndex) + ": �ε��� ������ �Ѿ���ϴ�.");
			return float4::Zero;
		}

		return cutData_[_textureIndex][_cutDataIndex];
	}

	size_t GetCount()
	{
		return this->scratchImage_.GetImageCount();
	}


private:
	void LoadTextures(const std::string_view& _folderPath);
	void VSSetting(int _bindPoint);
	void PSSetting(int _bindPoint);

	void VSReset(int _bindPoint);
	void PSReset(int _bindPoint);

private:
	std::map<std::string, int> nameIndexPairs_;	//�ؽ�ó ������ �̸���, �� �ؽ�ó�� �ε��� ����.


	std::vector<DirectX::ScratchImage> loadedScratchImages_;	//DirectXTex�� �ҷ��� �ؽ�ó��.

	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	std::vector<DirectX::Image> images_;		//loadedScratchImages_���� ������ �̹�����.

	DirectX::ScratchImage scratchImage_;		//images_�� �ϳ��� ��Ƽ� ���� �ؽ�ó ����.

	ID3D11ShaderResourceView* shaderResourceView_;		//scratchImage_�� ���� ���̴����ҽ���.



	std::vector<std::vector<float4>> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� �ؽ�ó�� ���� ����.
};

