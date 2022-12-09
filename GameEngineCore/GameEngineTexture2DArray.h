#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

class GameEngineTexture2DArray: public GameEngineRes<GameEngineTexture2DArray>
{
	//텍스처2D배열 관리 클래스.

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

	std::map<std::string, size_t> nameIndexPairs_;	//텍스처 각각의 이름과, 그 텍스처의 인덱스 모음.

	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex로 불러온 텍스처의 각종 정보들.

	ID3D11ShaderResourceView* shaderResourceView_;

	std::vector<std::vector<float4>> cutData_;	//프레임 애니메이션 만들 때 필요한 아틀라스텍스처 분할 정보.
};

