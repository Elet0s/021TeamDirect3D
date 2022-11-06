#include "PreCompile.h"
#include "GameEngineMesh.h"
#include "GameEngineDevice.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

GameEngineMesh::GameEngineMesh()
    : vertexBuffer_(nullptr),
    indexBuffer_(nullptr)
{
    SetVertexBuffer_InputAssembler1("RectVertex");
    SetIndexBuffer_InputAssembler2("RectIndex");
}

GameEngineMesh::~GameEngineMesh()
{
}

GameEngineMesh* GameEngineMesh::Create(const std::string_view& _meshName)
{
    return Create(_meshName, _meshName, _meshName);
}

GameEngineMesh* GameEngineMesh::Create(
    const std::string_view& _meshName,
    const std::string_view& _vertexBufferName,
    const std::string_view& _indexBufferName
)
{
    GameEngineMesh* newRes = CreateNamedRes(_meshName);
    newRes->SetVertexBuffer_InputAssembler1(_vertexBufferName);
    newRes->SetIndexBuffer_InputAssembler2(_indexBufferName);
    return newRes;
}

GameEngineMesh* GameEngineMesh::Create(GameEngineVertexBuffer* _vertexBuffer, GameEngineIndexBuffer* _indexBuffer)
{
    GameEngineMesh* newRes = CreateUnnamedRes();
    newRes->SetVertexBuffer_InputAssembler1(_vertexBuffer);
    newRes->SetIndexBuffer_InputAssembler2(_indexBuffer);
    return newRes;
}

void GameEngineMesh::SetVertexBuffer_InputAssembler1(const std::string_view& _vertexBufferName)
{
    this->vertexBuffer_ = GameEngineVertexBuffer::Find(_vertexBufferName);

    if (nullptr == vertexBuffer_)
    {
        MsgBoxAssertString(std::string(_vertexBufferName) + ": �׷� �̸��� ���ؽ����۰� �������� �ʽ��ϴ�.");
        return;
    }
}

void GameEngineMesh::SetVertexBuffer_InputAssembler1(GameEngineVertexBuffer* _vertexBuffer)
{
    if (nullptr == _vertexBuffer)
    {
        MsgBoxAssert("���ؽ����۰� �������� �ʽ��ϴ�.");
        return;
    }

    this->vertexBuffer_ = _vertexBuffer;
}

void GameEngineMesh::SetIndexBuffer_InputAssembler2(const std::string_view& _indexBufferName)
{
    this->indexBuffer_ = GameEngineIndexBuffer::Find(_indexBufferName);

    if (nullptr == indexBuffer_)
    {
        MsgBoxAssertString(std::string(_indexBufferName) + ": �׷� �̸��� �ε������۰� �������� �ʽ��ϴ�.");
        return;
    }
}

void GameEngineMesh::SetIndexBuffer_InputAssembler2(GameEngineIndexBuffer* _indexBuffer)
{
    if (nullptr == _indexBuffer)
    {
        MsgBoxAssert("�ε������۰� �������� �ʽ��ϴ�.");
        return;
    }

    this->indexBuffer_ = _indexBuffer;
}

void GameEngineMesh::Setting()
{
    this->InputAssembler1_VertexBufferSetting();
    this->InputAssembler2_IndexBufferSetting();
}

void GameEngineMesh::Render()
{
    GameEngineDevice::GetContext()->DrawIndexed(	//�ε����� ������ �������� �׸��� �Լ�.
        this->indexBuffer_->GetIndexCount(),//�ε��� ����.
        0,									//�б� ������ �ε��� ������ ���� ��ȣ. 
        0									//�б� ������ ���ؽ� ������ ���� ��ȣ. 
    );
    //���� ����Ϸ��� ī�޶� ����Ÿ���� ���� ��� �˰� �ű�� �׸��°���??
    //->ī�޶� �����ϱ� ���� ī�޶��� ����Ÿ���� ���� ����̽� ���ؽ�Ʈ�� �����ϰ�, 
    // �� ����̽� ���ؽ�Ʈ�� ���� ������ ���������� ������ �����ϹǷ� ���⼭ ����Ÿ���� ���������� �ʾƵ� 
    // ���� ���ϴ� ī�޶��� ����Ÿ�ٿ� ������ �� �ְ� �ȴ�.
}

const GameEngineInputLayoutDesc& GameEngineMesh::GetInputLayoutDesc() const
{
    if (nullptr == this->vertexBuffer_)
    {
        MsgBoxAssert("���ؽ����۰� �����ϴ�. ��ǲ ���̾ƿ� ������ ������ �� �����ϴ�.");
    }

    return vertexBuffer_->GetInputLayoutDesc();
}

void GameEngineMesh::InputAssembler1_VertexBufferSetting()
{
    this->vertexBuffer_->Setting();
}

void GameEngineMesh::InputAssembler2_IndexBufferSetting()
{
    this->indexBuffer_->Setting();
}
