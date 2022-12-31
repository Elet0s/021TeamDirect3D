#pragma once
#include "GameEngineRes.h"

enum class ShaderType
{
	VertexShader,
	PixelShader,
	GeometryShader,
	Max
};

class GameEngineShader;
class ShaderResSetter : public GameEngineNameObject
{
	//������ ���̴��鳢�� ������۳� �ٸ� ���̴� ���ҽ����� �����ϴ���, ���ε�����Ʈ ����
	// ���̴� ���ҽ� �����ΰ� �� �� ���� ������ �ٸ� ��쿡 �����ϱ� ���� ����, ���̴����ҽ� �ܺ����� ��������� Ŭ����.
	//���̴����ҽ� �� ��ü�� ������Ʈ�� ����� �ƴϹǷ� ���ӿ�����Ʈ�� ��ӹ޾Ƽ� ������ �� �ʿ��� �̸� ���� ��ɸ� �߰��Ѵ�.

public:
	GameEngineShader* parentShader_;	//�� ���ҽ����Ͱ� ���� ���ҽ��� ����� �θ� ���̴�.
	int bindPoint_;		//�ش� ���̴����ҽ��� ���ε�����Ʈ(�������� ��� ��ȣ).
	ShaderType parentShaderType_;	//�� ���ҽ����͸� �����ϰ� ������ �� �θ� ���̴��� ����.
	std::function<void()> settingFunction_;	//���̴��� ���� ���ҽ����� �����ϴ� �Լ�.
	std::function<void()> resetFunction_;	//���̴��� ���� ���ҽ����� �����ϴ� �Լ�.

protected:
	ShaderResSetter()
		: parentShader_(nullptr),
		bindPoint_(-1),
		parentShaderType_(ShaderType::Max),
		settingFunction_(nullptr),
		resetFunction_(nullptr)
	{
	}

	~ShaderResSetter() {}
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
	//���̴����� �ʿ�� �ϴ� ������ ������۰� ������ �ϴ� ���� ���� Ŭ����.


	friend class GameEngineShader;

public:
	//�� ������� ���Ͱ� �����, �θ� ���̴��� �ʿ�� �ϴ� �������.
	std::shared_ptr<GameEngineConstantBuffer> constantBuffer_;
	//���� ������� ���Ͱ� �ϳ��� ������۸� ������ �� �ִ�.

	//GPU�� ������, ������ ������۵��� ���� �������� �ּҰ�. 
	const void* settingDataToGPU_;

	size_t size_;	//������� ��ü ũ��. 
	//������۴� ũ��� �̸� �ΰ����� �з��Ǿ� �����ϰ� �����Ƿ� 
	//������ۼ��͵� �ڱⰡ ����ϴ� ������۸� ��Ȯ�� ã�� ���� �� �� �����Ѵ�.

	std::vector<char> originalData_;
	// �ƿ� �ڱ� �޸𸮷� �����??

	void Setting() const;
	void Bind();

	//private:	<-������ �� ���⿣ ���� �ʹ� ���������� ������ ������ �ܺο��� ����ؼ� �ȵȴ�.
	// ���⼭ �ܺδ� �� ���ҽ��� ���� ����� GameEngineShader�� �ڽ� Ŭ������� ���̴��� ����� GameEngineRenderingPipeLine,
	// ������ ������������ ����� GameEngineDefaultRendererŬ������ �� �ڽ�Ŭ�������� �����ϰ�� �� �ܺ��̴�.

	GameEngineConstantBufferSetter()
		: constantBuffer_(),
		settingDataToGPU_(nullptr),
		size_(-1)
	{
	}

};

class GameEngineTexture;
class GameEngineTextureSetter : public ShaderResSetter
{
	//�� Ŭ������ ������??

	friend class GameEngineShader;
	friend class GameEngineShaderResourceHelper;

	//�� �ؽ�ó���Ͱ� ������ �ؽ�ó. 
	std::shared_ptr<GameEngineTexture> texture_;
	//�߰����� �ؽ�ó�� ���������� ������ ��� �������� "NSet.png"�� �״�� �����ǰ� �Ѵ�. 

public:
	void Setting() const;
	void Reset() const;
	void Bind();

	//private:	<-������ �� ���⿣ ���� �ʹ� ���������� ������ ������ �ܺο��� ����ؼ� �ȵȴ�.
	// ���⼭ �ܺδ� �� ���ҽ��� ���� ����� GameEngineShader�� �ڽ� Ŭ������� ���̴��� ����� GameEngineRenderingPipeLine,
	// ������ ������������ ����� GameEngineDefaultRendererŬ������ �� �ڽ�Ŭ�������� �����ϰ�� �� �ܺ��̴�.

	GameEngineTextureSetter() : texture_(nullptr)
	{
	}
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{
	friend class GameEngineShader;
	friend class GameEngineShaderResourceHelper;


	//�� ���÷����Ͱ� ������ ���÷�.
	std::shared_ptr<GameEngineSampler> sampler_;

public:
	void Setting() const;
	void Bind();

	//private:	<-������ �� ���⿣ ���� �ʹ� ���������� ������ ������ �ܺο��� ����ؼ� �ȵȴ�.
	// ���⼭ �ܺδ� �� ���ҽ��� ���� ����� GameEngineShader�� �ڽ� Ŭ������� ���̴��� ����� GameEngineRenderingPipeLine,
	// ������ ������������ ����� GameEngineDefaultRendererŬ������ �� �ڽ�Ŭ�������� �����ϰ�� �� �ܺ��̴�.

	GameEngineSamplerSetter() : sampler_(nullptr)
	{
	}
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter : public ShaderResSetter
{
	friend class GameEngineShader;
	friend class GameEngineShaderResourceHelper;
	friend class GameEngineFBXAnimationRenderer;
	friend class GameEngineInstancing;
	friend class GameEngineInstancingRenderer;

public:
	void Setting() const;
	void Bind();
	void Resize(size_t _count);
	size_t GetDataSize();


private:
	// ������ۿ� ������ �����ϰ� �����ϰ� �����ϸ� �˴ϴ�.

	std::shared_ptr<GameEngineStructuredBuffer> structuredBuffer_;
	const void* settingDataToGPU_;
	size_t size_;
	size_t count_;
	std::vector<char> originalData_;

public:
	template <typename DataType>
	void Push(DataType& _data, UINT _count)
	{
		size_t leftSize = sizeof(DataType);
		size_t rightSize = this->GetDataSize();

		if (leftSize != rightSize)
		{
			MsgBoxAssert("����ȭ���ۿ� �������� �������� ũ�Ⱑ �ٸ��ϴ�.");
		}

		PushData(&_data, _count);
	}

	GameEngineStructuredBufferSetter()
		: structuredBuffer_(),
		settingDataToGPU_(nullptr),
		size_(-1),
		count_(-1)
	{
	}

private:
	void PushData(const void* _data, UINT _count);
};

class GameEngineTexture2DArray;
class GameEngineTexture2DArraySetter: public ShaderResSetter
{
	friend class GameEngineShader;
	friend class GameEngineShaderResourceHelper;


	void Setting() const;
	void Reset() const;
	void Bind();


	std::shared_ptr<GameEngineTexture2DArray> texture2DArray_;

public:
	GameEngineTexture2DArraySetter() : texture2DArray_(nullptr)
	{
	}
};


class GameEngineShader
{
	//�� �����ӿ�ũ �� ��� ���̴��� ���̴����� ����ϴ� ���ҽ����� �����ϴ� Ŭ����.

	friend class GameEngineShaderResourceHelper;
	//

public:
	GameEngineShader();
	virtual ~GameEngineShader();

protected:
	GameEngineShader(const GameEngineShader& _other) = delete;
	GameEngineShader(GameEngineShader&& _other) noexcept = delete;

private:
	GameEngineShader& operator=(const GameEngineShader& _other) = delete;
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete;


public:
	//������ ����� HLSL�ڵ带 �ؼ��ϰ� �� ������ ���̴��� ���̴����ҽ��� ����� �Լ�.
	static void AutoCompile(const std::string_view& _path);

	GameEngineConstantBufferSetter& GetConstantBufferSetter(const std::string& _name);

	//�� ���̴��� �־��� �̸��� ������ۼ��͸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsConstantBuffer(const std::string_view& _name);

	//�� ���̴��� �־��� �̸��� �ؽ�ó���͸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsTexture(const std::string_view& _name);

	//�� ���̴��� �־��� �̸��� ���÷����͸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsSampler(const std::string_view& _name);

	//�� ���̴��� �־��� �̸��� ����ȭ���ۼ��͸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsStructuredBuffer(const std::string_view& _name);
	
	//�� ���̴��� �־��� �̸��� �ؽ�ó2D�迭���͸� ������ �ִ°��� �ܺο��� Ȯ���ϴ� �Լ�.
	bool IsTexture2DArray(const std::string_view& _name);

protected:
	//�о���� HLSL�ڵ带 �������ϴµ� �ʿ��� HLSL ������ �����ϴ� �Լ�.
	void CreateVersion(const std::string_view& _shaderType, UINT _versionHigh, UINT _versionLow);

	//ShaderCompile()�Լ��� ��ü�ϴ�, ���̴� ���� HLSL�ڵ� ������ �Լ�.
	void CompileHLSLCode(const std::string_view& _path);

	//���� �Է��� HLSL�ڵ��� ������ ���̴��� ���ҽ��� �ִ��� Ȯ���ϰ�, ���ҽ����͸� ���� ���ҽ� ������ �����Ѵ�.
	//������۴� ã�ƺ��� ������ �������� ���ٸ� �����Ѵ�.
	//�ؽ�ó�� ���÷��� �ϴ� ���� �⺻���� ���ҽ��� �����Ѵ�. 
	void ShaderResCheck(const std::string_view& _thisShaderName);
	//�� ������ ���� �� �����ӿ�ũ�� ���̴��� �����ΰ� � ���̴����ҽ��� �ʿ�� �ϴ��� ���� �� �� �ִ�.

protected:
	std::string entryPoint_;	//HLSL �ڵ��� �������Լ� �̸�.
	std::string shaderVersion_;	//HLSL �ڵ��� ��� ������ �����Ϸ��� ����.
	ID3DBlob* binaryCode_;		//HLSL �ڵ带 �������� �����(����Ʈ�ڵ�).
	ShaderType shaderType_;		//�� ���̴��� ����.

	std::map<std::string, GameEngineConstantBufferSetter> constantBufferSetterMap_;
	std::map<std::string, GameEngineTextureSetter> textureSetterMap_;
	std::map<std::string, GameEngineSamplerSetter> samplerSetterMap_;
	std::map<std::string, GameEngineStructuredBufferSetter> structuredBufferSetterMap_;
	std::map<std::string, GameEngineTexture2DArraySetter> texture2DArraySetterMap_;

	//���̴����ҽ����͵��� �������� ������ ������??
	//->���̴� ���ҽ� ������ �پ����� �ʾƼ� �������� �����ص� ���� �����̳ʵ��� ���� �ʿ䰡 ����, 
	// ������ ���ҽ����� �и��ؼ� ���� �����ϰ� ������ �� �ִٴ� ������ �̿��� �� �ֱ� ����.

	//std::map<std::string, ShaderResSetter*> resSetterMap_;
	//�̷��� �����Ҵ��ؼ� ���̴����ҽ����� �����Ѵٸ�, �������� �̿��ؼ� ShaderResSetter�� ��ӹ��� ��� ���̴����ҽ����� 
	// �ϳ��� �����̳ʷ� �� ���� �޸𸮷� ������ �� �ִ�.
	// ������ �������� ����ȭ�� �޸𸮰����� ������ �ʿ� �����Ƿ� ���Ͱ��� �����Ѵ�.

protected:
	inline void SetEntrtyPoint(const std::string_view& _entryPoint)
	{
		entryPoint_ = _entryPoint;
	}


};

