#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

class GameEngineInstancingTextures: public GameEngineRes<GameEngineInstancingTextures>
{
	//�ν��Ͻ̿� �ؽ�ó�� ���� Ŭ����.

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
	std::vector<DirectX::ScratchImage> scratchImages_;	//DirectXTex�� �ҷ��� �ؽ�ó��
	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	std::vector<ID3D11ShaderResourceView*> instancingShaderResourceViews_;

	std::vector<std::vector<float4>> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� ��Ʋ���ؽ�ó ���� ����.
};

