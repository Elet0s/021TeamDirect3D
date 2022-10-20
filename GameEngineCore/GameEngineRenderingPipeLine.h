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
class GameEngineRenderingPipeLine: public GameEngineRes<GameEngineRenderingPipeLine>
{
	//�� Ŭ������ ���� ����: ���̴��� ���̴����ҽ�, �����Ͷ������� ����, ���̽��ٽ��� ������ 
	// ������ ������ �����ϴ� Ŭ����.
 
	//�������� ������ ������ �ʿ��� ���ҽ����� ����Ÿ���� ������ �������� ���� ������, ���õ� ����Ÿ�ٿ� ������ ������ �ű�� �۾����� 
	// �������� �� ������ ��������Ƿ� �̸��� ������ �����������̾�����,
	// ����� ���ؽ�����, �ε������ۿ� ��� ������ ������ ����Ÿ�ٿ� �ű�� ��ο��ε����� �Լ����� �޽��� �Ѱ��ְ� 
	// ��ǲ���̾ƿ��� ���������� ������ ������ ���̻� ������ ���������� �� ������ �������� �ʰ� �Ǿ����Ƿ�
	// �� �̻� ������ �����������̶�� �θ� �� ����, ��ǻ� ���׸����̶�� �θ��°��� ������ �����Ƽ� ���� ����.


public:
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

protected:
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept = delete;

private:
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete;


public:	
	
	static GameEngineRenderingPipeLine* Create(const std::string& _renderingPipeLineName);
	static GameEngineRenderingPipeLine* Create();
	static void AllShaderReset();

public:
	//���� �غ� �Լ���.

	void SetVertexShader(const std::string& _name);	
	void SetVertexShader(GameEngineVertexShader* _vertexShader);	

	void SetRasterizer(const std::string& _name);
	void SetPixelShader(const std::string& _name);
	void SetBlend_OutputMerger(const std::string& _name);
	void SetDepthStencil_OutputMerger(const std::string& _name);

	void RenderInstancing(int _renderingCount, class GameEngineInstancingBuffer* _instancingBuffer);
	void Copy(GameEngineRenderingPipeLine* _original);

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
	//���� �Լ���.
	//���������� ���� ������ �״��� �߿����� �ʴ�. DrawIndexed() �Լ� ȣ�� ���������� ��� ������ ���������� �ȴ�.

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

