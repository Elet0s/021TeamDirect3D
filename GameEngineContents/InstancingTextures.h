#pragma once


class InstancingTextures: public GameEngineRes<InstancingTextures>
{
	//인스턴싱용 텍스처들 관리 클래스.
public:
	InstancingTextures();
	~InstancingTextures();

	InstancingTextures(const InstancingTextures& _other) = delete;
	InstancingTextures(InstancingTextures&& _other) noexcept = delete;
	InstancingTextures& operator=(const InstancingTextures& _other) = delete;
	InstancingTextures& operator=(const InstancingTextures&& _other) = delete;


public:	
	static std::shared_ptr<InstancingTextures> Load(const std::string_view& _path);
	static std::shared_ptr<InstancingTextures> Load(const std::string_view& _path, const std::string_view& _name);



private:
	void LoadFolderTextures(const std::string_view& _path);
	void Setting();

private:
	std::vector<DirectX::ScratchImage> scratchImages_;	//DirectXTex로 불러온 텍스처들
	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex로 불러온 텍스처의 각종 정보들.

	std::vector<ID3D11ShaderResourceView*> instancingShaderResourceViews_;

	std::vector<std::vector<float4>> cutData_;	//프레임 애니메이션 만들 때 필요한 아틀라스텍스처 분할 정보.
};

