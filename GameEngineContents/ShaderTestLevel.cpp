#include "PreCompile.h"
#include "ShaderTestLevel.h"
//#include "LoginUI.h"
//#include "Enums.h"
//#include "Player.h"
//#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

ShaderTestLevel::ShaderTestLevel(): shaderTestActor_(nullptr), shaderTestRenderer_(nullptr)
{
}

ShaderTestLevel::~ShaderTestLevel()
{
}

void ShaderTestLevel::Start()
{
	//std::shared_ptr<GameEngineTextureRenderer> sampleTextureRenderer =
	//	shaderTestActor_->CreateComponent<GameEngineTextureRenderer>("SampleTextureRenderer");



	shaderTestActor_ = CreateActor<GameEngineActor>(0, "ShaderTestActor");
	shaderTestActor_->GetTransform().SetLocalScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldPosition(float4::Zero);


	shaderTestRenderer_ = shaderTestActor_->CreateComponent<Texture2DShadowRenderer>("ShaderTestRenderer");

	shaderTestRenderer_->GetTransform().SetWorldScale(100, 100, 1);
}

void ShaderTestLevel::Update(float _deltaTime)
{

}

void ShaderTestLevel::End()
{
}
