#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"
#include "InstancingTextures.h"

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
	//sampleTextureRenderer->SetTexture("tree_Group_A.png");
	//sampleTextureRenderer->GetTransform().SetWorldScale(100, 100, 1);

	//shaderTestRenderer_ = shaderTestActor_->CreateComponent<GameEngineTextureRenderer>("ShaderTestRenderer");
	//shaderTestRenderer_->GetTransform().SetWorldScale(25, 25, 1);


	//GameEngineDirectory monsterTextureDir;
	//monsterTextureDir.MoveParentToExistChildDirectory("ContentsResources");
	//monsterTextureDir.MoveToChild("ContentsResources");
	//monsterTextureDir.MoveToChild("Actor");
	//monsterTextureDir.MoveToChild("Monster");


	//InstancingTextures::Load(monsterTextureDir.GetFullPath());

	std::shared_ptr<GameEngineCamera> mainCameraComponent = this->GetMainCamera();
	GameEngineInstancing& textureInst = mainCameraComponent->GetInstancing("TextureInst");

	for (size_t i = 0; i < 111; i++)
	{
		if (110 == i)
		{
			int i = 0;
		}

		float4 randomPos = GameEngineRandom::mainRandom_.RandomFloat4(-300.f, 300.f);
		//randomPos.z = 0.f;

		std::shared_ptr<GameEngineTextureRenderer> tempRenderer = shaderTestActor_->CreateComponent<GameEngineTextureRenderer>();
		tempRenderer->GetTransform().SetWorldScale(25, 25, 25);
		tempRenderer->GetTransform().SetWorldPosition(randomPos);

		textureInst.PushUnit(
			tempRenderer->GetRenderUnit(),
			[=](GameEngineInstancing::InstancingData& _instData)
			{
				_instData.Link("Inst_TransformData", tempRenderer->GetTransformData());
				_instData.Link("Inst_AtlasData", tempRenderer->GetAtlasData());
			}
		);
	}



}

void ShaderTestLevel::Update(float _deltaTime)
{
}

void ShaderTestLevel::End()
{
}
