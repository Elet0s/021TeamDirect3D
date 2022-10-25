#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayout;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineMaterial: public GameEngineRes<GameEngineMaterial>
{
	//이 클래스의 존재 이유: 셰이더와 셰이더리소스, 래스터라이저와 블렌드, 깊이스텐실을 가지고 
	// 렌더링 과정에 관여하는 클래스.
 
	//이전에는 렌더링 과정에 필요한 리소스들중 렌더타겟을 제외한 나머지를 전부 가졌고, 세팅된 렌더타겟에 렌더링 정보를 옮기는 작업까지 
	// 렌더링의 전 과정을 담당했으므로 이름이 렌더링 파이프라인이었지만,
	// 현재는 버텍스버퍼, 인덱스버퍼와 모든 렌더링 정보를 렌더타겟에 옮기는 드로우인덱스드 함수까지 메쉬에 넘겨주고 
	// 인풋레이아웃과 토폴로지도 떨어져 나가서 더이상 렌더링 파이프라인 전 과정을 수행하지 않게 되었으므로
	// 더 이상 렌더링 파이프라인이라고 부를 수 없고, 사실상 마테리얼이라고 부르는것이 맞지만 귀찮아서 수정 안함.


public:
	GameEngineMaterial();
	~GameEngineMaterial();

protected:
	GameEngineMaterial(const GameEngineMaterial& _other) = delete;
	GameEngineMaterial(GameEngineMaterial&& _other) noexcept = delete;

private:
	GameEngineMaterial& operator=(const GameEngineMaterial& _other) = delete;
	GameEngineMaterial& operator=(const GameEngineMaterial&& _other) = delete;


public:	
	
	static GameEngineMaterial* Create(const std::string& _renderingPipeLineName);
	static GameEngineMaterial* Create();
	static void AllShaderReset();

public:
	//세팅 준비 함수들.

	void SetVertexShader(const std::string& _name);	
	void SetVertexShader(GameEngineVertexShader* _vertexShader);	

	void SetRasterizer(const std::string& _name);
	void SetPixelShader(const std::string& _name);
	void SetBlend_OutputMerger(const std::string& _name);
	void SetDepthStencil_OutputMerger(const std::string& _name);

	void RenderInstancing(int _renderingCount, class GameEngineInstancingBuffer* _instancingBuffer);
	void Copy(GameEngineMaterial* _original);

	void Setting();
public:

	inline GameEngineVertexShader* GetVertexShader()
	{
		return this->vertexShader_;
	}
	inline GameEnginePixelShader* GetPixelShader()
	{
		return this->pixelShader_;
	}

private:
	//세팅 함수들.
	//실질적으로 세팅 순서는 그다지 중요하지 않다. DrawIndexed() 함수 호출 이전까지만 모든 세팅이 끝나있으면 된다.

	void InputAssembler1_InstancingBufferSetting(class GameEngineInstancingBuffer* _instancingBuffer);	
	void VertexShaderSetting();			
	void RasterizerSetting();
	void PixelShaderSetting();
	void OutputMerger_DepthStencilSetting();
	void OutputMerger_BlendSetting();


	void InstancingDraw(int _renderingCount);

	void InstancingDataCollect();	


private:
	GameEngineVertexShader* vertexShader_;

	GameEngineRasterizer* rasterizer_;

	GameEnginePixelShader* pixelShader_;

	GameEngineDepthStencil* depthStencil_;

	GameEngineBlend* blend_;

};

