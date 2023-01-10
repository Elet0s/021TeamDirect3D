#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Mouse.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"
#include "FieldRenderingActor.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"
#include "GameEngineStatusWindow.h"

ShaderTestLevel::ShaderTestLevel()
	: shaderTestActor_(nullptr),
	testTextureDesc_(),
	testTexture_(nullptr),
	testUAVDesc_()
{
}

ShaderTestLevel::~ShaderTestLevel()
{
}

void ShaderTestLevel::Start()
{
	this->GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);
	this->GetMainCamera()->SetFarZ(500.f);
	//this->GetCamera(static_cast<UINT>(CameraOrder::MousePointerCamera))->SetProjectionMode(CameraProjectionMode::Perspective);


	shaderTestActor_ = CreateActor<Mouse>(0, "ShaderTestActor");

	//typedef struct D3D11_TEXTURE2D_DESC
	//{
	//	UINT Width;
	//	UINT Height;
	//	UINT MipLevels;
	//	UINT ArraySize;
	//	DXGI_FORMAT Format;
	//	DXGI_SAMPLE_DESC SampleDesc;
	//	D3D11_USAGE Usage;
	//	UINT BindFlags;
	//	UINT CPUAccessFlags;
	//	UINT MiscFlags;
	//} 	D3D11_TEXTURE2D_DESC;

	testTextureDesc_.Width = GameEngineWindow::GetScale().UIX();
	testTextureDesc_.Height = GameEngineWindow::GetScale().UIY();
	testTextureDesc_.MipLevels = 1;
	testTextureDesc_.ArraySize = 1;
	testTextureDesc_.Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
	testTextureDesc_.SampleDesc.Count = 1;
	testTextureDesc_.SampleDesc.Quality = 0;
	testTextureDesc_.Usage = D3D11_USAGE_DEFAULT;
	testTextureDesc_.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	testTextureDesc_.CPUAccessFlags = 0;
	testTextureDesc_.MiscFlags = 0;

	testTexture_ = GameEngineTexture::Create("TestTexture", testTextureDesc_);
	testTexture_->CreateUnorderedAccessView();
	testTexture_->CSSetUnorderedAccessView(0);


	//typedef struct D3D11_UNORDERED_ACCESS_VIEW_DESC
	//{
	//	DXGI_FORMAT Format;
	//	D3D11_UAV_DIMENSION ViewDimension;
	//	union
	//	{
	//		D3D11_BUFFER_UAV Buffer;
	//		D3D11_TEX1D_UAV Texture1D;
	//		D3D11_TEX1D_ARRAY_UAV Texture1DArray;
	//		D3D11_TEX2D_UAV Texture2D;
	//		D3D11_TEX2D_ARRAY_UAV Texture2DArray;
	//		D3D11_TEX3D_UAV Texture3D;
	//	};
	//} 	D3D11_UNORDERED_ACCESS_VIEW_DESC;


	//testUAVDesc_.Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
	//testUAVDesc_.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	//testUAVDesc_.Texture2D.MipSlice = 0;
	//GameEngineDevice::GetDevice()->CreateUnorderedAccessView()


	int i = 0;
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}

void ShaderTestLevel::Update(float _deltaTime)
{
	
}

void ShaderTestLevel::End()
{
}

void ShaderTestLevel::LevelStartEvent()
{
	//shaderTestActor_->SetProjectionMode(ProjectionMode::Perspective);
}