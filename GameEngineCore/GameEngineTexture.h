#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

struct PixelColor
{
	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned int color_;
	};

	PixelColor() : color_(0)
	{
	}
};

class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
	//ID3D11Texture2D* 형태로 할당된 텍스쳐와 거기서 파생된 각종 서브리소스뷰들을 저장, 관리하기 위한 클래스.
	//자기 텍스쳐와 관계된 리소스뷰들'만' 관리하는 클래스.
	//렌더링 파이프라인에 리소스뷰들을 연결하는건 해당 리소스뷰 클래스에서 한다.

	//리소스: 렌더링 과정에서 사용되는 모든 실수 배열 데이터를 말한다. 크게 텍스쳐와 버퍼 두가지로 나누어진다.
	//DirectX에서 리소스는 Direct3D 렌더링 파이프라인에서 사용할 수 있는 그래픽카드 내 메모리 영역이다.

	//리소스뷰: 일종의 형변환을 통해 텍스쳐에서 파생된 리소스들을 렌더링 파이프라인에 연결할 수 있는 형태로 만든 것.


	friend GameEngineRes<GameEngineTexture>;
	//GameEngineTexture클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineFolderTexture;
	//GameEngineFolderTexture는 왜 프렌드??

	friend class GameEngineDepthStencilTexture;
	//GameEngineDepthStencilTexture는 왜 프렌드??

private:
	GameEngineTexture();
	~GameEngineTexture();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineTexture(const GameEngineTexture& _other) = delete;
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete;


public:

	static GameEngineTexture* Create(const std::string_view& _name, ID3D11Texture2D* _texture);
	static GameEngineTexture* Create(ID3D11Texture2D* _texture);
	static GameEngineTexture* Create(const D3D11_TEXTURE2D_DESC& _desc);
	static GameEngineTexture* Create(const std::string_view& _name, const D3D11_TEXTURE2D_DESC& _desc);

	static GameEngineTexture* Load(const std::string_view& _path);
	static GameEngineTexture* Load(const std::string_view& _path, const std::string_view& _name);

	//private:
	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11ShaderResourceView* CreateShaderResourceView();
	ID3D11UnorderedAccessView* CreateUnorderedAccessView();
	ID3D11DepthStencilView* CreateDepthStencilView();

	void VSSetShaderResource(int _bindPoint);
	void CSSetShaderResource(int _bindPoint);
	void PSSetShaderResource(int _bindPoint);

	void VSResetShaderResource(int _bindPoint);
	void PSResetShaderResource(int _bindPoint);

	void CSSetUnorderedAccessView(int _bindPoint);

	//지정한 텍스처를 가로 x등분, 세로 y등분으로 균일 분할.
	static void Cut(const std::string_view& _textureName, int _x, int _y);

	//원하는 절단 지점의 픽셀좌표와 크기를 UV값으로 변환 후 저장.
	void Cut(UINT _startX, UINT _startY, UINT _sizeX, UINT _sizeY);

	float4 GetPixelToFloat4(int _x, int _y);	//float4는 실수 특성상 색상값의 오차 발생 가능성 있음.
	PixelColor GetPixelToPixelColor(int _x, int _y);	//unsigned int 형태로 받아서 색상값의 오차 없음.

public:
	float4 GetFrameData(int _index)
	{
		if (true == this->cutData_.empty())
		{
			MsgBoxAssertString(this->GetNameCopy() + ": 아직 자르지 않은 텍스쳐입니다.");
			return float4();
		}

		if (cutData_.size() <= _index)
		{
			MsgBoxAssertString(this->GetNameCopy() + ": 인덱스 범위를 넘어섰습니다.");
			return float4();
		}

		return cutData_[_index];
	}

	float4 GetScale()
	{
		//(metadata_.width), (metadata_.height)이거쓰면 0,0되서 텍스쳐 생성에 실패함 뜸
		return float4(static_cast<float>(desc_.Width),
			static_cast<float>(desc_.Height));
	}

	size_t GetCutCount()
	{
		return cutData_.size();
	}

	float4 GetCutScale(int _index)
	{
		return float4(cutData_[_index].sizeX * static_cast<float>(desc_.Width),
			cutData_[_index].sizeY * static_cast<float>(desc_.Height));
	}

	float4 GetCutPos(int _index)
	{
		return float4(cutData_[_index].posX * static_cast<float>(desc_.Width),
			cutData_[_index].posY * static_cast<float>(desc_.Height));
	}

private:
	//지정한 경로에서 텍스처를 불러오는 함수. 셰이더리소스뷰 생성 과정까지 포함되어 있음.
	void LoadTexture(const std::string_view& _path);

	//ID3D11Texture2D* 형 텍스처 생성 함수. 
	void CreateTexture(const D3D11_TEXTURE2D_DESC& _desc);

	void Cut(int _x, int _y);

private:
	ID3D11Texture2D* texture2D_;
	//픽셀별 색상 정보가 든 2차원 배열이 저장된 그래픽카드 내 메모리 영역을 관리하는 인터페이스 ID3D11Texture2D* 타입 멤버변수.

	ID3D11RenderTargetView* renderTargetView_;
	//
	//렌더타겟뷰: 렌더링 파이프라인을 전부 거친 결과물로서의 색상값 2차원 배열을 받는데 사용되는 그래픽 카드 내 메모리 영역.

	ID3D11ShaderResourceView* shaderResourceView_;	//셰이더리소스뷰.
	//
	//셰이더리소스뷰: 

	ID3D11UnorderedAccessView* unorderedAccessView_;//순서없는 연결뷰.
	//
	//순서없는 연결뷰:

	ID3D11DepthStencilView* depthStencilView_;	//깊이스텐실뷰.
	//
	//깊이스텐실뷰:

	D3D11_TEXTURE2D_DESC desc_;	//텍스처 생성용 명세서.


	DirectX::ScratchImage scratchImage_;//DirectXTex로 불러온 텍스처
	DirectX::TexMetadata metaData_;		//DirectXTex로 불러온 텍스처의 각종 정보들.

	std::vector<float4> cutData_;	//프레임 애니메이션 만들 때 필요한 아틀라스텍스처 분할 정보.

};

