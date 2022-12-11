#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"
#include "FieldRenderingActor.h"

ShaderTestLevel::ShaderTestLevel(): shaderTestActor_(nullptr), shaderTestRenderer_(nullptr)
{
}

ShaderTestLevel::~ShaderTestLevel()
{
}

void ShaderTestLevel::Start()
{
	GameEngineDirectory tempDir;
	tempDir.MoveParentToExistChildDirectory("ContentsResources");
	tempDir.MoveToChild("ContentsResources");
	tempDir.MoveToChild("InstancingTest");
	tempDir.MoveToChild("Field");

	GameEngineTexture2DArray::Load(tempDir.GetFullPath());




	shaderTestActor_ = CreateActor<FieldRenderingActor>(0, "ShaderTestActor");
	//shaderTestActor_->InitializeFieldObject();
	shaderTestActor_->GetTransform().SetLocalScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldPosition(float4::Zero);




	//GameEngineDirectory mapObjectTextureDir;
	//mapObjectTextureDir.MoveParentToExistChildDirectory("ContentsResources");
	//mapObjectTextureDir.MoveToChild("ContentsResources");
	//mapObjectTextureDir.MoveToChild("InstancingTest");
	//GameEngineTexture2DArray::Load(mapObjectTextureDir.GetFullPath());

	//GameEngineTime::SetFrameLimit(70);

	//int testNumber = 144;
	//
	//GameEngineInstancingRenderer& testInstancingRenderer = this->GetMainCamera()->GetInstancingRenderer("Test");
	//testInstancingRenderer.Initialize(static_cast<size_t>(testNumber), "Rect", "Test");
	////testInstancingRenderer.SetTexture("TEX", "NSet.png");
	////testInstancingRenderer.SetTexture2DArray("Inst_Textures", "InstancingTest");
	//testInstancingRenderer.SetSampler("POINTCLAMP", "POINTCLAMP");

	//testRenderOptionVector_.resize(testNumber);
	//testInstancingRenderer.SetAllUnitsWorldScale({ 50, 50, 1 });

	//for (int i = 0; i < testNumber; i++)
	//{
	//	float4 randomPos = GameEngineRandom::mainRandom_.RandomFloat4(-600.f, 600.f);

	//	testInstancingRenderer.GetInstancingUnit(i).GetAtlasData().frameData_.posX = 0.f;
	//	testInstancingRenderer.GetInstancingUnit(i).GetAtlasData().frameData_.posY = 0.f;
	//	testInstancingRenderer.GetInstancingUnit(i).GetAtlasData().frameData_.sizeX = 1.f;
	//	testInstancingRenderer.GetInstancingUnit(i).GetAtlasData().frameData_.sizeY = 1.f;
	//	testInstancingRenderer.GetInstancingUnit(i).GetAtlasData().pivotPos_ = float4::Zero;

	//	testRenderOptionVector_[i].bytePad1_ = GameEngineRandom::mainRandom_.RandomInt(0, 4);

	//	testInstancingRenderer.GetInstancingUnit(i).SetWorldPosition(randomPos);

	//	testInstancingRenderer.GetInstancingUnit(i).Link("Inst_RenderOption", testRenderOptionVector_[i]);
	//}
}

void ShaderTestLevel::Update(float _deltaTime)
{
	shaderTestActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
}

void ShaderTestLevel::End()
{
}
