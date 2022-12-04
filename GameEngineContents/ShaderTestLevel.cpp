#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"

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


	//GameEngineInstancingTextures::Load(monsterTextureDir.GetFullPath());

	//GameEngineTime::SetFrameLimit(70);

	//std::shared_ptr<GameEngineCamera> mainCameraComponent = this->GetMainCamera();
	//GameEngineInstancing& textureInst = mainCameraComponent->GetInstancing("TextureInst");

	//for (size_t i = 0; i < 111; i++)
	//{
	//	if (110 == i)
	//	{
	//		int i = 0;
	//	}

	//	float4 randomPos = GameEngineRandom::mainRandom_.RandomFloat4(-300.f, 300.f);
	//	//randomPos.z = 0.f;

	//	std::shared_ptr<GameEngineTextureRenderer> tempRenderer = shaderTestActor_->CreateComponent<GameEngineTextureRenderer>();
	//	tempRenderer->GetTransform().SetWorldScale(25, 25, 25);
	//	tempRenderer->GetTransform().SetWorldPosition(randomPos);

	//	textureInst.PushUnit(
	//		tempRenderer->GetRenderUnit(),
	//		[=](GameEngineInstancing::InstancingData& _instData)
	//		{
	//			_instData.Link("Inst_TransformData", tempRenderer->GetTransformData());
	//			_instData.Link("Inst_AtlasData", tempRenderer->GetAtlasData());
	//		}
	//	);
	//}
	int testNumber = 144;
	
	GameEngineInstancingRenderer& testInstancingRenderer = this->GetMainCamera()->GetInstancingRenderer("Test");
	testInstancingRenderer.Initialize(static_cast<size_t>(testNumber));
	testInstancingRenderer.SetTexture("TEX", "NSet.png");
	testInstancingRenderer.SetSampler("POINTCLAMP", "POINTCLAMP");

	testAtlasDataVector_.reserve(testNumber);


	for (int i = 0; i < testNumber; i++)
	{
		float4 randomPos = GameEngineRandom::mainRandom_.RandomFloat4(-300.f, 300.f);
		testAtlasDataVector_.push_back(AtlasData());

		testAtlasDataVector_[i].frameData_.posX = GameEngineRandom::mainRandom_.RandomFloat(0.f, 0.5f);
		testAtlasDataVector_[i].frameData_.posY = GameEngineRandom::mainRandom_.RandomFloat(0.f, 0.5f);
		testAtlasDataVector_[i].frameData_.sizeX = 1.f - testAtlasDataVector_[i].frameData_.posX;
		testAtlasDataVector_[i].frameData_.sizeY = 1.f - testAtlasDataVector_[i].frameData_.posY;
		testAtlasDataVector_[i].pivotPos_ = float4::Zero;

		std::shared_ptr<GameEngineTransformComponent> tempComponent = shaderTestActor_->CreateComponent<GameEngineTransformComponent>();
		tempComponent->GetTransform().SetWorldScale(25.f, 25.f, 1.f);
		tempComponent->GetTransform().SetWorldPosition(randomPos);
		testInstancingRenderer.GetInstancingUnit(i).SetTransformData(tempComponent->GetTransformData());
		//testInstancingRenderer.GetInstancingUnit(i).GetRenderOption().bytePad1_ = 4;

		testInstancingRenderer.GetInstancingUnit(i).Link("Inst_AtlasData", testAtlasDataVector_[i]);
	}



}

void ShaderTestLevel::Update(float _deltaTime)
{
}

void ShaderTestLevel::End()
{
}
