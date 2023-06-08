#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

class GameEngineTexture2DArray: public GameEngineRes<GameEngineTexture2DArray>
{
	//텍스처2D배열 관리 클래스.

	friend GameEngineRes<GameEngineTexture2DArray>;
	//GameEngineTexture2DArray 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineTexture2DArraySetter;
	//GameEngineTexture2DArraySetter 클래스에서 리소스세팅 함수들을 호출하기 위해 프렌드.

private:
	GameEngineTexture2DArray();
	~GameEngineTexture2DArray();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineTexture2DArray(const GameEngineTexture2DArray& _other) = delete;
	GameEngineTexture2DArray(GameEngineTexture2DArray&& _other) noexcept = delete;
	GameEngineTexture2DArray& operator=(const GameEngineTexture2DArray& _other) = delete;
	GameEngineTexture2DArray& operator=(const GameEngineTexture2DArray&& _other) = delete;


public:	
	static GameEngineTexture2DArray* Load(const std::string_view& _path);
	static GameEngineTexture2DArray* Load(const std::string_view& _path, const std::string_view& _name);

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
			MsgBoxAssertString(std::string(_textureFileName) + ": 그런 이름의 텍스처가 이 텍스처 배열에 없습니다.");
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
			MsgBoxAssertString(std::string(_textureName) + ": 그런 이름의 텍스처가 없습니다.");
			return float4::Zero;
		}

		return GetCutData(findIter->second, _cutDataIndex);
	}

	const float4& GetCutData(int _textureIndex, int _cutDataIndex)
	{
		if (true == this->cutData_[_textureIndex].empty())
		{
			MsgBoxAssertString(this->GetNameCopy()+ "-" + std::to_string(_textureIndex) + ": 아직 자르지 않은 텍스쳐입니다.");
			return float4::Zero;
		}

		if (cutData_[_textureIndex].size() <= _cutDataIndex)
		{
			MsgBoxAssertString(this->GetNameCopy() + "-" + std::to_string(_textureIndex) + ": 인덱스 범위를 넘어섰습니다.");
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
	void VSSetShaderResource(int _bindPoint);
	void CSSetShaderResource(int _bindPoint);
	void PSSetShaderResource(int _bindPoint);

	void VSResetShaderResource(int _bindPoint);
	void PSResetShaderResource(int _bindPoint);

private:
	std::map<std::string, int> nameIndexPairs_;	//텍스처 각각의 이름과, 그 텍스처의 인덱스 모음.


	std::vector<DirectX::ScratchImage> loadedScratchImages_;	//DirectXTex로 불러온 텍스처들.

	std::vector<DirectX::TexMetadata> metaDatas_;		//DirectXTex로 불러온 텍스처의 각종 정보들.

	std::vector<DirectX::Image> images_;		//loadedScratchImages_에서 추출한 이미지들.

	DirectX::ScratchImage scratchImage_;		//images_를 하나로 모아서 만든 텍스처 모음.

	ID3D11ShaderResourceView* shaderResourceView_;		//scratchImage_로 만든 셰이더리소스뷰.



	std::vector<std::vector<float4>> cutData_;	//프레임 애니메이션 만들 때 필요한 텍스처별 분할 정보.
};

