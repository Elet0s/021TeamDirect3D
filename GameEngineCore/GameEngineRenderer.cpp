#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineInstancing.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"

GameEngineRenderUnit::GameEngineRenderUnit()
	: parentRenderer_(),
	mesh_(nullptr),
	inputLayout_(nullptr),
	material_(nullptr),
	topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	SetMesh("Rect");
}

GameEngineRenderUnit::~GameEngineRenderUnit()
{
}

GameEngineRenderUnit::GameEngineRenderUnit(const GameEngineRenderUnit& _other)
{
	this->parentRenderer_ = _other.parentRenderer_;
	this->mesh_ = _other.mesh_;
	this->inputLayout_ = _other.inputLayout_;
	this->material_ = _other.material_;
	this->topology_ = _other.topology_;

	this->shaderResourceHelper_.ResourceCheck(this->material_);
}

void GameEngineRenderUnit::SetMaterial(const std::string_view& _materialName)
{
	material_ = GameEngineMaterial::Find(_materialName);

	if (nullptr == material_)
	{
		MsgBoxAssertString(std::string(_materialName) + ": �׷� �̸��� ���׸����� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == inputLayout_ && nullptr != mesh_)
	{
		inputLayout_ = GameEngineInputLayout::Create(
			this->mesh_->GetInputLayoutDesc(),
			this->material_->GetVertexShader()
		);
		//�޽��� ���ؽ����ۿ� ������ ������������ ���ؽ����̴��� ��� �غ�Ǹ� ��ǲ ���̾ƿ��� �����Ѵ�.
		//��� ���� �غ�� �� �𸣹Ƿ� �޽��� ���� �غ�Ǵ� ���� ������ ������������ ���� �غ�Ǵ� ��� 
		// �ΰ��� ��� ����Ѵ�.
	}

	shaderResourceHelper_.ResourceCheck(this->material_);
}

void GameEngineRenderUnit::SetMesh(const std::string_view& _meshName)
{
	mesh_ = GameEngineMesh::Find(_meshName);

	if (nullptr == mesh_)
	{
		MsgBoxAssertString(std::string(_meshName) + ": �׷� �̸��� �޽��� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == inputLayout_ && nullptr != material_)
	{
		inputLayout_ = GameEngineInputLayout::Create(
			this->mesh_->GetInputLayoutDesc(),
			this->material_->GetVertexShader()
		);
		//�޽��� ���ؽ����ۿ� ������ ������������ ���ؽ����̴��� ��� �غ�Ǹ� ��ǲ ���̾ƿ��� �����Ѵ�.
		//��� ���� �غ�� �� �𸣹Ƿ� �޽��� ���� �غ�Ǵ� ���� ������ ������������ ���� �غ�Ǵ� ��� 
		// �ΰ��� ��� ����Ѵ�.
	}
}

void GameEngineRenderUnit::SetMesh(std::shared_ptr<GameEngineMesh> _mesh)
{
	if (nullptr == _mesh)
	{
		MsgBoxAssert("�޽��� �������� �ʽ��ϴ�.");
		return;
	}

	this->mesh_ = _mesh;

	if (nullptr == inputLayout_ && nullptr != material_)
	{
		inputLayout_ = GameEngineInputLayout::Create(
			this->mesh_->GetInputLayoutDesc(),
			this->material_->GetVertexShader()
		);
		//�޽��� ���ؽ����ۿ� ������ ������������ ���ؽ����̴��� ��� �غ�Ǹ� ��ǲ ���̾ƿ��� �����Ѵ�.
		//��� ���� �غ�� �� �𸣹Ƿ� �޽��� ���� �غ�Ǵ� ���� ������ ������������ ���� �غ�Ǵ� ��� 
		// �ΰ��� ��� ����Ѵ�.
	}
}

void GameEngineRenderUnit::EngineShaderResourceSetting(std::shared_ptr<GameEngineRenderer> _parentRenderer)
{
	if (nullptr == _parentRenderer)
	{
		return;
	}
	parentRenderer_ = _parentRenderer;

	if (true == this->shaderResourceHelper_.IsConstantBuffer("TRANSFORMDATA"))
	{
		shaderResourceHelper_.SetConstantBuffer_Link(
			"TRANSFORMDATA",
			&this->parentRenderer_.lock()->GetTransformData(),
			sizeof(parentRenderer_.lock()->GetTransformData())
		);
	}
	if (true == this->shaderResourceHelper_.IsConstantBuffer("RENDEROPTION"))
	{
		this->shaderResourceHelper_.SetConstantBuffer_Link(
			"RENDEROPTION",
			&this->parentRenderer_.lock()->renderOptionInst_,
			sizeof(RenderOption)
		);
	}
}

void GameEngineRenderUnit::Render(float _deltaTime)
{
	if (nullptr == this->material_)
	{
		MsgBoxAssert("���׸����� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("�޽��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	mesh_->Setting();

	inputLayout_->Setting();

	GameEngineDevice::GetContext()->IASetPrimitiveTopology(topology_);

	material_->Setting();

	shaderResourceHelper_.AllResourcesSetting();

	mesh_->Render();

	shaderResourceHelper_.AllResourcesReset();
}

std::shared_ptr<GameEngineMaterial> GameEngineRenderUnit::GetMaterial()
{
	return this->material_;
}

std::shared_ptr<GameEngineMaterial> GameEngineRenderUnit::GetClonePipeLine()
{
	if (false == material_->IsOriginal())
	{
		return material_;
	}

	material_ = ClonePipeLine(material_);
	return material_;
}

std::shared_ptr<GameEngineMaterial> GameEngineRenderUnit::ClonePipeLine(std::shared_ptr<GameEngineMaterial> _original)
{
	std::shared_ptr<GameEngineMaterial> clone = GameEngineMaterial::Create();
	clone->Copy(_original);
	return clone;
}

void GameEngineRenderUnit::SetRenderer(std::shared_ptr<GameEngineRenderer> _parentRenderer)
{
	parentRenderer_ = _parentRenderer;
	if (true == parentRenderer_.expired())
	{
		MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
		return;
	}

	EngineShaderResourceSetting(_parentRenderer);
}

GameEngineRenderer::GameEngineRenderer()
	: camera_(),
	renderOptionInst_(),
	cameraOrder_(CameraOrder::MainCamera),
	renderingOrder_(0),
	isInstancing_(false)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::ChangeCamera(CameraOrder _order)
{
	this->GetActor()->GetLevel()->PushRenderer(
		std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()), _order);
}

void GameEngineRenderer::SetRenderingOrder(int _renderingOrder)
{
	camera_.lock()->ChangeRenderingOrder(
		std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()), _renderingOrder);
}

bool GameEngineRenderer::IsInstancing(std::shared_ptr<GameEngineMaterial> _pipeLine)
{
	std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator instancingIter
		= this->camera_.lock()->instancingMap_.find(_pipeLine.get());

	if (this->camera_.lock()->instancingMap_.end() == instancingIter)
	{
		return false;
	}

	return true == isInstancing_ && GameEngineInstancing::minInstancingCount_ <= instancingIter->second.count_;
}

void GameEngineRenderer::InstancingDataSetting(std::shared_ptr<GameEngineMaterial> _pipeLine)
{
	int instancingIndex = this->camera_.lock()->PushInstancingIndex(_pipeLine);

	GameEngineInstancing* instancing = camera_.lock()->GetInstancing(_pipeLine);

	if (nullptr == instancing)
	{
		MsgBoxAssert("�ν��Ͻ��� ���� ������ �ν��Ͻ� �غ�� �Ǿ����� �ʽ��ϴ�.");
		return;
	}

	if (true == instancing->shaderResourceHelper_.IsStructuredBuffer("allInstancingTransformDatas"))
	{
		GameEngineStructuredBufferSetter* sBufferSetter
			= instancing->shaderResourceHelper_.GetStructuredBufferSetter("allInstancingTransformDatas");

		sBufferSetter->Push(this->GetTransformData(), instancingIndex);
	}
}

void GameEngineRenderer::Start()
{
	GameEngineRenderer::PushRendererToMainCamera();
}

void GameEngineRenderer::PushRendererToMainCamera()
{
	this->GetRoot<GameEngineActor>()->GetLevel()->PushRendererToMainCamera(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
}

void GameEngineRenderer::PushRendererToUICamera()
{
	this->GetActor()->GetLevel()->PushRendererToUICamera(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
}

//void GameEngineRenderer::Render(float _deltaTime)
//{
//	//�ӽ� ������ �ڵ�.
//	GameEngineVertexBuffer* renderVertex = GameEngineVertexBuffer::Find("BoxVertex");
//	GameEngineIndexBuffer* renderIndex = GameEngineIndexBuffer::Find("BoxIndex");
//
//	std::vector<POINT> drawVertex;
//	drawVertex.resize(renderIndex->indexes_.size());
//
//	std::vector<float4> copiedVertex;
//	copiedVertex.resize(renderIndex->indexes_.size());
//
//	for (size_t i = 0; i < renderIndex->indexes_.size(); i++)
//	{
//		int triIndex = renderIndex->indexes_[i];
//		copiedVertex[i] = renderVertex->vertexes_[triIndex];
//		//tempIndex�� ����� �ε����� triIndex��� �̸����� �ű� �� 
//		//triIndex�� �����Ǵ� ���ؽ� ������ ������� copiedVertex�� �ű��.
//
//		copiedVertex[i] *= this->GetTransform().GetWorldViewProjection();	
//		//���� world��Ŀ� �����, ������ı��� ����� ���� copiedVertex[i]�� �ݿ��Ѵ�.
//
//		copiedVertex[i] /=  copiedVertex[i].w;
//		//��������� ������� ����� w��ġ��ŭ copiedVertex�� ��ǥ���� ������ ��ҽ�Ų��.
//		
//		copiedVertex[i] *= tempViewport_;
//		//�ӽú���Ʈ ����� �����ؼ� ���ϴ� ũ���� �ٽ� Ȯ��� ��ǥ�� ������ �Է��Ѵ�.
//	
//		drawVertex[i] = copiedVertex[i].ConvertToWindowsPoint();
//		//�Էµ� ��ǥ��� POINT ����ü�� ���� ����.
//	}
//
//	for (size_t i = 0; i < drawVertex.size(); i += 3)
//	{
//		Polygon(GameEngineWindow::GetInst().GetHDC(), &drawVertex[i], 3);
//	}
//}

