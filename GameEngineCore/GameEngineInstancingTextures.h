#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

class GameEngineInstancingTextures: public GameEngineRes<GameEngineInstancingTextures>
{
	//인스턴싱용 텍스처들 관리 클래스.

	friend class GameEngineInstancingTexturesSetter;
public:
	GameEngineInstancingTextures();
	~GameEngineInstancingTextures();

	GameEngineInstancingTextures(const GameEngineInstancingTextures& _other) = delete;
	GameEngineInstancingTextures(GameEngineInstancingTextures&& _other) noexcept = delete;
	GameEngineInstancingTextures& operator=(const GameEngineInstancingTextures& _other) = delete;
	GameEngineInstancingTextures& operator=(const GameEngineInstancingTextures&& _other) = delete;


public:	
	static std::shared_ptr<GameEngineInstancingTextures> Load(const std::string_view& _path);
	static std::shared_ptr<GameEngineInstancingTextures> Load(const std::string_view& _path, const std::string_view& _name);



private:
	void LoadFolderTextures(const std::string_view& _path);
	void VSSetting(int _bindPoint);
	void PSSetting(int _bindPoint);

private:
	std::vector<DirectX::ScratchImage> scratchImages_;	//DirectXTex로 불러온 텍스처들
	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex로 불러온 텍스처의 각종 정보들.

	std::vector<ID3D11ShaderResourceView*> instancingShaderResourceViews_;

	std::vector<std::vector<float4>> cutData_;	//프레임 애니메이션 만들 때 필요한 아틀라스텍스처 분할 정보.
};

