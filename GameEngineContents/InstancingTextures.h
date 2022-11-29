#pragma once


class InstancingTextures: public GameEngineRes<InstancingTextures>
{
	//�ν��Ͻ̿� �ؽ�ó�� ���� Ŭ����.
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
	std::vector<DirectX::ScratchImage> scratchImages_;	//DirectXTex�� �ҷ��� �ؽ�ó��
	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	std::vector<ID3D11ShaderResourceView*> instancingShaderResourceViews_;

	std::vector<std::vector<float4>> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� ��Ʋ���ؽ�ó ���� ����.
};

