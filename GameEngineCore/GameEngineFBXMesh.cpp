#include "PreCompile.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXMesh::GameEngineFBXMesh()
{
}

GameEngineFBXMesh::~GameEngineFBXMesh()
{
}

GameEngineFBXMesh* GameEngineFBXMesh::Load(const std::string& _path)
{
	return Load(_path, GameEnginePath::GetFileName(_path));
}

GameEngineFBXMesh* GameEngineFBXMesh::Load(const std::string& _path, const std::string& _name)
{
	GameEngineFBXMesh* newRes = CreateNamedRes(_name);
	newRes->SetPath(_path);



	return newRes;
}

void GameEngineFBXMesh::LoadMesh(const std::string& _path, const std::string& _name)
{
	if (false == CreateFBXSystemInitialize(_path))
	{
		MsgBoxAssert("FBX 시스템 로드 실패.");
		return;
	}

	FBXConvertScene();
}

void GameEngineFBXMesh::MeshLoad()
{
}

