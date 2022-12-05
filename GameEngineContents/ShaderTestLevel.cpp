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


	GameEngineDirectory mapObjectTextureDir;
	mapObjectTextureDir.MoveParentToExistChildDirectory("ContentsResources");
	mapObjectTextureDir.MoveToChild("ContentsResources");
	mapObjectTextureDir.MoveToChild("InstancingTest");
	GameEngineTexture2DArray::Load(mapObjectTextureDir.GetFullPath());

	//GameEngineTime::SetFrameLimit(70);
	int testNumber = 144;
	
	GameEngineInstancingRenderer& testInstancingRenderer = this->GetMainCamera()->GetInstancingRenderer("Test");
	testInstancingRenderer.Initialize(static_cast<size_t>(testNumber));
	//testInstancingRenderer.SetTexture("TEX", "NSet.png");
	//testInstancingRenderer.SetTexture2DArray("Inst_Textures", "InstancingTest");
	testInstancingRenderer.SetSampler("POINTCLAMP", "POINTCLAMP");

	testAtlasDataVector_.reserve(testNumber);


	for (int i = 0; i < testNumber; i++)
	{
		float4 randomPos = GameEngineRandom::mainRandom_.RandomFloat4(-300.f, 300.f);
		testAtlasDataVector_.push_back(AtlasData());

		testAtlasDataVector_[i].frameData_.posX = 0.f;
		testAtlasDataVector_[i].frameData_.posY = 0.f;
		testAtlasDataVector_[i].frameData_.sizeX = 1.f;
		testAtlasDataVector_[i].frameData_.sizeY = 1.f;
		testAtlasDataVector_[i].pivotPos_ = float4::Zero;

		std::shared_ptr<GameEngineTransformComponent> tempComponent = shaderTestActor_->CreateComponent<GameEngineTransformComponent>();
		tempComponent->GetTransform().SetWorldScale(50.f, 50.f, 1.f);
		tempComponent->GetTransform().SetWorldPosition(randomPos);
		testInstancingRenderer.GetInstancingUnit(i).SetTransformData(tempComponent->GetTransformData());
		
		//렌더옵션 전달 테스트용 임시코드. 나중에 지울 것.
		testInstancingRenderer.GetInstancingUnit(i).GetRenderOption().shadowAngle_ = 1.f;
		testInstancingRenderer.GetInstancingUnit(i).GetRenderOption().bytePad1_ = 2.f;

		testInstancingRenderer.GetInstancingUnit(i).Link("Inst_AtlasData", testAtlasDataVector_[i]);
	}



}

void ShaderTestLevel::Update(float _deltaTime)
{
}

void ShaderTestLevel::End()
{
}
