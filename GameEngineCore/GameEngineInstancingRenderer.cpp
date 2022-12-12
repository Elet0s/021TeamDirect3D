#include "PreCompile.h"
#include "GameEngineInstancingRenderer.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexes.h"


GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
	const std::set<std::string>& _structuredBufferSetterNames,
	const std::string_view& _meshName,
	const std::string_view& _materialName
)
{
	for (const std::string& name : _structuredBufferSetterNames)
	{
		data_.insert(std::make_pair(name, nullptr));
	}

	this->renderUnit_ = std::make_shared<GameEngineRenderUnit>();
	this->renderUnit_->SetMesh(_meshName);
	this->renderUnit_->SetMaterial(_materialName);
	this->renderUnit_->Off();
	this->textureIndex_ = 0;
	//this->isRendering_ = true;
}

void GameEngineInstancingRenderer::InstancingUnit::Link(const std::string_view& _name, const void* _data)
{
	std::string uppercaseDataName = GameEngineString::ToUpperReturn(_name);

	if (data_.end() == data_.find(uppercaseDataName))
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 인스턴싱 데이터가 존재하지 않습니다.");
		//트랜스폼데이터, 아틀라스데이터를 링크시켜도 여기로 들어오는점 주의.
		return;
	}
	else
	{
		data_.find(uppercaseDataName)->second = _data;
	}
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldScale(const float4& _worldScaleVector)
{
	this->transformData_.worldScaleVector_ = _worldScaleVector;
	this->transformData_.localScaleMatrix_.Scale(_worldScaleVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldRotation(const float4& _worldRotationVector)
{
	this->transformData_.worldRotationVector_ = _worldRotationVector;
	this->transformData_.localRotationMatrix_.Rotate3AxisByDegree(_worldRotationVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldPosition(const float4& _worldPositionVector)
{
	this->transformData_.worldPositionVector_ = _worldPositionVector;
	this->transformData_.localPositionMatrix_.Position(_worldPositionVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetTextureIndex(unsigned int _textureIndex)
{
	textureIndex_ = _textureIndex;
}

void GameEngineInstancingRenderer::InstancingUnit::CalWorldWorldMatrix()
{
	this->transformData_.worldWorldMatrix_
		= this->transformData_.localScaleMatrix_ 
		* this->transformData_.localRotationMatrix_ 
		* this->transformData_.localPositionMatrix_;
}

GameEngineInstancingRenderer::GameEngineInstancingRenderer()
	: instancingUnitCount_(0),
	topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

GameEngineInstancingRenderer::~GameEngineInstancingRenderer()
{
}

void GameEngineInstancingRenderer::Initialize(
	size_t _instancingUnitCount,
	const std::string_view& _meshName,
	const std::string_view& _materialName
)
{
	if (0 == _instancingUnitCount)
	{
		MsgBoxAssert("인스턴스 개수는 0이 될 수 없습니다.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": 이 마테리얼의 버텍스셰이더는 인스턴싱 준비가 되어있지 않습니다.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetPixelShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": 이 마테리얼의 픽셀셰이더는 인스턴싱 준비가 되어있지 않습니다.");
		return;
	}

	this->instancingUnitCount_ = _instancingUnitCount;


	this->mesh_ = GameEngineMesh::Find(_meshName);

	//인스턴스 단위 크기.
	UINT instancingSize = this->mesh_->GetInputLayoutDesc().instanceSize_;
	
	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instancingSize);
	//instancingUnitCount_ * instancingSize크기의 인스턴싱버퍼 생성.

	instanceIndexBuffer_.resize(static_cast<size_t>(instancingSize) * instancingUnitCount_);
	//instancingUnitCount_ * instancingSize크기로 로우인덱스 버퍼 크기 조정.


	this->material_ = GameEngineMaterial::Create();
	this->material_->Copy(GameEngineMaterial::Find(_materialName));

	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetVertexShader()->GetInst_VertexShader());
	//this->shaderResourceHelper_.ShaderCheck(
	//	GameEngineMaterial::Find(_materialName)->GetPixelShader());
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetPixelShader()->GetInst_PixelShader());


	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//셰이더리소스헬퍼에 등록된 구조화버퍼 세터를 전부 가져온다.



	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		//트랜스폼데이터, 아틀라스데이터는 따로 처리해야하므로 크기 조정만 하고 structuredBufferSetterNames_에는 등록하지 않는다.
		if (0 == iter->first.compare("INST_TRANSFORMDATA")
			|| 0 == iter->first.compare("INST_ATLASDATA"))
		{
			iter->second.Resize(instancingUnitCount_);
			continue;
		}

		if (std::string::npos != iter->first.find("INST_"))
		{
			//structuredBufferSetters의 모든 구조화버퍼 세터들 중 이름에 "INST_" 라는 문자열이 포함된 것들만 골라서 
			// structuredBufferSetterNames_에 이름을 등록한다.
			structuredBufferSetterNames_.insert(iter->first);

			//그 세터와 연결된 구조화버퍼를 생성하거나 크기를 조정한다.
			iter->second.Resize(instancingUnitCount_);
		}
	}

	this->allInstancingUnits_.reserve(instancingUnitCount_);
	for (size_t i = 0; i < instancingUnitCount_; ++i)
	{
		allInstancingUnits_.push_back(
			GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
				this->structuredBufferSetterNames_,
				_meshName,
				_materialName
			)
		);
	}
}

void GameEngineInstancingRenderer::SetAllUnitsWorldScale(const float4& _worldScaleVector)
{
	for (InstancingUnit& singleInstancingUnit : allInstancingUnits_)
	{
		singleInstancingUnit.transformData_.localScaleMatrix_.Scale(_worldScaleVector);
		singleInstancingUnit.CalWorldWorldMatrix();
	}
}

void GameEngineInstancingRenderer::Render(
	float _deltaTime,
	const float4x4& _viewMatrix,
	const float4x4& _projectionMatrix
)
{
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	int* instanceIndexBufferPtr = reinterpret_cast<int*>(&instanceIndexBuffer_[0]);

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		//if (false == allInstancingUnits_[index].isRendering_)
		//{
		//	continue;
		//}

		{
			//트랜스폼데이터는 뷰행렬, 투영행렬을 적용해야 하므로 따로 처리.
			allInstancingUnits_[index].transformData_.worldViewMatrix_
				= allInstancingUnits_[index].transformData_.worldWorldMatrix_ * _viewMatrix;

			allInstancingUnits_[index].transformData_.worldViewProjectionMatrix_
				= allInstancingUnits_[index].transformData_.worldViewMatrix_ * _projectionMatrix;

			//if (false == float4x4::IsInViewFrustum(
			//	allInstancingUnits_[index].transformData_.worldViewProjectionMatrix_,
			//	float4::Zero))
			//{
			//	//이게 의미가 있나?
			//	continue;
			//}

			size_t transforDataSize = sizeof(TransformData);
			char* transformDataPtr
				= &shaderResourceHelper_.GetStructuredBufferSetter("Inst_TransformData")->originalData_[index * transforDataSize];

			int copyResult = memcpy_s(	//
				transformDataPtr,		//
				transforDataSize,		//
				&allInstancingUnits_[index].transformData_,	//
				transforDataSize		//
			);

			if (0 != copyResult)
			{
				MsgBoxAssert("트랜스폼데이터 복사 실패!");
				return;
			}
		}

		{
			//아틀라스데이터도 따로 처리.
			size_t atlasDataSize = sizeof(AtlasData);
			char* atlasDataPtr
				= &shaderResourceHelper_.GetStructuredBufferSetter("Inst_AtlasData")->originalData_[index * atlasDataSize];

			int copyResult = memcpy_s(	//
				atlasDataPtr,		//
				atlasDataSize,		//
				&allInstancingUnits_[index].atlasData_,	//
				atlasDataSize		//
			);

			if (0 != copyResult)
			{
				MsgBoxAssert("아틀라스데이터 복사 실패!");
				return;
			}
		}

		for (std::map<std::string, const void*>::iterator unitDataIter = allInstancingUnits_[index].data_.begin();
			unitDataIter != allInstancingUnits_[index].data_.end(); ++unitDataIter)
		{
			if (nullptr == unitDataIter->second)
			{
				MsgBoxAssertString(unitDataIter->first + ": 셰이더로 보내기로 한 데이터가 인스턴싱 유닛에 없습니다.");
				return;
			}

			//구조화버퍼세터로 각 유닛별 데이터 전달.
			for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = structuredBufferSetters.lower_bound(unitDataIter->first);
				sBufferSetterIter != structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter) 
			{
			
				size_t originalDataSize = sBufferSetterIter->second.size_;
				//구조화버퍼 세터가 들고 있는 originalData_의 단위 크기.

				char* originalDataPtr = &sBufferSetterIter->second.originalData_[index * originalDataSize];
				//구조화버퍼 세터가 들고 있는 originalData_의 포인터.

				int copyResult = memcpy_s(	//
					originalDataPtr,		//구조화버퍼 세터의 originalData_로 
					originalDataSize,		//originalData_의 단위 크기만큼 == 인스턴싱유닛이 들고있는 데이터 크기만큼
					unitDataIter->second,	//인스턴싱유닛이 들고있는 데이터를 복사한다.
					originalDataSize		//originalData_의 단위 크기만큼 == 인스턴싱유닛이 들고있는 데이터 크기만큼.
				);

				if (0 != copyResult)
				{
					MsgBoxAssert("메모리 복사 실패!");
					return;
				}
			}
		}

		*instanceIndexBufferPtr = static_cast<int>(index);
		instanceIndexBufferPtr += 1;
		//인스턴스인덱스버퍼에 인스턴스 인덱스를 기록하고 뒤로 넘어간다.

		*instanceIndexBufferPtr = allInstancingUnits_[index].textureIndex_;
		instanceIndexBufferPtr += 1;
		//인스턴싱인덱스버퍼에 텍스처배열 인덱스를 기록하고 뒤로 넘어간다.
	}



	instancingBuffer_->ChangeData(&instanceIndexBuffer_[0], instanceIndexBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	
	
	
	allInstancingUnits_[0].renderUnit_->RenderInstancing2(_deltaTime, instancingUnitCount_, instancingBuffer_);


}

