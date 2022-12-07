#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineDevice.h"
#include "GameEngineTexture.h"
#include "GameEngineTexture2DArray.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexes.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineInstancingBuffer.h"

#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineInputLayout.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineBlend.h"
#include "GameEngineFont.h"

#include "GameEngineFBXMesh.h"
#include "GameEngineFBXAnimation.h"

void EngineInputLayout()
{
	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"POSITION",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"COLOR",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"TEXCOORD",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"NORMAL",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"BINORMAL",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"TANGENT",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"BLENDWEIGHT",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	);

	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"BLENDINDICES",
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT
	);



	GameEngineVertex::inputLayoutInfo_.ResetOffset();

	//�ν��Ͻ� �����Ϳ�.
	GameEngineVertex::inputLayoutInfo_.AddInputLayout(
		"ROWINDEX",
		DXGI_FORMAT::DXGI_FORMAT_R32_UINT,
		-1,
		1,
		1,
		D3D11_INPUT_PER_INSTANCE_DATA
	);






}

void EngineSubSetting()
{
	//typedef struct D3D11_RASTERIZER_DESC
	//{
	//	D3D11_FILL_MODE FillMode;		�������� �մ� �� ���̸� ä���� ���� �����ϴ� �ɼ�.
	//	D3D11_CULL_MODE CullMode;		�յ޸� �� ��� ���� �ø����� �����ϴ� �ɼ�.
	//	BOOL FrontCounterClockwise;		�ݽð�������� ��ġ�� �������� �������� ��������, �� �ݴ�� ���� �����ϴ� �ɼ�.
	//	INT DepthBias;					���� ���̾ƽ�??
	//	FLOAT DepthBiasClamp;			���� ���̾ƽ� Ŭ����??
	//	FLOAT SlopeScaledDepthBias;		??
	//	BOOL DepthClipEnable;			���� Ŭ���� ���� ����.
	//	BOOL ScissorEnable;				�������ʱ� �ø�(������ �簢�� ���� ��� ��Ҹ� �׸��� ����) ���� ����.
	//	BOOL MultisampleEnable;			��Ƽ���ø� ���� ����.
	//	BOOL AntialiasedLineEnable;		���� ��Ƽ�ٸ����(�ȼ����� �ʺ��� ���� ��Ƽ�ٸ����) ���� ����.
	//} 	D3D11_RASTERIZER_DESC;


	D3D11_RASTERIZER_DESC rasterizerDesc = {};

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;	//�ٲٸ� �¿������ ������ �ȵ�.

	GameEngineRasterizer::Create("EngineRasterizer", rasterizerDesc);





	//typedef struct D3D11_BLEND_DESC
	//{
	//	BOOL AlphaToCoverageEnable;							���ĺ������� ��Ƽ���ø��� �ϴ� ����� ���� �� Ŀ�������� ������ �� ����.
	//	BOOL IndependentBlendEnable;						����Ÿ�ٵ��� ������ �������� ���� �������� ������ �� �� ����. 
	//														 true: 8���� ���� �������� ����.
	//														 false: 0�� �������� ������ �����.
	// 
	//	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];		����Ÿ�ٿ� ����� ���ĺ��� ������ ������ ������ D3D11_RENDER_TARGET_BLEND_DESC����ü �迭.
	//														 �ִ� 8�� ����Ÿ�ٿ� ���� �ٸ� ���ĺ��� ����� ������ �� �ִ�.

	//	typedef struct D3D11_RENDER_TARGET_BLEND_DESC
	//	{
	//		BOOL BlendEnable;						���ĺ����� �� �� ����.
	//		D3D11_BLEND SrcBlend;					���ĺ��� ������ srcFactor�� 4�� ���Ҹ� ��� ä���� �����ϴ� �ɼ�.
	//		D3D11_BLEND DestBlend;					���ĺ��� ������ destFactor�� 4�� ���Ҹ� ��� ä���� �����ϴ� �ɼ�.
	//		D3D11_BLEND_OP BlendOp;					���ĺ��� ������ �ɼ� �κп� � ������ �������� �����ϴ� �ɼ�.
	//		D3D11_BLEND SrcBlendAlpha;				srcColor�� ���İ� ����.
	//		D3D11_BLEND DestBlendAlpha;				destColor�� ���İ� ����.
	//		D3D11_BLEND_OP BlendOpAlpha;			���ĺ��� ������ �ɼ� �׸� ���ϱ� ����. ���İ� ��꿡�� ����ȴ�.
	//		UINT8 RenderTargetWriteMask;			������ ������ ����. RGBA�� ����� �����ؼ� ���ĺ����� ������ ���� �ִ�.
	//	} 	D3D11_RENDER_TARGET_BLEND_DESC;
	//
	//} 	D3D11_BLEND_DESC;

	D3D11_BLEND_DESC alphaBlendDesc = { 0 };

	alphaBlendDesc.AlphaToCoverageEnable = false;		//���� �� Ŀ������ ������.
	alphaBlendDesc.IndependentBlendEnable = false;		//0�� ����Ÿ���� ���ĺ��� �������� ��� ����Ÿ�ٿ� ����.
	alphaBlendDesc.RenderTarget[0].BlendEnable = true;	//���ĺ��� ��.
	alphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//D3D11_COLOR_WRITE_ENABLE_ALL: RGBA ��� ���� ���� ����.

	//���ĺ��� ����.
	//output: ���� �����.
	//dest: ������� ���� ����.
	//src: ������� ����� ������ ������ ����.
	//�ɼ�: BlendOp���� �����ϴ� ���� ���� ���.
	//outputColor = (srcColor * srcFactor) �ɼ� (destColor * destFactor)

	alphaBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//�ɼ� ������ ���ϱ�� �Ѵ�.

	alphaBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//srcFactor�� srcColor�� ���İ��� �ϰ� ����.

	alphaBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//destFactor�� (1 - srcColor�� ���İ�)�� �ϰ� ����.

	//�������� ���� ó��.
	alphaBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	alphaBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	//�� �� �ٸ� �ּ�ó���� �� ��.->�ϸ� ���� ������Ʈ ���� ����.

	GameEngineBlend::Create("AlphaBlend", alphaBlendDesc);







	D3D11_BLEND_DESC transparentBlendDesc = { 0 };

	transparentBlendDesc.AlphaToCoverageEnable = false;		//���� �� Ŀ������ ������.
	transparentBlendDesc.IndependentBlendEnable = false;		//0�� ����Ÿ���� ���ĺ��� �������� ��� ����Ÿ�ٿ� ����.
	transparentBlendDesc.RenderTarget[0].BlendEnable = true;	//���ĺ��� ��.
	transparentBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//D3D11_COLOR_WRITE_ENABLE_ALL: RGBA ��� ���� ���� ����.

	transparentBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//??

	transparentBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//??

	transparentBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//??

	//�������� ���� ó��.
	transparentBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	transparentBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	GameEngineBlend::Create("TransparentBlend", transparentBlendDesc);






	//typedef struct D3D11_DEPTH_STENCIL_DESC
	//{
	//	BOOL DepthEnable;						�����׽�Ʈ Ȱ��ȭ ����.
	//	D3D11_DEPTH_WRITE_MASK DepthWriteMask;	�����׽�Ʈ ����� ���� ���� �����Ϳ� ���� �� ����??
	//	D3D11_COMPARISON_FUNC DepthFunc;		�����׽�Ʈ ���.
	//	BOOL StencilEnable;						���ٽ��׽�Ʈ�� Ȱ��ȭ ����.
	//	UINT8 StencilReadMask;					???
	//	UINT8 StencilWriteMask;					???
	//	D3D11_DEPTH_STENCILOP_DESC FrontFace;	???
	//	D3D11_DEPTH_STENCILOP_DESC BackFace;	???
	//} 	D3D11_DEPTH_STENCIL_DESC;

	D3D11_DEPTH_STENCIL_DESC engineBaseDepthStencilDesc = { 0 };

	engineBaseDepthStencilDesc.DepthEnable = true;
	//true: �����׽�Ʈ ��.

	engineBaseDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	//D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL: ���� ���̵����Ϳ� �� ��.

	engineBaseDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	//D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS: �������� ���� �������� �����Ŵ.

	engineBaseDepthStencilDesc.StencilEnable = false;
	//false: ���ٽ� �׽�Ʈ ����.

	GameEngineDepthStencil::Create("EngineBaseDepth", engineBaseDepthStencilDesc);






	D3D11_DEPTH_STENCIL_DESC alwaysDepthStencilDesc = { 0 };

	alwaysDepthStencilDesc.DepthEnable = true;
	//true: �����׽�Ʈ ��.

	alwaysDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	//D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL: ���� ���̵����Ϳ� �� ��.
	//�̰� ���η� �ٲٸ� �� �����׽�Ʈ�� ����� �� �Ǵ� �ɱ�??

	alwaysDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
	//D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS: �׻� �����Ŵ.

	alwaysDepthStencilDesc.StencilEnable = false;
	//false: ���ٽ� �׽�Ʈ ����.

	GameEngineDepthStencil::Create("AlwaysDepth", alwaysDepthStencilDesc);


}

void EngineTextureLoad()
{

	//typedef struct D3D11_SAMPLER_DESC
	//	D3D11_FILTER Filter;					�ؽ��ĸ� ���ø��Ҷ� ������ ����.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressU;	UV��ǥ 0~1������ ���η� ��� �޽��� ���� ó�� ���.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressV;	UV��ǥ 0~1������ ���η� ��� �޽��� ���� ó�� ���.
	//	D3D11_TEXTURE_ADDRESS_MODE AddressW;	??
	//	FLOAT MipLODBias;						�Ӹ� ���� ������??
	// 
	//	UINT MaxAnisotropy;						���漺 ���͸� �ִ밪. 1~16 ������ ����. 1�� ���漺 ���͸� ��� ����.
	//�ִ밪�� 16���� �ϸ� 1/16�� ��ҵ� �Ӹ� �̹������� ���� ����Ѵٴ� �ǰ�??
	//Filter�� D3D11_FILTER_ANISOTROPIC, D3D11_FILTER_COMPARISON_ANISOTROPIC�϶��� ����.
	// 
	//	D3D11_COMPARISON_FUNC ComparisonFunc;	���ø� �����͸� ���� ���ø� �����Ϳ� ���� �� ����Ǵ� �ɼ�??
	//���� �ɼ��� D3D11_FILTER_COMPARISON_~ ���� ������ ���� ����.
	// 
	//	FLOAT BorderColor[4];					rgba 0~1 ���������� ��輱 ������ ���Ѵ�.
	//AddressU, AddressV, AddressW �� D3D11_TEXTURE_ADDRESS_BORDER�� ������ ������ ����ȴ�.
	// 
	//	FLOAT MinLOD;							�Ӹ� ���� ���� ���� ����. 0�̸� ���� ũ�� ���� �Ӹ� ����.
	//	FLOAT MaxLOD;							�Ӹ� ���� ���� �ְ� ����. 0�̸� ���� ũ�� ���� �Ӹ� ����. �ݵ�� MinLOD���� ũ�ų� ���� ���̾�� �Ѵ�.
	//											
	//} 	D3D11_SAMPLER_DESC;


	//�Ӹ�: ���� �ؽ�ó�� �ػ󵵸� ���� ���� ���� ������ �̸� ����� �����صΰ� �ʿ��� �� ������ ���� ��. 
	// Ŀ�ٶ� ���� �ؽ�ó�� ����Ѵٸ� ī�޶󿡼� �ָ� �ִ� �ؽ�ó�� ��� �ؽ�ó�� ������ ������ �а� �Ǿ ���⿡�� ���� �ʰ� 
	// �޸� ĳ���� ȿ���� �ް��ϰ� ��������. ���� �ؽ�ó �ܰ迡�� �ٿ���ϸ��� ���� ��Ƽ�ٸ������ ���� �ʿ䰡 �ִµ�, 
	// �̰��� �̸� �صδ� ���� �Ӹ���, �Ӹ����� ���� �ؽ�ó ������ �Ӹ��̴�.

	D3D11_SAMPLER_DESC pointClampSamplerDesc = { };

	pointClampSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	//D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT: 
	// ���(Minification), Ȯ��(Magnification), �� ���� ���ø��� ���� ������ ���ø����� �Ѵ�.
	//���伥 Ȯ��/����� �ִ�����(Nearest Neighbor. �ֺ� ���� ���� �ʰ� �� �� �ϳ��� ��� ��) �ɼǰ� ���� ���.

	//D3D11_FILTER::D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR:
	//���(Minification), Ȯ��(Magnification)�� ������ ���ø�����, �� ���� ���ø��� ���������Ѵ�.

	//D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR:
	//���(Minification), Ȯ��(Magnification), �� ���� ���ø��� ���� �������� �Ѵ�. 

	//D3D11_FILTER::D3D11_FILTER_ANISOTROPIC:
	// ���漺(ANISOTROPIC) ���͸�: �����¿츦 ������ ������ Ȯ�� ����� �Ӹ� �̹����� ����ϴ� ���� �ƴ϶�, 
	// ���ϳ� �¿� ������ �ٸ� ������ Ȯ�� ����� �Ӹ��̹����� ����ؼ� ī�޶� �پ��� ��ġ�� �������� �׿� �´� ������ �Ӹ��� ����ϴ� ���.

	//�� �ܿ��� ���� ���͸� �ɼǵ��� �ִ�. 


	//typedef
	//enum D3D11_TEXTURE_ADDRESS_MODE			UV��ǥ���� 0~1�� ��� ��ǥ�� �޽� ������ ���� ���.
	//{
	//	D3D11_TEXTURE_ADDRESS_WRAP = 1,			�ؽ��ĸ� �״�� �����ؼ� �׸���.	
	//	D3D11_TEXTURE_ADDRESS_MIRROR = 2,		�¿�/���� ����� �׸���.
	//	D3D11_TEXTURE_ADDRESS_CLAMP = 3,		�׸��� �ʴ´�.
	//	D3D11_TEXTURE_ADDRESS_BORDER = 4,		�ؽ��� �ش� ���� ��輱�� ���� �÷� �׸���
	//	D3D11_TEXTURE_ADDRESS_MIRROR_ONCE = 5	�¿�/���ϸ� ����� �ѹ��� �׸���.
	//} 	D3D11_TEXTURE_ADDRESS_MODE;

	pointClampSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
	pointClampSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
	pointClampSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

	//D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP�� �⺻�� ����: 
	// �Ǽ� ������ UV���� 1�� �ʰ��ص� �� �׸��� �ʰ� ������ �����Ƿ� ���� ����ϰ� ���´�.


	pointClampSamplerDesc.MipLODBias = 0.f;
	pointClampSamplerDesc.MaxAnisotropy = 1;	//1: ���漺 �Ӹ� ���� ����.

	//	typedef 
	//	enum D3D11_COMPARISON_FUNC
	//	{
	//		D3D11_COMPARISON_NEVER = 1,			�ƹ��͵� �����Ű�� ����.
	//		D3D11_COMPARISON_LESS = 2,			���� ���� �͸� ���.
	//		D3D11_COMPARISON_EQUAL = 3,			���� ���� �͸� ���.
	//		D3D11_COMPARISON_LESS_EQUAL = 4,	���� �۰ų� ���� �͸� ���.
	//		D3D11_COMPARISON_GREATER = 5,		���� ū �͸� ���.
	//		D3D11_COMPARISON_NOT_EQUAL = 6,		���� ���� ���� �͸� ���.
	//		D3D11_COMPARISON_GREATER_EQUAL = 7,	���� ũ�ų� ���� �͸� ���.
	//		D3D11_COMPARISON_ALWAYS = 8			������ ���.
	//	} 	D3D11_COMPARISON_FUNC;	

	pointClampSamplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	//���ʿ� ���� �ɼ��� ������ �ʴ� �ɼ����� �߱� ������ �� ��� ������ ������� �ʴ´�.

	pointClampSamplerDesc.MinLOD = -FLT_MAX;
	pointClampSamplerDesc.MaxLOD = FLT_MAX;

	GameEngineSampler::Create("POINTCLAMP", pointClampSamplerDesc);


	D3D11_SAMPLER_DESC pointWrapSamplerDesc = {};
	pointWrapSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	pointWrapSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	pointWrapSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	pointWrapSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	pointWrapSamplerDesc.MipLODBias = 0.f;
	pointWrapSamplerDesc.MaxAnisotropy = 1;
	pointWrapSamplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	pointWrapSamplerDesc.MinLOD = -FLT_MAX;
	pointWrapSamplerDesc.MaxLOD = FLT_MAX;
	GameEngineSampler::Create("POINTWRAP", pointWrapSamplerDesc);



	D3D11_SAMPLER_DESC linearMirrorSamplerDesc = {};
	linearMirrorSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	linearMirrorSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
	linearMirrorSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
	linearMirrorSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
	linearMirrorSamplerDesc.MipLODBias = 0.f;
	linearMirrorSamplerDesc.MaxAnisotropy = 1;
	linearMirrorSamplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	linearMirrorSamplerDesc.MinLOD = -FLT_MAX;
	linearMirrorSamplerDesc.MaxLOD = FLT_MAX;
	GameEngineSampler::Create("LINEARMIRROR", linearMirrorSamplerDesc);



	D3D11_SAMPLER_DESC linearWrapSamplerDesc = {};
	linearWrapSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	linearWrapSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	linearWrapSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	linearWrapSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	linearWrapSamplerDesc.MipLODBias = 0.f;
	linearWrapSamplerDesc.MaxAnisotropy = 1;
	linearWrapSamplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	linearWrapSamplerDesc.MinLOD = -FLT_MAX;
	linearWrapSamplerDesc.MaxLOD = FLT_MAX;
	GameEngineSampler::Create("LINEARWRAP", linearWrapSamplerDesc);

	//D3D11 ERROR: ID3D11DeviceContext::DrawIndexed: 
	//The Pixel Shader unit expects a Sampler configured for default filtering to be set at Slot 0, 
	//but the sampler bound at this slot is configured for comparison filtering.  
	//This mismatch will produce undefined behavior if the sampler is used (e.g. it is not skipped due to shader code branching).
	//[ EXECUTION ERROR #390: DEVICE_DRAW_SAMPLER_MISMATCH]
	//->���÷� ���� �ɼ��� D3D11_FILTER::D3D11_FILTER_COMPARISON_~���� ����������, 
	// HLSL�ڵ�����δ� �� ���� �ɼ��� Ȱ������ �ʾ��� �� ������ ����� �Ѵ�..


	GameEngineDirectory currentDir;

	currentDir.MoveParentToExistChildDirectory("GameEngineResources");
	currentDir.MoveToChild("GameEngineResources");
	currentDir.MoveToChild("Texture");

	std::vector<GameEngineFile> textures = currentDir.GetAllFiles();

	for (size_t i = 0; i < textures.size(); i++)
	{
		GameEngineTexture::Load(textures[i].GetFullPath());
	}

	currentDir.MoveToParent("GameEngineResources");
	currentDir.MoveToChild("Texture2DArray");
	currentDir.MoveToChild("NSet5Colors");


	GameEngineTexture2DArray::Load(currentDir.GetFullPath());
}

void EngineMaterial()
{

	std::shared_ptr<GameEngineMaterial> newMaterial1
		= GameEngineMaterial::Create("Color");
	newMaterial1->SetVertexShader("Color.hlsl");
	newMaterial1->SetPixelShader("Color.hlsl");
	newMaterial1->SetRasterizer("EngineRasterizer");
	newMaterial1->SetBlend_OutputMerger("AlphaBlend");
	newMaterial1->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial2
		= GameEngineMaterial::Create("Texture");
	newMaterial2->SetVertexShader("Texture.hlsl");
	newMaterial2->SetPixelShader("Texture.hlsl");
	newMaterial2->SetRasterizer("EngineRasterizer");
	newMaterial2->SetBlend_OutputMerger("AlphaBlend");
	newMaterial2->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial3
		= GameEngineMaterial::Create("TextureAtlas");
	newMaterial3->SetVertexShader("TextureAtlas.hlsl");
	newMaterial3->SetPixelShader("TextureAtlas.hlsl");
	newMaterial3->SetRasterizer("EngineRasterizer");
	newMaterial3->SetBlend_OutputMerger("AlphaBlend");
	newMaterial3->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial4
		= GameEngineMaterial::Create("3DDebug");
	newMaterial4->SetVertexShader("Debug3D.hlsl");
	newMaterial4->SetPixelShader("Debug3D.hlsl");
	newMaterial4->SetRasterizer("EngineRasterizer");
	newMaterial4->SetBlend_OutputMerger("AlphaBlend");
	newMaterial4->SetDepthStencil_OutputMerger("AlwaysDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial5
		= GameEngineMaterial::Create("DebugTexture");
	newMaterial5->SetVertexShader("DebugTexture.hlsl");
	newMaterial5->SetPixelShader("DebugTexture.hlsl");
	newMaterial5->SetRasterizer("EngineRasterizer");
	newMaterial5->SetBlend_OutputMerger("AlphaBlend");
	newMaterial5->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial6
		= GameEngineMaterial::Create("TargetMerge");
	newMaterial6->SetVertexShader("TargetMerge.hlsl");
	newMaterial6->SetPixelShader("TargetMerge.hlsl");
	newMaterial6->SetRasterizer("EngineRasterizer");
	newMaterial6->SetBlend_OutputMerger("AlphaBlend");
	newMaterial6->SetDepthStencil_OutputMerger("AlwaysDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial7
		= GameEngineMaterial::Create("Blur");
	newMaterial7->SetVertexShader("Blur.hlsl");
	newMaterial7->SetPixelShader("Blur.hlsl");
	newMaterial7->SetRasterizer("EngineRasterizer");
	newMaterial7->SetBlend_OutputMerger("AlphaBlend");
	newMaterial7->SetDepthStencil_OutputMerger("EngineBaseDepth");


	std::shared_ptr<GameEngineMaterial> newMaterial8
		= GameEngineMaterial::Create("TextureAnimation");
	newMaterial8->SetVertexShader("TextureAnimation.hlsl");
	newMaterial8->SetPixelShader("TextureAnimation.hlsl");
	newMaterial8->SetRasterizer("EngineRasterizer");
	newMaterial8->SetBlend_OutputMerger("AlphaBlend");
	newMaterial8->SetDepthStencil_OutputMerger("EngineBaseDepth");

	std::shared_ptr<GameEngineMaterial> newMaterial9
		= GameEngineMaterial::Create("LightTest");
	newMaterial9->SetVertexShader("LightTest.hlsl");
	newMaterial9->SetPixelShader("LightTest.hlsl");
	newMaterial9->SetRasterizer("EngineRasterizer");
	newMaterial9->SetBlend_OutputMerger("AlphaBlend");
	newMaterial9->SetDepthStencil_OutputMerger("EngineBaseDepth");

}

void EngineMesh()
{
	//�⺻ �簢��.
	std::vector<GameEngineVertex> rectVertex;
	rectVertex.reserve(4);
	rectVertex.push_back({ float4(-0.5f, 0.5f), float4::Black, float4(0, 0), float4::Back });	//0�� ��.
	rectVertex.push_back({ float4(0.5f, 0.5f), float4::Black, float4(1, 0), float4::Back });	//1�� ��.
	rectVertex.push_back({ float4(0.5f, -0.5f), float4::Black, float4(1, 1), float4::Back });	//2�� ��.
	rectVertex.push_back({ float4(-0.5f, -0.5f), float4::Black, float4(0, 1), float4::Back });	//3�� ��.
	GameEngineVertexBuffer::Create("RectVertex", rectVertex);

	std::vector<int> rectIndex;
	rectIndex.reserve(6);
	//1�� �ﰢ��.
	rectIndex.push_back(0);
	rectIndex.push_back(1);
	rectIndex.push_back(2);
	//2�� �ﰢ��.
	rectIndex.push_back(0);
	rectIndex.push_back(2);
	rectIndex.push_back(3);
	GameEngineIndexBuffer::Create("RectIndex", rectIndex);

	GameEngineMesh::Create("Rect", "RectVertex", "RectIndex");





	//������ ��ü ũ�� �簢��.
	std::vector<GameEngineVertex> fullrectVertex;
	fullrectVertex.reserve(4);
	fullrectVertex.push_back({ float4(-1.f, 1.f), float4::Black, float4(0, 0), float4::Back });	//0�� ��.
	fullrectVertex.push_back({ float4(1.f, 1.f), float4::Black, float4(1, 0), float4::Back });		//1�� ��.
	fullrectVertex.push_back({ float4(1.f, -1.f), float4::Black, float4(1, 1), float4::Back });	//2�� ��.
	fullrectVertex.push_back({ float4(-1.f, -1.f), float4::Black, float4(0, 1), float4::Back });	//3�� ��.
	GameEngineVertexBuffer::Create("FullrectVertex", fullrectVertex);

	std::vector<int> fullrectIndex;
	fullrectIndex.reserve(6);
	//1�� �ﰢ��.
	fullrectIndex.push_back(0);
	fullrectIndex.push_back(1);
	fullrectIndex.push_back(2);
	//2�� �ﰢ��.
	fullrectIndex.push_back(0);
	fullrectIndex.push_back(2);
	fullrectIndex.push_back(3);
	GameEngineIndexBuffer::Create("FullrectIndex", fullrectIndex);

	GameEngineMesh::Create("Fullrect", "FullrectVertex", "FullrectIndex");

	//�⺻ ����ü.
	std::vector<GameEngineVertex> boxVertex;
	boxVertex.reserve(8);
	boxVertex.push_back({ float4(-0.5f, 0.5f, -0.5f), float4::Black, float4(0, 0), float4(-0.5773f, 0.5773f, -0.5773f) });		//0�� ��.
	boxVertex.push_back({ float4(0.5f, 0.5f, -0.5f), float4::Black, float4(1, 0),  float4(0.5773f, 0.5773f, -0.5773f) });		//1�� ��.
	boxVertex.push_back({ float4(0.5f, -0.5f, -0.5f), float4::Black, float4(1, 1), float4(0.5773f, -0.5773f, -0.5773f) });		//2�� ��.
	boxVertex.push_back({ float4(-0.5f, -0.5f, -0.5f), float4::Black, float4(0, 1), float4(-0.5773f, -0.5773f, -0.5773f) });	//3�� ��.

	boxVertex.push_back({ float4(0.5f, 0.5f, 0.5f), float4::Black, float4(0, 1), float4(0.5773f, 0.5773f, 0.5773f) });		//4�� ��.
	boxVertex.push_back({ float4(-0.5f, 0.5f, 0.5f), float4::Black, float4(1, 1), float4(-0.5773f, 0.5773f, 0.5773f) });		//5�� ��.
	boxVertex.push_back({ float4(-0.5f, -0.5f, 0.5f), float4::Black, float4(1, 0), float4(-0.5773f, -0.5776f, 0.5776f) });		//6�� ��.
	boxVertex.push_back({ float4(0.5f, -0.5f, 0.5f), float4::Black, float4(0, 0), float4(0.5773f, -0.5773f, 0.5773f) });		//7�� ��.
	GameEngineVertexBuffer::Create("BoxVertex", boxVertex);

	std::vector<int> boxIndex;
	rectIndex.reserve(36);

	//���� 1�� �ﰢ��.
	boxIndex.push_back(0);
	boxIndex.push_back(1);
	boxIndex.push_back(2);
	//���� 2�� �ﰢ��.
	boxIndex.push_back(0);
	boxIndex.push_back(2);
	boxIndex.push_back(3);
	//�ĸ� 1�� �ﰢ��.
	boxIndex.push_back(4);
	boxIndex.push_back(5);
	boxIndex.push_back(6);
	//�ĸ� 2�� �ﰢ��.
	boxIndex.push_back(4);
	boxIndex.push_back(6);
	boxIndex.push_back(7);

	//�¸� 1�� �ﰢ��.
	boxIndex.push_back(5);
	boxIndex.push_back(0);
	boxIndex.push_back(3);
	//�¸� 2�� �ﰢ��.
	boxIndex.push_back(5);
	boxIndex.push_back(3);
	boxIndex.push_back(6);
	//��� 1�� �ﰢ��.
	boxIndex.push_back(1);
	boxIndex.push_back(4);
	boxIndex.push_back(7);
	//��� 2�� �ﰢ��.
	boxIndex.push_back(1);
	boxIndex.push_back(7);
	boxIndex.push_back(2);

	//��� 1�� �ﰢ��.
	boxIndex.push_back(5);
	boxIndex.push_back(4);
	boxIndex.push_back(1);
	//��� 2�� �ﰢ��.
	boxIndex.push_back(5);
	boxIndex.push_back(1);
	boxIndex.push_back(0);
	//�ϸ� 1�� �ﰢ��.
	boxIndex.push_back(2);
	boxIndex.push_back(3);
	boxIndex.push_back(6);
	//�ϸ� 2�� �ﰢ��.
	boxIndex.push_back(2);
	boxIndex.push_back(6);
	boxIndex.push_back(7);

	GameEngineIndexBuffer::Create("BoxIndex", boxIndex);

	GameEngineMesh::Create("Box", "BoxVertex", "BoxIndex");




	{
		GameEngineVertex V;
		std::vector<GameEngineVertex> VBVector;
		std::vector<UINT> IBVector;

		float Radius = 0.5f;
		// �ϱ������� �����մϴ�.
		V.POSITION = float4(0.0f, Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 0.0f);
		// �븻 ���� Ȥ�� �������Ͷ�� �Ҹ���
		// �鿡 ������ ���͸� �ǹ��ϰ� �ȴ�.
		// ���� �ݻ��Ҷ� �ʼ�.
		V.NORMAL = float4(0.0f, Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize3D();
		V.NORMAL.w = 0.0f;
		V.TANGENT = float4(1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, 1.0f, 0.0f);

		VBVector.push_back(V);

		UINT iStackCount = 40; // ���� ���� �����Դϴ�.
		UINT iSliceCount = 40; // ���κ��� ����

		float yRotAngle = GameEngineMath::PI / (float)iStackCount;
		float zRotAngle = (GameEngineMath::PI * 2) / (float)iSliceCount;

		// UV�� ���μ��� ���ݰ��� ���Ѵ�.
		float yUvRatio = 1.0f / (float)iStackCount;
		float zUvRatio = 1.0f / (float)iStackCount;

		for (UINT y = 1; y < iStackCount; ++y)
		{
			// �� ���ݿ� ���� ������
			float phi = y * yRotAngle;
			for (UINT z = 0; z < iSliceCount + 1; ++z)
			{
				float theta = z * zRotAngle;
				V.POSITION = float4{
					Radius * sinf(y * yRotAngle) * cosf(z * zRotAngle),
					Radius * cosf(y * yRotAngle),
					Radius * sinf(y * yRotAngle) * sinf(z * zRotAngle),
					1.0f // ��ġ ũ�� ���� ������ �ֱ� ���ؼ�
				};

				// V.Pos *= GameEngineRandom::RandomFloat(-0.9f, 0.1f);

				V.TEXCOORD = float4(yUvRatio * z, zUvRatio * y);
				V.NORMAL = float4::Normalize3DReturn(V.POSITION);
				V.NORMAL.w = 0.0f;

				V.TANGENT.x = -Radius * sinf(phi) * sinf(theta);
				V.TANGENT.y = 0.0f;
				V.TANGENT.z = Radius * sinf(phi) * cosf(theta);
				V.TANGENT = float4::Normalize3DReturn(V.TANGENT);
				V.TANGENT.w = 0.0f;

				V.BINORMAL = float4::Cross3D(V.TANGENT, V.NORMAL);
				V.BINORMAL = float4::Normalize3DReturn(V.BINORMAL);
				V.BINORMAL.w = 0.0f;

				VBVector.push_back(V);
			}
		}

		// ������
		V.POSITION = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 1.0f);
		V.NORMAL = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize3D();
		V.NORMAL.w = 0.0f;
		V.TANGENT = float4(-1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, -1.0f, 0.0f);
		VBVector.push_back(V);

		// �ε��� ���۸� ����ϴ�.
		IBVector.clear();

		// �ϱ����� �̷�� ���� ����°�.
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(0);
			IBVector.push_back(i + 2);
			IBVector.push_back(i + 1);
		}

		for (UINT y = 0; y < iStackCount - 2; y++)
		{
			for (UINT z = 0; z < iSliceCount; z++)
			{
				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + z + 1);

				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * y + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);

			}
		}

		// ���������� ������ �ε���
		UINT iBotIndex = (UINT)VBVector.size() - 1;
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(iBotIndex);
			IBVector.push_back(iBotIndex - (i + 2));
			IBVector.push_back(iBotIndex - (i + 1));
		}

		GameEngineVertexBuffer::Create("Sphere", VBVector);
		GameEngineIndexBuffer::Create("Sphere", IBVector);
		GameEngineMesh::Create("Sphere");

	}




	GameEngineFont::Load("����");
}

void ShaderCompile()
{
	GameEngineDirectory engineResourceDir;

	engineResourceDir.MoveParentToExistChildDirectory("GameEngineResources");
	engineResourceDir.MoveToChild("GameEngineResources");
	engineResourceDir.MoveToChild("GameEngineShader");

	std::vector<GameEngineFile> shaders = engineResourceDir.GetAllFiles("hlsl");

	for (size_t i = 0; i < shaders.size(); i++)
	{
		GameEngineShader::AutoCompile(shaders[i].GetFullPath());
	}
}

void GameEngineCore::EngineResourceInitialize()
{
	EngineTextureLoad();	//���÷��� �����ϰ� �ؽ�ó�� �ҷ����� �Լ�.
	EngineInputLayout();	//���� �⺻���� ��ǲ ���̾ƿ��� �����ϴ� �Լ�.
	EngineMesh();			//���� �⺻���� �簢���� ����ü �޽��� �����ϴ� �Լ�.
	EngineSubSetting();		//���� �⺻���� �����Ͷ�����, ����, ���̽��ٽ��� �����ϴ� �Լ�.
	ShaderCompile();		//���� �⺻���� HLSL�ڵ带 �������ؼ� ���̴��� ���̴����ҽ��� ����, �����ϴ� �Լ�.

	EngineMaterial();		//���� �⺻���� ���׸������ �����ϴ� �Լ�.
}

void GameEngineCore::EngineResourceDestroy()
{
	//�簢��, ����ü, �����ؽ��� ���, ���� ���ؿ��� �⺻������ �����Ǿ�� �ϴ� ���ҽ��� �����ϴ� �Լ�.
	GameEngineMaterial::ResourceDestroy();

	GameEngineInputLayout::ResourceDestroy();
	GameEngineVertexBuffer::ResourceDestroy();
	GameEngineVertexShader::ResourceDestroy();
	GameEngineIndexBuffer::ResourceDestroy();
	GameEngineRasterizer::ResourceDestroy();
	GameEnginePixelShader::ResourceDestroy();
	GameEngineDepthStencil::ResourceDestroy();
	GameEngineBlend::ResourceDestroy();

	GameEngineMesh::ResourceDestroy();
	GameEngineFBXMesh::ResourceDestroy();
	GameEngineFBXAnimation::ResourceDestroy();

	GameEngineConstantBuffer::ResourceDestroy();
	GameEngineStructuredBuffer::ResourceDestroy();
	GameEngineInstancingBuffer::ResourceDestroy();
	GameEngineRenderTarget::ResourceDestroy();
	GameEngineTexture::ResourceDestroy();
	GameEngineFolderTexture::ResourceDestroy();
	GameEngineSampler::ResourceDestroy();
	GameEngineSound::ResourceDestroy();
	GameEngineFont::ResourceDestroy();

	GameEngineDevice::Destroy();
	//��� ���ҽ����� ���̷�ƮX ����̽��� ������ �־�� ������ �� �����Ƿ�,
	// ���ҽ��� ���� �ı��� �Ŀ� ����̽��� �����Ѵ�.
}
