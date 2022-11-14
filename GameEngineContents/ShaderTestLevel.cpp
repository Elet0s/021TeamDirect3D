#include "PreCompile.h"
#include "ShaderTestLevel.h"
//#include "LoginUI.h"
//#include "Enums.h"
//#include "Player.h"
//#include "GlobalContentsValue.h"
#include "ContentsTextureShadowRenderer.h"

ShaderTestLevel::ShaderTestLevel(): shaderTestActor_(nullptr), shaderTestRenderer_(nullptr)
{
}

ShaderTestLevel::~ShaderTestLevel()
{
}

void ShaderTestLevel::Start()
{
	shaderTestActor_ = CreateActor<GameEngineActor>(0, "ShaderTestActor");
	shaderTestActor_->GetTransform().SetLocalScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldPosition(float4::Zero);

	//std::shared_ptr<GameEngineTextureRenderer> sampleTextureRenderer =
	//	shaderTestActor_->CreateComponent<GameEngineTextureRenderer>("SampleTextureRenderer");

	shaderTestRenderer_ = shaderTestActor_->CreateComponent<ContentsTextureShadowRenderer>("ShaderTestRenderer");
	shaderTestRenderer_->SetMesh("Rect");
	shaderTestRenderer_->SetMaterial("TextureShadow");
	shaderTestRenderer_->GetRenderUnit().GetShaderResourceHelper().SetConstantBuffer_Link("ShadowColor", float4::Red);
	shaderTestRenderer_->ChangeCamera(CameraOrder::MainCamera);
	shaderTestRenderer_->GetTransform().SetWorldScale(100, 100, 1);
}

void ShaderTestLevel::Update(float _deltaTime)
{

}

void ShaderTestLevel::End()
{
}
