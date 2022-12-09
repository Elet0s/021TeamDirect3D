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



private:
	void LoadTextures(const std::string_view& _folderPath);
	void VSSetting(int _bindPoint);
	void PSSetting(int _bindPoint);

private:

	DirectX::ScratchImage scratchImage_;
	
	std::vector<DirectX::ScratchImage> tempScratchImages_;

	std::vector<DirectX::Image> images_;

	std::map<std::string, size_t> nameIndexPairs_;	//�ؽ�ó ������ �̸���, �� �ؽ�ó�� �ε��� ����.

	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	ID3D11ShaderResourceView* shaderResourceView_;

	std::vector<std::vector<float4>> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� ��Ʋ���ؽ�ó ���� ����.
};

