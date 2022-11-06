#include "PreCompile.h"
#include "ShaderTestLevel.h"
//#include "LoginUI.h"
//#include "Enums.h"
//#include "Player.h"
//#include "GlobalContentsValue.h"

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


	shaderTestRenderer_ = shaderTestActor_->CreateComponent<GameEngineDefaultRenderer>("ShaderTestRenderer");
	shaderTestRenderer_->SetMesh("Rect");
	shaderTestRenderer_->SetMaterial("Test");
	shaderTestRenderer_->GetRenderUnit().GetShaderResourceHelper().SetConstantBuffer_Link("TestColor", float4::Red);
	shaderTestRenderer_->ChangeCamera(CameraOrder::MainCamera);
	shaderTestRenderer_->GetTransform().SetWorldScale(100, 100, 1);
}

void ShaderTestLevel::Update(float _deltaTime)
{
	float4 shaderTestActorWorldPos = shaderTestActor_->GetTransform().GetWorldPosition();
	float4 shaderTestRendererWorldPos = shaderTestRenderer_->GetTransform().GetWorldPosition();
	int i = 0;
}

void ShaderTestLevel::End()
{
}
