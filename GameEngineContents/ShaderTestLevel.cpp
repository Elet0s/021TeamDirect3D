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
	lighting_(nullptr),
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


	shaderTestActor_ = CreateActor<FieldRenderingActor>(0, "ShaderTestActor");
	shaderTestActor_->Initialize(
		550,
		100,
		float4(100, 100),
		60.f
	);

	lighting_ = CreateActor<GameEngineLighting>(0, "Lighting");
	lighting_ = CreateActor<GameEngineLighting>(0, "TestLevelLighting");
	//테스트레벨에 조명 추가.

	lighting_->GetTransform().SetWorldRotation(45.f, 45.f, 0.f);
	//조명 각도 설정.

	lighting_->GetLightingData().mainLightColor_ = float4(0.7f, 0.7f, 0.7f);
	//정반사광, 난반사광 색, 밝기 설정.

	lighting_->GetLightingData().ambientLightColor_ = float4(0.1f, 0.1f, 0.1f);
	//환경광 색, 밝기 설정.

	lighting_->GetLightingData().specularLightRatio_ = 0.f;
	//정반사광 사용 안함.

	lighting_->GetLightingData().diffuseLightRatio_ = 2.f;
	//난반사광을 두배로 적용.

	this->GetMainCamera()->PushLighting(lighting_);
	//메인카메라에 조명 등록.


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

	//testTextureDesc_.Width = GameEngineWindow::GetInst().GetScale().UIX();
	//testTextureDesc_.Height = GameEngineWindow::GetInst().GetScale().UIY();
	//testTextureDesc_.MipLevels = 1;
	//testTextureDesc_.ArraySize = 1;
	//testTextureDesc_.Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
	//testTextureDesc_.SampleDesc.Count = 1;
	//testTextureDesc_.SampleDesc.Quality = 0;
	//testTextureDesc_.Usage = D3D11_USAGE_DEFAULT;
	//testTextureDesc_.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	//testTextureDesc_.CPUAccessFlags = 0;
	//testTextureDesc_.MiscFlags = 0;

	//testTexture_ = GameEngineTexture::Create("TestTexture", testTextureDesc_);
	//testTexture_->CreateUnorderedAccessView();
	//testTexture_->CSSetUnorderedAccessView(0);


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


	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}

void ShaderTestLevel::Update(float _deltaTime)
{
	static float4 lightingRotation = float4(45.f, 45.f, 0.f);

	if (true == GameEngineInput::GetInst().IsPressed("TestD"))
	{
		lightingRotation += float4(45.f * _deltaTime, 0.f, 0.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("TestU"))
	{
		lightingRotation += float4(-45.f * _deltaTime, 0.f, 0.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("TestL"))
	{
		lightingRotation += float4(0.f, -45.f * _deltaTime, 0.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("TestR"))
	{
		lightingRotation += float4(0.f, 45.f * _deltaTime, 0.f);
	}

	lighting_->GetTransform().SetWorldRotation(lightingRotation);

	shaderTestActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
	shaderTestActor_->SetLightingRotation(
		lighting_->GetTransform().GetWorldRotation().x,
		lighting_->GetTransform().GetWorldRotation().y
	);

	shaderTestActor_->GetTransform().SetWorldPosition(this->GetMainCamera()->GetTransform().GetWorldPosition());
}

void ShaderTestLevel::End()
{
}

void ShaderTestLevel::LevelStartEvent()
{
	//shaderTestActor_->SetProjectionMode(ProjectionMode::Perspective);
	this->GetMainCamera()->SetFarZ(100000.f);
}