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

	const float4& GetFrameData(int _textureIndex, int _cutDataIndex)
	{
		if (true == this->cutData_[_textureIndex].empty())
		{
			MsgBoxAssertString(this->GetNameCopy() + ": ���� �ڸ��� ���� �ؽ����Դϴ�.");
			return float4();
		}

		if (cutData_[_textureIndex].size() <= _cutDataIndex)
		{
			MsgBoxAssertString(this->GetNameCopy() + ": �ε��� ������ �Ѿ���ϴ�.");
			return float4();
		}

		return cutData_[_textureIndex][_cutDataIndex];
	}


private:
	void LoadTextures(const std::string_view& _folderPath);
	void VSSetting(int _bindPoint);
	void PSSetting(int _bindPoint);

private:
	std::map<std::string, int> nameIndexPairs_;	//�ؽ�ó ������ �̸���, �� �ؽ�ó�� �ε��� ����.


	std::vector<DirectX::ScratchImage> loadedScratchImages_;	//DirectXTex�� �ҷ��� �ؽ�ó��.

	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	std::vector<DirectX::Image> images_;		//loadedScratchImages_���� ������ �̹�����.

	DirectX::ScratchImage scratchImage_;		//images_�� �ϳ��� ��Ƽ� ���� �ؽ�ó ����.

	ID3D11ShaderResourceView* shaderResourceView_;		//scratchImage_�� ���� ���̴����ҽ���.



	std::vector<std::vector<float4>> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� �ؽ�ó�� ���� ����.
};

